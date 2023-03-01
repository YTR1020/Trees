//�ۺϱ���������1
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

typedef char* HuffmanCode[2 * M];     //huffman����

//typedef long long LL;
using namespace std;

char x[1024];     //�γ̱���
char y[1024];     //huffman����


fstream in("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/in3.txt");
fstream out("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/out3.txt");

void Runlength_encode(char a[1024]);     //�γ̱��뺯��
void Runlength_decode(char a[1024]);     //�γ����뺯��
void Huffman_encode(char* ch);     //Huffman���뺯��
void Huffman_decode();     //Huffman���뺯��
int canshu(int k, int b);     //�жϷ�����ܲ����Ƿ�Ϸ�
string FSjiami(string str, int k, int b);     //������ܺ���
string FSjiemi(string pass, int k, int b);     //������ܺ���
void create_G();     //��ʼ����׼���ɾ���
void create_S();     //��ʼ�������
int bin_to_deci(string inin);     //������תʮ����
string deciToBin_8bit(int deci);     //ʮ����ת��λ������
void string_to_ascii(string info, string a[]);     //ת����ASCII�봮
string channel_encode(string infomation);     //�ŵ�����
string channel_decode(string infomation);     //�ŵ�����
string BSC(string infomation);     //ģ��BSC�ŵ�����


int main()
{
	const char lim = '#';
	char s1[1024];

	int k, b;     //�����㷨�Ĳ���
	cout << "����������㷨�Ĳ���(k,b)��";
	cin >> k >> b;
	while (!canshu(k, b))
	{
		cout << "�������Ϸ�������kӦ����mod��26��Ϊ�����������������룺";
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
		cout << "��Դ�ķ������У�" << s1 << endl;
		out << "��Դ�ķ������У�" << s1 << endl << endl;
		cout << endl;

		for (int q = 0; q < 1024; q++)
		{
			x[q] = '\0';
			y[q] = '\0';
		}

		Runlength_encode(s1);
		//��s1�����γ̱���õ�x�ַ�������
		cout << endl;
		out << endl;

		Huffman_encode(x);
		//��x����Huffman����õ�y�ַ�������
		cout << endl;
		out << endl;


		string jiami1;     //����������ģ�ASCII�봮��
		jiami1 = FSjiami(y, k, b);
		cout << "������ܺ�" << jiami1 << endl;
		out << "������ܺ�" << jiami1 << endl;
		cout << endl;
		out << endl;

		create_G();     //���ɾ���
		create_S();     //���������
		int lenth = jiami1.length();
		string* a = new string[lenth];     //�洢���ĵ�ASCII�봮
		string* output = new string[lenth];     //�洢�ŵ�������̵Ĵ�
		string_to_ascii(jiami1, a);     //����ת��ΪASCII�봮
		string  output1 = "";     //�洢�ŵ�������ASCII�봮����

		cout << "�ŵ����룺";
		out << "�ŵ����룺";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_encode(a[i]);     //�ŵ�����
			cout << output[i];
			out << output[i];
		}
		cout << endl << endl;
		out << endl << endl;

		cout << "ģ�⴫�ݴ���";
		out << "ģ�⴫�ݴ���";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = BSC(output[i]);     //�ŵ�����
			cout << output[i];
			out << output[i];
		}
		cout << endl << endl;
		out << endl << endl;

		cout << "�ŵ����룺";
		out << "�ŵ����룺";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_decode(output[i]);     //�ŵ�����
			cout << output[i];
			out << output[i];
			int f = 0;
			f = bin_to_deci(output[i]);//��������ת��ʮ����
			output1 += (char)f;//���ASCII���Ӧ���ַ��������ܺ������

		}
		cout << endl << endl;
		out << endl << endl;

		//������ܺ���ַ���
		string jiemi1 = FSjiemi(output1, k, b);
		cout << "������ܺ�" << jiemi1 << endl;
		out << "������ܺ�" << jiemi1 << endl;
		cout << endl;
		out << endl;

		//Huffman����
		Huffman_decode();
		cout << endl;
		out << endl;

		//�γ�����
		Runlength_decode(x);
		//��x�����γ�����
		cout << endl;
		out << endl;

	}
	in.close();
	out.close();
	return 0;

}

