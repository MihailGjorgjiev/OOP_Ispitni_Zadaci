#include <iostream>
#include <string.h>
using namespace std;

class StockRecord
{
private:
    char id[12];
    char ime[50];
    double cena_kupuvanje;
    double cena_momentalna;
    int broj_akcii;
public:
    StockRecord(char *id="",char *ime="",double cena_kupuvanje=0,int broj_akcii=0)
    {
        strcpy(this->id,id);
        strcpy(this->ime,ime);
        this->cena_kupuvanje=cena_kupuvanje;
        this->broj_akcii=broj_akcii;
        cena_momentalna=0.0;
    }
    StockRecord(const StockRecord &s)
    {
        strcpy(ime,s.ime);
        strcpy(id,s.id);
        cena_kupuvanje=s.cena_kupuvanje;
        cena_momentalna=s.cena_momentalna;
        broj_akcii=s.broj_akcii;
    }

    ~StockRecord(){}
    void setNewPrice(double c)
    {
        this->cena_momentalna=c;
    }
    const int getBroj()
    {
        return broj_akcii;
    }

    const double getCena_kupuvanje()
    {
        return cena_kupuvanje;
    }
    const char *getIme()
    {
        return ime;
    }
    const double getCena_momentalna()
    {
        return cena_momentalna;
    }
    double value()
    {
        return broj_akcii*cena_momentalna;
    }
    double profit()
    {
        return broj_akcii*(cena_momentalna-cena_kupuvanje);
    }
    StockRecord &operator=(const StockRecord &from)
    {
        if(this!=&from)
        {
            strcpy(id,from.id);
            strcpy(ime,from.ime);
            cena_kupuvanje=from.cena_kupuvanje;
            cena_momentalna=from.cena_momentalna;
            broj_akcii=from.broj_akcii;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &output,StockRecord &s)
    {
//        output<<s.ime<<s.broj_akcii<<s.cena_kupuvanje<<s.cena_momentalna<<s.profit()<<endl;
        output<<s.getIme()<<" "<<s.getBroj()<<" "<<s.getCena_kupuvanje()<<" "<<s.getCena_momentalna()<<" "<<s.profit()<<endl;
        return output;
    }
};

class Client
{
private:
    char ime_prezime[60];
    int id;
    StockRecord *kompanii;
    int broj;
public:
    Client(char *ime_prezime="",int id=0)
    {
        strcpy(this->ime_prezime,ime_prezime);
        this->id=id;
        broj=0;
        kompanii=NULL;
    }
    Client(const Client &k)
    {
        strcpy(ime_prezime,k.ime_prezime);
        id=k.id;
        broj=k.broj;
        kompanii=new StockRecord[broj];
        for(int i=0;i<broj;i++)
        {
            kompanii[i]=k.kompanii[i];
        }
    }
    ~Client()
    {
        delete [] kompanii;
    }
    double totalValue()
    {
        double total=0.0;
        for(int i=0;i<broj;i++)
        {
            total+=kompanii[i].value();
//            cout<<"TOTAL: "<<total<<endl;
        }
        return total;
    }
    Client &operator+=(const StockRecord & from)
    {
        StockRecord *tmp;
        tmp=new StockRecord[broj+1];
        for(int i=0;i<broj;i++)
        {
            tmp[i]=kompanii[i];
        }
        tmp[broj]=from;
        delete []kompanii;
        broj++;
        kompanii=tmp;
        return *this;
    }
    friend ostream & operator<<(ostream &out,Client &cl)
    {
        out<<cl.id<<" "<<cl.totalValue()<<endl;
        for(int i=0;i<cl.broj;i++)
        {
            cout<<cl.kompanii[i];
        }
        return out;
    }

};
int main(){

    int test;
    cin >> test;

    if(test == 1){
    	double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
    	char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
        	cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
    	cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
        	StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
            	cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
