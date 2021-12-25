#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include<chrono>
#include<thread>
#define ComN 200				//公司数量
using namespace std;

/*股票详细数据*/
typedef struct {
	string date;				//日期
	string oprice;				//开盘价
	string cprice;				//收盘价
	string maxprice;			//最高价
	string minprice;			//最低价
	string volume;				//成交量
	string turnover;			//成交额
	string rate;				//换手率
	string iodamount;			//涨跌额
	string iodrate;				//涨跌幅
}detail;
typedef struct{
	string StockNum;			//股票代码
	string StockName;			//股票简称
	string StockCode;			//行业编码
	string _1Kind;				//一级门类
	string _2Kind;				//二级门类
	string StockLE;				//上市交易所 Listed Exchange
	string StockWN;				//公司全称 Whole Name
	string StockTime;			//上市时间
	string StockProv;			//省份
	string StockCity;			//城市
	string StockLP;				//法人 Legal Person
	string StockAddr;			//地址
	string StockWeb;			//网址
	string StockEmail;			//邮箱
	string StockTel;			//电话
	string StockMB;				//主营业务 Main Business
	string StockBS;				//经营范围 Business Scope
	detail* details;			//详细信息
}stock;
typedef struct LNode{
	stock data;
	struct LNode* next;
}*LinkList,LNode;

typedef struct BSTNode {
	stock data;							
	struct BSTNode* lchild, * rchild;			//左右孩子指针
}BSTNode,*BSTree;


LinkList Array[97];
void MainMenu(stock stocks[]);
void Welcome(stock stocks[]);
void SearchMenu(stock stocks[]);
//void AnalyzeMenu(stock stocks[]);
void S_StockInfo(stock stocks[]);



