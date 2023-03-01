//算术编码与译码
#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<string.h>
#include<string>
#include<set>
#include<cmath>
#include <sstream>
#include"math.h"

#pragma warning(disable:4996)
using namespace std;

//定义全局变量
char S1[100], S2[100], A[10];//用户的原数据码字,保存的输入编码字符集
double P[10], f1[10], f2[10], gFs1, gFs2;//编码字符概率，映射区间边界点，
char bm[100], jm[100]; //保存码字
double l1, l2;//保存算术编码的码字长度


fstream in("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/in1.txt");
fstream out("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/out1.txt");

void encode(int a, int h1, int h2);
void decode(int a);

void main()
{
	int a, i, h1, h2 = 0;  //a为编码字符集个数，i为循环变量，h为原始数据字符串长度
	const char lim = '#';
	string str;
	bool beg = false;

	cout << "编码符号个数：";
	cin >> a;
	cout << endl;

	cout << "输入编码符号及其概率值：" << endl;
	for (i = 0; i < a; i++)
	{
		cin >> A[i] >> P[i];
	}

	//将要编码的数据映射到一个位于[0,1)的实数区间中，即划分初始区间
	for (i = 1; i < a; i++)
	{
		f1[0] = 0; f2[0] = 0;
		f1[i] = f1[i - 1] + P[i - 1];
		f2[i] = f2[i - 1] + P[i - 1];
	}

	//进行算术编码与译码
	while (!in.eof())
	{
		cout << "输入需要编码的符号序列，同时用#结尾：" << endl;
		h1 = 0; h2 = 0;

		//将第一组要编码的字符存入到数组S1中
		while (1)
		{
			char cc;
			in >> cc;
			if (cc == '#')
				break;//在以“#”为结尾的时候结束存储
			S1[h1++] = cc;
			cout << cc;
		}
		cout << endl;

		//将第二组要编码的字符存入到数组S2中
		while (1)
		{
			char cc2;
			in >> cc2;
			if (cc2 == '#')
				break;//在以“#”为结尾的时候结束存储
			S2[h2++] = cc2;
			cout << cc2;
		}
		cout << endl;

		cout << endl;

		cout << "算术编码结果：" << endl;
		encode(a, h1, h2);

		cout << "对应的译码结果：" << endl;
		decode(a);

		system("pause");
	}
	in.close();
	out.close();
}


void encode(int a, int h1, int h2)//算术编码，a为编码字符集个数，h为原始数据字符串长度
{
	int i, j;     //循环变量
	double fr;     //划分区间的对应点
	double D1 = 1 , D2 = 1;     //区间间隔
	double Fs1 = 0 , Fs2 = 0;     //区间起始点
	double Sp1[100], Sp2[100];   //S数组中字符对应的概率


	//以待编码的个数和字符集个数为循环周期，将待编码的字符串所对应的概率小数存入到Fs中
	for (i = 0; i < h1; i++)
	{
		for (j = 0; j < a; j++)
		{
			if (S1[i] == A[j])
			{
				Sp1[i] = P[j];
				fr = f1[j];  //将划分好的[0,1)区间的对应起始点赋值给fr
			}
		}
		Fs1 = Fs1 + D1 * fr;
		D1 *= Sp1[i];
	}
	cout << "Fs1=" << fixed << setprecision(20) << Fs1 << endl;

	for (i = 0; i < h2; i++)
	{
		for (j = 0; j < a; j++)
		{
			if (S2[i] == A[j])
			{
				Sp2[i] = P[j];
				fr = f2[j];  //将划分好的[0,1)区间的对应起始点赋值给fr
			}
		}
		Fs2 = Fs2 + D2 * fr;
		D2 *= Sp2[i];
	}
	cout << "Fs2=" << fixed << setprecision(20) << Fs2 << endl;

	gFs1 = Fs1;
	gFs2 = Fs2;

	out << "算术编码结果为：" << endl;
	out << "Fs1=" << fixed << setprecision(16) << Fs1 << endl;
	out << "Fs2=" << fixed << setprecision(16) << Fs2 << endl;



	l1 = log((double)1 / D1) / log((double)2);     //计算算术编码的码字长度l1
	if (l1 > (int)l1)
		l1 = (int)l1 + 1;
	else
		l1 = int(l1);

	//将Fs转换成二进制形式(乘二取个位)
	int d1[100];
	int m1 = 0;     //表示二进制形式位数
	while (l1 > m1)
	{
		Fs1 = 2 * Fs1;
		if (Fs1 > 1)
		{
			Fs1 = Fs1 - 1;
			d1[m1] = 1;
		}
		else if (Fs1 < 1)
			d1[m1] = 0;
		else
		{
			d1[m1] = 1;
			break;
		}
		m1++;
	}

	int z = m1;

	/*if (m1 >= l1)     //解决有关算术编码的进位问题
	{
		while (1)
		{
			d1[m1 - 1] = (d1[m1 - 1] + 1) % 2;
			if (d1[m1 - 1] == 1) break;
			else m1--;
		}
	}*/

	cout << "s1=";
	out << "s1=";

	for (int e = 0; e < z; e++)
	{
		cout << d1[e];
		out << d1[e];
	}
	cout << endl;
	out << endl;



	l2 = log((double)1 / D2) / log((double)2);     //计算算术编码的码字长度l2
	if (l2 > (int)l2)
		l2 = (int)l2 + 1;
	else
		l2 = int(l2);

	//将Fs转换成二进制形式(乘二取个位)
	int d2[100];
	int m2 = 0;
	while (l2 > m2)
	{
		Fs2 = 2 * Fs2;
		if (Fs2 > 1)
		{
			Fs2 = Fs2 - 1;
			d2[m2] = 1;
		}
		else if (Fs2 < 1)
			d2[m2] = 0;
		else
		{
			d2[m2] = 1;
			break;
		}
		m2++;
	}

	int z2 = m2;

	/*if (m2 >= l2)     //解决有关算术编码的进位问题
	{
		while (1)
		{
			d2[m2 - 1] = (d2[m2 - 1] + 1) % 2;
			if (d2[m2 - 1] == 1) break;
			else m2--;
		}
	}*/

	cout << "s2=";
	out << "s2=";

	for (int e = 0; e < z2; e++)
	{
		cout << d2[e];
		out << d2[e];
	}
	cout << endl;
	out << endl;

}



