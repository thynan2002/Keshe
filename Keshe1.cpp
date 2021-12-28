#include"Structs.h"

LinkList Array[97];

//MGraph floyd;

void MainMenu(stock stocks[], MGraph g);
void Welcome(stock stocks[], MGraph g);
void SearchMenu(stock stocks[], MGraph g);
void AnalyzeMenu(stock stocks[], MGraph g);
void S_StockInfo(stock stocks[], MGraph g);


void ReadCSV_basic(stock stocks[], MGraph g) {
	ifstream inFile1("A股公司简介.csv", ios::in);
	string lineStr1;
	getline(inFile1, lineStr1);
	int i = 0;
	while (getline(inFile1, lineStr1))
	{
		stringstream ss(lineStr1);
		string str1[200];
		int j = 0;
		while (getline(ss, str1[j], ','))
		{
			j++;
		}
		stocks[i].StockNum = str1[0];
		stocks[i].StockName = str1[1];
		stocks[i].StockCode = str1[2];
		stocks[i]._1Kind = str1[3];
		stocks[i]._2Kind = str1[4];
		stocks[i].StockLE = str1[5];
		stocks[i].StockWN = str1[6];
		stocks[i].StockTime = str1[7];
		stocks[i].StockProv = str1[8];
		stocks[i].StockCity = str1[9];
		stocks[i].StockLP = str1[10];
		stocks[i].StockAddr = str1[11];
		stocks[i].StockWeb = str1[12];
		stocks[i].StockEmail = str1[13];
		stocks[i].StockTel = str1[14];
		stocks[i].StockMB = str1[15];
		stocks[i].StockBS = str1[16];
		i++;
	}

}
void ReadCSV_2(stock stocks[], MGraph g) {								//读取点和评分
	ifstream inFile1("60支股票信息2.csv", ios::in);
	string lineStr1;
	getline(inFile1, lineStr1);
	while (getline(inFile1, lineStr1))
	{
		stringstream ss(lineStr1);
		string str1[200];
		int j = 0;
		while (getline(ss, str1[j], ','))
		{
			j++;
		}
		for (int i = 0; i < 200; i++) {
			if (stocks[i].StockNum == str1[2]) {
				stocks[i].point = stoi(str1[0]);
				stocks[i].score = str1[3];
				//cout <<stocks[i].StockName<<"   "<<stocks[i].StockNum<<"    " << stocks[i].point << "\t" << stocks[i].score << endl;
			}
		}
		
	}
}
void ReadCSV_1_1(MGraph &g,int a,int b) {
	ifstream inFile1("60支股票信息1.csv", ios::in);
	string lineStr1;
	getline(inFile1, lineStr1);
	while (getline(inFile1, lineStr1))
	{
		stringstream ss(lineStr1);
		string str1[200];
		int j = 0;
		while (getline(ss, str1[j], ','))
		{
			j++;
		}
		for (int i = 0; i < 60; i++) {
			for (int k = 0; k < 60; k++) {
				if (i == stoi(str1[0]) && k == stoi(str1[1])) {
					g.value[stoi(str1[0])][stoi(str1[1])] = stoi(str1[2]);
					//cout <<i<<"   "<<k <<"   "<<g.value[i][k] << endl;
				}
				
			}
		}
	}
	for (int k = 0; k < 60; k++) {//中间节点
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (g.value[i][j] > g.value[i][k] + g.value[k][j]) {
					g.value[i][j] = g.value[i][k] + g.value[k][j];
				}
			}
		}
	}
	if (g.value[a][b] != INF) {
		cout << g.value[a][b];
	}
}
MGraph ReadCSV_1_2(MGraph& g) {
	ifstream inFile1("60支股票信息1.csv", ios::in);
	string lineStr1;
	getline(inFile1, lineStr1);
	while (getline(inFile1, lineStr1))
	{
		stringstream ss(lineStr1);
		string str1[200];
		int j = 0;
		while (getline(ss, str1[j], ','))
		{
			j++;
		}
		for (int i = 0; i < 60; i++) {
			for (int k = 0; k < 60; k++) {
				if (i == stoi(str1[0]) && k == stoi(str1[1])) {
					g.value[stoi(str1[0])][stoi(str1[1])] = stoi(str1[2]);
					//cout <<i<<"   "<<k <<"   "<<g.value[i][k] << endl;
				}

			}
		}
	}
	for (int k = 0; k < 60; k++) {											//floyd算法
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (g.value[i][j] > g.value[i][k] + g.value[k][j]) {
					g.value[i][j] = g.value[i][k] + g.value[k][j];
				}
			}
		}
	}
	return g;
}


