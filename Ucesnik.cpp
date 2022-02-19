#include <iostream>
#include <string.h>
using namespace std;

class Ucesnik
{
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik()
    {
        ime=NULL;
    }
    Ucesnik(char *ime,bool pol,int vozrast)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->pol=pol;
        this->vozrast=vozrast;
    }
    Ucesnik(const Ucesnik &u)
    {
        ime=new char[strlen(u.ime)+1];
        strcpy(ime,u.ime);
        vozrast=u.vozrast;
        pol=u.pol;
    }
    ~Ucesnik()
    {
        delete [] ime;
    }
    Ucesnik &operator=(const Ucesnik &from)
    {
        if(this!=&from)
        {
            delete []ime;
            ime=new char[strlen(from.ime)+1];
            strcpy(ime,from.ime);
            pol=from.pol;
            vozrast=from.vozrast;
        }
        return *this;
    }
    bool operator>(const Ucesnik &u)
    {
        return (vozrast>u.vozrast);
    }
    friend ostream &operator<<(ostream &out,Ucesnik &u)
    {
        out<<u.ime<<endl;
        if(u.pol==true)
        {
            out<<"mashki"<<endl;
        }
        else
        {
            out<<"zhenski"<<endl;
        }
        out<<u.vozrast<<endl;

        return out;
    }
    int getVozrast()
    {
        return vozrast;
    }
};

class Maraton
{
private:
    char lokacija[100];
    Ucesnik *niza;
    int broj;
public:
    Maraton(char *lokacija)
    {
        strcpy(this->lokacija,lokacija);
        niza=NULL;
        broj=0;
    }
    Maraton(const Maraton &m)
    {
        strcpy(lokacija,m.lokacija);
        broj=m.broj;
        niza=new Ucesnik[broj];
        for(int i=0;i<broj;i++)
        {
            niza[i]=m.niza[i];
        }
    }
    ~Maraton()
    {
        delete [] niza;
    }
    Maraton &operator=(const Maraton &from)
    {
        if(this!=&from)
        {
            strcpy(lokacija,from.lokacija);
            delete niza;
            broj=from.broj;
            niza=new Ucesnik[broj];
            for(int i=0;i<broj;i++)
            {
                niza[i]=from.niza[i];
            }
        }
        return *this;
    }
    Maraton &operator+=(const Ucesnik &u)
    {
        Ucesnik *tmp;
        tmp=niza;
        niza=new Ucesnik[broj+1];
        for(int i=0;i<broj;i++)
        {
            niza[i]=tmp[i];
        }
        niza[broj]=u;
        delete [] tmp;
        broj++;

        return *this;
    }
    double prosecnoVozrast()
    {
        int godini=0;
        for(int i=0;i<broj;i++)
        {
            godini+=niza[i].getVozrast();
        }
        return double(godini)/broj;
    }
    void pecatiPomladi(Ucesnik &u)
    {
        for(int i=0;i<broj;i++)
        {
            if(u.getVozrast()>niza[i].getVozrast())
            {
                cout<<niza[i];
            }
        }
    }
};

// vashiot kod ovde

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}

