#include <iostream>
#include"Calculator.h"

int main()
{
    Integer ZHENGSHU;  //整数类
    Fraction a, b, result, real;  //分数类
    int f, m, n; int r = 0;   //功能序号、参与运算的整数
    char t;     //运算符

    ZHENGSHU.display();

    do
    {
        cout << "  请输入功能序号（0-7）：  ";
        cin >> f;    //输入功能序号

        if (f == 1)      //选择分数与整数的四则运算
        {
            cout << endl << "  1 分数与整数的四则运算：" << endl;
            cout << endl << "    请输入一个分数：    ";
            cin >> a;
            cout << endl << "    请输入运算符：    ";
            cin >> t;
            cout << endl << "    请输入一个整数：    ";
            cin >> m;
            if (t == '+')
                result = a + m;
            if (t == '-')
                result = a - m;
            if (t == '*')
                result = a * m;
            if (t == '/')
            {
                if (m == 0)
                {
                    cerr << "  \n错误！！除数不能为0！结果出错！" << endl;
                }
                else
                    result = a / m;
            }
                
            real = result.reduce();  //化简

            cout << endl << "运算过程为：  " << a << t << '(' << m << ')' << '=' << real << endl;
            cout << endl;
        }

        if (f == 2)   //选择整数与分数的四则运算
        {
            cout << endl << "  2 整数与分数的四则运算：" << endl;
            cout << endl << "    请输入一个整数：    ";
            cin >> m;
            cout << endl << "    请输入运算符：    ";
            cin >> t;
            cout << endl << "    请输入一个分数：    ";
            cin >> b;
            if (t == '+')
                result = b + m;
            if (t == '-')
                result = m - b;
            if (t == '*')
                result = b * m;
            if (t == '/')
            {
                if (b == 0)
                {
                    cerr << "  \n错误！！除数不能为0！结果出错！" << endl;
                }
                else
                    result = m / b;
            }
                

            real = result.reduce();  //化简

            cout << endl << "运算过程为：  " << m << t << b << '=' << real << endl;
            cout << endl;
        }

        if (f == 3)      //选择分数与分数的运算
        {
            cout << endl << "  3 分数与分数的四则运算：" << endl;
            cout << endl << "    请输入一个分数：    ";
            cin >> a;
            cout << endl << "    请输入运算符：    ";
            cin >> t;
            cout << endl << "    请输入一个分数：    ";
            cin >> b;
            if (t == '+')
                result = a + b;
            if (t == '-')
                result = a - b;
            if (t == '*')
                result = a * b;
            if (t == '/')
            {
                if (b == 0)
                {
                    cerr << "  \n错误！！除数不能为0！结果出错！" << endl;
                }
                else
                    result = a / b;
            }

            real = result.reduce();  //化简

            cout << endl << "运算过程：  " << a << t << b << '=' << real << endl;
            cout << endl;
        }

        if (f == 4)      //选择整数与整数的运算
        {
            cout << endl << "  4 整数与整数的四则运算；" << endl;
            cout << endl << "    请输入一个整数：    ";
            cin >> m;
            cout << endl << "    请输入运算符：    ";
            cin >> t;
            cout << endl << "    请输入一个整数：    ";
            cin >> n;
            if (t == '+')
                r = m + n;
            if (t == '-')
                r = m - n;
            if (t == '*')
                r = m * n;
            if (t == '/')
            {
                if (n == 0)
                {
                    cerr << "  \n错误！！除数不能为0！结果出错！" << endl;
                }
                else
                    result = m / n;
            }
               
            cout << endl << "运算过程：  " << m << t << n << '=' << r << endl;
            cout << endl;
        }

        if (f == 5)      //选择分数的化简
        {
            cout << endl << "  5 分数的化简；" << endl;
            cout << endl << "    请输入一个分数：    ";
            cin >> a;

            result = a.reduce();

            cout << endl << "化简结果：  " << result << endl;
            cout << endl;
        }

        if (f == 6)      //选择分数取倒数
        {
            cout << endl << "  6 分数取倒数；" << endl;
            cout << endl << "    请输入一个分数：    ";
            cin >> a;

            result = ~a;
            real = result.reduce();  //化简

            cout << endl << "取倒结果：  " << real << endl;
            cout << endl;
        }

        if (f == 7)      //选择分数比较大小
        {
            cout << endl << "  7 分数比较大小；" << endl;
            cout << endl << "    请输入一个分数：    ";
            cin >> a;
            cout << endl << "    请输入另一个分数：    ";
            cin >> b;
            if (a > b)
                cout << endl << a << "前者大于后者" << b << endl;
            if (a < b)
                cout << endl << a << "前者小于后者" << b << endl;
            if (a == b)
                cout << endl << a << "前者等于后者" << b << endl;

            cout << endl;
        }

    } while (f != 0);

    return 0;
}


