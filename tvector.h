#ifndef TVECTOR_H
#define TVECTOR_H
#include <iostream>
#include <cassert>
#include <cstring>
#include <math.h>

using namespace std;
class TVector
{
private:
    int v_length;
    long double* v_data; //указатель на первый элемент массива
public:
  TVector(); //конструктор по умолчанию
  TVector(int length);//конструктор по размеру
  TVector(const TVector& arg);//конструктор копирования, не реализован 
  virtual ~TVector(); //виртуальный деструктор
  int size()const {return v_length;} //возвращаем размер вектора
  void resize(int length);
  TVector& operator = (const TVector& arg);
  long double& operator [] (int i)const {return v_data[i];}//опереатор доступа к элементу
  long double operator * (const TVector& arg)const;
  TVector operator * (long double arg)const;
  TVector operator ^ (const TVector& arg)const;
  TVector operator + (const TVector& arg)const;
  TVector operator - (const TVector& arg)const;
  TVector& normalize();
  long double vector_length(bool screen);
  void v_show() const; //метод вывода вектора на экран
  void v_show(int n) const; //метод вывода вектора на экран (n первых элементов)
};

#endif // TVECTOR_H