void ReadTXT(stock stocks[], MGraph g) {
	string k = "股票涨跌数据/";
	string as;
	string ss;
	for (int i = 0; i < ComN; i++)
	{
		stocks[i].details = new detail;
		stocks[i].details->next = NULL;
		det temp, p = stocks[i].details;
		k = "股票涨跌数据/";
		k += stocks[i].StockNum + ".txt";
		//cout << k<<endl;
		ifstream infile(k);
		for (int j = 0; j < 10; j++) infile >> ss;//读表头
		while (infile >> as) {
			temp = new detail;
			temp->date = as;
			infile >> temp->oprice >> temp->cprice >> temp->maxprice >> temp->minprice >> temp->volume >> temp->turnover >> temp->rate >> temp->iodamount >> temp->iodrate;
			temp->next = NULL;
			p->next = temp;
			p = p->next;
			//cout << temp->date << " " <<temp->oprice <<" "<< temp->cprice << " " << temp->maxprice << " " << temp->minprice << " " << temp->volume << " " << temp->turnover << " " << temp->rate<<" " << temp->iodamount << " " << temp->iodrate << " " << endl;
		}
		infile.close();
	}
}




/***********    Search    ************/
//股票网址查询
void get_next(string t, vector<int>& next)
{
	int i = 0, j = -1;
	next[0] = -1;
	while (i < t.size() - 1)
	{
		if (j == -1 || t[i] == t[j])
		{
			next[++i] = ++j;
		}
		else
		{
			j = next[j];
		}
	}
}
void S_StockWeb_KMP(stock stocks[], MGraph g) {				//查询_股票网址查询
	cout << "**********************************" << endl;
	cout << "*这是一个基于KMP算法的股票网址查询*" << endl;
	cout << "**********************************" << endl;
	cout << "请输入你要查找的：";
	string tobes; cin >> tobes;
	//int len = tobes.size();
	for (int k = 0; k < 200; k++) {
		int i = 0, j = 0;
		vector<int> next(tobes.size());
		get_next(tobes, next);
		while (j == -1 || (i < stocks[k].StockWeb.size() && j < tobes.size())) 
		{
			if (j == -1 || stocks[k].StockWeb[i] == tobes[j])
			{
				i++;
				j++;
			}
			else
			{
				j = next[j];
			}
		}
		if (j == tobes.size()) {
			cout << "查找成功！详情如下：" << endl;
			cout << stocks[k].StockNum << "\t" << stocks[k].StockName << endl;
			break;
		}
		else {
			if (k == 199) {
				cout << "查找失败" << endl;
				break;
			}
		}
			
	}

	system("pause");
	SearchMenu(stocks,g);

}

