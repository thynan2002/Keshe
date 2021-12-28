#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include<iomanip>
#include<chrono>
#include<thread>
#define ComN 200				//��˾����
#define	INF 999999999
using namespace std;

/*��Ʊ��ϸ����*/
typedef struct detail {
	string date;				//����
	double oprice;				//���̼�
	double cprice;				//���̼�
	double maxprice;			//��߼�
	double minprice;			//��ͼ�
	double volume;				//�ɽ���
	double turnover;			//�ɽ���
	string rate;				//������
	double iodamount;			//�ǵ���
	string iodrate;				//�ǵ���
	struct detail* next;
}detail, * det;

typedef struct {
	int value[61][61];
}MGraph;

typedef struct {
	string StockNum;			//��Ʊ����
	string StockName;			//��Ʊ���
	string StockCode;			//��ҵ����
	string _1Kind;				//һ������
	string _2Kind;				//��������
	string StockLE;				//���н����� Listed Exchange
	string StockWN;				//��˾ȫ�� Whole Name
	string StockTime;			//����ʱ��
	string StockProv;			//ʡ��
	string StockCity;			//����
	string StockLP;				//���� Legal Person
	string StockAddr;			//��ַ
	string StockWeb;			//��ַ
	string StockEmail;			//����
	string StockTel;			//�绰
	string StockMB;				//��Ӫҵ�� Main Business
	string StockBS;				//��Ӫ��Χ Business Scope
	det details;				//��ϸ��Ϣ_�������
	string score;				//��Ʊ����
	int point;					//��
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
	stock data;									//�洢����������
	struct BSTNode* lchild, * rchild;			//���Һ���ָ��
}BSTNode, * BSTree;

struct QueueSq {
	int* queue1;
	int  front1;
	int  rear;
	int MaxSize;
};