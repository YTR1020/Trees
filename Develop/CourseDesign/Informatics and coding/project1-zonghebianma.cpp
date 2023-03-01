//综合编码与译码1
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cctype>
#include<algorithm>
#include<cmath>
#include<vector>
#include<ctime>

#pragma warning(disable:4996)
#define N 200
#define M 2*N-1

#define TOLOWER(p) {transform(p.begin(),p.end(),p.begin(),::tolower);}

typedef char* HuffmanCode[2 * M];     //huffman编码

//typedef long long LL;
using namespace std;

char x[1024];     //游程编码
char y[1024];     //huffman编码


fstream in("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/in3.txt");
fstream out("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/out3.txt");

void Runlength_encode(char a[1024]);     //游程编码函数
void Runlength_decode(char a[1024]);     //游程译码函数
void Huffman_encode(char* ch);     //Huffman编码函数
void Huffman_decode();     //Huffman译码函数
int canshu(int k, int b);     //判断仿射加密参数是否合法
string FSjiami(string str, int k, int b);     //仿射加密函数
string FSjiemi(string pass, int k, int b);     //仿射解密函数
void create_G();     //初始化标准生成矩阵
void create_S();     //初始化译码表
int bin_to_deci(string inin);     //二进制转十进制
string deciToBin_8bit(int deci);     //十进制转八位二进制
void string_to_ascii(string info, string a[]);     //转换成ASCII码串
string channel_encode(string infomation);     //信道编码
string channel_decode(string infomation);     //信道译码
string BSC(string infomation);     //模拟BSC信道传输


int main()
{
	const char lim = '#';
	char s1[1024];

	int k, b;     //加密算法的参数
	cout << "请输入加密算法的参数(k,b)：";
	cin >> k >> b;
	while (!canshu(k, b))
	{
		cout << "参数不合法（参数k应该与mod·26互为素数），请重新输入：";
		cin >> k >> b;
	}


	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}

	while (!in.eof())
	{
		in.getline(s1, 1024, lim);
		if (s1[0] == '\0' || s1[0] == '\n')
			break;
		cout << "信源的符号序列：" << s1 << endl;
		out << "信源的符号序列：" << s1 << endl << endl;
		cout << endl;

		for (int q = 0; q < 1024; q++)
		{
			x[q] = '\0';
			y[q] = '\0';
		}

		Runlength_encode(s1);
		//对s1进行游程编码得到x字符串数组
		cout << endl;
		out << endl;

		Huffman_encode(x);
		//对x进行Huffman编码得到y字符串数组
		cout << endl;
		out << endl;


		string jiami1;     //加密输出密文（ASCII码串）
		jiami1 = FSjiami(y, k, b);
		cout << "仿射加密后：" << jiami1 << endl;
		out << "仿射加密后：" << jiami1 << endl;
		cout << endl;
		out << endl;

		create_G();     //生成矩阵
		create_S();     //生成译码表
		int lenth = jiami1.length();
		string* a = new string[lenth];     //存储密文的ASCII码串
		string* output = new string[lenth];     //存储信道编码过程的串
		string_to_ascii(jiami1, a);     //密文转化为ASCII码串
		string  output1 = "";     //存储信道译码后的ASCII码串密文

		cout << "信道编码：";
		out << "信道编码：";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_encode(a[i]);     //信道编码
			cout << output[i];
			out << output[i];
		}
		cout << endl << endl;
		out << endl << endl;

		cout << "模拟传递串：";
		out << "模拟传递串：";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = BSC(output[i]);     //信道传输
			cout << output[i];
			out << output[i];
		}
		cout << endl << endl;
		out << endl << endl;

		cout << "信道译码：";
		out << "信道译码：";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_decode(output[i]);     //信道译码
			cout << output[i];
			out << output[i];
			int f = 0;
			f = bin_to_deci(output[i]);//将二进制转成十进制
			output1 += (char)f;//变成ASCII码对应的字符，即加密后的密文

		}
		cout << endl << endl;
		out << endl << endl;

		//仿射解密后的字符串
		string jiemi1 = FSjiemi(output1, k, b);
		cout << "仿射解密后：" << jiemi1 << endl;
		out << "仿射解密后：" << jiemi1 << endl;
		cout << endl;
		out << endl;

		//Huffman译码
		Huffman_decode();
		cout << endl;
		out << endl;

		//游程译码
		Runlength_decode(x);
		//对x进行游程译码
		cout << endl;
		out << endl;

	}
	in.close();
	out.close();
	return 0;

}