//股票信息查询
void BSTInsert(BSTNode*& p, stock elem) {					//在给定的BSTree中插入elem，使之成为新的BSTree
	if (NULL == p){											//空树，创建根节点
		p = new BSTNode;
		p->data = elem;
		p->lchild = NULL;
		p->rchild = NULL;
		//cout << endl << 1 << endl;						//测试用
	}
	if (elem.StockNum < p->data.StockNum) {
		//cout << endl << 1 << endl;
		return BSTInsert(p->lchild, elem);
	}
	if (elem.StockNum > p->data.StockNum) {
		//cout << endl << 1 << endl;
		return BSTInsert(p->rchild, elem);
	}
}
void CreatBST(BSTNode *& T,stock stocks[]) {
	for (int i = 0; i < ComN; i++) {
		BSTInsert(T, stocks[i]);
	}
}
BSTNode *BSTsearch(BSTree T,string Tobes){
	if (NULL == T) {
		return NULL;
	}
	if (Tobes == T->data.StockNum) {
		return T;
	}
	if (Tobes < T->data.StockNum) {
		//cout << endl << 1 << endl;			//测试用
		return BSTsearch(T->lchild, Tobes);
	}
	if(Tobes > T->data.StockNum){
		//cout << endl << 1 << endl;
		return BSTsearch(T->rchild, Tobes);
	}
}
void S_SI_BT(stock stocks[], MGraph g) {					//查询_股票网址查询_基于二叉树BT
	BSTree Tree = NULL;							//创建并初始化二叉树，头节点置为空
	CreatBST(Tree,stocks);
	cout << "**********************************" << endl;
	cout << "*这是一个基于二叉树的股票信息查询*" << endl;
	cout << "**********************************" << endl;
	cout << "请输入你要查询的股票代码:";
	string tobes; cin >> tobes;
	BSTNode* b = NULL;
	b = BSTsearch(Tree, tobes);
	if (b != NULL) {
		cout << "查找成功，详情如下：" << endl;
		cout << b->data.StockNum << "\t" << b->data.StockName << "\t" << endl;
		cout <<setiosflags(ios::fixed)<< b->data.details->next->oprice<< "\t" << setiosflags(ios::fixed) << b->data.details->next->cprice << "\t" << b->data.details->next->iodrate << endl;
	}
	else {
		cout << "未找到相关信息，请确认输入信息有效" << endl;
	}
	cout << "即将进入到上一级菜单" << endl; system("pause");
	SearchMenu(stocks,g);

}

void CreatHash(stock stocks[], MGraph g) {				//创建哈希表
	stock initHash;
	for (int i = 0; i < 97; i++){
		Array[i] = new LNode;
		Array[i]->next = NULL;
		Array[i]->data = initHash;
	}
	int key = 0;
	for (int i = 0; i < ComN; i++) {
		key = 0;
		string::iterator it = stocks[i].StockNum.begin();
		for (; it < stocks[i].StockNum.end(); it++) {				//获取取模前key的总值
			key += *it;
		}
		key %= 97;													//对key取模，获取hash的key值
		LinkList p = Array[key];
		LinkList q = new LNode;
		q->data = stocks[i];
		q->next = p->next;
		p->next = q;
	}
}
void S_SI_Hash(stock stocks[], MGraph g) {					//查询_股票网址查询_基于哈希表hash
	cout << "**********************************" << endl;
	cout << "*这是一个基于哈希表的股票信息查询*" << endl;
	cout << "**********************************" << endl;
	cout << "请输入你要查询的股票代码：";
	string tobes;
	cin >> tobes;
	int key = 0;
	string::iterator iter = tobes.begin();
	for (; iter < tobes.end(); iter++) {
		key += *iter;
	}
	key %= 97;
	LinkList p = new LNode;
	p = Array[key];
	while (p) {
		if (tobes == p->data.StockNum) {
			cout << p->data.StockName << "\t" << p->data.StockNum << "\t" << p->data._1Kind << "\t" << p->data._2Kind << "\t" << p->data.StockMB << endl;
			break;
		}
		p = p->next;
		if (!p) {
			cout << "查找失败" << endl;
			break;
		}
	}
	
	cout << "即将进入到上一级菜单" << endl; system("pause");
	SearchMenu(stocks,g);
}
void S_StockInfo(stock stocks[], MGraph g) {					//查询_股票基本信息查询
	cout << "请选择查询方式：1—基于哈希表 || 2—基于二叉排序树" << endl;
	int ToDo = -1; cin >> ToDo;
	if (ToDo == 1) {
		S_SI_Hash(stocks,g);
	}
	else if (ToDo == 2) {
		S_SI_BT(stocks,g);
	}
	else {
		cout << "请输入有效选择项！" << endl;
		system("cls");
		S_StockInfo(stocks,g);
	}
}
//股票价格查询
void S_StockPrice(stock stocks[], MGraph g) {				//查询_股票的价格信息
	cout << "**********************************" << endl;
	cout << "*这是一个基于单链表的股票价格查询*" << endl;
	cout << "**********************************" << endl;
	cout << "请输入你要查找的日期:";
	string tobes; cin >> tobes;
	cout << "为您找到该日的相关信息：" << endl;
	cout << setfill(' ') << setw(15) << "股票代码" << setfill(' ') << setw(15) << "股票名称" << "\t" << setiosflags(ios::fixed) << setfill(' ') << setw(10)<<"开盘价" << setfill(' ') << setw(20)<< "收盘价" << setfill(' ') << setw(20)<< "涨跌幅" << endl;
	for (int i = 0; i < ComN; i++) {
		det p = stocks[i].details;
		
		while (p) {
			if (tobes == p->date) {
				cout << setfill(' ') << setw(15) << stocks[i].StockNum << setfill(' ') << setw(15) << stocks[i].StockName << "\t" <<setiosflags(ios::fixed)<<setfill(' ') << setw(10) << stocks[i].details->next->oprice << setfill(' ') << setw(20) << stocks[i].details->next->cprice << setfill(' ') << setw(20) << stocks[i].details->next->iodrate << endl;
				break;
			}
			else {
				if(!p->next)
					cout << setfill(' ') << setw(15) << stocks[i].StockNum << setfill(' ') << setw(15)  << stocks[i].StockName << "\t" << "没有该股票该日的相关信息" << endl;
				p = p->next;
			}
			
		}
		if (p == NULL&&i == ComN) {
			cout << "未找到相关信息，请检查输入是否有效!" << endl;
		}
	}
	cout << "即将进入到上一级菜单" << endl; system("pause");
	SearchMenu(stocks,g);
}
//查询二级菜单
void SearchMenu(stock stocks[], MGraph g) {					//查询
	cout << endl << "可进行的操作有：" << endl;
	cout << "1——股票的基本信息" << endl;
	cout << "2——股票的网址" << endl;
	cout << "3——股票的价格信息" << endl;
	cout << "4——返回到主页面菜单" << endl;
	cout << "请选择:";

	int ToDo = -1;
	cin >> ToDo;
	if (ToDo == 1) {
		S_StockInfo(stocks,g);
	}
	else if (ToDo == 2) {
		S_StockWeb_KMP(stocks, g);
	}
	else if (ToDo == 3) {
		S_StockPrice(stocks, g);
	}
	else if (ToDo == 4) {
		MainMenu(stocks, g);
	}
	else {
		cout << "请输入有效选择项！" << endl;
		SearchMenu(stocks, g);
	}
}
/***********    Analyze    ************/

