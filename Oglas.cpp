#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class NegativnaVrednost
{
public:
    void message()
    {
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglas
{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(){}
    Oglas(char *naslov,char *kategorija,char *opis,float cena)
    {
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }
    ~Oglas(){}

    bool operator>(Oglas &o)
    {
        if(this->cena>o.cena)
        {
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &out,Oglas &o)
    {
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        out<<endl;
        return out;
    }

    char *getNaslov()
    {
        return naslov;
    }
    char *getOpis()
    {
        return opis;
    }

    char *getKategorija()
    {
        return kategorija;
    }

    float getCena()
    {
        return cena;
    }


};

class Oglasnik
{
private:
    char ime[20];
    Oglas *oglasi;
    int broj_oglasi;
public:
    Oglasnik(char *ime="")
    {
        strcpy(this->ime,ime);
        oglasi=NULL;
        broj_oglasi=0;
    }
    ~Oglasnik()
    {
        delete [] oglasi;
    }
    Oglasnik &operator+=(Oglas &o)
    {
        if(o.getCena()<0)
        {
            throw NegativnaVrednost();
        }
        else
        {
            Oglas *tmp;
            tmp=new Oglas[broj_oglasi+1];
            for(int i=0;i<broj_oglasi;i++)
            {
                tmp[i]=oglasi[i];
            }
            tmp[broj_oglasi]=o;
            broj_oglasi++;
            delete [] oglasi;
            oglasi=tmp;
            return *this;
        }
    }

    friend ostream &operator<<(ostream &out,Oglasnik &o)
    {
        out<<o.ime<<endl;
        for(int i=0;i<o.broj_oglasi;i++)
        {
//            out<<oglasi[i];
            out<<o.oglasi[i].getNaslov()<<endl;
            out<<o.oglasi[i].getOpis()<<endl;
            out<<o.oglasi[i].getCena();
            out<<" evra"<<endl;
            out<<endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k)
    {
        for(int i=0;i<broj_oglasi;i++)
        {
            if(strcmp(oglasi[i].getKategorija(),k)==0)
            {
                cout<<oglasi[i];
//                cout<<oglasi[i].getNaslov()<<" "<<oglasi[i].getOpis()<<" "<<oglasi[i].getCena()<<endl;
            }
        }
    }
    void najniskaCena()
    {
        int inx=0;
        for(int i=1;i<broj_oglasi;i++)
        {
            if(oglasi[i].getCena()<oglasi[inx].getCena())
            {
                inx=i;
            }
        }
        cout<<oglasi[inx];
//        cout<<oglasi[inx].getNaslov()<<" "<<oglasi[inx].getOpis()<<" "<<oglasi[inx].getCena()<<endl;

    }
};



int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
            ogl+=o;
        	}
        	catch(NegativnaVrednost &nv)
        	{
        	    nv.message();
        	}
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
			ogl+=o;
        	}
        	catch(NegativnaVrednost &nv)
        	{
        	    nv.message();
        	}
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
            ogl+=o;
        	}
        	catch(NegativnaVrednost &hv)
        	{
        	    hv.message();
        	}
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}

