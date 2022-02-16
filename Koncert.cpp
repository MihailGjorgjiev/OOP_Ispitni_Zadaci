#include <iostream>
#include <cstring>

using namespace std;


class Koncert
{
private:
    char naziv[20];
    char lokacija[20];
    static float sezonski_popust;
    float cena_bilet;
public:
    Koncert(){}
    Koncert(char *naziv,char *lokacija,float cena_bilet)
    {
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cena_bilet=cena_bilet;
    }
    virtual ~Koncert(){}
    static void setSezonskiPopust(float novPopust)
    {
        sezonski_popust=novPopust;
    }
    static float getSezonskiPopust()
    {
        return sezonski_popust;
    }

    void setNaziv(char *newNaziv)
    {
        strcpy(this->naziv,newNaziv);
    }
    char *getNaziv()
    {
        return naziv;
    }
    void setLokacija(char *newLokacija)
    {
        strcpy(this->lokacija,newLokacija);
    }
    char *getLokacija()
    {
        return lokacija;
    }
    void setCenaBilet(float newCena)
    {
        cena_bilet=newCena;
    }
    float getCenaBilet()
    {
        return cena_bilet;
    }


    virtual float cena()
    {
        return cena_bilet*(1-sezonski_popust);
    }
};
float Koncert::sezonski_popust=0.2;




class ElektronskiKoncert:public Koncert
{
private:
    char *ime;
    float vremetraenje;
    bool denski;

    void copy_func(const ElektronskiKoncert &e)
    {
//        setNaziv(e.getNaziv());
//        setLokacija(e.getLokacija());
//        setCenaBilet(e.getCenaBilet());

        this->ime=new char[strlen(e.ime)+1];
        strcpy(this->ime,e.ime);
        this->vremetraenje=e.vremetraenje;
        this->denski=e.denski;
    }
public:
    ElektronskiKoncert(char *naziv,char *lokacija,float cena_bilet,char *ime,float vremetraenje,bool denski):Koncert(naziv,lokacija,cena_bilet)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vremetraenje=vremetraenje;
        this->denski=denski;
    }
    ~ElektronskiKoncert()
    {
        delete [] ime;
    }
    ElektronskiKoncert(const ElektronskiKoncert &e)
    {
        copy_func(e);
    }
    ElektronskiKoncert &operator=(const ElektronskiKoncert &e)
    {
        if(this!=&e)
        {
            delete [] ime;
            copy_func(e);
        }
        return *this;
    }

    bool getDenski()
    {
        return denski;
    }

    float cena()
    {
        float total=Koncert::cena();
        if(vremetraenje>7)
        {
            total+=360;
        }
        else if(vremetraenje>5)
        {
            total+=150;
        }
        if(denski==true)
        {
            total-=50;
        }
        else
        {
            total+=100;
        }
        return total;
    }

};

void najskapKoncert(Koncert ** koncerti, int n)
{
    int inx=0;
    int ele=0;
    for(int i=1;i<n;i++)
    {
        if(koncerti[i]->cena()>koncerti[inx]->cena())
        {
            inx=i;
        }
        ElektronskiKoncert *ek=dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if(ek!=0)
        {
            ele++;
        }

    }

    cout<<"Najskap koncert: "<<koncerti[inx]->getNaziv()<<" "<<koncerti[inx]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<ele<<" od vkupno "<<n<<endl;

}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski)
{
    if(elektronski==true)
    {
        for(int i=0;i<n;i++)
        {
            ElektronskiKoncert *ek=dynamic_cast<ElektronskiKoncert *>(koncerti[i]);

            if( ek!=0 && strcmp(ek->getNaziv(),naziv)==0)
            {
                cout<<ek->getNaziv()<<" "<<ek->cena()<<endl;
                return true;
            }
        }
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(koncerti[i]->getNaziv(),naziv)==0)
            {
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}


int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}


