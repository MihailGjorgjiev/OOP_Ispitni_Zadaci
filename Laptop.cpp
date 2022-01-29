#include <iostream>
#include <string.h>

using namespace std;

struct Laptop
{
    char firma[100];
    float monitor;
    bool touch;
    int cena;
};

struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop niza[100];
    int broj;
};
void print(ITStore *s,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<s[i].ime<<" "<<s[i].lokacija<<endl;
        for(int j=0;j<s[i].broj;j++)
        {
            cout<<s[i].niza[j].firma<<" "<<s[i].niza[j].monitor<<" "<<s[i].niza[j].cena<<endl;
        }
    }
}

void najeftina_ponuda(ITStore *s,int n)
{
    int cena_min=99999;
    int inx=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<s[i].broj;j++)
        {
            if(s[i].niza[j].touch==true && cena_min>s[i].niza[j].cena)
            {
                inx=i;
                cena_min=s[i].niza[j].cena;
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    cout<<s[inx].ime<<" "<<s[inx].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<cena_min<<endl;
}
int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0;i<n;i++)
    {
        cin>>s[i].ime;
        cin>>s[i].lokacija;
        cin>>s[i].broj;

        for(int j=0;j<s[i].broj;j++)
        {
            cin>>s[i].niza[j].firma;
            cin>>s[i].niza[j].monitor;
            cin>>s[i].niza[j].touch;
            cin>>s[i].niza[j].cena;
        }
    }



    //pecatenje na site prodavnici


    print(s,n);
    najeftina_ponuda(s,n);

    //povik na glavnata metoda

    return 0;
}

