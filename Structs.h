#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include<iomanip>
#include<chrono>
#include<thread>
#define ComN 200				//公司数量
#define	INF 999999999
using namespace std;

/*股票详细数据*/
typedef struct detail {
	string date;				//日期
	double oprice;				//开盘价
	double cprice;				//收盘价
	double maxprice;			//最高价
	double minprice;			//最低价
	double volume;				//成交量
	double turnover;			//成交额
	string rate;				//换手率
	double iodamount;			//涨跌额
	string iodrate;				//涨跌幅
	struct detail* next;
}detail, * det;

typedef struct {
	int value[61][61];
}MGraph;

typedef struct {
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
	det details;				//详细信息_最近日期
	string score;				//股票评分
	int point;					//点
	//MGraph floyd;				
}stock;



typedef struct lnode {
	detail details;
	string stock_num;
	string stock_name;
	struct lnode* next;
}*linklist,lnode;

typedef struct LNode {
	stock data;
	struct LNode* next;
}*LinkList, LNode;

typedef struct BSTNode {
	stock data;									//存储的数据类型
	struct BSTNode* lchild, * rchild;			//左右孩子指针
}BSTNode, * BSTree;

struct QueueSq {
	int* queue1;
	int  front1;
	int  rear;
	int MaxSize;
};