//�γ̱���
void Runlength_encode(char a[1024])
{
	char yc[1024];
	int i = 0, j = 0, count = 1;
	yc[0] = a[0];     //�γ̱����һ���ַ�Ϊ�ַ�����һ���ַ�
	for (i = 0; a[i] != '\0'; i++)     //�����ַ���
	{
		if (a[i] == a[i + 1])     //ͳ����ͬ�ַ�����
			count++;
		else
		{
			yc[j + 1] = count + 48;     //ASCII���intת�����ַ�char
			j = j + 2;
			yc[j] = a[i + 1];
			count = 1;
		}
	}
	yc[j] = '\0';
	cout << "�γ̱����" << yc << endl;
	out << "�γ̱����" << yc << endl;
	strcpy_s(x, yc);
}

//�γ�����
void Runlength_decode(char a[1024])
{
	char ym[1024];
	int j = 0, count, sign = 0;
	for (int i = 0; a[i] != '\0'; i = i + 2)
	{
		ym[sign] = a[i];     //��һλΪ��־λ��ʾ�γ̷���
		for (j = sign, count = 1; count <= a[i + 1] - 48; count++, j++)
			ym[j] = a[i];     //������ͬ�����ķ���װ�������ַ�����
		sign = j;
	}
	ym[j] = '\0';
	cout << "�γ������" << ym << endl;
	out << "�γ������" << ym << endl;
}


//Huffman�������ݽṹ����
typedef struct
{
	int weight;     //Ȩֵ
	int parent;     //���ڽڵ�
	int LChild;     //���ӽڵ�
	int RChild;     //���ӽڵ�
}HTNode, Huffman[M + 1];     //Huffman��

typedef struct
{
	int Weight;     //Ҷ�ӽ���Ȩֵ
	char c;     //Ҷ�ӽ��
	int num;     //Ҷ�ӽ��Ķ�������ĳ���
}WNode, WeightNode[N];

//����Ҷ�ӽ����ַ���Ȩֵ
void CreateWeight(char ch[], int* s, WeightNode CW, int* p)
{
	int i, j, k;
	int tag;
	*p = 0;     //Ҷ�ӽ�����

	//ͳ���ַ����ָ���������CW
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
					CW[*p].Weight++;     //Ȩֵ�ۼ�
			}
		}
	}
	*s = i;     //�ַ�������
}

//����Huffman��
void CreateHuffmanTree(Huffman ht, WeightNode w, int n)
{
	int i, j;
	int s1, s2;
	//��ʼ����������
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
		s1 = j; //�ҵ���һ��˫��Ϊ��Ľ��
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s1 = ht[s1].weight > ht[j].weight ? j : s1;
		ht[s1].parent = i;
		ht[i].LChild = s1;

		for (j = 1; j <= i - 1; j++)
			if (!ht[j].parent)
				break;
		s2 = j; //�ҵ��ڶ���˫��Ϊ��Ľ��
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s2 = ht[s2].weight > ht[j].weight ? j : s2;
		ht[s2].parent = i;
		ht[i].RChild = s2;

		ht[i].weight = ht[s1].weight + ht[s2].weight;//Ȩֵ�ۼ�
	}
}

