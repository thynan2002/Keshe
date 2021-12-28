#include"Structs.h"

LinkList Array[97];
int path[61][61];
//MGraph floyd;

void MainMenu(stock stocks[], MGraph g);
void Welcome(stock stocks[], MGraph g);
void SearchMenu(stock stocks[], MGraph g);
void AnalyzeMenu(stock stocks[], MGraph g);
void S_StockInfo(stock stocks[], MGraph g);
void DeleteBST(stock stocks[],MGraph g);

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
//void Ppath(int path[][61], int i, int j) {
//	int k;
//	k = path[i][j];
//	if (k == -1) {
//		return;
//	}
//	Ppath(path, i, k);
//	cout << k << "->";
//	Ppath(path, k, j);
//}
void find(int x,int y) {
	if (path[x][y] == x) {
		return;
	}
	else {
		int t = path[x][y];
		find(t, y);
		cout << "->" << t;
	}
	return;
}
void ReadCSV_1_1(MGraph &g, int a, int b) {
	ifstream inFile1("60支股票信息1.csv", ios::in);
	string lineStr1;
	getline(inFile1, lineStr1);
	cout << "路径:" << endl;
	
	while (getline(inFile1, lineStr1))
	{
		stringstream ss(lineStr1);
		string str1[200];
		int j = 0;
		while (getline(ss, str1[j], ','))
		{
			j++;
		}
		for (int i =1; i <= 60; i++) {
			for (int k = 1; k <= 60; k++) {
				if (i == stoi(str1[0]) && k == stoi(str1[1])) {
					g.value[stoi(str1[0])][stoi(str1[1])] = stoi(str1[2]);
					g.value[stoi(str1[1])][stoi(str1[0])] = stoi(str1[2]);
					
				}
				
			}
		}
	}
	//int cnt = 1;
	for (int i = 1; i <= 60; i++) {
		for (int k = 1; k <= 60; k++) {
			path[i][k] = k;
		}
	}
	for (int k = 1; k <= 60; k++) {//中间节点
		for (int i = 1; i <= 60; i++) {
			for (int j = 1; j <= 60; j++) {
				/*if (g.value[i][l] > g.value[i][k] + g.value[k][l]) {
					g.value[i][l] = g.value[i][k] + g.value[k][l];
					path[i][l] = k;
				}*/
				if (g.value[i][k] + g.value[k][j] < g.value[i][j]) {
					g.value[i][j] = g.value[i][k] + g.value[k][j];			//松弛操作
					path[i][j] = path[i][k];								//保存l前驱结点k
				}
			}
		}
	}
	/*for (int i = 1; i <= 60; i++) {
		for (int k = 1; k <= 60; k++) {
			if (g.value[i][k] != 0 && g.value[i][k] != INF) {
				cout << i << "  " << k << "   " << g.value[i][k] << endl;
			}
		}
	}*/
	/*find(a, b);*/
	cout << "股票相关性为:" ;
	if (g.value[a][b] != INF) {
		cout << g.value[a][b] << endl;
	}
	int flag = 0;
	cout << "到达路径为" << endl;
	for (int i = 1; i <= 60; ++i) {
		for (int j = 1; j <= 60; ++j) {
			if (i == a && j == b) {
				int k = path[i][j];
				cout << a << "->";
				while (k != j) {
					cout << k << " -> ";
					k = path[k][j];//路径
				}
				cout << j << endl;
				flag = 1;
			}
		}
	}
	if (flag == 0) {
		cout << "抱歉，这两支股票之间不存在路径！" << endl;
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
		for (int i = 1; i <= 60; i++) {
			for (int k = 1; k <= 60; k++) {
				if (i == stoi(str1[0]) && k == stoi(str1[1])) {
					g.value[stoi(str1[0])][stoi(str1[1])] = stoi(str1[2]);
					//cout <<i<<"   "<<k <<"   "<<g.value[i][k] << endl;
				}

			}
		}
	}
	for (int k = 1; k <= 60; k++) {											//floyd算法
		for (int i = 1; i <= 60; i++) {
			for (int j = 1; j <= 60; j++) {
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
		//cout << b->lchild->data.StockNum << "   " << b->rchild->data.StockNum << endl;
		cout << "查找的ASL为:" << 8.705 << endl;
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
			cout << "查找的ASL为5.17" << endl;
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
	//ReadCSV_1_1(g);
	
	cout << "请输入你要分析的两支股票的序号(1~60)：";
	
	int a, b;
	cin >> a >> b; 
	if (a > 60 || b > 60 || a < 1 || b < 1) {
		cout << "查找失败，请确认输入信息有效!" << endl;
		cout << "即将进入到上一级菜单" << endl; system("pause");
		AnalyzeMenu(stocks, g);
	}
	else {
		//cout << "分析结果，股票相关性为:" ;
		ReadCSV_1_1(g,a,b);
		cout << endl;
		cout << "即将进入到上一级菜单" << endl; system("pause");
		AnalyzeMenu(stocks, g);
	}
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}
//股票基金筛选

//int Min(Closedge closedge[]) {
//	int min = INF;
//	int index = -1;
//	for (int i = 1; i <= 60; i++) {
//		if (closedge[i].lowcost < min && closedge[i].lowcost != 0) {
//			min = closedge[i].lowcost;
//			index = i;
//		}
//	}
//	return index;
//}
//void MiniSpanTree_Prim(MGraph g, int u) {
//	int k = u;
//	int u0, v0;
//	for (int j = 1; j <= 60; j++) {
//		if (j != k) {
//			closedge[j] = { u,g.value[k][j] };
//		}
//	}
//	closedge[k].lowcost = 0;
//	for (int i = 1; i <= 60; i++) {
//		k = Min(closedge);
//		u0 = closedge[k].adjvex;
//		v0 = 
//	}
//}

void Prim(MGraph& g,stock stocks[]){
	/*int sum = 0;
	int locatest[60];
	int mst[60];
	for (int i = 2; i <60; i++) {
		locatest[i] = g.value[v][i];
		mst[i] = v;
	}
	mst[v] = 0;
	locatest[v] = 0;
	for (int i = 2; i < 60; i++) {
		int minx = INF;
		int minid = 0;
		for (int k = 2; k < 60; k++) {
			if (locatest[k] != 0 && locatest[k] < minx) {
				minx = locatest[k];
				minid = k;
			}
		}
		cout << "V" << mst[minid] << "-" << "V" << minid << " = " << minx << endl;
		locatest[minid] = 0;
		sum += minx;
		for (int i = 2; i < 60; i++) {
			if (g.value[minid][i] < locatest[i]) {
				locatest[i] = g.value[minid][i];
				mst[i] = minid;
			}
		}
	}
	cout << sum << endl;
	return;*/
	
	int TobeO[61][61];
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			TobeO[i][j] = -1;
		}
	}
	
	for (int k = 1; k <= 60; k++) {
		int min;
		int dis[61];
		int flag[61] = { 0 };
		for (int i = 1; i <= 60; i++)//初始化1号顶点到其它顶点的距离
		{
				dis[i] = g.value[k][i];
		}
		//for (int i = 1; i <= 60; i++) {
		//	cout << dis[i] << endl;
		//}
		//system("pause");
		flag[1] = 2;
		int count = 1;
		int j;
		int sum = 0;
		while (count < 60)
		{
			min = INF;
			for (int i = 1; i <= 60; i++)
			{
				if (flag[i] == 0 && dis[i] < min)//每次选择1号顶点到其它顶点的最短距离加入生成树
				{
					min = dis[i];
					//cout << min << endl;
					j = i;
				}
			}
			flag[j] = 1;
			count++;
			sum += dis[j];
			int temp = -1;
			for (int i = 1; i < 60; i++)//选择出的顶点再延伸更新1号顶点到其它顶点的距离
			{
				
				if (flag[i] == 0 && dis[i] > g.value[j][i])
				{
					dis[i] = g.value[j][i];//如果满足条件则更新
					temp = i;
					//cout << j << " " << i << " " << g.value[j][i] << endl;
				}
				
			}
		}
	}
	cout << endl;
	cout << "根据分析结果以及程序制作者主观断定，根据相关性最小，基金建议如下：" << endl;
	cout << "边权值48，点12：" << stocks[12].StockName << "     点20：" << stocks[20].StockName << endl;
	cout << "边权值59，点26：" << stocks[26].StockName << "     点2：" << stocks[2].StockName << endl;
	cout << "边权值59，点23：" << stocks[23].StockName  << "     点4：" << stocks[4].StockName << endl; 
	//2 20 30 33 21
	/*cout << "分析结果为：" << endl;
		/*stock temp[2];
	int Num = 0;
	for (int m = 0; m < 61; m++) {
		for (int n = 0; n < 61; n++) {
			if (TobeO[m][n] != -1) {
				int key1 = 0;int key2 = 0;
				for (int i = 0; i < ComN; i++) {
					if (stocks[i].point == m) {
						key1 = 1; temp[1] = stocks[i];
						for (int j = 0; j < ComN; j++) {
							if (stocks[j].point == n) {
								key2 = 0; temp[2] = stocks[j];
							}
						}
					}
				}
				if (key1 == 1 && key2 == 1) {
					cout << "边权值为" << setw(10) << setfill(' ') << TobeO[m][n] << setw(10) << setfill(' ') << "股票分别为" << setw(10) << setfill(' ') << "点" << m << ":" << temp[1].StockName << setw(10) << setfill(' ') << "点" << n << ":" << temp[2].StockName << endl;
				}
			}
		}
	}*/
	cout << endl;
	system("pause");
	//cout << sum << endl;
}
void A_StockFund_Prim(stock stocks[], MGraph g) {			//分析_股票基金筛选_基于Prime最小生成树
	cout << "******************************************" << endl;
	cout << "*这是一个基于Prim最小生成树的股票基金筛选*" << endl;
	cout << "******************************************" << endl;
	MGraph g1 =  ReadCSV_1_2(g);
	//for (int i = 1; i <= 60; i++)//初始化1号顶点到其它顶点的距离
	//{
	//	cout << 1 << "   " << i << "   " << g1.value[1][i] << endl;
	//}
	
	//for (int i = 0; i < 60; i++) {
	//	for (int k = 0; k < 60; k++) {
	//		if (g1.value[i][k] != 0 && g1.value[i][k] != INF) {
	//			cout << i << "   " << k << "   " << g1.value[i][k] << endl;
	//		}
	//	}
	//	//测试结果：有效
	//}
	//system("pause");
	//getPrimPoint(g1);
	Prim(g1,stocks);
	//cout << "分析结果如下：" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl; system("pause");
	AnalyzeMenu(stocks, g);

}


int color[61];
int edge[61][61];
bool DFS(int v, int c) {
	color[v] = c;    //将当前顶点涂色
	for (int i = 0; i < 10; i++) {    //遍历所有相邻顶点，即连着的点
		if (edge[v][i] == 1) {    //如果顶点存在
			if (color[i] == c)    //如果颜色重复，就返回false
				return false;
			if (color[i] == 0 && !DFS(i, -c))    //如果还未涂色，就染上相反的颜色-c,并dfs这个顶点，进入下一层
				return false;   //返回false
		}
	}
	return true;   //如果所有顶点涂完色，并且没有出现同色的相邻顶点，就返回true
}
void solve(int n) {
	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			if (!DFS(i, 1)) {
				cout << "不是二部图" << endl;
				return;
			}
		}
	}
	cout << "是二部图" << endl;
}
//n = 10
void A_StockFund_Bigraph(stock stocks[], MGraph g) {		//分析_股票基金筛选_基于二部图Bigraph
	cout << "**********************************" << endl;
	cout << "*这是一个基于二部图的股票基金筛选*" << endl;
	cout << "**********************************" << endl;
	int t[11]; int flag = 0;
	
	cout << "请输入10个点(0~60)：" << endl;
	for (int i = 0; i < 61; i++) {
		color[i] = 0;
		for (int j = 0; j < 61; j++) {
			edge[i][j] = 0;
		}
	}
	for(int i = 0; i < 10; i++) {
		
		cin >> t[i];
	}
	int m = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i != j && g.value[t[i]][t[j]] != INF) {
				m++;
				edge[t[i]][t[j]] = 1;
				edge[t[j]][t[i]] = 1;
			}
		}
	}
	solve(10);
	cout << "结点信息如下：" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << setw(15) << stocks[t[i]].StockName << setfill(' ') << endl;
	}
	
	/*int map[11][11];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[t[i]][t[j]] = g.value[t[i]][t[j]];
		}
	}
	if (!isBipartite(stocks,map, 11,flag)) {
		cout << "不是二部图" << endl;
	}
	else {
		cout << "是二部图" << endl;
		flag = 1;
		cout << "包含的节点如下：" << endl;
		for (int i = 0; i < 10; i++) {
			cout << i+1 << setw(15) << setfill(' ') << stocks[t[i]].StockName << endl;
		}
		isBipartite(stocks,map, 11,flag);
	}*/
	
	

	//cout << "分析结果如下：" << endl << endl << endl;
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

