#pragma once
#include<iostream>
using namespace std;

class Integer      //������
{
protected:
	int fenzi;
	int fenmu;
public:
	Integer(int a = 0, int b = 1) :fenzi(a), fenmu(b) {};     //���캯��
	~Integer() {};                                            //��������
	void display();                                           //��ʾ����
};

class Fraction :public Integer                 //������
{
public:
	Fraction(int a=0,int b=1):Integer(a,b){}

	friend istream & operator>>(istream &, Fraction &);       //����������
	friend ostream & operator<<(ostream &, Fraction &);      //���������

	Fraction operator+(const Fraction& c);                    //����+������������������
	Fraction operator+(int n);                          //����+������������������
	Fraction operator-(const Fraction& c);                    //����-������������������
	Fraction operator-(int n);                          //����-������������������
	friend Fraction operator-(int n, const Fraction& c);      //����-�������������������
	Fraction operator*(const Fraction& c);                    //����*������������������
	Fraction operator*(int n);                          //����*������������������
	Fraction operator/(const Fraction& c);                    //����/������������������
	Fraction operator/(int n);                          //����/������������������
	friend Fraction operator/(int n, const Fraction& c);      //����/�������������������
	//������Ԫfriend������ȫ�ַ�������Ϊ�����Ԫ�������Ϳ��Զ����˽�г�Ա��������ķ����ˡ�

	Fraction operator~();         //ȡ����һĿ�����

	bool operator>(const Fraction& c);
	bool operator<(const Fraction& c);
	bool operator==(const Fraction& c);
	bool operator!=(const Fraction& c);
	bool operator>=(const Fraction& c);
	bool operator<=(const Fraction& c);
	
	Fraction reduce();                     //Լ�ֺ���

	~Fraction() {};                           //��������
	void display();                        //��ͷ������ʾ����
};


void Integer::display()   //��ͷ����
{
	cout << endl;
	cout << "--------------------����������--------------------" << endl << endl;
	cout << "  �˵���ѡ���ܣ���" << endl << endl;
	cout << "               1 �������������������㣻" << endl << endl;
	cout << "               2 ������������������㣻" << endl << endl;
	cout << "               3 ������������������㣻" << endl << endl;
	cout << "               4 �������������������㣻" << endl << endl;
	cout << "               5 �����Ļ���" << endl << endl;
	cout << "               6 ����ȡ������" << endl << endl;
	cout << "               7 �����Ƚϴ�С��" << endl << endl;
	cout << "               0 ����0���˳�Ӧ��" << endl << endl;
	cout << "--------------------------------------------------" << endl << endl;
}

Fraction Fraction::reduce()            //����Լ�ֺ���
{
	int fz, fm, sign = 1;
	Fraction temp;
	if (fenzi == 0)
	{
		temp.fenzi = 0;
		temp.fenmu = fenmu;
	}
	else
	{
		if (fenzi < 0 && fenmu < 0)          //ʹ���ӷ�ĸ��Ϊ����
		{
			fenzi = -fenzi;
			fenmu = -fenmu;
		}
		if (fenzi > 0 && fenmu < 0)
		{
			fenmu = -fenmu;
			sign = -1;
		}
		if (fenzi < 0 && fenmu>0)
		{
			fenzi = -fenzi;
			sign = -1;
		}

		//շת����������Լ��
		/*շת������� ����ŷ������㷨��Euclidean algorithm����
	  ���ľ���������:
	  �ýϴ������Խ�С�������ó��ֵ���������һ������ȥ��������
	  ���ó��ֵ��������ڶ�������ȥ����һ������
	  ��˷�����ֱ�����������0Ϊֹ��
	  ������������������Լ������ô���ĳ��������������������Լ����
	*/

		fz = fenzi;
		fm = fenmu;
		int t;
		if (fz < fm)     //ʹ���ӱȷ�ĸ������
		{
			t = fz;
			fz = fm;
			fm = t;
		}
		int r;
		r = fz % fm;
		while (r != 0)
		{
			fz = fm;
			fm = r;
			r = fz % fm;
		}
		temp.fenzi = sign * (fenzi / fm);
		temp.fenmu = fenmu / fm;
	}
	return temp;
}

Fraction Fraction::operator+(const Fraction& c)          //�������������ļӷ������
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu + fenmu * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator+(int n)         //���ط����������ļӷ������
{
	Fraction temp;
	temp.fenzi = fenmu * n + fenzi;
	temp.fenmu = fenmu;
	return temp;
}

Fraction operator-(int n, const Fraction& c)      //���������������ļ��������
{
	Fraction temp;
	temp.fenzi = c.fenmu * n - c.fenzi;
	temp.fenmu = c.fenmu;
	return temp;
}

Fraction Fraction::operator-(int n)       //���ط����������ļ��������
{
	Fraction temp;
	temp.fenzi = fenzi - fenmu * n;
	temp.fenmu = fenmu;
	return temp;
}

Fraction Fraction::operator-(const Fraction& c)     //�������������ļ��������
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu - fenmu * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator*(const Fraction& c)   //�������������ĳ˷������
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator*(int n)    //���ط����������ĳ˷������
{
	Fraction temp;
	temp.fenzi = fenzi * n;
	temp.fenmu = fenmu;
	return temp;
}

