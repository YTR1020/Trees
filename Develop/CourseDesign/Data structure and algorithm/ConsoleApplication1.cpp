//家谱管理系统

#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<malloc.h>
#pragma warning(disable:4996)
using namespace std;


//结构体-日期-年月日
typedef struct DATA
{
	int year;
	int month;
	int day;
}DATA;

//结构体-成员信息数据域
typedef struct PeopleInfo
{
	int seniority;  //辈分数 第几世
	int sex;  //性别 1为男性,0为女性
	int isalive;  //目前状况 1为健在,0为身故
	int age;  //年龄
	char name[100];  //姓名
	char fedname[100];  //配偶姓名
	DATA birth_data;  //结构Data定义的出生日期

}PeopleInfo;

//结构体-孩子兄弟树结点
typedef struct CSTNode
{
	PeopleInfo people_data;  //该结点的数据域
	struct CSTNode* first_Child, * next_brother, * father;
	//第一个孩子指针，下一个兄弟指针，父亲指针
}CSTNode, * CSTree, * CSForest;  //树结点，树指针，森林指针

//结构体-队列链表结点
typedef struct LNode
{
	CSTree tree_data;  //链表结点数据域
	struct LNode* next;  //指向下一个的指针域
}LNode, * LinkList;  //链表结点，链表指针

//结构体-枚举类型返回值
typedef enum status
{
	TRUE,  //1
	FALSE,  //0
	OK,  //1
	ERROR,  //0
	SUCCESS,  //0
	//OVERFLOW,  //-2
	EMPTY  //空或0返回1，非空返回0
}Status;


//全局变量
CSForest T;  //根结点指针  
CSTree A, B;  //记录search函数返回值的指针
fstream file("c:\\Users\\youye\\Desktop\\lastFamily.txt", ios::out);  //清空txt文件
fstream in("c:\\Users\\youye\\Desktop\\lastFamily.txt");  //打开txt文件


//基本树操作模块函数声明
void InitCSTNode(CSTree& A);  //初始化结点数据函数,避免出现野指针
void CreateCSTNode(CSTree& A);  //创建结点函数
void Destroy(CSTree A);  //销毁树函数
void DeleteNode(CSTree A);  //删除结点函数
void InsertNode(CSTree& father, CSTree child);  //插入结点函数
void SearchNode(CSForest T, char name[100], CSTree& B);  //查找函数
void ShowPeopleInfo(CSTree A);  //展示成员信息数据域函数
void ChangePeopleInfo(CSTree& B, CSForest T);  //修改成员信息数据域函数
void ChangeBirth(CSTree& A);  //修改成员生日函数
void ChangeFather(CSTree& A, CSForest T);  //修改成员父亲函数
void RefreshSeniority(CSForest& T);  //辈分刷新函数
void InorderCousin(CSTree T, CSTree A);  //输出所有堂兄弟函数
void InorderBro(CSTree T, CSTree A);  //输出所有同世代的兄弟
void PrintASTree(CSTree T);  //凹入表输出家谱函数

Status PrintTree(CSTree t);  //层次遍历输出函数
Status InitQueue(LinkList& L);  //初始化队列
LNode* CreateLNode(CSTNode* p);  //新建结点
Status Enqueue(LNode* p, CSTNode* q);  //元素q入队列
Status Dequeue(LNode* p, CSTNode* q);  //出队列，并保存q返回值
Status IfEmpty(LinkList L);  //队列判空
void DestroyQueue(LinkList L);  //销毁队列
Status Traverse(CSTree T, LinkList L);  //用队列遍历输出CSTree


//主程序代码实现模块函数声明
void Init();  //初始化函数，从文件中读取信息自动生成孩子兄弟二叉树
void welcome();  //主菜单函数
void InsertNew();  //插入新人物函数
void Delete();  //删除人物函数
void Change();  //修改人物信息函数
void Search();  //查找人物函数
void Relationship();  //人物关系查询函数
void Save(CSTree T);  //退出菜单保存修改后的文件,凹入表保存家谱



