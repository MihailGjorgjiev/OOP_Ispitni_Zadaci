#include <iostream>
#include <string.h>
using namespace std;

enum tip{pop,rap,rok};

class Pesna
{
private:
    char *ime;
    int vreme;
    tip kojtip;
public:
    Pesna()
    {
        ime=NULL;
        vreme=0;
    }
    Pesna(char *ime,int vreme,tip kojtip)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vreme=vreme;
        this->kojtip=kojtip;
    }
    Pesna(const Pesna &p)
    {
        ime=new char[strlen(p.ime)+1];
        strcpy(ime,p.ime);
        vreme=p.vreme;
        kojtip=p.kojtip;
    }
    ~Pesna()
    {
        delete [] ime;
    }
    Pesna &operator=(const Pesna &from)
    {
        if(this!=&from)
        {
            delete [] ime;
            ime=new char[strlen(from.ime)+1];
            strcpy(ime,from.ime);
            vreme=from.vreme;
            kojtip=from.kojtip;
        }
        return *this;
    }
    void pecati()
    {
//        "Happy"-5min
        cout<<"\""<<ime<<"\"-"<<vreme<<"min"<<endl;
    }
    tip getTip()
    {
        return kojtip;
    }
    int getVreme()
    {
        return vreme;
    }

};

class CD
{
private:
    Pesna kolekcija[10];
    int broj;
    int vreme_max;
public:
    CD(int vreme_max)
    {
        this->vreme_max=vreme_max;
        broj=0;
    }
    CD(const CD &c)
    {
        broj=c.broj;
        for(int i=0;i<broj;i++)
        {
            kolekcija[i]=c.kolekcija[i];
        }
        vreme_max=c.vreme_max;
    }
    ~CD(){}
    CD & operator =(const CD &from)
    {
        if(this!=&from)
        {
            broj=from.broj;
            for(int i=0;i<broj;i++)
            {
                kolekcija[i]=from.kolekcija[i];
            }
            vreme_max=from.vreme_max;
        }
        return *this;
    }
    void dodadiPesna (Pesna p)
    {
        if(vreme_max>=p.getVreme() && broj<10)
        {
            kolekcija[broj]=p;
            broj++;
            vreme_max-=p.getVreme();
        }
    }
    void pecatiPesniPoTip(tip t)
    {
        for(int i=0;i<broj;i++)
        {
            if(kolekcija[i].getTip()==t)
            {
                kolekcija[i].pecati();
            }
        }
    }
    Pesna getPesna(int i)
    {
        return kolekcija[i];
    }
    int getBroj()
    {
        return broj;
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
