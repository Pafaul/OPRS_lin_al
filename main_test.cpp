#include "tvector.h"
#include "tmatrix.h"
#include "white_noise.h"
using namespace std;

int main_test()
{
    //просто последний тест с методом Гаусса, тест-прогу не делал
    /*TMatrix M(3,3);
    TMatrix N(2,8);
    M.fillMatrix('M');
    N = M;
    N = !N;
    N.m_show();
    N = !N;
    N.m_show();
    cout<<N.det()<<endl;*/
    ofstream fout, tstout;
    fout.open("/home/nikonikoni/QtProjects/OPRS/linearAlgebra/w_n_file.txt");
    tstout.open("/home/nikonikoni/QtProjects/OPRS/linearAlgebra/w_n_test.txt");
    //if (fout) {cout<<"test";}
    //if(tstout) {cout<<"test1";}
    white_noise wn;
    int counter = 0;
    long double time = 0;
    while(counter < 10000)
    {    counter++;
        fout<<wn.white_noise_generator()<<"|";
        //cout<<wn.white_noise_generator()<<endl;
       // cout<<counter<<endl;
    }
    while (time <= 2*wn.t_corr)
    {
        tstout<<wn.get_nu(time)<<endl;
        cout<<time<<endl;
        time +=0.0001;
    }
   // cout<<counter;
    fout.close();
    tstout.close();
}
