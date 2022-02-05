#include <iostream>
#include <string.h>
using namespace std;

struct Voz
{
    char relacija[50];
    double kilometri;
    int patnici;
};

struct ZeleznickaStanica
{
    char grad[20];
    Voz vozovi[30];
    int broj;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
{

    int inx=0;
    int jnx=0;
    double rel=999999;
    int city=strlen(grad);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<zs[i].broj;j++)
        {
            if(zs[i].vozovi[j].kilometri<=rel && strncmp(zs[i].vozovi[j].relacija,grad,city)==0)
            {
                inx=i;
                jnx=j;
                rel=zs[i].vozovi[j].kilometri;
//            cout<<zs[i].vozovi[j].kilometri<<" 1 "<<rel<<endl;
            }

        }
    }
    cout<<"Najkratka relacija: "<<zs[inx].vozovi[jnx].relacija<<" ("<<zs[inx].vozovi[jnx].kilometri<<" km)"<<endl;

}

int main(){

    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        for(i=0;i<n;i++)
    {
        cin>>zStanica[i].grad;
        cin>>zStanica[i].broj;

        for(int j=0;j<zStanica[i].broj;j++)
        {
            cin>>zStanica[i].vozovi[j].relacija;
            cin>>zStanica[i].vozovi[j].kilometri;
            cin>>zStanica[i].vozovi[j].patnici;
        }
    }
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}