int main()
{
	system("title FamilyTree Management System");  //标题
	Init();  //初始化,读取文件创建树
	welcome();  //主菜单
	system("pause");
}





//基本树操作模块函数声明

//初始化结点函数,避免出现野指针，参数为树结点指针
void InitCSTNode(CSTree& A)
{
	if (A == NULL)
		return;
	A->father = NULL;
	A->first_Child = NULL;
	A->next_brother = NULL;
	A->people_data.seniority = 0;
	A->people_data.sex = 0;
	A->people_data.isalive = 0;
	A->people_data.age = 0;
	A->people_data.birth_data.year = 0;
	A->people_data.birth_data.month = 0;
	A->people_data.birth_data.day = 0;
	strcpy(A->people_data.name, "无");
	strcpy(A->people_data.fedname, "无");
	return;
}

//创建结点函数，参数为树结点指针
void CreateCSTNode(CSTree& A)
{
	A = new CSTNode;  //分配内存空间
	//(*A)=(CSTree)malloc(sizeof(CSTNode));
	if (A == NULL)
		return;
	InitCSTNode(A);  //初始化结点
}

//销毁树函数(同二叉树一样，递归)，参数为树结点指针
void Destroy(CSTree A)
{
	if (A == NULL)
		return;
	Destroy(A->first_Child);
	Destroy(A->next_brother);
	delete A;
}

//删除结点函数，参数为树结点指针
void DeleteNode(CSTree A)
{
	CSTree prebro;

	//如果A是父亲结点的第一个孩子，则让A的兄弟成为父亲结点的第一个孩子
	if (A->father->first_Child == A)
	{
		A->father->first_Child = A->next_brother;
	}
	else  //A不是父亲结点的第一个孩子，让A的前一个兄弟指向A的下一个兄弟
	{
		//把A的前一个兄弟赋值给prebro
		for (prebro = A->father->first_Child; prebro->next_brother != A;)
		{
			prebro = prebro->next_brother;
		}
		prebro->next_brother = A->next_brother;
	}
	A->next_brother = NULL;  //释放A指向下一个兄弟的指针域
	A->father = NULL;  //释放A指向父亲的指针域
	system("pause");
	Destroy(A);  //将A的后代全部移除，释放A的空间
}

//插入结点函数，参数为父亲结点指针和孩子结点指针
void InsertNode(CSTree& father, CSTree child)
{
	child->people_data.seniority = father->people_data.seniority + 1;  //孩子的代数比父亲大一
	child->father = father;  //配置插入孩子的父亲指针
	int birth = (child->people_data.birth_data.year) * 10000 + (child->people_data.birth_data.month) * 100 + (child->people_data.birth_data.day);
	CSTree bro1 = father->first_Child;

	//如果father没有first_Child，直接插入child
	if (bro1 == NULL)
	{
		father->first_Child = child;
		return;
	}

	int bro1birth = (bro1->people_data.birth_data.year) * 10000 + (bro1->people_data.birth_data.month) * 100 + (bro1->people_data.birth_data.day);
	//如果插入孩子的生日早于父亲的第一个孩子，那么插入孩子成为新first_Child
	if (bro1birth >= birth)
	{
		child->next_brother = bro1;
		father->first_Child = child;
		return;
	}

	//如果插入孩子生日晚于父亲第一个孩子，那么遍历兄弟链表找到插入位置
	CSTree bro2 = father->first_Child;
	int bro2birth = (bro2->people_data.birth_data.year) * 10000 + (bro2->people_data.birth_data.month) * 100 + (bro2->people_data.birth_data.day);
	bro1 = bro2->next_brother;
	//找到bro2生日早于child生日早于bro1生日的位置
	for (; (bro1 != NULL) && (birth > bro1birth);)
	{
		bro2 = bro2->next_brother;
		bro1 = bro2->next_brother;
	}
	child->next_brother = bro1;
	bro2->next_brother = child;

	return;
}

