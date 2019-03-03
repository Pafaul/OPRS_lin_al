#ifndef CUSTOM_H
#define CUSTOM_H
#include "math_model.h"

class TArenstorfModel: public math_model
{
protected:
    static const long double m;
public:
    TArenstorfModel();
    void getRight(const TVector& X, long double t, TVector& Y);
};

#endif // CUSTOM_H
