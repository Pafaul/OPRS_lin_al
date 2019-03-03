#include "white_noise.h"

using namespace std;
white_noise::white_noise()
{
    t_corr = 2*3.14159/w;
}
vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}
vector<string> split(const std::string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
long double white_noise::get_nu(long double time)
{
    ifstream w_n_file("/home/nikonikoni/QtProjects/OPRS/linearAlgebra/w_n_file.txt");
    string str;
    getline(w_n_file, str);
    vector<string> nu_time = split(str, '|');
    int number = (int)(time/t_corr);
    long double res = stold(nu_time[number]);
    return res;
}
long double white_noise::white_noise_generator()
{
    long double D = 1/t_corr;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<long double> distribution(0.0, 1.0);
    nu_0 = distribution(generator)*pow(D, 0.5);
    return nu_0;
}
white_noise::~white_noise()
{

}
