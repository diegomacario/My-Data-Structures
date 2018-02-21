#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int initRandomSeed()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(int(time(NULL)));
        initialized = true;
    }
}

int randomInteger(int low, int high)
{
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return (floor(s + low));
}

int main(int argc, char * argv[])
{
    for (int i = 1; i <= 100; ++i)
    {
        cout << "Run " << i << ": " << randomInteger(1, 10) << '\n';
    }

    int x;
    cin >> x;
}
