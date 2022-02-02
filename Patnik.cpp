#include <iostream>
#include<string.h>
using namespace std;

class Patnik
{
private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik(char *ime="",int klasa=0, bool velosiped=false)
    {
        strcpy(this->ime,ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    Patnik &operator=(const Patnik &from)
    {
        if(this!=&from)
        {
            strcpy(ime,from.ime);
            klasa=from.klasa;
            velosiped=from.velosiped;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,Patnik &p)
    {
        out<<p.ime<<endl;
        out<<p.klasa<<endl;
        out<<p.velosiped<<endl;
        return out;
    }
    bool getVelo()
    {
        return velosiped;
    }
    int getKlasa()
    {
        return klasa;
    }

};

class Voz
{
private:
    char destinacija[100];
    Patnik *pat;
    int broj;
    int br_velo;
public:
    Voz(char *destinacija="",int br_velo=0)
    {
        strcpy(this->destinacija,destinacija);
        this->br_velo=br_velo;
        broj=0;
        pat=NULL;
    }
    Voz(const Voz &v)
    {
        strcpy(destinacija,v.destinacija);
        broj=v.broj;
        pat=new Patnik[broj];
        for(int i=0;i<broj;i++)
        {
            pat[i]=v.pat[i];
        }
    }
    ~Voz()
    {
        delete [] pat;
    }
    Voz &operator+=(Patnik &p)
    {
        if(br_velo-p.getVelo()>=0)
        {
            Patnik *tmp;
            tmp=pat;
            pat=new Patnik[broj+1];
            for(int i=0;i<broj;i++)
            {
                pat[i]=tmp[i];
            }
            pat[broj]=p;
            broj++;
//            if(p.getVelo()==true)
//            {
//                br_velo--;
//            }
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,Voz &v)
    {
        out<<v.destinacija<<endl;
        for(int i=0;i<v.broj;i++)
        {
            out<<v.pat[i]<<endl;
        }
        return out;
    }
    void patniciNemaMesto()
    {
        int velo1=0;
        int velo2=0;
        for(int i=0;i<broj;i++)
        {
            if(pat[i].getKlasa()==1 && pat[i].getVelo()==true)
            {
                velo1++;
            }
            else if(pat[i].getKlasa()==2 && pat[i].getVelo()==true)
            {
                velo2++;
            }
        }
            while(velo1>0 && br_velo>0)
            {
                velo1--;
                br_velo--;
            }
            while(velo2>0 && br_velo>0)
            {

                velo2--;
                br_velo--;
            }



            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<velo1<<endl;
            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<velo2<<endl;
    }
};
int main()
{
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();

	return 0;
}