//游程编码
void Runlength_encode(char a[1024])
{
	char yc[1024];
	int i = 0, j = 0, count = 1;
	yc[0] = a[0];     //游程编码第一个字符为字符串第一个字符
	for (i = 0; a[i] != '\0'; i++)     //遍历字符串
	{
		if (a[i] == a[i + 1])     //统计相同字符数量
			count++;
		else
		{
			yc[j + 1] = count + 48;     //ASCII码把int转换成字符char
			j = j + 2;
			yc[j] = a[i + 1];
			count = 1;
		}
	}
	yc[j] = '\0';
	cout << "游程编码后：" << yc << endl;
	out << "游程编码后：" << yc << endl;
	strcpy_s(x, yc);
}

//游程译码
void Runlength_decode(char a[1024])
{
	char ym[1024];
	int j = 0, count, sign = 0;
	for (int i = 0; a[i] != '\0'; i = i + 2)
	{
		ym[sign] = a[i];     //第一位为标志位表示游程符号
		for (j = sign, count = 1; count <= a[i + 1] - 48; count++, j++)
			ym[j] = a[i];     //遍历相同数量的符号装入译码字符串中
		sign = j;
	}
	ym[j] = '\0';
	cout << "游程译码后：" << ym << endl;
	out << "游程译码后：" << ym << endl;
}


//Huffman树的数据结构定义
typedef struct
{
	int weight;     //权值
	int parent;     //父节节点
	int LChild;     //左子节点
	int RChild;     //右子节点
}HTNode, Huffman[M + 1];     //Huffman树

typedef struct
{
	int Weight;     //叶子结点的权值
	char c;     //叶子结点
	int num;     //叶子结点的二进制码的长度
}WNode, WeightNode[N];

//产生叶子结点的字符和权值
void CreateWeight(char ch[], int* s, WeightNode CW, int* p)
{
	int i, j, k;
	int tag;
	*p = 0;     //叶子结点个数

	//统计字符出现个数，放入CW
	for (i = 0; ch[i] != '\0'; i++)
	{
		tag = 1;
		for (j = 0; j < i; j++)
		{
			if (ch[j] == ch[i])
			{
				tag = 0;
				break;
			}
		}
		if (tag)
		{
			CW[++ * p].c = ch[i];
			CW[*p].Weight = 1;
			for (k = i + 1; ch[k] != '\0'; k++)
			{
				if (ch[i] == ch[k])
					CW[*p].Weight++;     //权值累加
			}
		}
	}
	*s = i;     //字符串长度
}

//创建Huffman树
void CreateHuffmanTree(Huffman ht, WeightNode w, int n)
{
	int i, j;
	int s1, s2;
	//初始化哈夫曼树
	for (i = 1; i <= n; i++)
	{
		ht[i].weight = w[i].Weight;
		ht[i].parent = 0;
		ht[i].LChild = 0;
		ht[i].RChild = 0;
	}
	for (i = n + 1; i <= 2 * n - 1; i++)
	{
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].LChild = 0;
		ht[i].RChild = 0;
	}
	for (i = n + 1; i <= 2 * n - 1; i++)
	{
		for (j = 1; j <= i - 1; j++)
			if (!ht[j].parent)
				break;
		s1 = j; //找到第一个双亲为零的结点
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s1 = ht[s1].weight > ht[j].weight ? j : s1;
		ht[s1].parent = i;
		ht[i].LChild = s1;

		for (j = 1; j <= i - 1; j++)
			if (!ht[j].parent)
				break;
		s2 = j; //找到第二个双亲为零的结点
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s2 = ht[s2].weight > ht[j].weight ? j : s2;
		ht[s2].parent = i;
		ht[i].RChild = s2;

		ht[i].weight = ht[s1].weight + ht[s2].weight;//权值累加
	}
}

