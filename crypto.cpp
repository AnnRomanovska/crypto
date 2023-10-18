// crypto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool checkHex(string s)
{
    try {
        istringstream stream(s);
        unsigned int value;
        stream >> hex >> value;
        return true;
    }
    catch (exception& e) {
        return false;
    }
}
unsigned int* turnToArr(string s)
{
    int n = s.size();
    unsigned int* a = new unsigned int[n];
    for (int i = 0; i < n; i++)
    {
        if ((s[i] - '0') >= 0 && (s[i] - '0') <= 9)
        {
            a[i] = s[i] - '0';
        }
        else
        {
            a[i] = (s[i] - 'a') + 10;
        }
    }
    return a;
}
unsigned int* EmptyArray(int numb)
{
    unsigned int* a = new unsigned int[numb];
    for (int i = 0; i < numb; i++)
    {
        a[i] = 0;
    }
    return a;
}
unsigned int* invArr(unsigned int* a, int n)
{
    unsigned int* inv = new unsigned int[n];
    int numb = n - 1;
    for (int i = 0; i < n; i++)
    {
        int value = a[i];
        inv[numb] = value;
        numb--;
    }
    return inv;
}

class MyInt
{
private:
    unsigned int* a;
    int n;
protected:
    MyInt Add(MyInt a, MyInt b)
    {
        MyInt result(n);
        unsigned int* numb = new unsigned int[a.n];
        for (int i = a.n - 1, k = b.n - 1; i >= 0; i--, k--)
        {
            if (k >= 0)
            {
                numb[i] = a.a[i] + b.a[k];
            }
            else
            {
                numb[i] = a.a[i];
            }
        }
        for (int i = n - 1; i > 0; i--)
        {
            if (numb[i] > 15)
            {
                numb[i - 1] = numb[i - 1] + (int)numb[i] / 16;
                numb[i] = numb[i] % 16;
            }
        }
        if (numb[0] > 15)
        {
            MyInt resultLast(n + 1);
            resultLast.a[0] = (int)numb[0] / 16;
            numb[0] = numb[0] % 16;
            for (int i = 0; i < n; i++)
            {
                resultLast.a[i + 1] += numb[i];
            }
            return resultLast;
        }
        else
        {
            result.a = numb;
            return result;
        }
    }
    MyInt Sub(MyInt a, MyInt b)
    {
        MyInt result(a.n);
        unsigned int* numb = new unsigned int[n];
        for (int i = a.n - 1, k = b.n - 1; i >= 0; i--, k--)
        {
            if (k >= 0)
            {
                if (a.a[i] >= b.a[k])
                {
                    numb[i] = a.a[i] - b.a[k];
                }
                else if (a.a[i] < b.a[k])
                {
                    if (i != 0)
                    {
                        a.a[i] = a.a[i] + 16;
                        a.a[i - 1] = a.a[i - 1] - 1;
                        numb[i] = a.a[i] - b.a[k];
                    }
                    else
                    {
                        cout << endl << "You trying to sub largest value" << endl;
                        return 0;
                    }
                }
            }
            else
            {
                numb[i] = a.a[i];
            }
        }
        result.a = numb;
        return result;
    }
    MyInt devideAndrule(MyInt a, MyInt b)
    {
        unsigned int* linearConvolution = new unsigned int[a.n + b.n - 1];
        MyInt result(a.n + b.n - 1);
        linearConvolution = EmptyArray(a.n + b.n - 1);
        int nextCarry = 0;
        for (int i = 0; i < b.n; i++)
        {
            for (int j = 0; j < a.n; j++)
            {
                linearConvolution[i + j] += b.a[i] * a.a[j];
            }
        }
        linearConvolution = invArr(linearConvolution, a.n + b.n - 1);
        for (int i = 0; i < a.n + b.n - 1; i++) {
            linearConvolution[i] += nextCarry;
            result.a[i] = result.a[i] + linearConvolution[i] % 16;
            nextCarry = linearConvolution[i] / 16;
        }
        if (nextCarry > 0)
        {
            MyInt resultLast(a.n + b.n);
            resultLast.a[a.n + b.n - 1] = nextCarry;
            for (int i = 0; i < a.n + b.n - 1; i++)
            {
                resultLast.a[i] = result.a[i];
            }
            resultLast.inv();
            return resultLast;
        }
        result.inv();
        return result;
    }
public:
    MyInt() { a = 0; n = 0; }
    MyInt(int numb) 
    {
        n = numb;
        a = EmptyArray(numb);
    }
    MyInt(string s)
    {
        n = s.size();
        a = turnToArr(s);
    }
    void setHex(string s)
    {
        n = s.size();
        a = turnToArr(s);
    }
    string getHex()
    {
        string str;
        int numb = 0;
        if (a!=NULL)
        {
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 10)
                {
                    str = str + 'a';
                }
                else if (a[i] == 11)
                {
                    str = str + 'b';
                }
                else if (a[i] == 12)
                {
                    str = str + 'c';
                }
                else if (a[i] == 13)
                {
                    str = str + 'd';
                }
                else if (a[i] == 14)
                {
                    str = str + 'e';
                }
                else if (a[i] == 15)
                {
                    str = str + 'f';
                }
                else if (a[i] > -1 || a[i] < 10)
                {
                    numb = a[i];
                    str = str + to_string(numb);
                }
            }
            return str;
        }
        else
        {
            cout << endl << "You trying to print null value" << endl;
            return "";
        }
    }
    void inv()
    {
        unsigned int* inv = new unsigned int[n];
        int numb = n - 1;
        for (int i = 0; i < n; i++)
        {
            int value = a[i];
            inv[numb] = value;
            numb--;
        }
        a = inv;
    }
    MyInt XOR (MyInt B)
    {
        MyInt C(n);
        if (n == B.n)
        {
            for (int i = 0; i < n; i++)
            {
                C.a[i] = a[i] ^ B.a[i];
            }
            return C;
        }
        else
        {
            cout << endl << "Value lenght not match" << endl;
            return 0;
        }
    }
    MyInt OR(MyInt B)
    {
        MyInt C(n);
        if (n == B.n)
        {
            for (int i = 0; i < n; i++)
            {
                C.a[i] = a[i] | B.a[i];
            }
            return C;
        }
        return 0;
    }
    MyInt AND(MyInt B)
    {
        MyInt C(n);
        if (n == B.n)
        {
            for (int i = 0; i < n; i++)
            {
                C.a[i] = a[i] & B.a[i];
            }
            return C;
        }
        return 0;
    }
    MyInt operator>>(int numb)
    {
        __int64 x=0, base = 1;
        for (int i = n-1; i >= 0; i--)
        {
            x = x + a[i] * base;
            base = base * 16;
        }
        x >>= numb;
        stringstream ss;
        ss << hex << x;
        string res(ss.str());
        MyInt a(res);
        return a;
    }
    MyInt operator<<(int numb)
    {
        __int64 x = 0, base = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            x = x + a[i] * base;
            base = base * 16;
        }
        x <<= numb;
        stringstream ss;
        ss << hex << x;
        string res(ss.str());
        MyInt a(res);
        return a;
    }
    MyInt operator+(MyInt& other)
    {
        if (n >= other.n)
        {
            MyInt result;
            result = Add(*this, other);
            return result;
        }
        else if (n<other.n)
        {
            MyInt result;
            result=Add(other, *this);
            return result;
        }
        return 0;
    }
    MyInt operator-(MyInt& other)
    {
        if (n >= other.n)
        {
            MyInt result(n);
            result=Sub(*this, other);
            return result;
        }
        else
        {
            cout << endl << "You trying to sub largest value" << endl;
            return 0;
        }
    }
    MyInt operator*(MyInt& other)
    {
        MyInt result;
        result = devideAndrule(*this, other);
        return result;
    }
    long long operator%(long long mod)
    {
        MyInt result; 
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = (ans * 16 + a[i]) % mod;
        }
        return ans;
    }
};

