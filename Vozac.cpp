#include <iostream>
#include <cstring>
using namespace std;

class Vozac
{
protected:
    char ime[100];
    int vozrast;
    int broj_trki;
    bool daliVeteran;
public:
    Vozac(){}
    Vozac(char *ime,int vozrast,int broj_trki,bool daliVeteran)
    {
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->broj_trki=broj_trki;
        this->daliVeteran=daliVeteran;
    }
    virtual ~Vozac(){}

    virtual double zarabotka()=0;
    virtual double danok()=0;

    friend ostream &operator<<(ostream &out,Vozac &v)
    {
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.broj_trki<<endl;
        if(v.daliVeteran==true)
        {
            out<<"VETERAN"<<endl;
        }

        return out;
    }
};

class Avtomobilist:public Vozac
{
protected:
    double cena;
public:
    Avtomobilist(){}
    Avtomobilist(char *ime,int vozrast,int broj_trki,bool daliVeteran,double cena):Vozac(ime,vozrast,broj_trki,daliVeteran)
    {
        this->cena=cena;
    }
    ~Avtomobilist(){}

    double zarabotka()
    {
        return 1.0*cena/5;
    }
    double danok()
    {
        if(broj_trki>10)
        {
            return zarabotka()*0.15;
        }
        return zarabotka()*0.1;
    }
};

class Motociklist:public Vozac
{
protected:
    int mokjnost;
public:
    Motociklist(){}
    Motociklist(char *ime,int vozrast,int broj_trki,bool daliVeteran,int mokjnost):Vozac(ime,vozrast,broj_trki,daliVeteran)
    {
        this->mokjnost=mokjnost;
    }
    ~Motociklist(){}
    double zarabotka()
    {
        return 1.0*mokjnost*20;
    }
    double danok()
    {
        if(daliVeteran==true)
        {
            return zarabotka()*0.25;
        }
        return zarabotka()*0.2;
    }

};

bool operator==(Vozac &v1,Vozac &v2)
{
    if(v1.zarabotka()==v2.zarabotka())
    {
        return true;
    }
    return false;
}

int soIstaZarabotuvachka(Vozac **voz,int n,Vozac *comp)
{
    int counter=0;
    for(int i=0;i<n;i++)
    {
        if(*voz[i]==*comp)
        {
            counter++;
        }
    }
    return counter;
}

// vashiot kod ovde

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}

