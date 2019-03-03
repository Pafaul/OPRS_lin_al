#ifndef ARENSTORPH_MODEL_H
#define ARENSTORPH_MODEL_H
#include "tvector.h"
#include "tmatrix.h"
#include "math_model.h"

class Arenstorph_model : public math_model
{
    protected:
        double mu, mu1;

    public:
        Arenstorph_model(): mu(0.012277471), mu1(1.0-mu) {;}
        Arenstorph_model(double t0, double tk, double sampling_increment, const TVector &X);        
        void get_right(const TVector &X, long double t, TVector &Y);
        ~Arenstorph_model();
};

#endif