//先序遍历查找函数，T为树的根结点，name为需要找的人，B储存找到的结点位置
void SearchNode(CSForest T, char name[100], CSTree& B)
{
	if (T == NULL)
		return;
	if (strcmp(T->people_data.name, name) == 0)  //如果T的name与查找目标相同
	{
		B = T;
		return;
	}
	SearchNode(T->first_Child, name, B);
	if (B != NULL)
		return;
	SearchNode(T->next_brother, name, B);
}

//展示成员信息数据域函数
void ShowPeopleInfo(CSTree A)
{
	if (A == NULL)
		return;
	if (A->people_data.seniority == 0)  //A的辈分为0，是根结点
	{
		cout << "该结点为森林根结点，禁止操作！\n";
		system("pause");
		return;
	}
	cout << "姓名：" << A->people_data.name << "  ";
	if (A)
		cout << "性别：男  ";
	else
		cout << "性别：女  ";
	cout << "配偶姓名：" << A->people_data.fedname << "  ";
	cout << "辈分：" << A->people_data.seniority << "  ";
	cout << "第" << (A->people_data.seniority) + 12 << "世  ";
	cout << "生日：" << A->people_data.birth_data.year << "." << A->people_data.birth_data.month << "." << A->people_data.birth_data.day << "  ";
	if (A->people_data.isalive == 1)
		cout << "目前状况：健在  ";
	else
		cout << "目前状况：身故  ";

	if (A->people_data.seniority != 1)
		cout << "父亲姓名：" << A->father->people_data.name << "  ";
	else
		cout << "为家族祖先" << endl;

	cout << endl;

}

//修改成员信息数据域函数，B为欲修改的结点，T为根结点
void ChangePeopleInfo(CSTree& B, CSForest T)
{
	if (B == NULL)
		return;
	if (B->people_data.seniority == 0)  //B的辈分为0，是根结点
	{
		cout << "该结点为森林根结点，禁止操作！\n";
		system("pause");
		return;
	}
	int choice;
W:system("cls");
	ShowPeopleInfo(B);  //列出B结点当前具体信息
	cout << endl;
	cout << "请选择想要修改的信息序号：" << endl << endl;
	cout << "*************************" << endl << endl;
	cout << "    1.name" << endl;
	cout << "    2.sex" << endl;
	cout << "    3.fedname" << endl;
	cout << "    4.birth" << endl;
	cout << "    5.father" << endl;
	cout << "    6.isalive" << endl;
	cout << "    7.break" << endl << endl;
	cout << "*************************" << endl << endl;
	cout << "请输入序号：";
	//fflush(stdin); //cin.clear;
	cin >> choice;

	switch (choice)
	{
	case 1:  //修改name
		cout << "请输入新的姓名：";
		char name[100];
		cin >> name;
		strcpy(B->people_data.name, name);
		system("pause");
		goto W;
	case 2:  //修改sex
		cout << "你的性别为：（男性请输入1，女性请输入2）";
		int sex;
		cin >> sex;
		if ((sex != 2) && (sex != 1))
		{
			cout << "输入有误" << endl;
			system("pause");
			goto W;
		}
		B->people_data.sex = sex;
		system("pause");
		goto W;
	case 3:  //修改fedname
		cout << "请输入其配偶的新姓名：";
		char fedname[100];
		cin >> fedname;
		strcpy(B->people_data.fedname, fedname);
		system("pause");
		goto W;
	case 4:  //修改birth
		ChangeBirth(B);  //修改成员生日函数
		system("pause");
		goto W;
	case 5:  //修改father
		ChangeFather(B, T);  //修改成员父亲函数
		system("pause");
		goto W;
	case 6:  //修改isalive
		if (B->people_data.isalive)
			B->people_data.isalive = 0;
		else
			B->people_data.isalive = 1;
		system("pause");
		goto W;
	case 7:  //结束修改成员信息模块
		Save(T);
		break;
	default:
		goto W;
	}

	return;

}

