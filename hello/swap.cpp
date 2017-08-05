#include <iostream>
using namespace std;

template<typename T>
void Swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a = 10;
    int b = 20;
    Swap(a, b);
    cout << "a = " << a << "; b = " << b << endl;

    string s1 = "Hello";
    string s2 = "World";
    Swap(s1, s2);
    cout << "s1 = " << s1 << "; s2 = " << s2 << endl;

    return 0;
}
