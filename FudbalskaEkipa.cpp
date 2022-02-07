#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa
{
protected:
    char imeTrener[100];
    int pole[10];
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *imeTrener,int *pole)
    {
        strcpy(this->imeTrener,imeTrener);
        for(int i=0;i<10;i++)
        {
            this->pole[i]=pole[i];
        }
    }
    virtual ~FudbalskaEkipa(){}

    char *getImeTrener()
    {
        return imeTrener;
    }
    int *getPole()
    {
        return pole;
    }
    virtual int uspeh()=0;

    bool operator>(FudbalskaEkipa &f)
    {
        if(uspeh()>f.uspeh())
        {
            return true;
        }
        return false;
    }
    FudbalskaEkipa &operator+=(int num)
    {
        for(int i=1;i<10;i++)
        {
            pole[i-1]=pole[i];
        }
        pole[9]=num;
        return *this;
    }

};


class Klub:public FudbalskaEkipa
{
protected:
    char imeKlub[100];
    int brojTituli;
public:
    Klub(char *imeTrener,int *pole,char *imeKlub,int brojTituli):FudbalskaEkipa(imeTrener,pole)
    {
        this->brojTituli=brojTituli;
        strcpy(this->imeKlub,imeKlub);
    }
    ~Klub(){}

    char *getImeKlub()
    {
        return imeKlub;
    }
    int getBrojTituli()
    {
        return brojTituli;
    }
//    Klub &operator+=(int num)
//    {
//        pole[9]+=num;
//        return *this;
//    }
    int uspeh()
    {
        int total=0;
        for(int i=0;i<10;i++)
        {
            total+=pole[i];
        }
        total*=3;
        total+=(brojTituli*1000);
        return total;
    }

};


class Reprezentacija:public FudbalskaEkipa
{
protected:
    char imeDrzava[100];
    int nastapi;
public:
    Reprezentacija(char *imeTrener,int *pole,char *imeDrzava,int nastapi):FudbalskaEkipa(imeTrener,pole)
    {
        strcpy(this->imeDrzava,imeDrzava);
        this->nastapi=nastapi;
    }
    ~Reprezentacija(){}
    char *getImeDrzava()
    {
        return imeDrzava;
    }
    int getNastapi()
    {
        return nastapi;
    }
//    Reprezentacija &operator+=(int num)
//    {
//        pole[9]+=num;
//        return *this;
//    }
    int uspeh()
    {
        int total=0;
        for(int i=0;i<10;i++)
        {
            total+=pole[i];
        }
        total*=3;
        total+=(nastapi*50);
        return total;
    }

};


ostream &operator<<(ostream &out,FudbalskaEkipa &fe)
{
    Reprezentacija *r=dynamic_cast<Reprezentacija *>(&fe);
    if(r!=0)
    {
        out<<r->getImeDrzava()<<endl;
        out<<r->getImeTrener()<<endl;
        out<<r->uspeh()<<endl;
    }
    Klub *k=dynamic_cast<Klub *>(&fe);
    if(k!=0)
    {
        cout<<k->getImeKlub()<<endl;
        cout<<k->getImeTrener()<<endl;
        cout<<k->uspeh()<<endl;
    }
    return out;
}

void najdobarTrener(FudbalskaEkipa **ekipa,int n)
{
    int inx=0;
    for(int i=1;i<n;i++)
    {
        if(*ekipa[i]>*ekipa[inx])
        {
            inx=i;
        }
    }
    cout<<*ekipa[inx];
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}