//对叶子结点编码
void CrtHuffmanNodeCode(Huffman ht, char ch[], HuffmanCode h, WeightNode w, int m, int n)
{
	int i, c, p, start;
	char* cd;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';//置于末尾
	for (i = 1; i <= n; i++)
	{
		start = n - 1; //cd串每次从末尾开始
		c = i;
		p = ht[i].parent;//p在n+1至n-1
		while (p) //沿父亲方向遍历，直到为空
		{
			start--;//依次向前置值
			if (ht[p].LChild == c)//与左子相同,置0
				cd[start] = '0';
			else//否则置1
				cd[start] = '1';
			c = p;
			p = ht[p].parent;
		}
		w[i].num = n - start; //二进制码的长度(包含末尾)
		h[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(h[i], &cd[start]);//将二进制字符串拷贝到指针数组h中
	}
	free(cd);//释放cd内存
	//system("pause");
}

//对所有字符的编码
void CrtHuffmanCode(char ch[], HuffmanCode h, HuffmanCode hc, WeightNode w, int n, int m)
{
	int i, k;
	for (i = 0; i < m; i++)
	{
		for (k = 1; k <= n; k++)      //从w[k].c中查找与ch[i]相等的下标K
			if (ch[i] == w[k].c)
				break;
		hc[i] = (char*)malloc((w[k].num) * sizeof(char));
		strcpy(hc[i], h[k]); //拷贝二进制编码
	}
}

//霍夫曼树解码
void TrsHuffmanTree(Huffman ht, WeightNode w, HuffmanCode hc, int n, int m)
{
	int i = 0, j, p;
	while (i < m)
	{
		p = 2 * n - 1;//从父亲节点向下遍历直到叶子节点
		for (j = 0; hc[i][j] != '\0'; j++)
		{
			if (hc[i][j] == '0')
				p = ht[p].LChild;
			else
				p = ht[p].RChild;
		}
		printf("%c", w[p].c); //打印原信息
		out << w[p].c;
		i++;
	}
	out << endl;
}

//当霍夫曼树使用完成之后，释放huffman编码内存
void FreeHuffmanCode(HuffmanCode h, HuffmanCode hc, int n, int m)
{
	int i;
	for (i = 1; i <= n; i++)//释放叶子结点的编码
		free(h[i]);
	for (i = 0; i < m; i++) //释放所有结点的编码
		free(hc[i]);
}

int n;     //n为叶子结点的个数
int m;     //m为字符串ch[]的长度
Huffman ht;     //Huffman二叉树
HuffmanCode h, hc;     //h存放叶子结点的编码，hc 存放所有结点的编码
WeightNode w;     //存放叶子结点的信息

//Huffman编码函数
void Huffman_encode(char* ch)
{
	n = 0;
	int i;
	m = 0;
	CreateWeight(ch, &m, w, &n);     //产生叶子结点信息w，m为字符串ch[]的长度，n为叶子结点的个数
	CreateHuffmanTree(ht, w, n);     //产生Huffman树ht
	CrtHuffmanNodeCode(ht, ch, h, w, m, n);     //叶子结点的编码h
	CrtHuffmanCode(ch, h, hc, w, n, m);     //所有字符的编码hc
	cout << "Huffman编码后：";     //打印字符串的编码
	out << "Huffman编码后：";
	int j = 0;
	for (i = 0; i < m; i++)
	{
		cout << hc[i];
		out << hc[i];
		if (y[i] == '\0')
			strcpy(&y[i], hc[i]);
		else if (y[i] != '\0')
		{
			while (y[j] != '\0')
				j++;
			strcpy(&y[j], hc[i]);
		}
	}
	cout << endl;
	out << endl;
	//system("pause");
}

//Huffman译码函数
void Huffman_decode()
{
	cout << "huffman译码后：";
	out << "huffman译码后：";
	TrsHuffmanTree(ht, w, hc, n, m);     //译码，打印w[p].c
	FreeHuffmanCode(h, hc, n, m);     //释放huffman编码内存
	cout << endl;
	out << endl;
	//system("pause");
}


//使用仿射密码进行加密解密
int canshu(int k, int b)
{
	int c = 1, t, mod = 26;    //模 26
	if (k == 1 || k % 2 == 0)
		return 0;
	if (mod < k)
	{
		t = mod;
		mod = k;
		k = t;
	}
	while (c != 0)
	{
		c = mod % k;
		mod = k;
		k = c;
	}
	if (mod == 1)
		return 1;
	else
		return 0;
}

//仿射加密
string FSjiami(string str, int k, int b)
{
	int i;
	//cout << "\n输入的需要加密的明文为:" << str << endl;
	for (i = 0; i < str.length(); i++)
	{
		int a;
		//a = (str[i] - 97) * k + b;    //加密
		a = (str[i]) * k + b;
		if (a > 25)    //对照为0-25     mod为26
		{
			do     //保证不超出域
			{
				a = a - 26;
			} while (a > 25);
			a = a + 97;        //加密后得到的ASCII码;
			str[i] = (char)a;
		}
		else
		{
			a = a + 97;
			str[i] = (char)a;
		}
	}

	return str;
}

//仿射解密
string FSjiemi(string pass, int k, int b)
{
	int i;
	for (i = 0; i < pass.length(); i++)                //解密过程
	{
		int d;
		d = (pass[i] - 97) - b;
		while (d % k != 0)
		{
			d = d + 26;
		}
		d = d / k;
		pass[i] = (char)(d + 26);
	}

	return pass;
}



//这里是标准生成矩阵，所以省略了前四列的单位阵,此矩阵4行3列
int G[4][3];

//这里是译码表，由于（7，4）系统循环码最小码距d=3，纠错能力t=1；
//故这里只有8行
string S[8][16];

//初始化标准生成矩阵
void create_G()
{
	//初始化生成矩阵，同时，生成阵的转置为监督阵
	G[0][0] = 1; G[0][1] = 0; G[0][2] = 1;     //第一行  1 0 1
	G[1][0] = 1; G[1][1] = 1; G[1][2] = 1;     //第二行  1 1 1
	G[2][0] = 1; G[2][1] = 1; G[2][2] = 0;     //第三行  1 1 0
	G[3][0] = 0; G[3][1] = 1; G[3][2] = 1;     //第四行  0 1 1
}

//初始化译码表
void create_S()
{
	//初始化译码表第一行,第一行都为需用码字
	S[0][0] = "0000000"; S[0][1] = "1111111"; S[0][2] = "0001011"; S[0][3] = "0010110";
	S[0][4] = "0101100"; S[0][5] = "1011000"; S[0][6] = "0110001"; S[0][7] = "1100010";
	S[0][8] = "1000101"; S[0][9] = "0011101"; S[0][10] = "0111010"; S[0][11] = "1110100";
	S[0][12] = "1101001"; S[0][13] = "1010011"; S[0][14] = "0100111"; S[0][15] = "1001110";
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 16; j++)     //循环生成所有可以纠错的图样
		{
			int x = 0; string s = "", befor = "", after = "";
			befor = S[0][j].substr(0, i);
			after = S[0][j].substr(i + 1, (S[0][j].length()) - i - 1);
			s = S[0][j].substr(i, 1);
			x = stoi(s);     //string转int
			x = (x + 1) % 2;
			s = std::to_string(x);     //int转string

			S[i + 1][j] = befor + s + after;
		}
	}
}



