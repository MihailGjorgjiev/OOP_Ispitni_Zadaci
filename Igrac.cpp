#include <iostream>
#include <string.h>
using namespace std;

struct Igrac
{
    char ime[15];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra
{
    char ime[20];
    Igrac player[30];
    int broj;
};
void najdobarIgrac(KompjuterskaIgra *lista, int n)
{
    int inx_g=0;
    int pl=0;
    for(int i=0;i<n;i++)
    {
        if(lista[i].broj>pl)
        {
            pl=lista[i].broj;
            inx_g=i;
        }
    }
//    int pts_max=0;
//    int nivo_max=0;
    int inx_l=0;
    for(int i=1;i<lista[inx_g].broj;i++)
    {
        if(lista[inx_g].player[inx_l].poeni<lista[inx_g].player[i].poeni)
        {
//            pts_max=lista[inx_g].player[i].poeni;
            inx_l=i;
//            continue;
        }
        else if(lista[inx_g].player[inx_l].poeni==lista[inx_g].player[i].poeni)
        {
            if(lista[inx_g].player[inx_l].nivo<lista[inx_g].player[i].nivo)
            {
//                pl=lista[inx_g].player[i].nivo;
                inx_l=i;
//                continue;
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<lista[inx_g].player[inx_l].ime;
    cout<<" koj ja igra igrata "<<lista[inx_g].ime<<endl;
}
int main()
{
    KompjuterskaIgra k[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>k[i].ime;
        cin>>k[i].broj;
        for(int j=0;j<k[i].broj;j++)
        {
            cin>>k[i].player[j].ime;
            cin>>k[i].player[j].nivo;
            cin>>k[i].player[j].poeni;
        }
    }
    najdobarIgrac(k,n);
    return 0;
}

