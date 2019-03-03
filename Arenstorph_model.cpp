#include "Arenstorph_model.h"

Arenstorph_model::Arenstorph_model(double t0, double tk, double sampling_increment, const TVector &X)
{
    this->t0 = t0;
    this->tk = tk;
    this->sampling_increment = sampling_increment;
    this->X0 = X;
}

void Arenstorph_model::get_right(const TVector &X, long double t, TVector &Y)
{
    double d1 = powl((powl((X[0]+mu), 2) + X[1]*X[1]), 1.5);
    double d2 = powl((powl((X[0]-mu1), 2) + X[1]*X[1]), 1.5);
    Y[0] = Y[2];
    Y[1] = Y[3];
    Y[2] = X[0] + 2*X[3] - mu1*(X[0]+mu)/d1 - mu*(X[0]-mu1)/d2;
    Y[3] = X[1] - 2*X[2] - mu1*X[1]/d1 - mu*X[1]/d2;
}


Arenstorph_model::~Arenstorph_model()
{
    X0.~TVector();

}
