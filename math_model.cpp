#include "math_model.h"

void math_model::add_resut(const TVector &X, long double t)
{
    if (N ==result.rowCount())
        result.resize(N+1,get_order()+1);
    result(N,0) = t;
    for(int i = X.size(); i > 0; i--)
            result(N,i) = X[i-1];
    N++;
}
void math_model::clear_result()
{
    result.resize(0,0);
    N= 0;
}
void math_model::prepare_result()
{
    result.resize((int)((tk-t0)/sampling_increment)+1, get_order()+1);
    N = 0;
}