//修改成员生日函数
void ChangeBirth(CSTree& A)
{
	cout << "生日修改为：（输入格式：代表年份的四位整数 代表月份的1-12整数 代表日期的0-31整数）";
	int year, month, day;
	cin >> year >> month >> day;
	if ((year < 1) || (year > 10000) || (month < 1) || (month > 12) || (day < 1) || (day > 31))
	{
		cout << "输入有误" << endl;
		system("pause");
		return;
	}
	int Abirth = year * 10000 + month * 100 + day;
	int fatherbirth = (A->father->people_data.birth_data.year) * 10000 + (A->father->people_data.birth_data.month) * 100 + (A->father->people_data.birth_data.day);
	//如果A的父亲存在且A的父亲的生日晚于A
	if ((A->father->people_data.seniority != 0) && (fatherbirth >= Abirth))
	{
		cout << "生日不能比父亲早" << endl;
		return;
	}
	A->people_data.birth_data.year = year;
	A->people_data.birth_data.month = month;
	A->people_data.birth_data.day = day;

	CSTree B;
	CSTree C;
	C = A->father;
	//修改生日后需要重新排序兄弟结点，可先把该结点分离出来
	if (A->father->first_Child == A)
	{
		A->father->first_Child = A->next_brother;
		A->next_brother = NULL;
		A->father = NULL;
	}
	else
	{
		for (B = A->father->first_Child; B->next_brother != A; B = B->next_brother);
		B->next_brother = A->next_brother;
		A->next_brother = NULL;
		A->father = NULL;
	}
	//再调用含自动排序功能的InsertNode函数插入回二叉树内
	InsertNode(C, A);
}

//修改成员父亲函数
void ChangeFather(CSTree& A, CSForest T)
{
	cout << "父亲修改为：" << endl;
	int Abirth = (A->people_data.birth_data.year) * 10000 + (A->people_data.birth_data.month) * 100 + (A->people_data.birth_data.day);
	char fathername[100];
	cin >> fathername;

	//调用SearchNode函数找到新的父亲结点
	CSTree newfather = NULL;
	SearchNode(T, fathername, newfather);
	ShowPeopleInfo(newfather);  //显示新父亲结点的详细信息

	//查看新父亲结点是否存在
	if (newfather == NULL)
	{
		cout << "该成员不存在" << endl;
		system("pause");
		return;
	}
	system("pause");

	//查看新父亲结点生日是否早于孩子
	int fatherbirth = (newfather->people_data.birth_data.year) * 10000 + (newfather->people_data.birth_data.month) * 100 + (newfather->people_data.birth_data.day);
	if ((newfather->people_data.seniority != 0) && (fatherbirth >= Abirth))
	{
		cout << "生日不能早于父亲" << endl;
		return;
	}

	//将欲修改的A结点分离出来插入到新父亲结点下
	CSTree B;
	CSTree C;
	C = A->father;
	if (A->father->first_Child == A)
	{
		A->father->first_Child = A->next_brother;
		A->next_brother = NULL;
		A->father = NULL;
	}
	else
	{
		B = A->father->first_Child;
		for (; B->next_brother != A; B = B->next_brother);
		B->next_brother = A->next_brother;
		A->next_brother = NULL;
		A->father = NULL;
	}

	InsertNode(newfather, A);  //将A结点插入新父亲结点下
	RefreshSeniority(T);  //刷新辈分
}

//辈分刷新函数，利用先序遍历思想递归
void RefreshSeniority(CSForest& T)
{
	if (T == NULL)
		return;
	if (T->father == NULL)
		T->people_data.seniority = 0;
	else
	{
		T->people_data.seniority = T->father->people_data.seniority + 1;
	}
	RefreshSeniority(T->first_Child);
	RefreshSeniority(T->next_brother);
	return;
}

