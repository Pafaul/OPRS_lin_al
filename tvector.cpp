#include "tvector.h"
using namespace std;

TVector::TVector()
{
    v_length = 0;
    v_data = NULL; // возможно следует делать так: if(v_data) {delete[]v_data;} v_data = nullptr;
}
TVector::TVector(int length)
{
    v_length = 0;
    v_data = NULL;
    resize(length);
}

TVector::TVector(const TVector &arg)
{
    resize(arg.size());
    for ( int i = 0; i < size(); i++) v_data[i] = arg[i];
}
void TVector::resize(int length)
{
    /*чтобы скопировать один динам масив в другой (в общем случае разных длин) необходимо:
    1) создать новый пустой динам массив той же длины, что и копируемый
    2) любым способом переместить элементы
    3) удалить старый массив, чтобы не было утечек в памяти
    */
    long double *new_data = new long double[length]; //1)
    if(v_data) //если v_data не nullptr
    {
        int min_length = (this->v_length < length) ? this->v_length : length; //выбирыаем длину нового массива, как меньшую из текущей и новой
        memcpy(new_data, this->v_data, sizeof(long double)*min_length); //из текущего массива перемещаем количество элементов
        v_data = NULL;                                                  //sizeof(long double)*min_length в новый массив      
                                                                        //оставшиеся элементы удаляем
    }
       this->v_data = new_data; 
       v_length = length;
}

void TVector::v_show() const
{
    int counter = 0;
    if(v_data == NULL)
        cout<<"Vector is not inicialize!"<<endl;
    for (counter = 0; counter < v_length ; counter++ ){
        cout <<"  "<< v_data[counter] << "|";
    }
    cout<<endl;
}
void TVector::v_show(int n) const
{
    if (n > v_length)
        cout<<"В векторе меньше элементов, чем требуется вывести!"<<endl;
    for(int i = 0; i <= n - 1; i++)
    {
        cout<<v_data[i]<<"|";
    }
    cout<<endl;
}
TVector& TVector::operator = (const TVector& arg)
{ // смысл тот же, как в resize - если текущий вектор и тот, к который копируем, разных размеров, если текущий не пустой - 
    // удаляем все содержимое, переопределяем динам масив v_data длинной равной длине вектора, который копируем
    if(v_length != arg.v_length)
    {
        if(v_data)
            v_data = NULL; //delete[]v_data; v_data = nullptr; // ~TVector(); возможно стоит делать так, или же вызывать деструктор
        v_data = new long double(arg.v_length);
        v_length = arg.v_length;
    }
    // полностью копируем массив - аргумент в текущий массив.
    memcpy(v_data,arg.v_data, sizeof(long double)*v_length);
    return *this;
}
TVector::~TVector()
{// просто все удаляем
    if(v_data)
        v_data = NULL; //delete[]v_data; v_data = nullptr; возможно это делается так, надо тестить
    v_length = 0;
}
TVector TVector::operator *(long double arg) const //умножение вектора на число
{
    TVector res;
    for(int i = 0; i < v_length; i++)
    {
        res[i] = v_data[i] * arg;
    }
    return res;
}
long double TVector::operator *(const TVector& arg) const // скалярно умножение 
{
    assert(v_length == arg.v_length);
    long double res = 0;
    for(int i = 0; i < arg.v_length; i++)
    {
        res += v_data[i]*arg[i];
    }
    return res;
}
TVector TVector::operator ^ (const TVector& arg) const //векторное умножение, по хорошему нужно сделать для любого случая
{
    assert(v_length == arg.v_length);
    TVector res(3);
    res[0] = v_data[1]*arg[2] - arg[1]*v_data[2];
    res[1] = v_data[2]*arg[0] - arg[2]*v_data[0];
    res[2] = v_data[0]*arg[1] - arg[0]*v_data[1];
    return res;
}
long double TVector::vector_length(bool screen) // длина вектора, bool screen - выводить на экран или нет
{
    long double res = 0;
    for(int i = 0 ; i < v_length; i++)
    {
        res+=v_data[i]*v_data[i];
    }
    if (screen)
        cout<<"vector's length = "<<sqrt(res)<<endl;
    return sqrt(res);
}
TVector& TVector::normalize() //нормализация вектора, каждый элемент делим на длину
{
    long double length = vector_length(false);
    for(int i = 0; i < v_length; i++)
    {
        v_data[i] /=length;
    }
    return *this;
}
