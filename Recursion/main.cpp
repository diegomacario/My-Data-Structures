#include <iostream>

using namespace std;

int fib(int n);
int fib2(int n);

int main(int argc, char * argv[])
{
    cout << "fib(0) = " << fib2(0) << '\n';
    cout << "fib(1) = " << fib2(1) << '\n';
    cout << "fib(2) = " << fib2(2) << '\n';
    cout << "fib(3) = " << fib2(3) << '\n';
    cout << "fib(4) = " << fib2(4) << '\n';
    cout << "fib(5) = " << fib2(5) << '\n';
    
    int x;
    cin >> x;
}

// This function returns the nth fibonacci number
// Its time complexity is O(n - 1) + O(n - 2)
// Its space complexity is O(n) because of the call stack size 
int fib(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

// This function returns the nth fibonacci number
// Its time complexity is O(n)
// Its space complexity of O(1)
int fib2(int n)
{
    int fib_n = 1;
    int fib_n_minus_1 = 1;
    int fib_n_minus_2 = 1;

    for (int i = 2; i <= n; ++i)
    {
        fib_n = fib_n_minus_1 + fib_n_minus_2;
        fib_n_minus_2 = fib_n_minus_1;
        fib_n_minus_1 = fib_n;
    }

    return fib_n;
}
