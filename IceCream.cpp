#include <iostream>
#include <cstring>
using namespace std;

class IceCream
{
    char *ime;
    char sostav[100];
    float cena;
    int popust;
public:
    IceCream()
    {
        ime=NULL;
    }
    IceCream(char *ime,char *sostav,float cena)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->sostav,sostav);
        this->cena=cena;
        this->popust=0;
    }
    IceCream(const IceCream &ic)
    {
        ime=new char[strlen(ic.ime)+1];
        strcpy(ime,ic.ime);
        strcpy(sostav,ic.sostav);
        cena=ic.cena;
        popust=ic.popust;
    }
    ~IceCream()
    {
        delete [] ime;
    }
    IceCream & operator=(const IceCream &ic)
    {
        if(this!=&ic)
        {
            delete [] ime;
            ime=new char[strlen(ic.ime)+1];
            strcpy(ime,ic.ime);
            strcpy(sostav,ic.sostav);
            popust=ic.popust;
            cena=ic.cena;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,IceCream &ic)
    {
        out<<ic.ime<<": "<<ic.sostav<<" "<<ic.cena;
        if(ic.popust!=0)
        {
            out<<" ("<<ic.cena-(ic.cena*ic.popust/100)<<")";
        }
//        out<<endl;

        return out;
    }
    IceCream &operator++()
    {
//        IceCream tmp(*this);
        popust+=5;

        return *this;
    }
    IceCream operator+(char *name)
    {
        IceCream tmp(*this);
        delete [] tmp.ime;
        tmp.ime=new char[strlen(this->ime)+strlen(name)+4];
        strcpy(tmp.ime,this->ime);
        strcat(tmp.ime," + ");
        strcat(tmp.ime,name);
        tmp.cena+=10;

        return tmp;
    }
    void setDiscount(int discount)
    {
        if(discount>=0 &&discount<=100)
        {
            this->popust=discount;
        }
    }
    void setName(char* name)
    {
        delete [] ime;
        ime=new char[strlen(name)+1];
        strcpy(ime,name);
    }


};

class IceCreamShop
{
private:
    char ime[50];
    IceCream *cream;
    int broj;
public:
    IceCreamShop(char *ime)
    {
        strcpy(this->ime,ime);
        cream=NULL;
        broj=0;
    }
    IceCreamShop(const IceCreamShop &ics)
    {
        strcpy(ime,ics.ime);
        broj=ics.broj;
        cream=new IceCream[broj];
        for(int i=0;i<broj;i++)
        {
            cream[i]=ics.cream[i];
        }
    }
    ~IceCreamShop()
    {
        delete [] cream;
    }
    IceCreamShop &operator+=(const IceCream &ic)
    {
        IceCream *tmp;
        tmp=cream;
        cream=new IceCream[broj+1];
        for(int i=0;i<broj;i++)
        {
            cream[i]=tmp[i];
        }
        cream[broj]=ic;
        broj++;
        delete [] tmp;

        return *this;
    }
    friend ostream &operator<<(ostream &out,IceCreamShop &ics)
    {
        out<<ics.ime<<endl;
        for(int i=0;i<ics.broj;i++)
        {
            out<<ics.cream[i]<<endl;
        }

        return out;
    }
};
#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde

// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}