//输出所有堂兄堂弟
void InorderCousin(CSTree T, CSTree A)
{
	if (T == NULL)
		return;
	//从根结点开始遍历，如果找到与A结点父亲的父亲相同，即与A互为堂兄弟，输出
	if (T->people_data.seniority >= 3)
		if ((T->father->father == A->father->father) && (T != A))
			cout << "[" << T->people_data.seniority << "][第" << T->people_data.seniority + 12 << "世][" << T->people_data.birth_data.year << "." << T->people_data.birth_data.month << "." << T->people_data.birth_data.day << "]" << T->people_data.name << endl;
	InorderCousin(T->first_Child, A);
	InorderCousin(T->next_brother, A);
}

//输出所有同世代的兄弟
void InorderBro(CSTree T, CSTree A)
{
	if (T == NULL)
		return;
	//从根结点开始遍历，找到与A结点辈数相同的兄弟输出
	if (T->people_data.seniority >= 2)
		if ((T->people_data.seniority == A->people_data.seniority) && (T != A))
			cout << "[" << T->people_data.seniority << "][第" << T->people_data.seniority + 12 << "世][" << T->people_data.birth_data.year << "." << T->people_data.birth_data.month << "." << T->people_data.birth_data.day << "]" << T->people_data.name << endl;
	InorderBro(T->first_Child, A);
	InorderBro(T->next_brother, A);
}



//凹入表输出家谱，先根遍历（即二叉树存储的先序遍历）
void PrintASTree(CSTree T)
{
	int cnt;
	if (T)
	{
		//输出空格
		for (cnt = 1; cnt < T->people_data.seniority; cnt++)
			cout << "    ";
		//输出字符
		cout << "[" << T->people_data.seniority << "][第" << T->people_data.seniority + 12 << "世][" << T->people_data.birth_data.year << "." << T->people_data.birth_data.month << "." << T->people_data.birth_data.day << "]" << T->people_data.name << endl;
		cout << endl;
		PrintASTree(T->first_Child);
		PrintASTree(T->next_brother);
	}
}



//关于队列

//层次遍历输出函数
Status PrintTree(CSTree t)
{
	LinkList L;
	if (t == NULL)
	{
		cout << "森林不存在" << endl;
		return OK;
	}
	InitQueue(L);  //初始化队列
	Traverse(t->first_Child, L);  //利用队列输出
	DestroyQueue(L);  //销毁队列
	return OK;
}


//队列相关操作

//初始化队列
Status InitQueue(LinkList& L)
{
	L = new LNode;  //分配结点空间
	if (L == NULL)  //分配失败
	{
		return ERROR;
	}
	L->next = NULL;
	return OK;
}

//新建结点
LNode* CreateLNode(CSTNode* p)
{
	LNode* q;
	q = new LNode;  //分配结点空间
	if (q != NULL)  //分配成功
	{
		q->tree_data = p;
		q->next = NULL;
	}
	return q;
}

//元素q入队列
Status Enqueue(LNode* p, CSTNode* q)
{
	if (p == NULL)
		return ERROR;
	while (p->next != NULL)  //调至队列最后
		p = p->next;
	p->next = CreateLNode(q);  //生成q的队列结点让q进入队列
	return OK;
}

//出队列，并保存q返回值
Status Dequeue(LNode* p, CSTNode* q)
{
	LNode* aq;
	if (p == NULL || p->next == NULL)  //出队列的位置不合理
		return ERROR;
	aq = p->next;  //修改被出队结点aq的指针域
	p->next = aq->next;  //让p的下一个指针域指向p->next->next
	q = aq->tree_data;  //用q保存出队aq的数据域
	delete aq;  //释放结点aq
	return OK;
}

//队列判空
Status IfEmpty(LinkList L)
{
	if (L == NULL)  //队列不存在
		return ERROR;
	if (L->next == NULL)  //队列为空
		return TRUE;
	return FALSE;  //队列非空
}

//销毁队列
void DestroyQueue(LinkList L)
{
	LinkList p;
	if (L != NULL)
	{
		p = L;
		L = L->next;
		delete p;  //逐一释放
		DestroyQueue(L);  //递归销毁
	}
}

