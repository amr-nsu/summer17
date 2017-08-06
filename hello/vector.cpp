// CXXFLAGS = -std=c++14

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Print(const vector<string>& v)
{
    for(const auto& x : v) {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    vector<string> words {"hello", "world", "cat", "milk", "dog"};
    words.push_back("school");
    sort(begin(words), end(words));
    Print(words);

    return 0;
}
