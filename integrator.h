#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "math_model.h"
class Integrator {
protected:
    long double eps {1E-16};
public:
    Integrator() : eps(1E-16) {}
    inline void setEps(long double eps) { this->eps = eps; }
    inline long double getEps() { return this->eps; }
    virtual long double run(math_model * model) = 0;
    ~Integrator();
};

class DormanPrinceIntegrator : public Integrator {
protected:
    static const long double c[7], a[7][6], b1[7], b2[7];
    TVector K[7];
public:
    DormanPrinceIntegrator();
    virtual long double run(math_model *model);
    virtual ~DormanPrinceIntegrator();
};
#endif // INTEGRATOR_H
