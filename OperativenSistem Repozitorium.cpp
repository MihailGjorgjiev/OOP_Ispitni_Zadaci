#include <iostream>
#include <string.h>
using namespace std;

enum Tip{LINUX,UNIX,WINDOWS};

class OperativenSistem
{
private:
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem()
    {
        ime=NULL;
    }
    OperativenSistem(char *ime,float verzija,Tip tip,float golemina)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &os)
    {
        ime=new char[strlen(os.ime)+1];
        strcpy(ime,os.ime);
        golemina=os.golemina;
        tip=os.tip;
        verzija=os.verzija;
    }
    ~OperativenSistem()
    {
        delete [] ime;
    }
    OperativenSistem &operator=(const OperativenSistem &os)
    {
        if(this!=&os)
        {
            delete [] ime;
            ime=new char[strlen(os.ime)+1];
            strcpy(ime,os.ime);
            verzija=os.verzija;
            tip=os.tip;
            golemina=os.golemina;
        }
        return *this;
    }
    void pecati()
    {
        cout<<"Ime: "<<ime;
        cout<<" Verzija: "<<verzija;
        cout<<" Tip: "<<tip;
        cout<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os)
    {
        if(golemina==os.golemina && tip==os.tip && verzija==os.verzija &&strcmp(ime,os.ime)==0)
        {
            return true;
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os)
    {
        if(verzija==os.verzija)
        {
            return 0;
        }
        else if(os.verzija>verzija)
        {
            return -1;
        }
        return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba)
    {
        if(tip==sporedba.tip && strcmp(ime,sporedba.ime)==0)
        {
            return true;
        }
        return false;
    }
};

class Repozitorium
{
private:
    char ime[20];
    OperativenSistem *os;
    int broj;
public:
    Repozitorium(char *ime)
    {
        strcpy(this->ime,ime);
        os=NULL;
        broj=0;
    }
    ~Repozitorium()
    {
        delete [] os;
    }
    void pecatiOperativniSistemi()
    {
        cout<<"Repozitorium: "<<ime<<endl;
        for(int i=0;i<broj;i++)
        {
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem)
    {
        int inx=-1;
        for(int i=0;i<broj;i++)
        {
            if(os[i].ednakviSe(operativenSistem)==true)
            {
                inx=i;
                break;
            }
        }
        if(inx>=0)
        {
            OperativenSistem *tmp;
            tmp=os;
            os=new OperativenSistem[broj-1];
            for(int i=0,j=0;i<broj;i++)
            {
                if(i==inx)
                {
                    continue;
                }
                os[j]=tmp[i];
                j++;
            }
            broj--;
            delete []tmp;
        }
    }
    void dodadi(const OperativenSistem &nov)
    {
        int inx;
        bool add=true;
        for(int i=0;i<broj;i++)
        {
            if(os[i].istaFamilija(nov)==true && os[i].sporediVerzija(nov)==-1)
            {
                add=false;
                inx=i;
                break;
            }
        }
        if(add==false)
        {
            os[inx]=nov;
        }
        else
        {
            OperativenSistem *tmp;
            tmp=os;
            os=new OperativenSistem[broj+1];
            for(int i=0;i<broj;i++)
            {
                os[i]=tmp[i];
            }
            os[broj]=nov;
            broj++;
            delete [] tmp;
        }

    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}

