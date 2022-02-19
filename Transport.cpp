#include <iostream>
#include <cstring>
using  namespace std;

class Transport
{
protected:
    char destinacija[20];
    int osnovna_cena;
    int rastojanie;
public:
    Transport(){}
    Transport(char *destinacija,int osnovna_cena,int rastojanie)
    {
        strcpy(this->destinacija,destinacija);
        this->osnovna_cena=osnovna_cena;
        this->rastojanie=rastojanie;
    }
    virtual ~Transport(){}
    char *getDestinacija()
    {
        return destinacija;
    }
    int getOsnovnaCena()
    {
        return osnovna_cena;
    }
    int getRastojanie()
    {
        return rastojanie;
    }
    virtual void cenaTransport()=0;

};

class AvtomobilTransport:public Transport
{
protected:
    bool sofer;
public:
    AvtomobilTransport(char *destinacija,int osnovna_cena,int rastojanie,bool sofer):Transport(destinacija,osnovna_cena,rastojanie)
    {
        this->sofer=sofer;
    }
    AvtomobilTransport(AvtomobilTransport *a):Transport(a->getDestinacija(),a->getOsnovnaCena(),a->getRastojanie())
    {
        this->sofer=a->sofer;

    }
    ~AvtomobilTransport(){}

    void cenaTransport()
    {
        if(sofer==true)
        {
            osnovna_cena=osnovna_cena*1.2;
        }
    }
    bool operator<(Transport *t)
    {
        if(rastojanie<t->getRastojanie())
        {
            return true;
        }
        return false;
    }
};

class KombeTransport:public Transport
{
protected:
    int patnici;
public:
    KombeTransport(char *destinacija,int osnovna_cena,int rastojanie,int patnici):Transport(destinacija,osnovna_cena,rastojanie)
    {
        this->patnici=patnici;
    }
    KombeTransport(KombeTransport *k):Transport(k->getDestinacija(),k->getOsnovnaCena(),k->getRastojanie())
    {
        this->patnici=k->patnici;

    }
    ~KombeTransport(){}

    void cenaTransport()
    {
        osnovna_cena=osnovna_cena-(patnici*200);
    }

    bool operator<(Transport *t)
    {
        if(rastojanie<t->getRastojanie())
        {
            return true;
        }
        return false;
    }
};

void pecatiPoloshiPonudi(Transport **t,int n,AvtomobilTransport k)
{

    k.cenaTransport();
    Transport *tmp;
    int x=0;
    for(int i=0;i<n;i++)
    {
        AvtomobilTransport *a=dynamic_cast<AvtomobilTransport *>(t[i]);
        if(a!=0)
        {
            a->cenaTransport();
            t[i]=new AvtomobilTransport(a);
        }
        KombeTransport *kk=dynamic_cast<KombeTransport *>(t[i]);
        if(kk!=0)
        {
            kk->cenaTransport();
            t[i]=new KombeTransport(kk);
        }
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(t[i]->getOsnovnaCena()<t[j]->getOsnovnaCena())
            {
                tmp=t[i];
                t[i]=t[j];
                t[j]=tmp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(t[i]->getOsnovnaCena()>k.getOsnovnaCena())
        {
            x++;
        }

    }

    for(int i=0;i<x-1;i++)
    {
        for(int j=i+1;j<x;j++)
        {
            if(t[i]->getRastojanie()>t[j]->getRastojanie())
            {
                tmp=t[i];
                t[i]=t[j];
                t[j]=tmp;
            }
        }
    }
    for(int i=0;i<x;i++)
    {
        cout<<t[i]->getDestinacija()<<" "<<t[i]->getRastojanie()<<" "<<t[i]->getOsnovnaCena()<<endl;
    }
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}


