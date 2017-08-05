// CXXFLAGS = -std=c++14

#include <iostream>
using namespace std;

double Sum(double x, double y)
{
    return x + y;
}

int main()
{
    auto a = 1.23;
    auto b = 4.56;
    auto c = Sum(a, b);
    cout << "Sum(" << a << ", " << b << ") = " << c << endl;

    return 0;
}
