#include "custom.h"

using namespace std;
int sgn(long double val)
{
   return (val>0)?(1):((val<0)?(-1):(0));
}
const long double TArenstorfModel::m = 0.012277471;
TArenstorfModel::TArenstorfModel():math_model()
{
    X0.resize(4);
    X0[0] = 0.994; //y1
    X0[1] = 0;     //y2
    X0[2] = 0;     //y1'
    X0[3] = -2.00158510637908252240537862224; //y2'
}
void TArenstorfModel::getRight(const TVector &X, long double t, TVector &Y)
{
    Y.resize(4);
    long double D1 = pow(pow(X[0]+m,2)+pow(X[1],2),1.5);
    long double D2 = pow(pow(X[0]-(1-m),2)+pow(X[1],2),1.5);
    Y[0] = X[2];
    Y[1] = X[3];
    Y[2] = X[0]+2*X[3]-(1-m)*(X[0]+m)/D1-m*(X[0]-(1-m))/D2;
    Y[3] = X[1]-2*X[2]-(1-m)*X[1]/D1-m*X[1]/D2;
}