void QuickSort(stock* temp, int l, int r) {
	if (l < r) {
		int i = l, j = r;//将基准数挖出，形成第一个坑temp[i]
		stock x = temp[l];
		while (i < j) {
			while (i < j) {
				if (x.details->iodrate.size() > temp[j].details->iodrate.size()) {
					j--;//j--有后向前找到比他小的数，找到后挖出次数，然后填补前一个坑temp[i]
				}
				else if (x.details->iodrate.size() == temp[j].details->iodrate.size()) {
					if (temp[j].details->iodrate <= x.details->iodrate) {
						j--;
					}
					else if (temp[j].details->iodrate > x.details->iodrate) {
						break;
					}
				}
				else if (x.details->iodrate.size() < temp[j].details->iodrate.size()) {
					break;
				}
			}
			if (i < j) {
				temp[i++] = temp[j];
			}
			while (i < j) {
				if (x.details->iodrate.size() < temp[i].details->iodrate.size()) {
					i++;// i++由前向后找比它大的数，找到后也挖出此数填到前一个坑temp[j]中。
				}
				else if (x.details->iodrate.size() == temp[i].details->iodrate.size()) {
					if (x.details->iodrate < temp[i].details->iodrate) {
						i++;
					}
					else if (x.details->iodrate >= temp[i].details->iodrate) {
						break;
					}
				}
				else if (x.details->iodrate.size() > temp[i].details->iodrate.size()) {
					break;
				}
			}
			if (i < j) {
				temp[j--] = temp[i];
			}
		}
		temp[i] = x;
		QuickSort(temp, l, i-1); //递归    再重复执行2，3二步，直到i == j，将基准数填入temp[i]中
		QuickSort(temp, i + 1, r);
	}
}
void Display(stock temp[], int number) {
	int k = 1;
	for (int i = 0; i < number; i++) {							//我也不知道为啥这里一定要用取指针，不用指针他就是输出不了,真的很生气
		if (temp[i].score != "-1") {
			cout << setfill(' ') << setw(3) << k << setfill(' ') << setw(20) << temp[i].StockNum << setfill(' ') << setw(15) << temp[i].StockName << "\t\t" << temp[i].details->iodrate << "\t" << temp[i].details->date << endl;
			k++;
		}
	}
	
}
void A_StockPrice_QS(stock stocks[], MGraph g) {			//分析_股票价格分析_快速排序QuickS
	cout << "************************************" << endl;
	cout << "*这是一个基于快速排序的股票价格分析*" << endl;
	cout << "************************************" << endl;
	cout << "请输入你要分析的一级行业名称:" << endl;
	string tobes; cin >> tobes;
	stock temps[ComN];											//用来存储所有属于该一级行业的股票信息
	int Num = 0;
	for (int i = 0; i < ComN; i++) {
		//det d = stocks[i].details;
		if (stocks[i]._1Kind == tobes) {
			temps[Num] = stocks[i];
			//temps[Num].details = d;
			Num++;												//统计共有多少个属于该一级行业的股票
		}
	}
	if (Num == 0) {
		cout << "未找到相关信息，请确认输入信息有效！" << endl;
		cout << "即将进入上一级菜单" << endl;
		system("pause");
		AnalyzeMenu(stocks, g);
	}
	stock Max_temp[ComN];
	for (int i = 0; i < Num; i++) {
		det p = temps[i].details->next;
		Max_temp[i] = temps[i];
		while (p->next) {
			if (p->iodrate[0] == '-') {
				p = p->next;
				continue;
			}
			if (p->iodrate.size() > Max_temp[i].details->iodrate.size()) {
				Max_temp[i].details = p;
				//cout << Max_temp[i].StockName << "     " << p->iodrate << "      " << p->next->iodrate << "     " << Max_temp[i].details->date << endl;
				p = p->next;
			}
			else if (p->iodrate.size() == Max_temp[i].details->iodrate.size()) {
				if (p->iodrate > Max_temp[i].details->iodrate) {
					Max_temp[i].details = p;
					//cout <<Max_temp[i].StockName<<"     " << p->iodrate << "      " << p->next->iodrate<<"     " << Max_temp[i].details->date << endl;
				}
				p = p->next;
			}
			else if (p->iodrate.size() < Max_temp[i].details->iodrate.size()) {
				p = p->next;
			}
			
		}
	}
	//Display(Max_temp, Num);
	//cout << "_____________________" << endl;
	QuickSort(Max_temp, 0, Num-1);
	Display(Max_temp, Num);
	cout << "即将进入上一级菜单" << endl;
	system("pause");
	AnalyzeMenu(stocks, g);

}

