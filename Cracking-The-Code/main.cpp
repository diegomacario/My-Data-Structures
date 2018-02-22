#include <string>
#include <iostream>
#include <map>

using namespace std;

void permutationsOfString(const string& sourceStr);
void permutationsOfString(const string& sourceStr, const string& prefix);
int fibonacci(int n);
int fibonacci2(int n);
int fibonacci3(int n);

int main(int argc, char * argv[])
{
    cout << fibonacci3(8) << '\n';
    cout << fibonacci3(7) << '\n';
    cout << fibonacci3(6) << '\n';
    cout << fibonacci3(5) << '\n';
    cout << fibonacci3(4) << '\n';
    int x;
    cin >> x;
}

// Print out all the permutations of a string
void permutationsOfString(const string& sourceStr)
{
    permutationsOfString(sourceStr, "");
}

void permutationsOfString(const string& sourceStr, const string& prefix)
{
    if (sourceStr.length() == 0)
    {
        cout << prefix << '\n';
    }
    else
    {   
        string remainingStr;
        for (int i = 0; i < sourceStr.length(); ++i)
        {
            remainingStr = sourceStr.substr(0, i) + sourceStr.substr(i + 1);
            permutationsOfString(remainingStr, prefix + sourceStr[i]);
        }
    }
}

// Compute the nth fibonacci number (recursively)
int fibonacci(int n)
{
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

// Compute the nth fibonacci number (efficiently)
int fibonacci2(int n)
{
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        int fib_n_2 = 0;
        int fib_n_1 = 1;
        int fib;

        for (int i = 2; i <= n; ++i)
        {
            fib = fib_n_1 + fib_n_2;
            fib_n_2 = fib_n_1;
            fib_n_1 = fib;
        }

        return fib;
    }
}

// Compute the nth fibonacci number (super efficiently through memoization)
int fibonacci3(int n)
{
    static map<int, int> fibonacciNumbers;
    map<int, int>::iterator it = fibonacciNumbers.find(n);
    
    if (it != fibonacciNumbers.end())
    {
        return it->second;
    }
    else if (n == 0)
    {
        fibonacciNumbers[0] = 0;
        return 0;
    }
    else if (n == 1)
    {
        fibonacciNumbers[1] = 1;
        return 1;
    }
    else
    {
        int fib_n_2 = 0;
        int fib_n_1 = 1;
        int fib;

        for (int i = 2; i <= n; ++i)
        {
            fib = fib_n_1 + fib_n_2;
            fib_n_2 = fib_n_1;
            fib_n_1 = fib;
            fibonacciNumbers[i] = fib;
        }

        return fib;
    }
}