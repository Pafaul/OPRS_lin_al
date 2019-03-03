#include "integrator.h"
#include "Arenstorph_model.h"
#include "tvector.h"
using namespace std;

int main()
{
    TVector* X0 = new TVector(4);
    X0[0] = 0.994; X0[1] = 0.0;
    X0[2] = 0.0; X0[3] = -2.00158510637908252240537862224;
    Arenstorph_model* model = new Arenstorph_model(0, 100, 0.1, *X0);
    DormanPrinceIntegrator* integrator = new DormanPrinceIntegrator();
    integrator->run(model);
    model->~Arenstorph_model();
    integrator->~DormanPrinceIntegrator();
    X0->~TVector();
    return 0;
};