linklist CreatList(stock stocks[],string Tobes) {
	linklist L;
	string initL;
	L = new lnode;
	L->stock_name = initL;
	L->stock_num = initL;
	L->next = NULL;
	for (int i = 0; i < ComN; i++) {
		det d = stocks[i].details;
		for (int j = 0; j < 200; j++) {
			if (Tobes == d->date) {
				linklist p = L;
				linklist q = new lnode;
				q->stock_name = stocks[i].StockName;
				q->stock_num = stocks[i].StockNum;
				q->details.oprice = d->oprice;
				q->details.cprice = d->cprice;
				stof(d->next->iodrate);
				q->details.iodrate = d->iodrate;
				//q->data.details = stocks[i].details;
				q->next = p->next;
				p->next = q;
				//cout << q->stock_name << "    " << q->details.oprice << endl;
			}
			d = d->next;
			if (d == NULL) {
				break;
			}
		}
		
		
	}
	/*linklist p = L;
	while (p) {
		cout << p->details.oprice<< endl;
		p = p->next;
	}*/
	//system("pause");
	return L;
}

void InsertSort_oprice(linklist& L) {
	linklist curr = L->next->next;
	linklist temp, pre, r;
	L->next->next = NULL;
	while (curr)
	{
		pre = L;
		r = L->next;
		while (r != NULL && curr->details.oprice < r->details.oprice)//按开盘价
		{
			pre = pre->next;
			r = r->next;
		}
		temp = curr;
		curr = curr->next;
		pre->next = temp;
		temp->next = r;
	}
	/*linklist p = L;
	while (p) {
		cout << p->stock_num << "  " << p->stock_name << "    " << p->details.oprice << endl;
		p = p->next;
	}*/
}
void InsertSort_cprice(linklist& L) {
	linklist curr = L->next->next;
	linklist temp, pre, r;
	L->next->next = NULL;
	while (curr)
	{
		pre = L;
		r = L->next;
		while (r != NULL && curr->details.cprice < r->details.cprice)
		{
			pre = pre->next;
			r = r->next;
		}
		temp = curr;
		curr = curr->next;
		pre->next = temp;
		temp->next = r;
	}
}
void InsertSort_iodrate(linklist& L) {
	linklist curr = L->next->next;
	linklist temp, pre, r;
	L->next->next = NULL;
	while (curr)
	{
		pre = L;
		r = L->next;
		while (r != NULL && curr->details.iodrate < r->details.iodrate)
		{
			pre = pre->next;
			r = r->next;
		}
		temp = curr;
		curr = curr->next;
		pre->next = temp;
		temp->next = r;
	}
}
void fileWrite(linklist& L1, linklist& L2, linklist& L3,string Tobes) {
	ofstream outFile;
	outFile.open("价格和涨跌幅排序结果.csv", ios::out);
	outFile << "按照开盘价排序" << ',' << "日期:" << Tobes << endl;
	outFile << "序号" << ',' << "股票代码" << ',' << "股票名称" << ',' << "开盘价" << ',' << "收盘价" << ',' << "涨跌幅" << endl;
	int i = 1, j = 1, k = 1;
	while (L1->next) {
		//int i = 1;
		outFile << i << ',' << L1->next->stock_num << ',' << L1->next->stock_name << ',' << L1->next->details.oprice << ',' << L1->next->details.cprice << ',' << L1->next->details.iodrate << endl;
		L1 = L1->next;
		i++;
	}
		//cout << L1->stock_num << "    " << L1->stock_name << "    " << L1->details.oprice << endl;
		
	outFile << "按照收盘价排序" << ',' << "日期:" << Tobes << endl;
	while(L2->next){
		
		outFile << j << ',' << L2->next->stock_num << ',' << L2->next->stock_name << ',' << L2->next->details.oprice << ',' << L2->next->details.cprice << ',' << L2->next->details.iodrate << endl;
		L2 = L2->next;
		j++;
	}
	outFile << "按照涨跌幅排序" << ',' << "日期:" << Tobes << endl;
	while(L3->next){
		outFile << k << ',' << L3->next->stock_num << ',' << L3->next->stock_name << ',' << L3->next->details.oprice << ',' << L3->next->details.cprice << ',' << L3->next->details.iodrate << endl;
		L3 = L3->next;
		k++;
	}
	outFile << endl;
	outFile.close();
}
void A_StockPrice_DIS(stock stocks[], MGraph g) {			//分析_股票价格分析_基于直接插入排序DirectInsertS
	
	cout << "****************************************" << endl;
	cout << "*这是一个基于直接插入排序的股票价格分析*" << endl;
	cout << "****************************************" << endl;
	cout << "请输入你要查询的日期:";
	string tobes; cin >> tobes;
	linklist L1 = CreatList(stocks,tobes);
	linklist L2 = CreatList(stocks,tobes);
	linklist L3 = CreatList(stocks,tobes);
	//CreatList(stocks);
	//cout << "请输入你要进行分析的日期:";
	//stock temps1[ComN],temps2[ComN],temps3[ComN];												//存储指定日期的所有股票信息
	//for (int i = 0; i < ComN; i++) {
	//	temps1[i] = stocks[i];
	//	temps2[i] = stocks[i];
	//	temps3[i] = stocks[i];
	//}
	//for (int i = 0; i < ComN; i++) {
	//	det p = stocks[i].details;
	//	while (p) {
	//		if (p->date == tobes) {
	//			L1->data.details = p;
	//			L1->data.details = p;
	//			L1->data.details = p;
	//			//cout << temps[i].StockNum<<"\t"<< temps[i].details->date<<endl;
	//			break;
	//		}
	//		else {
	//			p = p->next;
	//		}
	//	}
	//}
	//insertSort_oprice(temps1,ComN);
	//insertSort_cprice(temps2, ComN);
	//insertSort_iodrate(temps3, ComN);
	//writeFile(temps1,temps2,temps3);
	InsertSort_oprice(L1);
	InsertSort_cprice(L2);
	InsertSort_iodrate(L3);
	//linklist p = L1;
	/*while (p) {
		cout << 1 << "   " << p->stock_num << "  " << p->stock_name << "  " << p->details.cprice << endl;
		p = p->next;
	}*/
	fileWrite(L1, L2, L3,tobes);
	cout << "分析结果已经写入您指定的文件中。" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}