int main()
{
    string a;
    int n;
    cout << "a: ";
    getline(cin, a);
    if (checkHex(a) == 1)
    {
        MyInt c, c1, res;
        c.setHex(a);
        cout << "enter 1-inv, 2-xor, 3-or, 4-and, 5-shiftR, 6-shiftL, 7-add, 8-sub, 9-mod, 10-mul" << endl;
        cin >> n;
        if (n == 1)
        {
            c.inv();
            cout << endl << a << endl << "result" << endl << c.getHex() << endl;
        }
        else if (n == 2)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c.XOR(c1);
                cout << endl << a << endl << "XOR" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else if (n == 3)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c.OR(c1);
                cout << endl << a << endl << "OR" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else if (n == 4)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c.AND(c1);
                cout << endl << a << endl << "AND" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else if (n == 5)
        {
            int numb;
            cout << "number: ";
            cin >> numb;
            res = c >> numb;
            cout << endl << a << endl << "ShiftR" << endl << "result" << endl << res.getHex() << endl;
        }
        else if (n == 6)
        {
            int numb;
            cout << "number: ";
            cin >> numb;
            res = c << numb;
            cout << endl << a << endl << "ShiftL" << endl << "result" << endl << res.getHex() << endl;
        }
        else if (n == 7)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c + c1;
                cout << endl << a << endl << "ADD" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else if (n == 8)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c - c1;
                cout << endl << a << endl << "SUB" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else if (n == 9)
        {
            long long numb, result;
            cout << "mod: ";
            cin >> numb;
            result = c % numb;
            cout << endl << a << endl << "MOD" << endl << numb << endl << "result" << endl << result << endl;
        }
        else if (n == 10)
        {
            string b;
            cout << "b: ";
            cin >> b;
            if (checkHex(b) == 1)
            {
                c1.setHex(b);
                res = c * c1;
                cout << endl << a << endl << "MUL" << endl << b << endl << "result" << endl << res.getHex() << endl;
            }
            else
            {
                cout << "Wrong input b";
            }
        }
        else
        {
            cout << "Wrong value n";
        }
    }
    else
    {
        cout << "Wrong input a";
    }
    
};

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
