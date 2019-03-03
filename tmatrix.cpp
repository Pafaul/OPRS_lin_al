#include "tmatrix.h"

TMatrix::TMatrix()
{
    m_data = NULL;
    m_row = m_col = 0;
}
TMatrix::TMatrix(int m_row, int m_col)
{
    this->m_row = this->m_col = 0;
    m_data = nullptr;
    resize(m_row, m_col);
}
void TMatrix::m_show()
{
    int i{0}, j{0};
    if(m_data == NULL)
        cout<<"Matrix is not inicialize!"<<endl;
    for(i = 0; i < m_row; i++){
        for(j = 0; j < m_col; j++){
            if(j == 0) {cout<<"\t"<<"|";}
            cout<<m_data[i][j]<<"|";
         }
        cout<<endl;
    }
    cout<<endl;
}
TMatrix::~TMatrix()
{//просто все удаляем
    if(m_data)
    {
        for(int i = 0; i < m_row - 1; i++)
            delete [] m_data[i];
        delete[] m_data;
    }
    m_data = nullptr;//плесс чекни чем отличается результат, если мы просто сделаем delete[]m_data или же m_data = nullptr (нуль поинтер) 
    m_row = m_col = 0;

}
void TMatrix::resize(int m_row, int m_col)
{
    //по смылсу то же, что и в векторах, только как дял строк, так и для столбцов
    int min_row = this->m_row < m_row ? this->m_row : m_row;
    if (this->m_col != m_col)
        {
            int min_col = this->m_col < m_col ? this->m_col : m_col;
            for (int i = 0; i < min_row; i++)
            {
                long double *newDataRow = new long double[ m_col ];
                memcpy(newDataRow, m_data[i], sizeof(long double)*min_col);
                delete[] m_data[i];
                m_data[i] = newDataRow;
            }
                this->m_col = m_col;
        }
    if (this->m_row != m_row)
        {
            long double **newData = new long double*[ m_row ];
            memcpy(newData, m_data, sizeof(long double)*min_row);
            for (int i = m_row; i < this->m_row; i++)
                delete[] m_data[i];
             if (m_data)
                delete[] m_data;
             for (int i = this->m_row; i < m_row; i++)
                newData[i] = new long double[ m_col ];
             m_data = newData;
             this->m_row = m_row;
        }
}
TMatrix& TMatrix::operator = (const TMatrix& X)
{
    if(this != &X) //если наша матрица не есть матрица, которую хотим скопировать
    {
        this->~TMatrix(); //удаляем ее
        resize(X.m_row, X.m_col); //выставляем требуемы размер
        for(int i = 0; i < m_row; i++)//поэлеметно перетаскиваем коипруемую матрицу в нашу матрицу
            memcpy(m_data[i], X.m_data[i], sizeof(long double)*m_row);
    }

    return *this; //иначе возвращаем ее же

}
TMatrix TMatrix::operator + (const TMatrix& X)const
{
    assert(m_row == X.m_row && m_col == X.m_col);
    TMatrix Result(m_row, m_col);
    for(int i = 0; i < m_row; i++)
    {
        for(int j = 0; j < m_col; j++){
            Result(i,j) = m_data[i][j] + X(i,j);
        }
    }
    return Result;
}
TMatrix TMatrix::operator - (const TMatrix& X)const
{
    assert(m_row == X.m_row && m_col == X.m_col);
    TMatrix Result(m_row, m_col);
    for(int i = 0; i < m_row; i++)
    {
        for(int j = 0; j < m_col; j++){
            Result(i,j) = m_data[i][j] - X(i,j);
        }
    }
    return Result;
}
TMatrix TMatrix::operator * (const TMatrix& X)const
{
    assert(this->m_col == X.m_row);
    TMatrix Result(m_row, X.m_col);
    for(int i = 0; i < Result.m_row; i++)
    {
        for(int j = 0; j < Result.m_col; j++)
        {
            Result(i,j) = 0;
            for(int k = 0; k < m_col; k++)
            {
                Result(i,j) += m_data[i][k]*X(k,j);
            }
        }
    }
    return Result;
}
void TMatrix::fillMatrix(char m_name)
{
    cout<<"Method of set the matrix "<<m_name<<endl;
    long double element{0};
    for(int i = 0; i < m_row; i++)
    {
        for(int j = 0; j < m_col; j++)
        {
            cout<<"Input the ("<<i<<", "<<j<<") element: ";
            cin >> element;
            m_data[i][j] = element;
            //cout<<endl;
        }
    }
    this->m_show();
   // cout<<endl;

}
TMatrix TMatrix::operator *(long double x)const
{
    TMatrix Result(this->m_row, this->m_col);
    for(int i = 0; i < m_row; i++)
        for(int j = 0; j < m_col; j++)
            Result(i,j) = m_data[i][j]*x;
    return Result;
}
TMatrix& TMatrix::transpose()
{
    assert(this->m_row == this->m_col);
    for(int i = 0; i < m_row -1 ; i++)
        for(int j = i + 1; j < m_row; j++)
           std::swap(m_data[i][j], m_data[j][i]);
    return *this;
}
long double TMatrix::det()
{//да да, тот самый рекурсивный метод, мне он нравится
    int i,j;
    long double det = 0;
    assert(this->m_row == this->m_col);
    if(m_row == 1)
        {
            det = m_data[0][0];
        }
    else if(m_row == 2)
        {
            det = m_data[0][0]*m_data[1][1]-m_data[0][1]*m_data[1][0];
        }
    else
        {
            TMatrix M(m_row-1, m_row-1);
            for(i = 0; i < m_row; i++)
                {
                for(j = 0; j < m_row - 1; j++)
                {
                    if(j < i)
                        {
                            for(int k = 0; k < m_row; k++)
                            {
                                M(j,k) = m_data[j][k];
                            }

                    }else{
                        for(int k = 0; k < m_row; k++)
                            {
                                M(j,k)=m_data[j+1][k];
                            }
                        }
                }
                    det+=pow(-1, (i+j))*M.det()*m_data[i][m_row-1];
                }
            }
    return det;
}
TMatrix TMatrix::I(int m_row)
{
    TMatrix I(m_row,m_row);
    for (int i = 0; i < m_row; i++){
        I(i,i) = 1;
        for(int j = i + 1; j < m_row; j++)
            {
                I(i,j) = I(j,i) = 0;
            }
        }
    return I;

}
TMatrix& TMatrix::swapRows(int pos, int newPos)
{
    long double tmp_cell;
    for(int k = 0; k < m_row; k++)
        {
            tmp_cell = m_data[pos][k];
            m_data[pos][k] = m_data[newPos][k];
            m_data[newPos][k] = tmp_cell;
        }
    return *this;
}
TMatrix TMatrix::operator !()const
{
    TMatrix R(m_row,m_row); //эту матрицу будем возвращать из метода, чтобы не ломать исходную
            TMatrix M;//в эту матрицу скопируем исходную матрицу
            M = *this;//чтобы так же не ломать исходную
            TMatrix I(m_row,m_row);
            I = I.I(m_row);
            long double element = 0;
            for(int i = 0; i < m_row; i++){
                element = m_data[i][i];
                if(element == 0){//если на главной диагонали нулевой элемент, меняем строки местами
                    bool swapFlag = false;
                    for(int s = i; s < m_row; s++){
                        if(m_data[s][i] != 0){
                            swapFlag = true;
                            M.swapRows(i,s);
                            I.swapRows(i,s);
                        }
                    }
                    if(swapFlag == false)
                        break;
                }//далее все по алгоритму. впринципе работает корректно
                element = m_data[i][i];
                for(int k = 0; k < m_row; k++){
                    m_data[i][k] = m_data[i][k]/element;
                    I(i,k) = I(i,k)/element;
                }
                double c = 0;
                for(int k = 0; k < m_row; k++){
                    if(k == i) continue;
                    c = m_data[k][i];
                    for(int p = 0; p < m_row; p++){
                        m_data[k][p] = m_data[k][p] - c*m_data[i][p];
                        I(k,p) = I(k,p) - c*I(i,p);
                        R(k,p) = I(k,p);
                    }
                }
            }
            for(int i = 0; i < m_row; i++){
                for(int j = 0; j < m_row; j++){
                    R(i,j) = I(i,j);
                }
            }
    return R;
}

