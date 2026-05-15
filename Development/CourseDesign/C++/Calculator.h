#pragma once
#include<iostream>
using namespace std;

class Integer      //整数类
{
protected:
	int fenzi;
	int fenmu;
public:
	Integer(int a = 0, int b = 1) :fenzi(a), fenmu(b) {};     //构造函数
	~Integer() {};                                            //析构函数
	void display();                                           //显示函数
};

class Fraction :public Integer                 //分数类
{
public:
	Fraction(int a=0,int b=1):Integer(a,b){}

	friend istream & operator>>(istream &, Fraction &);       //重载输入流
	friend ostream & operator<<(ostream &, Fraction &);      //重载输出流

	Fraction operator+(const Fraction& c);                    //重载+运算符（分数与分数）
	Fraction operator+(int n);                          //重载+运算符（整数与分数）
	Fraction operator-(const Fraction& c);                    //重载-运算符（分数与分数）
	Fraction operator-(int n);                          //重载-运算符（整数与分数）
	friend Fraction operator-(int n, const Fraction& c);      //重载-运算符（分数与整数）
	Fraction operator*(const Fraction& c);                    //重载*运算符（分数与分数）
	Fraction operator*(int n);                          //重载*运算符（整数与分数）
	Fraction operator/(const Fraction& c);                    //重载/运算符（分数与分数）
	Fraction operator/(int n);                          //重载/运算符（整数与分数）
	friend Fraction operator/(int n, const Fraction& c);      //重载/运算符（分数与整数）
	//加入友元friend，将该全局方法声明为类的友元方法，就可以对类的私有成员进行随意的访问了。

	Fraction operator~();         //取倒数一目运算符

	bool operator>(const Fraction& c);
	bool operator<(const Fraction& c);
	bool operator==(const Fraction& c);
	bool operator!=(const Fraction& c);
	bool operator>=(const Fraction& c);
	bool operator<=(const Fraction& c);
	
	Fraction reduce();                     //约分函数

	~Fraction() {};                           //析构函数
	void display();                        //开头界面显示函数
};


void Integer::display()   //开头界面
{
	cout << endl;
	cout << "--------------------分数计算器--------------------" << endl << endl;
	cout << "  菜单（选择功能）：" << endl << endl;
	cout << "               1 分数与整数的四则运算；" << endl << endl;
	cout << "               2 整数与分数的四则运算；" << endl << endl;
	cout << "               3 分数与分数的四则运算；" << endl << endl;
	cout << "               4 整数与整数的四则运算；" << endl << endl;
	cout << "               5 分数的化简；" << endl << endl;
	cout << "               6 分数取倒数；" << endl << endl;
	cout << "               7 分数比较大小；" << endl << endl;
	cout << "               0 输入0则退出应用" << endl << endl;
	cout << "--------------------------------------------------" << endl << endl;
}

Fraction Fraction::reduce()            //定义约分函数
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
		if (fenzi < 0 && fenmu < 0)          //使分子分母都为正数
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

		//辗转相除法求最大公约数
		/*辗转相除法， 又名欧几里德算法（Euclidean algorithm），
	  它的具体做法是:
	  用较大数除以较小数，再用出现的余数（第一余数）去除除数，
	  再用出现的余数（第二余数）去除第一余数，
	  如此反复，直到最后余数是0为止。
	  如果是求两个数的最大公约数，那么最后的除数就是这两个数的最大公约数。
	*/

		fz = fenzi;
		fm = fenmu;
		int t;
		if (fz < fm)     //使分子比分母大或相等
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

Fraction Fraction::operator+(const Fraction& c)          //重载两个分数的加法运算符
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu + fenmu * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator+(int n)         //重载分数和整数的加法运算符
{
	Fraction temp;
	temp.fenzi = fenmu * n + fenzi;
	temp.fenmu = fenmu;
	return temp;
}

Fraction operator-(int n, const Fraction& c)      //重载整数减分数的减法运算符
{
	Fraction temp;
	temp.fenzi = c.fenmu * n - c.fenzi;
	temp.fenmu = c.fenmu;
	return temp;
}

Fraction Fraction::operator-(int n)       //重载分数减整数的减法运算符
{
	Fraction temp;
	temp.fenzi = fenzi - fenmu * n;
	temp.fenmu = fenmu;
	return temp;
}

Fraction Fraction::operator-(const Fraction& c)     //重载两个分数的减法运算符
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu - fenmu * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator*(const Fraction& c)   //重载两个分数的乘法运算符
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenzi;
	temp.fenmu = fenmu * c.fenmu;
	return temp;
}

Fraction Fraction::operator*(int n)    //重载分数与整数的乘法运算符
{
	Fraction temp;
	temp.fenzi = fenzi * n;
	temp.fenmu = fenmu;
	return temp;
}

