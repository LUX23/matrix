#include <iostream>
#pragma once

using namespace std;

namespace psychoMatrix {
    class Matrix {
    private:
        double* data; // указатель на место в памяти, где будет хранится первый элемент в матрице
        int N, M; // строки столбцы

        static int counter;
        int id;
    public:
        Matrix();
        Matrix(int N); // квадратная
        Matrix(int N, int M); // прямоугольная
        Matrix(int N, int M, double* (*Function)(int, int)); // создание матрицы с заполнением
        Matrix(const Matrix& Matx); // конструктор копирования
        Matrix(Matrix&& Matx) noexcept; // конструктор перемещения

        void Input(); // заполнить матрицу с клавы
        int GetId() const; // геттер id
        int GetN() const; // геттер количества строк
        int GetM() const; // геттер количества столбцов
        double Get(const int& x, const int& y) const; // геттер заданного элемента
        bool СheckMultiplication(const Matrix& Matx) const;
        bool CheckAddition(const Matrix& Matx) const;
        double Max() const;
        double Min() const;

        class Line { // вложенный класс для двумерной индексации
        private:
            double* arr;
        public:
            Line(double* arr);
            double& operator[](const int& index); // для неконстантных обращений, передаем ссылкой т.к имел смысл менять значение объекта
            double operator[](const int& index) const; // для константных обращений, передаем через копирование, т.к изменять недопускается
        };

        Line operator[](const int& index);
        const Line operator[](const int& index) const; // первая const то что вернет const строку(неизменяемую), второй const гарантируют неизменяемость полей(элементов)
        Matrix& operator=(const Matrix& Matx); // оператор присваивания с копированием, без получения новых матриц
        Matrix& operator=(Matrix&& Matx) noexcept; // оператор присваивания с перемещением
        Matrix& operator+=(const Matrix& Matx); // оператор приблавения матрицы А к матрице B
        Matrix& operator-=(const Matrix& Matx); // оператор вычитания матрицы А из матрицы B
        Matrix& operator*=(const Matrix& Matx); // оператор умножения c присваиванием матрицы А на матрицу B
        Matrix& operator*=(const double& x); // оператор умножения матрицы на скаляр
        friend ostream& operator<<(ostream& strm, const Matrix& Matx);
        ~Matrix();
    };
    Matrix operator+(const Matrix& Matx1, const Matrix& Matx2); // перегрузки с получением новых матриц
    Matrix operator-(const Matrix& Matx1, const Matrix& Matx2);
    Matrix operator*(const Matrix& Matx1, const Matrix& Matx2);
    Matrix operator*(const double& x, const Matrix& Matx);
    Matrix operator*(const Matrix& Matx, const double& x);
}