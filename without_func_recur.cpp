#include <iostream>
using namespace std;

int main() {
    int n, result = 1;

    cout << "Enter a non-negative number: ";
    cin >> n;

    // Calculate factorial
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }

    cout << "Factorial of " << n << " = " << result;
    return 0;
}
