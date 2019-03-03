#ifndef MATH_MODEL_H
#define MATH_MODEL_H
#include "tvector.h"
#include "tmatrix.h"

class math_model
{
protected:
    TVector X0;
    long double sampling_increment;
    TMatrix result;
    long double t0, tk;
    int N;
public:
    math_model(): sampling_increment{1e-1}, t0{0.0}, tk{100.}, N{0} {;}
    int get_order() {return X0.size();}
    virtual void get_right(const TVector &X, long double t, TVector &Y) = 0;
    TVector get_initial_coinditions() const {return X0;}
    long double get_sampling_increment()const {return sampling_increment;}
    long double get_t0()const {return t0;}
    long double get_tk()const {return tk;}
    TMatrix get_result()const {return result;}
    virtual void add_resut(const TVector &X, long double t);
    virtual void clear_result();
    virtual void prepare_result();
};

#endif // MATH_MODEL_H