void decode(int a)     //算术译码,a为编码字符集个数
{
	int i = 0;
	double Ft1, Pt1, Ft2, Pt2;
	double Fs1 = 0, Fs2 = 0, D1 = 1, D2 = 1;
	double L1, L2;//保存由编码结果预计的原数据长度

	std::string str1;
	std::stringstream ss1;
	ss1 << std::setprecision(21) << gFs1;
	str1 = ss1.str();

	std::string str2;
	std::stringstream ss2;
	ss2 << std::setprecision(21) << gFs2;
	str2 = ss2.str();

	out << "算术译码后：\n";
	while (1)
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft1 = Fs1;
			Pt1 = D1;
			Ft1 += Pt1 * f1[j];     //对其进行逆编码
			Pt1 *= P[j];
			if (gFs1 >= Ft1)     //对其进行判断并将值存入到数组A中
			{
				Fs1 = Ft1;
				D1 = Pt1;
				cout << A[j];
				out << A[j];
				break;
			}
		}
		i++;

		L1 = log((double)1 / D1) / log((double)2);
		if (L1 > (int)L1)
			L1 = (int)L1 + 1;
		else
			L1 = int(L1);

		if (L1-4 > str1.length())
			break;
	}

	/*for (i = 0; i < h1; i++)     //以编码个数和符号个数为循环周期进行解码
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft1 = Fs1;
			Pt1 = D1;
			Ft1 += Pt1 * f1[j];     //对其进行逆编码
			Pt1 *= P[j];
			if (gFs1 >= Ft1)     //对其进行判断并将值存入到数组A中
			{
				Fs1 = Ft1;
				D1 = Pt1;
				cout << A[j];
				out << A[j];
				break;
			}
		}
	}*/

	cout << endl;
	out << endl;

	i = 0;
	while (1)
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft2 = Fs2;
			Pt2 = D2;
			Ft2 += Pt2 * f2[j];     //对其进行逆编码
			Pt2 *= P[j];
			if (gFs2 >= Ft2)     //对其进行判断并将值存入到数组A中
			{
				Fs2 = Ft2;
				D2 = Pt2;
				cout << A[j];
				out << A[j];
				break;
			}
		}
		i++;
		L2 = log((double)1 / D2) / log((double)2);
		if (L2 > (int)L2)
			L2 = (int)L2 + 1;
		else
			L2 = int(L2);

		if (L2-4 > str2.length())
			break;
	}

	/*for (i = 0; i < h2; i++)     //以编码个数和符号个数为循环周期进行解码
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft2 = Fs2;
			Pt2 = D2;
			Ft2 += Pt2 * f2[j];     //对其进行逆编码
			Pt2 *= P[j];
			if (gFs2 >= Ft2)     //对其进行判断并将值存入到数组A中
			{
				Fs2 = Ft2;
				D2 = Pt2;
				cout << A[j];
				out << A[j];
				break;
			}
		}
	}*/

	cout << endl;
	out << endl;
}
