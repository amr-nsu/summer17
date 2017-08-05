#include <iostream>
using namespace std;

template<typename T>
T Swap(T& a, T& b)
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

    return 0;
}