Fraction Fraction::operator/(const Fraction& c)   //重载两个分数的除法运算符
{
	Fraction temp;
	temp.fenzi = fenzi * c.fenmu;
	temp.fenmu = fenmu * c.fenzi;
	return temp;
}

Fraction Fraction::operator/(int n)    //重载分数除以整数的除法运算符
{
	Fraction temp;
	temp.fenzi = fenzi;
	temp.fenmu = fenmu * n;
	return temp;
	
}

Fraction operator/(int n, const Fraction& c)  //重载整数除以分数的除法运算符
{
	Fraction temp;
	temp.fenzi = n * c.fenmu;
	temp.fenmu = c.fenzi;
	return temp;
}


// 分数取倒数
Fraction Fraction:: operator~()
{
	Fraction x;
	if (fenzi == 0)
		cout << "  此分数无倒数！" << endl;
	else
	{
		x.fenzi = fenmu;
		x.fenmu = fenzi;   
		if (x.fenmu < 0)   //保证负分数的负号在分子上
		{
			x.fenzi = -x.fenzi;
			x.fenmu = -x.fenmu;
		}
	}
	return x;
}

// 分数比较大小
bool Fraction::operator>(const Fraction& c)
{
	int this_fenzi, c_fenzi, common_fenmu;
	this_fenzi = fenzi * c.fenmu;        // 计算分数通分后的分子，同分母为deno*c.deno
	c_fenzi = c.fenzi * fenmu;
	common_fenmu = fenmu * c.fenmu;
	if ((this_fenzi - c_fenzi) * common_fenmu > 0) return true;
	return false;
}

// 分数比较大小
bool Fraction::operator<(const Fraction& c)
{
	int this_fenzi, c_fenzi, common_fenmu;
	this_fenzi = fenzi * c.fenmu;        // 计算分数通分后的分子，同分母为deno*c.deno
	c_fenzi = c.fenzi * fenmu;
	common_fenmu = fenmu * c.fenmu;
	if ((this_fenzi - c_fenzi) * common_fenmu < 0) return true;
	return false;
}

// 分数比较大小
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

// 分数比较大小
bool Fraction::operator>=(const Fraction& c)
{
	if (*this < c) return false;
	return true;
}

// 分数比较大小
bool Fraction::operator<=(const Fraction& c)
{
	if (*this > c) return false;
	return true;
}


ostream& operator<<(ostream& output, Fraction& c)  //重载输出运算符，输出分数
{
	int fz, fm, t;
	fz = c.fenzi;
	fm = c.fenmu;

	if (fz == 0 || fm == 0)   //当分子或分母为0时，输出0
		cout << "0";
	if (fm == 1)          //当分母等于1时，输出分子
		cout << fz;
	if (fz == fm && fm != 1)        //当分子分母相等时，输出1
		cout << "1";

	if (fz > fm && fm != 1)   //分数为正假分数的输出
	{
		t = fz / fm;
		fz = fz % fm;
		if (fz != 0)
			cout << '(' << t << "又" << fz << '/' << fm << ')';
		else
			cout << t;
	}
	if (fz<0 && (-fz)>fm && fm != 1)   //分数为负假分数的输出
	{
		t = (-fz) / fm;
		fz = (-fz) % fm;
		if (fz != 0)
			cout << "(-(" << t << "又" << fz << '/' << fm << "))";
		else
			cout << '-' << t;
	}

	//分数为正真分数的输出
	if (c.fenzi > 0 && c.fenzi < c.fenmu && c.fenmu != 0 && c.fenmu != 1)  
		//output << c.fenzi << '/' << c.fenmu;
		cout << c.fenzi << '/' << c.fenmu;
	//分数为负真分数的输出
	if (c.fenzi < 0 && (-c.fenzi) < c.fenmu && c.fenmu != 0 && c.fenmu != 1)
		//output << "(" << c.fenzi << '/' << c.fenmu << ")";
		cout << "(" << c.fenzi << '/' << c.fenmu << ")";

	return output;
}

istream& operator>>(istream& input, Fraction& c)    //重载输入运算符，输入分数
{
	//int fz, fm;
	char t;
	//input >> fz >> t >> fm;
	while (1)
	{
		input >> c.fenzi >> t >> c.fenmu;
		if (t != '/')
		{
			cerr << "  错误！输入格式错误（请输入格式形如 m/n）！\n";
			
			//exit(0);
		}
		else if (c.fenmu == 0)
		{
			cerr << "  分母为0, 请重新输入！\n";
		}
		else
			break;
	}
	//预定义的对象 cerr 是 iostream 类的一个实例。
	//cerr 对象附属到标准输出设备，通常也是显示屏，但是 cerr 对象是非缓冲的，
	//且每个流插入到 cerr 都会立即输出。
	return input;
}