Fraction Fraction::operator/(const Fraction& c)   //�������������ĳ��������
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu;
	temp.fenmu = fenmu * c.fenzi;
	return temp;
}

Fraction Fraction::operator/(int n)    //���ط������������ĳ��������
{
	Fraction temp;
	temp.fenzi = fenzi;
	temp.fenmu = fenmu * n;
	return temp;
	
}

Fraction operator/(int n, const Fraction& c)  //�����������Է����ĳ��������
{
	Fraction temp;
	temp.fenzi = n * c.fenmu;
	temp.fenmu = c.fenzi;
	return temp;
}


// ����ȡ����
Fraction Fraction:: operator~()
{
	Fraction x;
	if (fenzi == 0)
		cout << "  �˷����޵�����" << endl;
	else
	{
		x.fenzi = fenmu;
		x.fenmu = fenzi;   
		if (x.fenmu < 0)   //��֤�������ĸ����ڷ�����
		{
			x.fenzi = -x.fenzi;
			x.fenmu = -x.fenmu;
		}
	}
	return x;
}

// �����Ƚϴ�С
bool Fraction::operator>(const Fraction& c)
{
	int this_fenzi, c_fenzi, common_fenmu;
	this_fenzi = fenzi * c.fenmu;        // �������ͨ�ֺ�ķ��ӣ�ͬ��ĸΪdeno*c.deno
	c_fenzi = c.fenzi * fenmu;
	common_fenmu = fenmu * c.fenmu;
	if ((this_fenzi - c_fenzi) * common_fenmu > 0) return true;
	return false;
}

// �����Ƚϴ�С
bool Fraction::operator<(const Fraction& c)
{
	int this_fenzi, c_fenzi, common_fenmu;
	this_fenzi = fenzi * c.fenmu;        // �������ͨ�ֺ�ķ��ӣ�ͬ��ĸΪdeno*c.deno
	c_fenzi = c.fenzi * fenmu;
	common_fenmu = fenmu * c.fenmu;
	if ((this_fenzi - c_fenzi) * common_fenmu < 0) return true;
	return false;
}

// �����Ƚϴ�С
bool Fraction::operator==(const Fraction& c)
{
	if (*this != c) return false;
	return true;
}


bool Fraction::operator!=(const Fraction& c)
{
	if (*this > c || *this < c) return true;
	return false;
}

// �����Ƚϴ�С
bool Fraction::operator>=(const Fraction& c)
{
	if (*this < c) return false;
	return true;
}

// �����Ƚϴ�С
bool Fraction::operator<=(const Fraction& c)
{
	if (*this > c) return false;
	return true;
}


ostream& operator<<(ostream& output, Fraction& c)  //���������������������
{
	int fz, fm, t;
	fz = c.fenzi;
	fm = c.fenmu;

	if (fz == 0 || fm == 0)   //�����ӻ��ĸΪ0ʱ�����0
		cout << "0";
	if (fm == 1)          //����ĸ����1ʱ���������
		cout << fz;
	if (fz == fm && fm != 1)        //�����ӷ�ĸ���ʱ�����1
		cout << "1";

	if (fz > fm && fm != 1)   //����Ϊ���ٷ��������
	{
		t = fz / fm;
		fz = fz % fm;
		if (fz != 0)
			cout << '(' << t << "��" << fz << '/' << fm << ')';
		else
			cout << t;
	}
	if (fz<0 && (-fz)>fm && fm != 1)   //����Ϊ���ٷ��������
	{
		t = (-fz) / fm;
		fz = (-fz) % fm;
		if (fz != 0)
			cout << "(-(" << t << "��" << fz << '/' << fm << "))";
		else
			cout << '-' << t;
	}

	//����Ϊ������������
	if (c.fenzi > 0 && c.fenzi < c.fenmu && c.fenmu != 0 && c.fenmu != 1)  
		//output << c.fenzi << '/' << c.fenmu;
		cout << c.fenzi << '/' << c.fenmu;
	//����Ϊ������������
	if (c.fenzi < 0 && (-c.fenzi) < c.fenmu && c.fenmu != 0 && c.fenmu != 1)
		//output << "(" << c.fenzi << '/' << c.fenmu << ")";
		cout << "(" << c.fenzi << '/' << c.fenmu << ")";

	return output;
}

istream& operator>>(istream& input, Fraction& c)    //����������������������
{
	//int fz, fm;
	char t;
	//input >> fz >> t >> fm;
	while (1)
	{
		input >> c.fenzi >> t >> c.fenmu;
		if (t != '/')
		{
			cerr << "  ���������ʽ�����������ʽ���� m/n����\n";
			
			//exit(0);
		}
		else if (c.fenmu == 0)
		{
			cerr << "  ��ĸΪ0, ���������룡\n";
		}
		else
			break;
	}
	//Ԥ����Ķ��� cerr �� iostream ���һ��ʵ����
	//cerr ����������׼����豸��ͨ��Ҳ����ʾ�������� cerr �����Ƿǻ���ģ�
	//��ÿ�������뵽 cerr �������������
	return input;
}
