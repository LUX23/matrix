#include "Matrix.h"
#include <iostream>
#include <string>

#pragma once

using namespace std;

namespace psychoMatrix {

    int Matrix::counter = 0;

    Matrix::Matrix() {
        cout << "The default constructor was triggered(1). Creating a matrix number: " << id << endl;
        this->id = counter; // id присваиваем значение счетчика
        counter++; // прибавляем счетчик
        this->N = 0; // уставнливаем нулевую размерность размерность
        this->M = 0; // уставнливаем нулевую размерность
        this->data = nullptr;
    }

    Matrix::Matrix(int N) {
        cout << "The square matrix constructor worked(2). Creating a matrix number:" << id << endl;
        this->id = counter; // id присваиваем значение счетчика
        counter++; // прибавляем счетчик
        if (N <= 0)
            throw "Matrix(int N) : Matrix(" + to_string(id) + ") : Negative N passed";
        this->N = N;
        this->M = N;
        this->data = new double[N * N];
    }

    Matrix::Matrix(int N, int M) {
        this->id = counter; // id присваиваем значение счетчика
        counter++; // прибавляем счетчик
        cout << "The matrix constructor worked(2). Creating a matrix number:" << id << endl;
        if ((N <= 0) || (M <= 0))
            throw "Matrix(int N, int M) : Matrix(" + to_string(id) + ") : Negative N or M passed";
        this->N = N;
        this->M = M;
        this->data = new double[N * M];
    }
    Matrix::Matrix(int N, int M, double* (*Function)(int, int)) {
        this->id = counter; // id присваиваем значение счетчика
        counter++; // прибавляем счетчик
        if ((N <= 0) || (M <= 0))
            throw "Matrix(int N, int M, double* (*Function)(int, int)) : Matrix(" + to_string(id) + ") : Negative N or M passed";
        cout << "The matrix constructor worked(3). Creating a matrix number:" << id << endl;
        this->N = N;
        this->M = M;
        this->data = Function(N, M);
    }
    Matrix::Matrix(const Matrix& Matx):Matrix(Matx.N, Matx.M) {
        for (int i = 0; i < (this->N * this->M); i++)
            this->data[i] = Matx.data[i];
    }
    Matrix::Matrix(Matrix&& Matx) noexcept {
        this->id = counter; // id присваиваем значение счетчика
        counter++; // прибавляем счетчик
        this->N = Matx.N;
        this->M = Matx.M;
        Matx.N = Matx.M = 0;
        this->data = Matx.data;
        Matx.data = NULL;
    }
    void Matrix::Input() {
        cout << "Enter the matrix" << id << endl;
        for (int i = 0; i < this->N; i++) {
            cout << "Fill in the row of the matrix " << i + 1 << endl;
            for (int j = 0; j < this->M; j++) {
                cin >> this->data[i * this->M + j];
            }
        }
    }
    int Matrix::GetId() const{
        return this->id;
    }
    int Matrix::GetN() const{
        return this->N;
    }
    int Matrix::GetM() const{
        return this->M;
    }
    double Matrix::Get(const int& x, const int& y) const{
        if ((x<0) || (x>=N) || (y<0) || (y>=M))
            throw "Get(const int& x, const int& y) : Matrix(" + to_string(id) + ") : Negative x or y, or x>=N or y>=M passed";
        return this->data[x * this->N + y];
    }
    bool Matrix::СheckMultiplication(const Matrix& Matx) const {
        return (this->M == Matx.GetN());
    }
    bool Matrix::CheckAddition(const Matrix& Matx) const {
        return ((this->M == Matx.GetM()) && (this->N == Matx.GetN()));
    }
    double Matrix::Max() const { // добавить проверку
        double max = this->data[0];
        for (int i = 1; i < this->M * this->N; i++) {
            if (this->data[i] > max)
                max = this->data[i];
        }
        return max;
    }
    double Matrix::Min() const { // добавить проверку
        double min = this->data[0];
        for (int i = 1; i < this->M * this->N; i++) {
            if (this->data[i] < min)
                min = this->data[i];
        }
        return min;
    }
    Matrix::Line::Line(double* arr) : arr(arr) { // arr = arr

    }
    double& Matrix::Line::operator[](const int& index) {
        return this->arr[index];
    }
    double Matrix::Line::operator[](const int& index) const{
        return this->arr[index];
    }
    Matrix::Line Matrix::operator[](const int& index) {
        return Line(this->data + this->M * index);
    }
    const Matrix::Line Matrix::operator[](const int& index) const {
        return Line(this->data + this->M * index);
    }
    Matrix& Matrix::operator=(const Matrix& Matx) {
        if ((this->N != Matx.N) || (this->M != Matx.M)) {
            delete[] this->data; // очистили память
            this->N = Matx.N; // присвоили новые значения
            this->M = Matx.M;
            this->data = new double[this->N * this->M]; // выделили новую память
        }

        for (int i = 0; i < this->N * this->M; i++) // заполняем матрицу элементами
            this->data[i] = Matx.data[i];

        return *this;
    }
    Matrix& Matrix::operator=(Matrix&& Matx) noexcept { // не выбрасывать исключение
        if (&Matx == this)
            return *this;
        this->N = Matx.N;
        this->M = Matx.M;
        delete[] this->data;
        this->data = Matx.data;
        Matx.data = NULL;
        return *this;
    }
    Matrix& Matrix::operator+=(const Matrix& Matx) {
        if (this->CheckAddition(Matx) == 0)
            throw "operator+=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : Matrices have different dimensions";
        for (int i = 0; i < this->N * this->M; i++)
            this->data[i] += Matx.data[i];
        return *this;
    }
    Matrix& Matrix::operator-=(const Matrix& Matx) {
        if (this->CheckAddition(Matx) == 0)
            throw "operator-=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : Matrices have different dimensions";
        for (int i = 0; i < this->N * this->M; i++)
            this->data[i] -= Matx.data[i];
        return *this;
    }
    Matrix& Matrix::operator*=(const Matrix& Matx) { // добавить возможность умножения нулевых матриц
        if (this->СheckMultiplication(Matx) == 0)
            throw "operator*=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : The multiplication condition is not met";



        double* arr = new double[this->N * Matx.M]; // создаем указатель типа double и ставим его на новую ленту в памяти размерностью кол-во строк матрицы A * на кол-во столбцов матрицы B
        double S; //счетчик сумм
        for (int i = 0; i < this->N; i++) { // считаем произведение матрицы строка*столбец
            for (int j = 0; j < Matx.M; j++) {
                S = 0;
                for (int k = 0; k < this->M; k++) {
                    S+= this->data[i * this->M + k] * Matx.data[k * Matx.M + j];
                }
                arr[i * Matx.M + j] = S; // записываем получившиеся в результаты умножения элементы
            }
        }
        delete[] this->data; // очищаем старую ленту
        this->M = Matx.M; // устанавливаем количество стобцов как в матрице B
        this->data = arr; // ставим указатель на новую ленту
        return *this;
    }
    Matrix& Matrix::operator*=(const double& x) {
        for (int i = 0; i < this->N * this->M; i++)
            this->data[i] *= x;
        return *this;
    }
    ostream& operator<<(ostream& strm, const Matrix& Matx) {
        int width = strm.width();
        for (int i = 0; i < Matx.N; i++) {
            for (int j = 0; j < Matx.M; j++) {
                if (width == 0)
                    strm.width(7);
                else
                    strm.width(width);
                strm << Matx.data[i * Matx.M + j];
            }
            strm << "\n";
        }
        return strm;
    }
    Matrix::~Matrix()
    {
        cout << "\n\tDestructor" << id << "\n";
        delete[] this->data;
    }
    Matrix operator+(const Matrix& Matx1, const Matrix& Matx2) {
        return move(Matrix(Matx1) += Matx2);
    }
    Matrix operator-(const Matrix& Matx1, const Matrix& Matx2) {
        return move(Matrix(Matx1) -= Matx2);
    }
    Matrix operator*(const Matrix& Matx1, const Matrix& Matx2) {
        return move(Matrix(Matx1) *= Matx2);
    }
    Matrix operator*(const double& x, const Matrix& Matx) {
        return move(Matrix(Matx) *= x);
    }
    Matrix operator*(const Matrix& Matx, const double& x) {
        return move(Matrix(Matx) *= x);
    }
}