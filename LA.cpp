#include "LA.h"
#include <cstring>
#include <math.h>

TVector::TVector() : n(0), data(nullptr) {}

TVector::TVector(unsigned long int n) : n(0), data(nullptr)
{
    resize(n);
}

TVector::TVector(const TVector& rval) : n(0), data(nullptr)
{
    *this = rval;
}

TVector& TVector::operator = (const TVector& rval)
{
    if (n != rval.n)
    {
        if (data)
        {
            delete[] data;
        }

        data = new double[rval.n];
        n = rval.n;
    }

    memcpy(data, rval.data, sizeof(double)*n);

    return (*this);
}

TVector::~TVector()
{
    if(data)
    {
        delete[] data;

        n = 0;
        data = nullptr;
    }
}

void TVector::resize(unsigned long n)
{
    if (n == this->n)
        return;

    double *newData = new double[n];

    if (data)
    {
        unsigned long min_n = (this->n < n) ? this->n : n;
        memcpy(newData, data, sizeof(double)*min_n);

        delete[] data;
    }
    data = newData;
    this->n = n;
}

double TVector::length() const
{
    double l = 0;

    for (unsigned long i = 0; i < n; i ++)
        l += data[i]*data[i];
    return sqrt(l);
}

TVector TVector::operator - () const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = - data[i];

    return V;
}

TVector TVector::operator - (const double rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = data[i] - rval;

    return V;
}

TVector TVector::operator - (const TVector& rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = data[i] - rval[i];

    return V;
}

TVector TVector::operator + (const double rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = data[i] + rval;

    return V;
}

TVector TVector::operator + (const TVector& rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = data[i] + rval[i];

    return V;
}

TVector TVector::operator ^ (const TVector& rval) const
{
    TVector V(3);

    V[0] = data[1]*rval[2] - rval[1]*data[2];
    V[1] = data[2]*rval[0] - rval[2]*data[0];
    V[2] = data[0]*rval[1] - rval[0]*data[1];

    return V;
}

double TVector::operator * (const TVector& rval) const
{
    double res = 0.0;

    for (unsigned long i = 0; i < n; i++)
        res += data[i]*rval[i];

    return res;
}

TVector TVector::operator * (const double rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
        V[i] = data[i]*rval;

    return V;
}

TMatrix::TMatrix() : n(0), m(0), data(nullptr) {}

TMatrix::TMatrix(unsigned long n, unsigned long m) : n(n), m(m)
{
    resize(n, m);
}

TMatrix::TMatrix(const TMatrix& rval)
{
    (*this) = rval;
}

TMatrix& TMatrix::operator =(const TMatrix& rval)
{
    if (this != &rval)
    {
        this->~TMatrix();

        resize(rval.n, rval.m);

        for (unsigned long i = 0; i < n; i++)
            memcpy(data[i], rval.data[i], sizeof(double)*m);
    }

    return (*this);
}

TMatrix::~TMatrix()
{
    if (data)
    {
        for (unsigned long i = 0; i < n; i++)
            delete[] data[i];

        delete[] data;
        data = nullptr;
        n = m = 0;
    }
}

void TMatrix::resize(unsigned long n, unsigned long m)
{
    unsigned long min_n = (this->n < n) ? this->n : n;

    if(this->m != m)
    {
        unsigned long min_m = (this->m < m) ? this->m : m;

        for (unsigned long i = 0; i < min_n; i++)
        {
            double * newDataRow = new double [m];
            memcpy(newDataRow, data[i], sizeof(double)*min_m);
            delete[] data[i];
            data[i] = newDataRow;
        }

        this->m = m;
    }

    if (this->n != n)
    {
        double **newData = new double*[n];

        memcpy(newData, data, sizeof(double*)*min_n);
        for (unsigned long i = n; i < this->n; i++)
                newData[i] = new double[m];

        data = newData;
        this->n = n;
    }
}

TMatrix TMatrix::operator - () const
{
    TMatrix M(n, m);

    for (unsigned long i = 0; i < n; i++)
        for (unsigned long j = 0; j < m; j++)
            M(i, j) = -data[i][j];

    return M;
}

TMatrix TMatrix::operator - (const TMatrix& rval) const
{
    TMatrix M(n, m);

    for (unsigned long i = 0; i < n; i++)
        for (unsigned long j = 0; j < m; j++)
            M(i, j) = data[i][j] - rval(i,j);

    return M;
}


TMatrix TMatrix::operator + (const TMatrix& rval) const
{
    TMatrix M(n, m);

    for (unsigned long i = 0; i < n; i++)
        for (unsigned long j = 0; j < m; j++)
            M(i, j) = data[i][j] + rval(i, j);

    return M;
}

TMatrix TMatrix::operator * (const double rval) const
{
    TMatrix M(n, m);

    for (unsigned long i = 0; i < n; i++)
        for (unsigned long j = 0; j < m; j++)
            M(i, j) = data[n][m] * rval;

    return M;
}

TMatrix TMatrix::operator * (const TMatrix& rval) const
{
    TMatrix M(n, rval.m);

    for (unsigned long i = 0; i < M.n; i++)
        for (unsigned long j = 0; j < M.m; j++)
        {
            M(i, j) = 0;
            for (unsigned long k = 0; k < m; k++)
                M(i,j) += data[i][k] * rval(k, j);
        }

    return M;
}

TVector TMatrix::operator * (const TVector& rval) const
{
    TVector V(n);

    for (unsigned long i = 0; i < n; i++)
    {
        V[i] = 0;
        for (unsigned long j = 0; j < m; j++)
            V[i] += data[i][j] * rval[j];
    }

    return V;
}

TMatrix TMatrix::t () const
{
    TMatrix M(m, n);

    for (unsigned long i = 0; i < n; i++)
        for (unsigned long j = 0; j < m; j++)
            M(i,j) = data[j][i];

    return M;
}

TMatrix TMatrix::E(unsigned long n)
{
    TMatrix E (n, n);

    for (unsigned long i = 0; i < n; i++)
        E(i, i) = 1;

    return E;
}

TMatrix TMatrix::operator ! () const
{
    TMatrix X( E(n) ),
    A(*this);

    double tmp;

    for (unsigned long i = 0; i < n; i++)
    {
        if (A(i,i) == 0)
        {
            for (unsigned long k = i+1; k < n; k++)
                if (A(k,i) != 0)
                {
                    A.swapRows(i, k);
                    X.swapRows(i, k);

                    break;
                }
        }

        for (unsigned long j = 0; j < n; j++)
        {
            A(i, j) /= tmp;
            X(i, j) /= tmp;
        }

        for (unsigned long k = 0; k < n; k++)
            if (k != i)
            {
                tmp = A(k, i);

                for (unsigned long j = 0; j < n; j++)
                {
                    A(k, j) -= A(i, j) * tmp;
                    X(k, j) -= X(i, j) * tmp;
                }
            }
    }

    return X;
}


/* Function swap rows	*/
TMatrix& TMatrix::swapRows(unsigned long i, unsigned long j)
{
    double buf;

    for (unsigned long k = 0; k < m; k++)
    {
        buf = data[i][k];
        data[i][k] = data[j][k];
        data[j][k] = buf;
    }

    return *this;
}
