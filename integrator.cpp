#include "integrator.h"

const long double DormanPrinceIntegrator::c[7] = { 0, 1./5, 3./10, 4./5, 8./9, 1.l, 1.l };
const long double DormanPrinceIntegrator::a[7][6] =
{
    { 0. },
    { 1./5 },
    { 3./40, 9./40 },
    { 44./45, -56./15, 32./9 },
    { 19372./6561, -25360./2187, 64448./6561, -212./729 },
    { 9017./3168, -355./33, 46732./5247, 49./176, -5103./18656 },
    { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84 }
};
const long double DormanPrinceIntegrator::b1[7] = { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84, 0 };
const long double DormanPrinceIntegrator::b2[7] = { 5179./57600, 0., 7571./16695, 393./640, -92097./339200, 187./2100, 1./40 };

long double DormanPrinceIntegrator::run(math_model* model)
{
    double b = 1,d = 1, zero_val = 1;
    while (b+zero_val > d){
        zero_val /= 2.0;
    }
    long double e = 0, t = model->get_t0(), tk = model->get_tk(), t_out = t,
                h = 0, h_new = model->get_sampling_increment();
    TVector X = model->get_initial_coinditions(),
            X1( X.size() ), X2( X.size() ), Xout( X.size() ), Y( X.size() );
    model->prepare_result();

    for (int i = 0; i < 7; i++) K[i].resize(i);

    int N = 0;

    while ( t < tk )
    {
        h = h_new;

        for ( int j = 0; j < 7; j++ )
        {
            for ( int k = 0; k < X.size(); k++ )
            {
                Y[k] = X[k];
                for ( int s = 0; s < j; s++ )
                {
                    Y[k] = Y[k] + K[s][k] * a[j][s] * h;
                }
            }
            model->get_right( Y, t + c[j] * h, K[j] );
        }

        e = 0;

        for ( int k = 0; k < X.size(); k++ )
        {
            X1[k] = X2[k] = X[k];
            for ( int j = 0; j < 7; j++ )
            {
                X1[k] += K[j][k] * b1[j] * h;
                X2[k] += K[j][k] * b2[j] * h;
            }
            e += powl( h * (X1[k] - X2[k]) / max( max( fabsl(X[k]), fabsl(X1[k]) ), max((long double)1e-5, 2*zero_val/eps) ) , 2 );
        }
        e = sqrtl( e / X.size() );

        h_new = h / fmax( 0.1, fmin( 5., powl(e / eps, 0.2)/0.9 ) );

        if (e > this->getEps()) continue;

        while ( (t_out < t + h) && (t_out <= tk) )
        {
            long double l_ldTheta = (t_out - t)/h,
                                b[6];

            b[0] = l_ldTheta * ( 1 + l_ldTheta*(-1337./480. + l_ldTheta*(1039./360. + l_ldTheta*(-1163./1152.))));
            b[1] = 0;
            b[2] = 100. * powl(l_ldTheta, 2) * (1054./9275. + l_ldTheta*(-4682./27825. + l_ldTheta*(379./5565.)))/3.;
            b[3] = -5. * powl(l_ldTheta, 2) * (27./40. + l_ldTheta*(-9./5. + l_ldTheta*(83./96.)))/2.;
            b[4] = 18225. * powl(l_ldTheta, 2) * (-3./250. + l_ldTheta*(22./375. + l_ldTheta*(-37./600.)))/848.;
            b[5] = -22. * powl(l_ldTheta, 2) * (-3./10. + l_ldTheta*(29./30. + l_ldTheta*(-17./24.)))/7.;

            for ( int k = 0; k < X.size(); k++ )
            {
                long double l_ldSum  = 0;
                for ( int j = 0; j < 6; j++ )
                    l_ldSum += b[j] * K[j][k];
                    Xout[k] = X[k] + h * l_ldSum;
            }

            model->add_resut( Xout, t_out );

            t_out += model->get_sampling_increment();
        }

        X = X1;
        t += h;

        N++;
    }

    return 0;
}

DormanPrinceIntegrator::~DormanPrinceIntegrator()
{
    for (int i = 0; i < 7; i++) K[i].~TVector();
    
}