void SelectSort(stock* temp, int num) {
	for (int i = 0; i < num; i++)  /*做n-1趟选取*/
	{
		int k = i;    /*在i开始的n-i+1个记录中选关键码最小的记录*/
		for (int j = i + 1; j <= num; j++)
			if (temp[j].score > temp[k].score)
				k = j;    /*k中存放关键码最小记录的下标*/
		if (i != k)    /*关键码最小的记录与第i个记录交换*/
		{
			stock temp_;
			temp_ = temp[k];
			temp[k] = temp[i];
			temp[i] = temp_;
		}
	}
}
void A_StockPrice_SS(stock stocks[], MGraph g) {			//分析_股票价格分析_基于简单选择排序SelectionS
	cout << "****************************************" << endl;
	cout << "*这是一个基于简单选择排序的股票价格分析*" << endl;
	cout << "****************************************" << endl;
	cout << "根据调研结果，分析结果如下：" << endl << endl << endl;
	stock temps[61];
	int Num = 0;
	for (int i = 0; i < ComN; i++) {
		if (stocks[i].score != "-1") {
			temps[Num] = stocks[i];
			temps[Num].details = stocks[i].details->next;
			Num++;
		}
	}
	SelectSort(temps, Num);
	for (int i = 0; i < Num; i++) {
		cout << setfill(' ') << setw(2)<< i+1 << setfill(' ') << setw(10) <<temps[i].point<< setfill(' ') << setw(15) << temps[i].StockName << setfill(' ') << setw(10) << temps[i].score << endl;
	}
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}
void A_StockPrice(stock stocks[], MGraph g) {				//分析_股票价格分析
	cout << "分析方式有" << endl;
	cout << "1—基于快速排序 || 2—基于直接插入排序 || 3—基于简单选择排序" << endl;
	cout << "请选择：";
	int ToDo = -1; cin >> ToDo;
	if (ToDo == 1) {
		A_StockPrice_QS(stocks, g);
	}
	else if (ToDo == 2) {
		A_StockPrice_DIS(stocks, g);
	}
	else if (ToDo == 3) {
		A_StockPrice_SS(stocks, g);
	}
	else {
		cout << "请输入有效选择项！" << endl;
		system("pause");
		cout << endl;
		A_StockPrice(stocks, g);
	}
}
//股票相关性分析

