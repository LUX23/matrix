#include <iostream>
#include "Matrix.h"
#include <string>

using namespace std;
using namespace psychoMatrix;

double* FunctInput(int N, int M) {
    double* arr = new double[N * M];
    for (int i = 0; i < N * M; i++) {
        arr[i] = i * 0.25;
    }
    return arr;
}

int main()
{
    int x, y;
    Matrix A;
    Matrix B(2, 3);
    A.Input();
    B.Input();
    cout << B << endl;
    cout << "Enter the dimension of the matrix C" << endl;
    cin >> x >> y;
    Matrix C(x, y, FunctInput);
    cout << C << endl;
    A = B * C;
    cout << A << endl;
    cout << A[0][1] << endl;
    system("Pause");
    return 0;
}