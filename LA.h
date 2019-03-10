#ifndef TVECTOR_H
#define TVECTOR_H

class TMatrix;

class TVector
{
protected:
    unsigned long int n;
    double* data;
public:
    TVector();
    TVector(unsigned long n);
    TVector(const TVector& rval);

    virtual ~TVector();

    inline unsigned long size() const { return n; }

    void resize(unsigned long n);

    inline double& operator[](unsigned long i) const { return data[i]; }
    TVector& operator = (const TVector& rval);

    double length() const;

    TVector operator - () const;
    TVector operator - (const double rval) const;
    TVector operator - (const TVector& rval) const;

    TVector operator + (const double rval) const;
    TVector operator + (const TVector& rval) const;

    TVector operator ^ (const TVector& rval) const;

    double operator * (const TVector& rval) const;
    TVector operator * (const double rval) const;

};

class TMatrix
{
protected:
    unsigned long n, m;

    double **data;

public:
    TMatrix();

    TMatrix(unsigned long n, unsigned long m);

    TMatrix(const TMatrix &rval);

    TMatrix& operator = (const TMatrix& rval);

    virtual ~TMatrix();

    inline unsigned long rowCount() const { return n; }
    inline unsigned long colCount() const { return m; }

    void resize( unsigned long n, unsigned long m );

    TMatrix& swapRows(unsigned long i, unsigned long j);

    inline double& operator() (unsigned long i, unsigned long j) { return data[i][j]; }
    inline const double& operator() (unsigned long i, unsigned long j) const { return data[i][j]; }

    TMatrix operator - () const;
    TMatrix operator - (const TMatrix& rval) const;
    TMatrix operator + (const TMatrix& rval) const;
    TMatrix operator * (const double rval) const;
    TMatrix operator * (const TMatrix& rval) const;
    TVector operator * (const TVector& rval) const;
    TMatrix operator !() const;

    TMatrix t() const;

    static TMatrix E(unsigned long n);

};



#endif // TVECTOR_H
