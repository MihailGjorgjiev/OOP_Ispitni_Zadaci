#include <iostream>
#include <string.h>
using namespace std;

class List
{
private:
    int *niza;
    int broj;
public:
    List()
    {
        niza=NULL;
        broj=0;
    }
    List(int *niza,int broj)
    {
        this->broj=broj;
        this->niza=new int[broj];
        for(int i=0;i<broj;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    List(const List &l)
    {
        broj=l.broj;
        niza=new int[broj];
        for(int i=0;i<broj;i++)
        {
            niza[i]=l.niza[i];
        }
    }
    ~List()
    {
        delete [] niza;
    }
    List & operator=(const List &from)
    {
        if(this!=&from)
        {
            delete [] niza;
            broj=from.broj;
            niza=new int [broj];
            for(int i=0;i<broj;i++)
            {
                niza[i]=from.niza[i];
            }
        }
        return *this;
    }
    int getBroj()
    {
        return broj;
    }
    int sum()
    {
        int suma=0;
        for(int i=0;i<broj;i++)
        {
            suma+=niza[i];
        }
        return suma;
    }
    double average()
    {
        int suma=sum();
        return (suma*1.0)/(broj*1.0);
    }
    void pecati()
    {
        cout<<broj<<": ";
        for(int i=0;i<broj;i++)
        {
            cout<<niza[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average();
        cout<<endl;
    }
};

class ListContainer
{
private:
    List *niza;
    int broj;
    int obidi;
public:
    ListContainer()
    {
        niza=NULL;
        broj=0;
        obidi=0;
    }
    ListContainer(const ListContainer &lc)
    {
        obidi=lc.obidi;
        broj=lc.broj;
        niza=new List[broj];
        for(int i=0;i<broj;i++)
        {
            niza[i]=lc.niza[i];
        }
    }
    ~ListContainer()
    {
        delete [] niza;
    }
    ListContainer &operator=(const ListContainer &from)
    {
        if(this!=&from)
        {
            broj=from.broj;
            obidi=from.obidi;
            delete [] niza;
            niza=new List[broj];
            for(int i=0;i<broj;i++)
            {
                niza[i]=from.niza[i];
            }
        }
        return *this;
    }
    void addNewList(List l)
    {
        obidi++;
        bool add=true;
        for(int i=0;i<broj;i++)
        {
            if(niza[i].sum()==l.sum())
            {
                add=false;
                break;
            }
        }
        if(add==true)
        {
            List *tmp;
            tmp=niza;
            niza=new List[broj+1];
            for(int i=0;i<broj;i++)
            {
                niza[i]=tmp[i];
            }
            niza[broj]=l;
            broj++;
            delete [] tmp;
        }
    }
    int sum()
    {
        int suma=0;
        for(int i=0;i<broj;i++)
        {
            suma+=niza[i].sum();
        }
        return suma;
    }
    double average()
    {
        int suma=sum();
        int n=0;
        for(int i=0;i<broj;i++)
        {
            n+=niza[i].getBroj();
        }
        return (suma*1.0)/(n*1.0);
    }
    void print()
    {
        if(broj>0)
        {
            for(int i=0;i<broj;i++)
            {
                cout<<"List number: "<<i+1<<" List info: ";
                niza[i].pecati();
            }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<broj<<" Failed attempts: "<<obidi-broj<<endl;
        }
        else
        {
            cout<<"The list is empty"<<endl;
        }
    }
};
int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}