//用队列遍历输出CSTree
Status Traverse(CSTree T, LinkList L)
{
	CSTree P = T;
	CSTree K;
	int i = 0;
	int j = 1;
	while (P)  //p指向森林里的每棵树
	{
		cout << "第" << j << "个家庭" << endl;
		K = P;  //利用K来遍历以P为根结点的子树中的结点
		Enqueue(L, K);  //根结点入队
		while (IfEmpty(L) == FALSE)  //只要队列不为空就依次出队直到队空
		{
			Dequeue(L, K);
			if (i != K->people_data.seniority)  //将K的辈数赋给i
			{
				cout << endl;
				i = K->people_data.seniority;
			}
			cout << "[" << K->people_data.seniority << "][第" << K->people_data.seniority + 12 << "世][" << K->people_data.birth_data.year << "." << K->people_data.birth_data.month << "." << K->people_data.birth_data.day << "]" << K->people_data.name << endl;

			if (K->first_Child)  //如果该结点不是森林中的叶节点则进入下一层即孩子层
			{
				K = K->first_Child;
				Enqueue(L, K);
				while (K->next_brother)  //入队同一层的兄弟结点
				{
					K = K->next_brother;
					Enqueue(L, K);
				}
			}

		}
		P = P->next_brother;  //递归
		cout << endl;
		j++;
	}
	return OK;
}





//主程序代码实现模块函数

//初始化函数，从文件中读取信息自动生成孩子兄弟二叉树
void Init()
{
	CreateCSTNode(T);  //创建根结点并初始化，此时T的name为“无”

	FILE* r;
	r = fopen("C:\\Users\\youye\\Desktop\\Family.txt", "r");  //打开文件夹
	if (r == NULL)
	{
		cout << "打开文件失败！" << endl;
	}

	A = NULL;
	B = NULL;
	char FatherName[100], tmp1[2], tmp2[2];

	CreateCSTNode(A);  //创建A临时结点

	cout << "读取文件中..." << endl;

	//读取文件直到循环结束
	while (fscanf(r, "%s %d %s %d%s%d%s%d %d %s", &A->people_data.name, &A->people_data.sex, &A->people_data.fedname, &A->people_data.birth_data.year, tmp1, &A->people_data.birth_data.month, tmp2, &A->people_data.birth_data.day, &A->people_data.isalive, FatherName) != EOF)
	{
		cout << A->people_data.name << "	" << A->people_data.sex << "	" << A->people_data.fedname << "	" << A->people_data.birth_data.year << tmp1 << A->people_data.birth_data.month << tmp2 << A->people_data.birth_data.day << "	" << A->people_data.isalive << "	" << FatherName;
		cout << endl << "Search..." << endl;
		SearchNode(T, FatherName, B);  //查找FatherName的结点储存到B临时父亲结点中
		//如果父亲结点存在就将A孩子结点插入其下，如果父亲结点为无就作为根结点的子节点存在

		if (B == NULL)
		{
			cout << "此人的父亲不在家谱里！" << endl;
			delete A;
		}
		int Abirth = (A->people_data.birth_data.year) * 10000 + (A->people_data.birth_data.month) * 100 + (A->people_data.birth_data.day);
		int Bbirth = (B->people_data.birth_data.year) * 10000 + (B->people_data.birth_data.month) * 100 + (B->people_data.birth_data.day);
		//如果B作为临时父亲结点存在且不是根结点且生日晚于A
		if ((B->people_data.seniority != 0) && (Bbirth >= Abirth))
		{
			cout << "孩子生日不能比父亲早" << endl;
			delete A;
		}
		else
		{
			cout << "Insert..." << endl;
			InsertNode(B, A);  //存在父亲结点，将A插入父亲结点下
		}

		B = NULL;
		A = NULL;
		CreateCSTNode(A);  //继续循环
	}
	delete A;
	A = NULL;
	fclose(r);
}