//二进制字符串转10进制，主要是使信道译码之后的字符串变成ASCII码的字符串，方便转换密文
int bin_to_deci(string inin)
{

	int len = inin.length();
	int n = 0;
	for (int i = 0; i < len; ++i)
	{
		//其中注意if的判断两个条件相等的符号
		if (inin.substr(i, 1) == "1")
			n += pow(2, len - 1 - i);
	}
	return n;
}

//十进制转二进制（八位二进制）
string deciToBin_8bit(int deci)
{
	string hexStr(8, ' ');
	int Value = 0;
	int i = 0;
	for (; deci != 0; ++i, deci /= 2)
	{
		Value = deci % 2;
		hexStr.at(i) = Value + '0';
	}
	hexStr = hexStr.substr(0, i);
	reverse(hexStr.begin(), hexStr.end());
	if (hexStr.length() < 8)
	{
		string add(8 - hexStr.length(), '0');
		hexStr = add + hexStr;
	}
	return hexStr;
}

//把密文转化位ASCII码方便信道编码（转成8位2进制）
void string_to_ascii(string info, string a[])
{
	string output = "", x;
	char c; int n;
	for (int i = 0; i < info.length(); i++)
	{
		c = info[i];
		n = (int)c;
		output = deciToBin_8bit(n);
		a[i] = output;
	}
}

