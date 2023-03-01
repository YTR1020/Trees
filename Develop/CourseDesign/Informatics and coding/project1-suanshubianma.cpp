//��������������
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

//����ȫ�ֱ���
char S1[100], S2[100], A[10];//�û���ԭ��������,�������������ַ���
double P[10], f1[10], f2[10], gFs1, gFs2;//�����ַ����ʣ�ӳ������߽�㣬
char bm[100], jm[100]; //��������
double l1, l2;//����������������ֳ���


fstream in("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/in1.txt");
fstream out("E:/A-Develop/Microsoft Visual Studio/A-PROGRAM/PROGRAM/CourseDesign/EncodeDecode/out1.txt");

void encode(int a, int h1, int h2);
void decode(int a);

void main()
{
	int a, i, h1, h2 = 0;  //aΪ�����ַ���������iΪѭ��������hΪԭʼ�����ַ�������
	const char lim = '#';
	string str;
	bool beg = false;

	cout << "������Ÿ�����";
	cin >> a;
	cout << endl;

	cout << "���������ż������ֵ��" << endl;
	for (i = 0; i < a; i++)
	{
		cin >> A[i] >> P[i];
	}

	//��Ҫ���������ӳ�䵽һ��λ��[0,1)��ʵ�������У������ֳ�ʼ����
	for (i = 1; i < a; i++)
	{
		f1[0] = 0; f2[0] = 0;
		f1[i] = f1[i - 1] + P[i - 1];
		f2[i] = f2[i - 1] + P[i - 1];
	}

	//������������������
	while (!in.eof())
	{
		cout << "������Ҫ����ķ������У�ͬʱ��#��β��" << endl;
		h1 = 0; h2 = 0;

		//����һ��Ҫ������ַ����뵽����S1��
		while (1)
		{
			char cc;
			in >> cc;
			if (cc == '#')
				break;//���ԡ�#��Ϊ��β��ʱ������洢
			S1[h1++] = cc;
			cout << cc;
		}
		cout << endl;

		//���ڶ���Ҫ������ַ����뵽����S2��
		while (1)
		{
			char cc2;
			in >> cc2;
			if (cc2 == '#')
				break;//���ԡ�#��Ϊ��β��ʱ������洢
			S2[h2++] = cc2;
			cout << cc2;
		}
		cout << endl;

		cout << endl;

		cout << "������������" << endl;
		encode(a, h1, h2);

		cout << "��Ӧ����������" << endl;
		decode(a);

		system("pause");
	}
	in.close();
	out.close();
}


void encode(int a, int h1, int h2)//�������룬aΪ�����ַ���������hΪԭʼ�����ַ�������
{
	int i, j;     //ѭ������
	double fr;     //��������Ķ�Ӧ��
	double D1 = 1 , D2 = 1;     //������
	double Fs1 = 0 , Fs2 = 0;     //������ʼ��
	double Sp1[100], Sp2[100];   //S�������ַ���Ӧ�ĸ���


	//�Դ�����ĸ������ַ�������Ϊѭ�����ڣ�����������ַ�������Ӧ�ĸ���С�����뵽Fs��
	for (i = 0; i < h1; i++)
	{
		for (j = 0; j < a; j++)
		{
			if (S1[i] == A[j])
			{
				Sp1[i] = P[j];
				fr = f1[j];  //�����ֺõ�[0,1)����Ķ�Ӧ��ʼ�㸳ֵ��fr
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
				fr = f2[j];  //�����ֺõ�[0,1)����Ķ�Ӧ��ʼ�㸳ֵ��fr
			}
		}
		Fs2 = Fs2 + D2 * fr;
		D2 *= Sp2[i];
	}
	cout << "Fs2=" << fixed << setprecision(20) << Fs2 << endl;

	gFs1 = Fs1;
	gFs2 = Fs2;

	out << "����������Ϊ��" << endl;
	out << "Fs1=" << fixed << setprecision(16) << Fs1 << endl;
	out << "Fs2=" << fixed << setprecision(16) << Fs2 << endl;



	l1 = log((double)1 / D1) / log((double)2);     //����������������ֳ���l1
	if (l1 > (int)l1)
		l1 = (int)l1 + 1;
	else
		l1 = int(l1);

	//��Fsת���ɶ�������ʽ(�˶�ȡ��λ)
	int d1[100];
	int m1 = 0;     //��ʾ��������ʽλ��
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

	/*if (m1 >= l1)     //����й���������Ľ�λ����
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



	l2 = log((double)1 / D2) / log((double)2);     //����������������ֳ���l2
	if (l2 > (int)l2)
		l2 = (int)l2 + 1;
	else
		l2 = int(l2);

	//��Fsת���ɶ�������ʽ(�˶�ȡ��λ)
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

	/*if (m2 >= l2)     //����й���������Ľ�λ����
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



void decode(int a)     //��������,aΪ�����ַ�������
{
	int i = 0;
	double Ft1, Pt1, Ft2, Pt2;
	double Fs1 = 0, Fs2 = 0, D1 = 1, D2 = 1;
	double L1, L2;//�����ɱ�����Ԥ�Ƶ�ԭ���ݳ���

	std::string str1;
	std::stringstream ss1;
	ss1 << std::setprecision(21) << gFs1;
	str1 = ss1.str();

	std::string str2;
	std::stringstream ss2;
	ss2 << std::setprecision(21) << gFs2;
	str2 = ss2.str();

	out << "���������\n";
	while (1)
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft1 = Fs1;
			Pt1 = D1;
			Ft1 += Pt1 * f1[j];     //������������
			Pt1 *= P[j];
			if (gFs1 >= Ft1)     //��������жϲ���ֵ���뵽����A��
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

	/*for (i = 0; i < h1; i++)     //�Ա�������ͷ��Ÿ���Ϊѭ�����ڽ��н���
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft1 = Fs1;
			Pt1 = D1;
			Ft1 += Pt1 * f1[j];     //������������
			Pt1 *= P[j];
			if (gFs1 >= Ft1)     //��������жϲ���ֵ���뵽����A��
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
			Ft2 += Pt2 * f2[j];     //������������
			Pt2 *= P[j];
			if (gFs2 >= Ft2)     //��������жϲ���ֵ���뵽����A��
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

	/*for (i = 0; i < h2; i++)     //�Ա�������ͷ��Ÿ���Ϊѭ�����ڽ��н���
	{
		for (int j = a - 1; j > -1; j--)
		{
			Ft2 = Fs2;
			Pt2 = D2;
			Ft2 += Pt2 * f2[j];     //������������
			Pt2 *= P[j];
			if (gFs2 >= Ft2)     //��������жϲ���ֵ���뵽����A��
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
