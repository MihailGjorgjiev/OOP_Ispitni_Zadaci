#include<iostream>
#include<string.h>
using namespace std;

class Delo
{
protected:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(){}
    Delo(char *ime,int godina,char *zemja)
    {
        strcpy(this->ime,ime);
        strcpy(this->zemja,zemja);
        this->godina=godina;
    }
    ~Delo(){}

    char *getIme()
    {
        return ime;
    }
    int getGodina()
    {
        return godina;
    }
    char *getZemja()
    {
        return zemja;
    }

    bool operator==(Delo &d)
    {
        if(strcmp(ime,d.ime)==0)
        {
            return true;
        }
        return false;
    }

};

class Pretstava
{
protected:
    Delo d;
    int prodadeni_karti;
    char data[15];
    int M;
    int N;
public:
    Pretstava(){}
    Pretstava(Delo d,int prodadeni_karti,char *data)
    {
        this->d=d;
        this->prodadeni_karti=prodadeni_karti;
        strcpy(this->data,data);
        setM();
        setN();
    }
    virtual ~Pretstava(){}
    void setM()
    {
        if(d.getGodina()>=1900)
        {
            M=50;
        }
        else if(d.getGodina()>=1800)
        {
            M=75;
        }
        else
        {
            M=100;
        }
    }
    void setN()
    {
        if(strcmp(d.getZemja(),"Italija")==0)
        {
            N=100;
        }
        else if(strcmp(d.getZemja(),"Rusija")==0)
        {
            N=150;
        }
        else
        {
            N=80;
        }

    }
    virtual int cena()
    {
        return M+N;
    }
    Delo getDelo()
    {
        return d;
    }
    int getProdadeni()
    {
        return prodadeni_karti;
    }

};


class Balet:public Pretstava
{
private:
    static int cenaBalet;
public:
    Balet(Delo d,int prodadeni_karti,char *data):Pretstava(d,prodadeni_karti,data){}
    ~Balet(){}
    int cena()
    {
        return Pretstava::cena()+cenaBalet;
    }
    static void setCenaBalet(int num)
    {
        cenaBalet=num;
    }
};
int Balet::cenaBalet=150;

class Opera:public Pretstava
{
public:
    Opera(Delo d,int prodadeni_karti,char *data):Pretstava(d,prodadeni_karti,data){}
    ~Opera(){}
};

int prihod(Pretstava **arr,int n)
{
    int total=0;
    for(int i=0;i<n;i++)
    {
        Balet *p=dynamic_cast<Balet *>(arr[i]);
        if(p!=0)
        {
            total+=p->cena()*p->getProdadeni();
        }
        else
        {
            total+=arr[i]->cena()*arr[i]->getProdadeni();
        }

    }
    return total;
}
int brojPretstaviNaDelo(Pretstava **arr,int n,Delo dd)
{
    int total=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]->getDelo()==dd)
        {
            total++;
        }
    }
    return total;
}



Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}