//主菜单函数
void welcome()
{
	int choice;
	system("pause");
Q:system("cls");  //清屏
	cout << "                 主菜单" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "	1.插入新人物" << endl << endl;
	cout << "	2.删除人物" << endl << endl;
	cout << "	3.修改人物信息" << endl << endl;
	cout << "	4.查找人物" << endl << endl;
	cout << "	5.人物关系查询" << endl << endl;
	cout << "	6.凹入表方式打印树状家谱" << endl << endl;
	cout << "	7.退出菜单并保存家谱" << endl << endl;
	cout << "*******************************************" << endl;
	cout << "-------------------------------------------" << endl << endl;
	cout << "请输入序号：";
	fflush(stdin);
	cin >> choice;

	switch (choice)
	{
	case 1:  //插入新人物
		InsertNew();
		system("pause");
		goto Q;  //从A处继续循环
	case 2:  //删除人物
		Delete();
		system("pause");
		goto Q;
	case 3:  //修改人物信息
		Change();
		system("pause");
		goto Q;
	case 4:  //查找人物
		Search();
		system("pause");
		goto Q;
	case 5:  //人物关系查询
		Relationship();
		system("pause");
		goto Q;
	case 6:  //凹入表方式打印树状家谱
		PrintASTree(T);
		system("pause");
		goto Q;
	case 7:  //退出菜单并保存家谱
		Save(T);
		cout << "已保存到c:\\Users\\youye\\Desktop\\lastFamily.txt" << endl;
		break;
	default:
		goto Q;
	}
	return;
}


//插入新人物函数
void InsertNew()
{
	char FatherName[100];
	A = NULL;  //使全局变量A和B都为空
	B = NULL;
	CreateCSTNode(A);  //创建临时结点A
	cout << "请输入：姓名		性别（男为1/女为2）	配偶姓名 	出生日期 	状态（健在为1/身故为0）	父亲姓名" << endl;
	cout << "例如：张三    1    无    2002 01 01    1    张大" << endl;
	cin >> A->people_data.name >> A->people_data.sex >> A->people_data.fedname >> A->people_data.birth_data.year >> A->people_data.birth_data.month >> A->people_data.birth_data.day >> A->people_data.isalive >> FatherName;
	cout << A->people_data.name << "	" << A->people_data.sex << "	" << A->people_data.fedname << "	" << A->people_data.birth_data.year << "." << A->people_data.birth_data.month << "." << A->people_data.birth_data.day << "    " << A->people_data.isalive << "    " << FatherName << endl;

	if ((A->people_data.sex != 1) && (A->people_data.sex != 0))
	{
		cout << "性别输入有误！" << endl;
		delete A;
		A = NULL;
		return;
	}
	if ((A->people_data.isalive != 1) && (A->people_data.isalive != 0))
	{
		cout << "状态输入有误！" << endl;
		delete A;
		A = NULL;
		return;
	}

	SearchNode(T, FatherName, B);  //查找A的父亲结点并赋值到B结点中
	if (B == NULL)
	{
		cout << "此人的父亲不在家谱里！" << endl;
		delete A;
		A = NULL;
		return;
	}
	int Abirth = (A->people_data.birth_data.year) * 10000 + (A->people_data.birth_data.month) * 100 + (A->people_data.birth_data.day);
	int Bbirth = (B->people_data.birth_data.year) * 10000 + (B->people_data.birth_data.month) * 100 + (B->people_data.birth_data.day);
	//如果B作为临时父亲结点存在且不是根结点且生日晚于A
	if ((B->people_data.seniority != 0) && (Bbirth >= Abirth))
	{
		cout << "孩子生日不能比父亲早" << endl;
		delete A;
		A = NULL;
		B = NULL;
		return;
	}

	InsertNode(B, A);  //在父亲结点下插入A
	cout << "插入成功！" << endl;
	A = NULL;  //令全局变量A恢复为空
	return;
}