//��Ҷ�ӽ�����
void CrtHuffmanNodeCode(Huffman ht, char ch[], HuffmanCode h, WeightNode w, int m, int n)
{
	int i, c, p, start;
	char* cd;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';//����ĩβ
	for (i = 1; i <= n; i++)
	{
		start = n - 1; //cd��ÿ�δ�ĩβ��ʼ
		c = i;
		p = ht[i].parent;//p��n+1��n-1
		while (p) //�ظ��׷��������ֱ��Ϊ��
		{
			start--;//������ǰ��ֵ
			if (ht[p].LChild == c)//��������ͬ,��0
				cd[start] = '0';
			else//������1
				cd[start] = '1';
			c = p;
			p = ht[p].parent;
		}
		w[i].num = n - start; //��������ĳ���(����ĩβ)
		h[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(h[i], &cd[start]);//���������ַ���������ָ������h��
	}
	free(cd);//�ͷ�cd�ڴ�
	//system("pause");
}

//�������ַ��ı���
void CrtHuffmanCode(char ch[], HuffmanCode h, HuffmanCode hc, WeightNode w, int n, int m)
{
	int i, k;
	for (i = 0; i < m; i++)
	{
		for (k = 1; k <= n; k++)      //��w[k].c�в�����ch[i]��ȵ��±�K
			if (ch[i] == w[k].c)
				break;
		hc[i] = (char*)malloc((w[k].num) * sizeof(char));
		strcpy(hc[i], h[k]); //���������Ʊ���
	}
}

//������������
void TrsHuffmanTree(Huffman ht, WeightNode w, HuffmanCode hc, int n, int m)
{
	int i = 0, j, p;
	while (i < m)
	{
		p = 2 * n - 1;//�Ӹ��׽ڵ����±���ֱ��Ҷ�ӽڵ�
		for (j = 0; hc[i][j] != '\0'; j++)
		{
			if (hc[i][j] == '0')
				p = ht[p].LChild;
			else
				p = ht[p].RChild;
		}
		printf("%c", w[p].c); //��ӡԭ��Ϣ
		out << w[p].c;
		i++;
	}
	out << endl;
}

//����������ʹ�����֮���ͷ�huffman�����ڴ�
void FreeHuffmanCode(HuffmanCode h, HuffmanCode hc, int n, int m)
{
	int i;
	for (i = 1; i <= n; i++)//�ͷ�Ҷ�ӽ��ı���
		free(h[i]);
	for (i = 0; i < m; i++) //�ͷ����н��ı���
		free(hc[i]);
}

int n;     //nΪҶ�ӽ��ĸ���
int m;     //mΪ�ַ���ch[]�ĳ���
Huffman ht;     //Huffman������
HuffmanCode h, hc;     //h���Ҷ�ӽ��ı��룬hc ������н��ı���
WeightNode w;     //���Ҷ�ӽ�����Ϣ

//Huffman���뺯��
void Huffman_encode(char* ch)
{
	n = 0;
	int i;
	m = 0;
	CreateWeight(ch, &m, w, &n);     //����Ҷ�ӽ����Ϣw��mΪ�ַ���ch[]�ĳ��ȣ�nΪҶ�ӽ��ĸ���
	CreateHuffmanTree(ht, w, n);     //����Huffman��ht
	CrtHuffmanNodeCode(ht, ch, h, w, m, n);     //Ҷ�ӽ��ı���h
	CrtHuffmanCode(ch, h, hc, w, n, m);     //�����ַ��ı���hc
	cout << "Huffman�����";     //��ӡ�ַ����ı���
	out << "Huffman�����";
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

//Huffman���뺯��
void Huffman_decode()
{
	cout << "huffman�����";
	out << "huffman�����";
	TrsHuffmanTree(ht, w, hc, n, m);     //���룬��ӡw[p].c
	FreeHuffmanCode(h, hc, n, m);     //�ͷ�huffman�����ڴ�
	cout << endl;
	out << endl;
	//system("pause");
}


//ʹ�÷���������м��ܽ���
int canshu(int k, int b)
{
	int c = 1, t, mod = 26;    //ģ 26
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

//�������
string FSjiami(string str, int k, int b)
{
	int i;
	//cout << "\n�������Ҫ���ܵ�����Ϊ:" << str << endl;
	for (i = 0; i < str.length(); i++)
	{
		int a;
		//a = (str[i] - 97) * k + b;    //����
		a = (str[i]) * k + b;
		if (a > 25)    //����Ϊ0-25     modΪ26
		{
			do     //��֤��������
			{
				a = a - 26;
			} while (a > 25);
			a = a + 97;        //���ܺ�õ���ASCII��;
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

//�������
string FSjiemi(string pass, int k, int b)
{
	int i;
	for (i = 0; i < pass.length(); i++)                //���ܹ���
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



//�����Ǳ�׼���ɾ�������ʡ����ǰ���еĵ�λ��,�˾���4��3��
int G[4][3];

//��������������ڣ�7��4��ϵͳѭ������С���d=3����������t=1��
//������ֻ��8��
string S[8][16];

//��ʼ����׼���ɾ���
void create_G()
{
	//��ʼ�����ɾ���ͬʱ���������ת��Ϊ�ල��
	G[0][0] = 1; G[0][1] = 0; G[0][2] = 1;     //��һ��  1 0 1
	G[1][0] = 1; G[1][1] = 1; G[1][2] = 1;     //�ڶ���  1 1 1
	G[2][0] = 1; G[2][1] = 1; G[2][2] = 0;     //������  1 1 0
	G[3][0] = 0; G[3][1] = 1; G[3][2] = 1;     //������  0 1 1
}

//��ʼ�������
void create_S()
{
	//��ʼ��������һ��,��һ�ж�Ϊ��������
	S[0][0] = "0000000"; S[0][1] = "1111111"; S[0][2] = "0001011"; S[0][3] = "0010110";
	S[0][4] = "0101100"; S[0][5] = "1011000"; S[0][6] = "0110001"; S[0][7] = "1100010";
	S[0][8] = "1000101"; S[0][9] = "0011101"; S[0][10] = "0111010"; S[0][11] = "1110100";
	S[0][12] = "1101001"; S[0][13] = "1010011"; S[0][14] = "0100111"; S[0][15] = "1001110";
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 16; j++)     //ѭ���������п��Ծ����ͼ��
		{
			int x = 0; string s = "", befor = "", after = "";
			befor = S[0][j].substr(0, i);
			after = S[0][j].substr(i + 1, (S[0][j].length()) - i - 1);
			s = S[0][j].substr(i, 1);
			x = stoi(s);     //stringתint
			x = (x + 1) % 2;
			s = std::to_string(x);     //intתstring

			S[i + 1][j] = befor + s + after;
		}
	}
}



//�������ַ���ת10���ƣ���Ҫ��ʹ�ŵ�����֮����ַ������ASCII����ַ���������ת������
int bin_to_deci(string inin)
{

	int len = inin.length();
	int n = 0;
	for (int i = 0; i < len; ++i)
	{
		//����ע��if���ж�����������ȵķ���
		if (inin.substr(i, 1) == "1")
			n += pow(2, len - 1 - i);
	}
	return n;
}

//ʮ����ת�����ƣ���λ�����ƣ�
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

//������ת��λASCII�뷽���ŵ����루ת��8λ2���ƣ�
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

//�ŵ����룬�����infomation��8λ������
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
	return e_info;     //���14λ��Ҳ�����������ֺϲ�
}

//�ŵ����룬����14λ����������
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
	return de_info;     //8λ������������λ��ϢԴ��������λУ��λ�Ѿ�ɾȥ
}

//ģ��BSC�ŵ�����
string BSC(string infomation)
{
	string output = "", X;
	for (int i = 0; i < infomation.length(); i++)     //һ���ַ�һ���ַ��ж�
	{
		srand((int)time(0));
		X = infomation.substr(i, 1);
		if (X == "0")
		{
			if (10 == rand() % 100)     //p=10�ĸ�2��
				X = "1";
			goto gon;     //��ֹ�˴�X���¸�ֵΪ1����뵽��һ���ж�
		}
		if (X == "1")
		{
			if (100 == rand() % 100)     //p=10�ĸ�2��
				X = "0";
			goto gon;
		}
	gon:output += X;
	}
	return output;
}