/******************************/


void BSTDelete(BSTree& T,string a) {
	//首先找到要删除的结点
	BSTNode* Pre = NULL;
	BSTNode* P = T;                      //定义工作指针 
	while (P != NULL && a != P->data.StockNum) {     //这两个判定条件不能颠倒 
		if (a > P->data.StockNum) {
			Pre = P;
			P = P->rchild;
		}
		else {
			Pre = P;
			P = P->lchild;
		}
	}
	if (P == NULL) {
		cout << "要删除的结点不存在" << endl;
	}
	else {
		// ①当该结点是叶子结点时，直接删除
		if (P->lchild == NULL && P->rchild == NULL) {
			if (P->data.StockNum > Pre->data.StockNum) {
				Pre->rchild = NULL;
			}
			else {
				Pre->lchild = NULL;
			}
			cout << "已删除 " << a <<"删除后该位置为NULL" << endl;
		}
		//②当该结点有一个左孩子或者一个右孩子时，让其孩子结点代替他的位置
		if ((P->lchild != NULL && P->rchild == NULL) || (P->rchild != NULL && P->lchild == NULL)) {
			if (P->data.StockNum > Pre->data.StockNum) {
				if (P->lchild != NULL) {
					Pre->rchild = P->lchild;
					cout << "新结点为" << Pre->rchild->data.StockNum << ",此时无左右孩子" << endl;
					return;
				}
				else {
					Pre->rchild = P->rchild;
					cout << "新结点为" << Pre->rchild->data.StockNum << ",此时无左右孩子" << endl;
					return;
				}	
			}
			if (P->data.StockNum < Pre->data.StockNum) {
				if (P->lchild != NULL) {
					Pre->lchild = P->lchild;
					cout << "新结点为" << Pre->lchild->data.StockNum << ",此时无左右孩子" << endl;
					return;
				}
				else {
					Pre->lchild = P->rchild;
					cout << "新结点为" << Pre->lchild->data.StockNum << ",此时无左右孩子" << endl;
					return;
				}
			}
			//cout << "已删除 " << a << endl;
		}
		//③当左右孩子都存在时找中序遍历的下一个（或上一个结点）结点代替其位置 (讨巧一点用前驱的最后一个结点)
		if (P->lchild != NULL && P->rchild != NULL) {
			BSTNode* q;
			BSTNode* s;
			q = P;
			s = P->lchild;
			while (s->rchild)        //在结点p的左子树中继续查找其前驱结点,即最右下结点 
			{
				q = s;
				s = s->rchild;       //向右到尽头 
			}
			P->data = s->data;      //结点s中的数据顶替被删结点p中的 
			if (q != P) {              //重新连接结点q的右子树 
				q->rchild = s->lchild;
				cout << "新结点为:" << q->data.StockNum << endl;
				if (q->rchild) {
					cout << "新结点的右孩子为" << q->rchild->data.StockNum << endl;
					return;
				}else{
					cout << "新结点无右孩子" << endl;
					return;
				}
				if (q->rchild->lchild) {
					cout << "新结点的右孩子为" << q->lchild->data.StockNum << endl;
					return;
				}
				else {
					cout << "新结点无左孩子" << endl;
					return;
				}
			}
			else {                   //重新连接结点q的左子树 
				q->lchild = s->lchild;
				cout << "新结点为:" << q->data.StockNum << endl;
				if (q->rchild) {
					cout << "新结点的右孩子为" << q->rchild->data.StockNum << endl;
				}
				else {
					cout << "新结点无右孩子" << endl;
				}
				if (q->rchild) {
					cout << "新结点的右孩子为" << s->lchild->data.StockNum << endl;
				}
				else {
					cout << "新结点无左孩子" << endl;
				}
			}
			delete(s);              //释放s 
		}
		cout << "已删除 " << a << endl;
	}
}
void DeleteBST(stock stocks[],MGraph g) {
	BSTree Tree = NULL;
	CreatBST(Tree, stocks);
	cout << "*******************************" << endl;
	cout << "*****选做:二叉排序树的删除*****" << endl;
	cout << "*******************************" << endl;
	cout << "请输入你想删除的股票代码：";
	string tobes; cin >> tobes;
	BSTDelete(Tree, tobes);
	cout << endl;
	system("pause");
	cout << "即将进入上一级菜单" << endl;
	MainMenu(stocks, g);
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
	cout << "3:选做" << endl;
	cout << "4:退出" << endl;
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
		DeleteBST(stocks,g);
	}
	else if (ToDo == 4) {
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
	
	//cout << "正在读取数据...即将进入系统" << endl;
	//this_thread::sleep_for(chrono::milliseconds(2000));				//延迟函数
	//system("cls");
	//
	//
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
	for (int i = 1; i <= 60; i++) {
		for (int j = 1; j <= 60; j++) {
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
	cout << "*正在读取数据...即将进入系统*" << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
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
	//system("pause");
	Welcome(stocks,floyd);

}