//信道编码，这里的infomation是8位二进制
string channel_encode(string infomation)
{
	string info, e_info = "", v1, v2, v3, v4;
	int n1 = 0, n2 = 0, n3 = 0;

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)info = infomation.substr(0, 4);
		if (i == 1)info = infomation.substr(4, 4);

		v1 = info.substr(0, 1);
		v2 = info.substr(1, 1);
		v3 = info.substr(2, 1);
		v4 = info.substr(3, 1);
		if (v1 == "1") { n1 += G[0][0]; n2 += G[0][1]; n3 += G[0][2]; }
		if (v2 == "1") { n1 += G[1][0]; n2 += G[1][1]; n3 += G[1][2]; }
		if (v3 == "1") { n1 += G[2][0]; n2 += G[2][1]; n3 += G[2][2]; }
		if (v4 == "1") { n1 += G[3][0]; n2 += G[3][1]; n3 += G[3][2]; }

		n1 = n1 % 2; n2 = n2 % 2; n3 = n3 % 2;
		v1 = std::to_string(n1); v2 = std::to_string(n2); v3 = std::to_string(n3);
		e_info = e_info + info + v1 + v2 + v3;
		n1 = 0; n2 = 0; n3 = 0;
	}
	return e_info;     //输出14位，也就是两个码字合并
}

//信道译码，输入14位，两个码字
string channel_decode(string infomation)
{
	string info, de_info = "";

	for (int x = 0; x < 2; x++)
	{

		if (x == 0)info = infomation.substr(0, 7);
		if (x == 1)info = infomation.substr(7, 14);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (S[i][j] == info)
				{
					de_info += info.substr(0, 4);
					goto goon;
				}
			}

		}

	goon:;
	}
	return de_info;     //8位，包含两个四位信息源，其余六位校验位已经删去
}

//模拟BSC信道传输
string BSC(string infomation)
{
	string output = "", X;
	for (int i = 0; i < infomation.length(); i++)     //一个字符一个字符判断
	{
		srand((int)time(0));
		X = infomation.substr(i, 1);
		if (X == "0")
		{
			if (10 == rand() % 100)     //p=10的负2次
				X = "1";
			goto gon;     //防止此处X重新赋值为1后进入到下一个判断
		}
		if (X == "1")
		{
			if (100 == rand() % 100)     //p=10的负2次
				X = "0";
			goto gon;
		}
	gon:output += X;
	}
	return output;
}
