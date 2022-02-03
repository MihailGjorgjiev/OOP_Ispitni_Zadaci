#include <iostream>
#include <string.h>
using namespace std;

class Pica
{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int promo;
public:
    Pica(char *ime="",int cena=0,char *sostojki="",int promo=0)
    {
        strcpy(this->ime,ime);
        this->sostojki=new char[strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->cena=cena;
        this->promo=promo;
    }
    Pica(const Pica &p)
    {
        strcpy(ime,p.ime);
        cena=p.cena;
        promo=p.promo;
        sostojki=new char[strlen(p.sostojki)+1];
        strcpy(sostojki,p.sostojki);
    }
    ~Pica()
    {
        delete [] sostojki;
    }
    Pica &operator=(const Pica &p)
    {
        if(this!=&p)
        {
            delete [] sostojki;
            sostojki=new char[strlen(p.sostojki)+1];
            strcpy(sostojki,p.sostojki);
            strcpy(ime,p.ime);
            cena=p.cena;
            promo=p.promo;
        }
        return *this;
    }
    void pecati()
    {
        cout<<ime<<" - "<<sostojki<<", "<<cena<<" ";
    }
    bool istiSe(Pica p)
    {
        if(strcmp(sostojki,p.sostojki)==0)
        {
            return true;
        }
        return false;
    }
    int getPromo()
    {
        return promo;
    }
    int getCena()
    {
        return cena;
    }
};


class Picerija
{
private:
    char ime[15];
    Pica *pici;
    int broj;
public:
    Picerija(char *ime)
    {
        strcpy(this->ime,ime);
        pici=NULL;
        broj=0;
    }
    Picerija(const Picerija &p)
    {
        strcpy(ime,p.ime);
        broj=p.broj;
        pici=new Pica[broj];
        for(int i=0;i<broj;i++)
        {
            pici[i]=p.pici[i];
        }
    }
    ~Picerija()
    {
        delete [] pici;
    }
    Picerija &operator+=(const Pica &P)
    {
        bool add=true;
        for(int i=0;i<broj;i++)
        {
            if(pici[i].istiSe(P)==true)
            {
                add=false;
                break;
            }
        }
        if(add==true)
        {
            Pica *tmp;
            tmp=pici;
            pici=new Pica[broj+1];
            for(int i=0;i<broj;i++)
            {
                pici[i]=tmp[i];
            }
            pici[broj]=P;
            broj++;
            delete [] tmp;
        }
        return *this;
    }
    void piciNaPromocija()
    {
        for(int i=0;i<broj;i++)
        {
            if(pici[i].getPromo()!=0)
            {
                pici[i].pecati();
                cout<<pici[i].getCena()-(pici[i].getCena()*pici[i].getPromo()/100)<<endl;
            }
        }
    }
    void setIme(char *name)
    {
        strcpy(ime,name);
    }
    char *getIme()
    {
        return ime;
    }
};
int main() {

	int n;
	char ime[15];
	cin >> ime;
	cin >> n;

	Picerija p1(ime);
	for (int i = 0; i < n; i++){
		char imp[100];
		cin.get();
		cin.getline(imp, 100);
		int cena;
		cin >> cena;
		char sostojki[100];
		cin.get();
		cin.getline(sostojki, 100);
		int popust;
		cin >> popust;
		Pica p(imp, cena, sostojki, popust);
		p1+=p;
	}

	Picerija p2 = p1;
	cin >> ime;
	p2.setIme(ime);
	char imp[100];
	cin.get();
	cin.getline(imp, 100);
	int cena;
	cin >> cena;
	char sostojki[100];
	cin.get();
	cin.getline(sostojki, 100);
	int popust;
	cin >> popust;
	Pica p(imp, cena, sostojki, popust);
	p2+=p;

	cout << p1.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p1.piciNaPromocija();

	cout << p2.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p2.piciNaPromocija();

	return 0;
}
