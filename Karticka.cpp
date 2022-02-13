#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException
{
public:
    void message()
    {
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
     virtual ~Karticka(){}
     virtual int tezinaProbivanje()
     {
         int tmp=pin;
         int k=0;
         while(tmp>0)
         {
             k++;
             tmp/=10;
         }
         return k;
     }
     friend ostream &operator<<(ostream &out,Karticka &k)
     {
         out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
         return out;
     }
     bool getDopolnitelenPin()
     {
         return povekjePin;
     }
     char *getSmetka()
     {
         return smetka;
     }
};

class SpecijalnaKarticka:public Karticka
{
private:
    static const int P;
    int *dopolnitelniPinovi;
    int brojPinovi;
public:
    SpecijalnaKarticka(char *smetka,int pin):Karticka(smetka,pin)
    {
        povekjePin=true;
        dopolnitelniPinovi=NULL;
        brojPinovi=0;
    }
    ~SpecijalnaKarticka()
    {
        delete [] dopolnitelniPinovi;
    }
    int tezinaProbivanje()
    {
        int total=Karticka::tezinaProbivanje();
        total+=brojPinovi;
        return total;
    }
    friend ostream &operator<<(ostream &out,SpecijalnaKarticka &k)
    {
        out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return out;
    }
    SpecijalnaKarticka &operator+=(int novPin)
    {
        if(brojPinovi==P)
        {
            throw OutOfBoundException();
        }
        else
        {
            int *tmp=new int[brojPinovi+1];
            for(int i=0;i<brojPinovi;i++)
            {
                tmp[i]=dopolnitelniPinovi[i];
            }
            tmp[brojPinovi]=novPin;
            brojPinovi++;
            delete [] dopolnitelniPinovi;
            dopolnitelniPinovi=tmp;
        }
        return *this;
    }

};
const int SpecijalnaKarticka::P=4;


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }

    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int num)
    {
        LIMIT=num;
    }

    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            SpecijalnaKarticka *sp=dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
            if(sp!=0 && sp->tezinaProbivanje()<=LIMIT)
            {
                cout<<*sp;
            }
            else if(karticki[i]->tezinaProbivanje()<=LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            SpecijalnaKarticka *sk=dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
            if(sk!=0 && strcmp(sk->getSmetka(),smetka)==0)
            {
                try{
                *sk+=novPin;
                }
                catch(OutOfBoundException &ob)
                {
                    ob.message();
                }
            }
        }
    }



};
int Banka::LIMIT=7;


int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

   komercijalna.dodadiDopolnitelenPin(smetka,pin);

}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
