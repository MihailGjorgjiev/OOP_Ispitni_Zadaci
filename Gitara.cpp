#include <iostream>
#include <string.h>
using namespace std;

class Gitara
{
private:
    char seriski_broj[25];
    double cena;
    int godina;
    char tip[40];
public:
//    Gitara(){}
    Gitara(char *tip="",char *seriski_broj="",int godina=0,double cena=0)
    {
        strcpy(this->tip,tip);
        strcpy(this->seriski_broj,seriski_broj);
        this->godina=godina;
        this->cena=cena;
    }
    Gitara(const Gitara &g)
    {
        strcpy(seriski_broj,g.seriski_broj);
        strcpy(tip,g.tip);
        godina=g.godina;
        cena=g.cena;
    }
    ~Gitara(){}
    Gitara & operator=(const Gitara &from)
    {
        if(this!=&from)
        {
            strcpy(seriski_broj,from.seriski_broj);
            strcpy(tip,from.tip);
            godina=from.godina;
            cena=from.cena;
        }
        return *this;
    }
    bool daliIsti(Gitara g)
    {
        if(strcmp(seriski_broj,g.seriski_broj)==0)
        {
            return true;
        }
        return false;
    }
    void pecati()
    {
        cout<<seriski_broj<<" "<<tip<<" "<<cena<<endl;
    }
    double getNabavna()
    {
        return cena;
    }
    int getGodina()
    {
        return godina;
    }
    char *getTip()
    {
        return tip;
    }
    char *getSeriski()
    {
        return seriski_broj;
    }

};


class Magacin
{
private:
    char ime[30];
    char lokacija[60];
    Gitara *kolekcija;
    int broj;
    int godina;
public:
//    Magacin()
//    {
//        kolekcija=NULL;
//        broj=0;
//        godina=0;
//        strcpy(lokacija,"");
//    }
    Magacin(char *ime="",char *lokacija="",int godina=0)
    {
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->godina=godina;
        kolekcija=NULL;
        broj=0;
    }
    Magacin(const Magacin &m)
    {
        strcpy(ime,m.ime);
        strcpy(lokacija,m.lokacija);
        godina=m.godina;
        broj=m.broj;
        kolekcija=new Gitara[broj];
        for(int i=0;i<broj;i++)
        {
            kolekcija[i]=m.kolekcija[i];
        }
    }
    ~Magacin()
    {
        delete [] kolekcija;
    }
    Magacin & operator=(const Magacin &from)
    {
        if(this!=&from)
        {
            strcpy(ime,from.ime);
            strcpy(lokacija,from.lokacija);
            broj=from.broj;
            godina=from.godina;
            delete [] kolekcija;
            kolekcija=new Gitara[broj];
            for(int i=0;i<broj;i++)
            {
                kolekcija[i]=from.kolekcija[i];
            }

        }
        return *this;
    }
    double vrednost()
    {
        double money=0.0;
        for(int i=0;i<broj;i++)
        {
            money+=kolekcija[i].getNabavna();
        }
        return money;
    }
    void dodadi(Gitara d)
    {
        Gitara *tmp;
        tmp=kolekcija;
        kolekcija=new Gitara[broj+1];
        for(int i=0;i<broj;i++)
        {
            kolekcija[i]=tmp[i];
        }
        kolekcija[broj]=d;
        broj++;
        delete [] tmp;
    }
    void prodadi(Gitara p)
    {
        int j=0;
        Gitara *tmp;
        tmp=new Gitara[broj];
        for(int i=0;i<broj;i++)
        {
            if(kolekcija[i].daliIsti(p)==false)
            {
                tmp[j]=kolekcija[i];
                j++;
            }
        }
        delete [] kolekcija;
        broj=j;
        kolekcija=new Gitara[broj];
        for(int i=0;i<broj;i++)
        {
            kolekcija[i]=tmp[i];
        }
        delete [] tmp;
    }
    void pecati(bool daliNovi)
    {
        cout<<ime<<" "<<lokacija<<endl;
        if(daliNovi==true)
        {
            for(int i=0;i<broj;i++)
            {
                if(kolekcija[i].getGodina()>godina)
                {
                    kolekcija[i].pecati();
                }
            }
        }
        else
        {

            for(int i=0;i<broj;i++)
            {
                kolekcija[i].pecati();
            }
        }
    }
};
    int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}