//删除人物函数
void Delete()
{
	A = NULL;  //全局变量A为空
	char name[100];
	cout << "请输入要删除的人物姓名：";
	cin >> name;
	cout << endl;
	SearchNode(T, name, A);  //根据名字查找目标并存到A结点中
	if (A == NULL)
	{
		cout << "不存在姓名为" << name << "的人";
		return;
	}
	if (A->first_Child != NULL)
	{
		cout << "此人有后代，不允许删除！";
		return;
	}
	DeleteNode(A);
	cout << "删除成功！" << endl;
	A = NULL;
}


//修改人物信息
void Change()
{
	A = NULL;
	char name[100];
	cout << "请输入要修改信息的人物姓名：";
	cin >> name;
	SearchNode(T, name, A);  //根据名字查找目标并存在A结点中
	if (A == NULL)
	{
		cout << "不存在名字为" << name << "的人" << endl;
		return;
	}
	ChangePeopleInfo(A, T);  //进入修改信息界面
	A = NULL;  //令全局变量A为空
}


//查找人物
void Search()
{
	A = NULL;
	char name[100];
	cout << "请输入要查找的人物姓名：";
	cin >> name;
	SearchNode(T, name, A);  //根据名字查找目标并存在A结点中
	if (A == NULL)
	{
		cout << "不存在名字为" << name << "的人" << endl;
		return;
	}
	ShowPeopleInfo(A);  //列出目标信息
	A = NULL;  //令全局变量A为空
}


//人物关系查询
void Relationship()
{
	A = NULL;
	B = NULL;  //令全局变量都为NULL
	char name[100];
	cout << "请输入需要查询关系的人物姓名：";
	cin >> name;
	SearchNode(T, name, B);  //查询目标并将其保存到B结点中
	if (B == NULL)
	{
		cout << "不存在名字为" << name << "的人" << endl;
		return;
	}

	int choice;
C:system("cls");  //清屏
	ShowPeopleInfo(B);  //列出目标人物的具体信息
	cout << endl;

	cout << "			人物关系查询菜单" << endl << endl;
	cout << "*******************************************" << endl << endl;
	cout << "	1.祖先" << endl;
	cout << "	2.堂兄弟" << endl;
	cout << "	3.同世代的兄弟" << endl;
	cout << "	4.后代" << endl;
	cout << "	5.break" << endl << endl;
	cout << "*******************************************" << endl << endl;
	cout << "请输入序号：";
	cin >> choice;

	switch (choice)
	{
	case 1:  //查询祖先
		A = B->father;
		//只要A不等于根结点，遍历A的父亲
		for (; A->people_data.seniority != 0; A = A->father)
		{
			cout << "[" << A->people_data.seniority << "][第" << A->people_data.seniority + 12 << "世][" << A->people_data.birth_data.year << "." << A->people_data.birth_data.month << "." << A->people_data.birth_data.day << "]" << A->people_data.name << endl;
		}
		system("pause");
		goto C;  //返回查询菜单继续循环
	case 2:  //查询堂兄弟
		InorderCousin(T, B);
		system("pause");
		goto C;
	case 3:  //查询同世代的兄弟  
		InorderBro(T, B);
		system("pause");
		goto C;
	case 4:  //查询后代关系
		PrintTree(B);  //层次遍历
		system("pause");
		goto C;
	case 5:  //退出查询菜单
		break;
	default:
		goto C;
	}
	B = NULL;
	A = NULL;
	return;
}


//退出菜单保存修改后的文件,凹入表保存家谱
void Save(CSTree T)
{
	int cnt;
	if (T)
	{
		//输出空格
		for (cnt = 1; cnt < T->people_data.seniority; cnt++)
			in << "    ";
		//输出字符
		in << "[" << T->people_data.seniority << "][第" << T->people_data.seniority + 12 << "世][" << T->people_data.birth_data.year << "." << T->people_data.birth_data.month << "." << T->people_data.birth_data.day << "]" << T->people_data.name << endl;
		in << endl;
		Save(T->first_Child);
		Save(T->next_brother);
	}
}