void Read(stock stocks[]) {
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
	for (int m = 0; m < ComN; m++) {
		string file_name = stocks[m].StockNum + ".txt";
		ifstream inFile(file_name, ios::in);
		string lineStr;
		getline(inFile, lineStr);
		int k = 0;
		while (getline(inFile, lineStr)) {
			stringstream ss(lineStr);
			string str[200];
			int j = 0;
			while (getline(ss, str[j], ' ')) {
				j++;
			}
			stocks[m].details = new detail[200];
			stocks[m].details[k].date = str[0];
			stocks[m].details[k].oprice = str[1];
			stocks[m].details[k].cprice = str[2];
			stocks[m].details[k].maxprice = str[3];
			stocks[m].details[k].minprice = str[4];
			stocks[m].details[k].volume = str[5];
			stocks[m].details[k].turnover = str[6];
			stocks[m].details[k].rate = str[7];
			stocks[m].details[k].iodamount = str[8];
			stocks[m].details[k].iodrate = str[9];
			k++;
			break;
		}

	}
	//string FileName = ""
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
void S_StockWeb_KMP(stock stocks[]) {				//查询_基本信息查询
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
		while (j == -1 || (i < stocks[k].StockWeb.size() && j < tobes.size())) // -1和unsigned比较
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
	SearchMenu(stocks);

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
void S_SI_BT(stock stocks[]) {					//查询_股票网址查询_基于二叉树BT
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
		cout << b->data.details->oprice << "\t" << b->data.details->cprice << "\t" << b->data.details->iodrate << endl;
	}
	else {
		cout << "未找到相关信息，请确认输入信息有效" << endl;
	}
	cout << "即将进入到上一级菜单" << endl; system("pause");
	SearchMenu(stocks);

}

void CreatHash(stock stocks[]) {				//创建哈希表
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
void S_SI_Hash(stock stocks[]) {					//查询_股票网址查询_基于哈希表hash
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
	SearchMenu(stocks);
}
void S_StockInfo(stock stocks[]) {					//查询_股票基本信息查询
	cout << "请选择查询方式：1—基于哈希表 || 2—基于二叉排序树" << endl;
	int ToDo = -1; cin >> ToDo;
	if (ToDo == 1) {
		S_SI_Hash(stocks);
	}
	else if (ToDo == 2) {
		S_SI_BT(stocks);
	}
	else {
		cout << "请输入有效选择项！" << endl;
		system("cls");
		S_StockInfo(stocks);
	}
}
//股票价格查询
void S_StockPrice(stock stocks[]) {				//查询_股票的价格信息
	cout << "**********************************" << endl;
	cout << "*这是一个基于单链表的股票价格查询*" << endl;
	cout << "**********************************" << endl;
	cout << "查询结果如下：" << endl << endl << endl;
	cout << "即将进入到上一级菜单" << endl; system("pause");
	SearchMenu(stocks);
}
//查询二级菜单
void SearchMenu(stock stocks[]) {					//查询
	cout << endl << "可进行的操作有：" << endl;
	cout << "1——股票的基本信息" << endl;
	cout << "2——股票的网址" << endl;
	cout << "3——股票的价格信息" << endl;
	cout << "4——返回到主页面菜单" << endl;
	cout << "请选择:";

	int ToDo = -1;
	cin >> ToDo;
	if (ToDo == 1) {
		S_StockInfo(stocks);
	}
	else if (ToDo == 2) {
		S_StockWeb_KMP(stocks);
	}
	else if (ToDo == 3) {
		S_StockPrice(stocks);
	}
	else if (ToDo == 4) {
		MainMenu(stocks);
	}
	else {
		cout << "请输入有效选择项！" << endl;
		SearchMenu(stocks);
	}
}
/***********    Analyze    ************/
//股票价格分析
//void A_StockPrice_QS(stock stocks[]) {			//分析_股票价格分析_快速排序QuickS
//	cout << "************************************" << endl;
//	cout << "*这是一个基于快速排序的股票价格分析*" << endl;
//	cout << "************************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl; system("pause");
//	AnalyzeMenu();
//
//}
//void A_StockPrice_DIS(stock stocks) {			//分析_股票价格分析_基于直接插入排序DirectInsertS
//	cout << "****************************************" << endl;
//	cout << "*这是一个基于直接插入排序的股票价格分析*" << endl;
//	cout << "****************************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl; system("pause");
//	AnalyzeMenu();
//
//}
//void A_StockPrice_SS(stock stocks[]) {			//分析_股票价格分析_基于简单选择排序SelectionS
//	cout << "****************************************" << endl;
//	cout << "*这是一个基于简单选择排序的股票价格分析*" << endl;
//	cout << "****************************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl; system("pause");
//	AnalyzeMenu();
//
//}
//void A_StockPrice(stock stocks[]) {				//分析_股票价格分析
//	cout << "分析方式有" << endl;
//	cout << "1—基于快速排序 || 2—基于直接插入排序 || 3—基于简单选择排序" << endl;
//	cout << "请选择：";
//	int ToDo = -1; cin >> ToDo;
//	if (ToDo == 1) {
//		A_StockPrice_QS();
//	}
//	else if (ToDo == 2) {
//		A_StockPrice_DIS();
//	}
//	else if (ToDo == 3) {
//		A_StockPrice_SS();
//	}
//	else {
//		cout << "请输入有效选择项！" << endl;
//		system("pause");
//		cout << endl;
//		A_StockPrice();
//	}
//}
////股票相关性分析
//void A_StockRelevance(stocks) {			//分析_股票相关性分析-基于Floyd
//	cout << "***********************************" << endl;
//	cout << "*这是一个基于Floyd的股票相关性分析*" << endl;
//	cout << "***********************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl; system("pause");
//	AnalyzeMenu();
//
//}
////股票基金筛选
//void A_StockFund_Prim(stocks) {			//分析_股票基金筛选_基于Prime最小生成树
//	cout << "******************************************" << endl;
//	cout << "*这是一个基于Prim最小生成树的股票基金筛选*" << endl;
//	cout << "******************************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl; system("pause");
//	AnalyzeMenu();
//
//}
//void A_StockFund_Bigraph(stocks) {		//分析_股票基金筛选_基于二部图Bigraph
//	cout << "**********************************" << endl;
//	cout << "*这是一个基于二部图的股票基金筛选*" << endl;
//	cout << "**********************************" << endl;
//
//	cout << "分析结果如下：" << endl << endl << endl;
//	cout << "即将进入到上一级菜单" << endl;	system("pause");
//	AnalyzeMenu();
//
//}
//void A_StockFund(stocks) {					//分析_股票基金筛选
//	cout << "分析方式有：" << endl;
//	cout << "1—基于Prim最小生成树 || 2—基于二部图" << endl;
//	cout << "请选择：";
//	int ToDo = -1; cin >> ToDo;
//	if (ToDo == 1) {
//		A_StockFund_Prim();
//	}
//	else if (ToDo == 2) {
//		A_StockFund_Bigraph();
//	}
//	else {
//		cout << "请输入有效选择项!" << endl;
//		system("pause");
//		cout << endl;
//		A_StockFund();
//	}
//}
////分析二级菜单
//void AnalyzeMenu(stocks) {				//分析
//	cout << endl << "可进行的操作有:" << endl;
//	cout << "1——股票价格分析" << endl;
//	cout << "2——股票相关性计算分析" << endl;
//	cout << "3——股票基金筛选" << endl;
//	cout << "4——返回到主页面菜单" << endl;
//	cout << "请选择:";
//
//	int ToDo = -1;
//	cin >> ToDo;
//	if (ToDo == 1) {
//		A_StockPrice();
//	}
//	else if (ToDo == 2) {
//		A_StockRelevance();
//	}
//	else if (ToDo == 3) {
//		A_StockFund();
//	}
//	else if (ToDo == 4) {
//		MainMenu();
//	}
//	else {
//		cout << "请输入有效选择项!" << endl;
//		AnalyzeMenu();
//	}
//}

/***********    主菜单    ************/
void MainMenu(stock stocks[]) {				//主菜单
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
		SearchMenu(stocks);
	}
	else if (ToDo == 2) {
		MainMenu(stocks);
		//AnalyzeMenu(stocks);
	}
	else if (ToDo == 3) {
		exit(0);
	}
	else {
		cout << "请输入有效选择项!" << endl;
		system("pause");
		MainMenu(stocks);
	}
}
/***********    进入系统界面    ************/
void Welcome(stock stocks[]) {				//欢迎界面
	//cout << "正在读取数据...即将进入系统" << endl;
	//this_thread::sleep_for(chrono::milliseconds(2000));				//延迟函数
	//system("cls");
	cout << "     *数据读取成功!*" << endl;
	cout << "欢迎进入股票查询与分析系统" << endl;
	cout << "             ——by 郭浩宇" << endl;

	LinkList p;
	system("pause");
	MainMenu(stocks);
}

int main()
{
	stock stocks[201];

	Read(stocks);
	CreatHash(stocks);
	Welcome(stocks);

}