void A_StockRelevance(stock stocks[], MGraph g) {			//分析_股票相关性分析-基于Floyd

	

	cout << "***********************************" << endl;
	cout << "*这是一个基于Floyd的股票相关性分析*" << endl;
	cout << "***********************************" << endl;
	cout << "请输入你要分析的两支股票的序号(1~60)：";
	int a, b;
	cin >> a >> b; 
	if (a > 60 || b > 60 || a < 1 || b < 1) {
		cout << "查找失败，请确认输入信息有效!" << endl;
		cout << "即将进入到上一级菜单" << endl; system("pause");
		AnalyzeMenu(stocks, g);
	}
	else {
		cout << "分析结果，股票相关性为:" ;
		ReadCSV_1_1(g,a,b);
		cout << endl;
		cout << "即将进入到上一级菜单" << endl; system("pause");
		AnalyzeMenu(stocks, g);
	}
	//string a, b; cin >> a >> b;
	//Floyd(g);
	////cout << "分析结果如下：" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}
//股票基金筛选
void A_StockFund_Prim(stock stocks[], MGraph g) {			//分析_股票基金筛选_基于Prime最小生成树
	cout << "******************************************" << endl;
	cout << "*这是一个基于Prim最小生成树的股票基金筛选*" << endl;
	cout << "******************************************" << endl;
	MGraph g1 =  ReadCSV_1_2(g);
	//for (int i = 0; i < 60; i++) {
	//	for (int k = 0; k < 60; k++) {
	//		if (g1.value[i][k] != 0 && g1.value[i][k] != INF) {
	//			cout << i << "   " << k << "   " << g1.value[i][k] << endl;
	//		}
	//	}
	//	//测试结果：有效
	//}
	prim minprim[3];
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {

		}
	}
	cout << "分析结果如下：" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}
