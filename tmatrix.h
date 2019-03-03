#ifndef TMATRIX_H
#define TMATRIX_H
#include <iostream>
#include <cassert>
#include <cstring>
#include <math.h>

using namespace std;
class TMatrix
{
protected:
    int m_row,m_col;
    long double  **m_data;
public:
    TMatrix();
    TMatrix(int m_row, int m_col);
    TMatrix(const TMatrix& X);
    /*virtual*/ ~TMatrix(); //долго думал нужен виртуальный конструктор или нет, в векторах - виртуальный, тут обычный, и там и там все работает, хз
    void m_show();
    void resize(int m_row, int m_col);
    int rowCount() const {return m_row;}
    int colCount() const {return m_col;}
    int rowHigh() const {return m_row-1;}//возвращает количество элементов
    int colHigh() const {return m_col-1;}//в итоге нигде не использовал, но пусть будет
    long double& operator () (int i, int j)const {return m_data[i][j];}//доступ к элементу
    TMatrix& operator = (const TMatrix& X);
    TMatrix operator + (const TMatrix& X) const;
    TMatrix operator - (const TMatrix& X) const;
    TMatrix operator * (const TMatrix& X) const;
    TMatrix operator * (long double x) const;
    TMatrix& transpose ();
    TMatrix I (int m_row);//формирование единичной матрицы, исходную не ломает
    TMatrix operator !()const; //инверс методом Гаусса
    TMatrix& swapRows(int pos, int newPos);
    long double det();//определеитель
    void fillMatrix(char m_name);//метод заполнения, чтобы не городить миллиард for
};

#endif // TMATRIX_H
