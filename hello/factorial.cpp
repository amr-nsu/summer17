#include <iostream>
using namespace std;

int Factorial(int n)
{
    if (n < 1) return 1;
    int result = 1;
    for(int i=1; i<=n; ++i) {
        result *= i;
    }
    return result;
}

int main()
{
    int n = 0;
    cin >> n;
    cout << n << "! = " << Factorial(n) << endl;

    return 0;
}