void A_StockFund_Bigraph(stock stocks[], MGraph g) {		//分析_股票基金筛选_基于二部图Bigraph
	cout << "**********************************" << endl;
	cout << "*这是一个基于二部图的股票基金筛选*" << endl;
	cout << "**********************************" << endl;

	cout << "分析结果如下：" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl;	system("pause");
	AnalyzeMenu(stocks, g);

}
void A_StockFund(stock stocks[], MGraph g) {					//分析_股票基金筛选
	cout << "分析方式有：" << endl;
	cout << "1—基于Prim最小生成树 || 2—基于二部图" << endl;
	cout << "请选择：";
	int ToDo = -1; cin >> ToDo;
	if (ToDo == 1) {
		A_StockFund_Prim(stocks, g);
	}
	else if (ToDo == 2) {
		A_StockFund_Bigraph(stocks, g);
	}
	else {
		cout << "请输入有效选择项!" << endl;
		system("pause");
		cout << endl;
		A_StockFund(stocks, g);
	}
}
//分析二级菜单
void AnalyzeMenu(stock stocks[], MGraph g) {				//分析
	cout << endl << "可进行的操作有:" << endl;
	cout << "1——股票价格分析" << endl;
	cout << "2——股票相关性计算分析" << endl;
	cout << "3——股票基金筛选" << endl;
	cout << "4——返回到主页面菜单" << endl;
	cout << "请选择:";

	int ToDo = -1;
	cin >> ToDo;
	if (ToDo == 1) {
		A_StockPrice(stocks,g);
	}
	else if (ToDo == 2) {
		A_StockRelevance(stocks,g);
	}
	else if (ToDo == 3) {
		A_StockFund(stocks,g);
	}
	else if (ToDo == 4) {
		MainMenu(stocks,g);
	}
	else {
		cout << "请输入有效选择项!" << endl;
		AnalyzeMenu(stocks,g);
	}
}

/***********    主菜单    ************/
void MainMenu(stock stocks[], MGraph g) {				//主菜单
	system("cls");
	cout << "****************************" << endl;
	cout << "***********主菜单***********" << endl;
	cout << "****************************" << endl;
	cout << "-—— 可进行的操作如下 ——-" << endl;
	cout << "1:查询" << endl;
	cout << "2:分析" << endl;
	cout << "3:退出" << endl;
	cout << "请选择:";

	int ToDo = -1;
	cin >> ToDo;
	if (ToDo == 1) {
		SearchMenu(stocks, g);
	}
	else if (ToDo == 2) {
		//MainMenu(stocks);
		AnalyzeMenu(stocks, g);
	}
	else if (ToDo == 3) {
		exit(0);
	}
	else {
		cout << "请输入有效选择项!" << endl;
		system("pause");
		MainMenu(stocks, g);
	}
}
/***********    进入系统界面    ************/
void Welcome(stock stocks[], MGraph g) {				//欢迎界面
	
	cout << "正在读取数据...即将进入系统" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));				//延迟函数
	system("cls");
	
	
	cout << "     *数据读取成功!*" << endl;
	cout << "欢迎进入股票查询与分析系统" << endl;
	cout << "             ——by 郭浩宇" << endl;

	system("pause");
	MainMenu(stocks, g);
}

int main()
{	//system("pause");
	stock stocks[201];
	MGraph floyd;
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			if (i == j) {
				floyd.value[i][j] = 0;
			}
			else {
				floyd.value[i][j] = INF;
			}
			
		}
	}
	for (int m = 0; m < 201; m++) {
		stocks[m].score = "-1";
		stocks[m].point = -1;
	}
	ReadCSV_basic(stocks,floyd);
	ReadCSV_2(stocks,floyd);

	//system("pause");
	ReadTXT(stocks,floyd);
	CreatHash(stocks,floyd);
	//system("pause");
	
	/*cout << "____________" << endl;
	for (int i = 0; i < 60; i++) {
		for (int k = 0; k < 60; k++) {
			if (floyd.value[i][k] != 0 && floyd.value[i][k] != -1) {
				cout << i << "    " << k << "   " << floyd.value[i][k] << endl;
			}
		}
	}*/
	system("pause");
	Welcome(stocks,floyd);

}