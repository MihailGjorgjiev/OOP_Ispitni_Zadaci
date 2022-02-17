#include <iostream>
#include <cstring>
using namespace std;

class Exception
{
public:
    void message()
    {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud
{
private:
    char tip;//c=konferenciski, j-spisanie
    int godinaIzdavanje;
public:
    Trud(){}
    Trud(char tip,int godinaIzdavanje)
    {

        this->tip=tip;
        this->godinaIzdavanje=godinaIzdavanje;
    }
    ~Trud(){}

    char getTip()
    {
        return tip;
    }

    int getGodinaIzdavanje()
    {
        return godinaIzdavanje;
    }
    friend istream &operator>>(istream &in,Trud &t)
    {
        in>>t.tip;
        in>>t.godinaIzdavanje;
        return in;
    }
    void setTip(char c)
    {
        tip=c;
    }
    void setGodinaIzdavanje(int num)
    {
        godinaIzdavanje=num;
    }

};

class Student
{
private:
    char ime[30];
    int indeks;
    int godinaUpis;
    int *ocenki;
    int brojOcenki;

    void copy_func(const Student &s)
    {
        strcpy(ime,s.ime);
        indeks=s.indeks;
        godinaUpis=s.godinaUpis;
        brojOcenki=s.brojOcenki;
        ocenki=new int[brojOcenki];
        for(int i=0;i<brojOcenki;i++)
        {
            ocenki[i]=s.ocenki[i];
        }
    }
public:
    Student()
    {
        ocenki=NULL;
        brojOcenki=0;
    }
    Student(char *ime,int indeks,int godinaUpis,int *ocenki,int brojOcenki)
    {
        strcpy(this->ime,ime);
        this->indeks=indeks;
        this->godinaUpis=godinaUpis;
        this->brojOcenki=brojOcenki;

        this->ocenki=new int[brojOcenki];
        for(int i=0;i<brojOcenki;i++)
        {
            this->ocenki[i]=ocenki[i];
        }
    }
    Student(const Student &s)
    {
        copy_func(s);
    }
    Student &operator=(const Student &s)
    {
        if(this!=&s)
        {
            delete [] ocenki;
            copy_func(s);
        }
        return *this;
    }
    virtual ~Student()
    {
        delete [] ocenki;
    }
    virtual double rang()
    {
        double avg=0;
        for(int i=0;i<brojOcenki;i++)
        {
            avg+=ocenki[i];
        }
        return (1.0*avg)/brojOcenki;
    }
    friend ostream &operator<<(ostream &out,Student &s)
    {
        out<<s.indeks<<" "<<s.ime<<" "<<s.godinaUpis<<" "<<s.rang()<<endl;
        return out;
    }
    int getGodinaUpis()
    {
        return godinaUpis;
    }
    int getIndeks()
    {
        return indeks;
    }
    void setIme(char *c)
    {
        strcpy(ime,c);
    }
    void setIndeks(int num)
    {
        indeks=num;
    }
    void setGodinaUpis(int num)
    {
        godinaUpis=num;
    }
    void setBrojOcenki(int num)
    {
        brojOcenki=num;
    }
    void setOcenki(int *arr,int num)
    {
        delete [] ocenki;
        ocenki=new int[brojOcenki];
        for(int i=0;i<num;i++)
        {
            ocenki[i]=arr[i];
        }
    }
    char *getIme()
    {
        return ime;
    }
    int *getOcenki()
    {
        return ocenki;
    }
    int getBrojOcenki()
    {
        return brojOcenki;
    }
};

class PhDStudent:public Student
{
private:
    Trud *trudovi;
    int brojTrudovi;
    static int poeniKonferenciski;
    static int poeniSpisanie;

    void copy_phd(PhDStudent &p)
    {
        setIme(p.getIme());
        setIndeks(p.getIndeks());
        setGodinaUpis(p.getGodinaUpis());
        setBrojOcenki(p.getBrojOcenki());
        setOcenki(p.getOcenki(),getBrojOcenki());
        brojTrudovi=p.brojTrudovi;
        trudovi=new Trud[brojTrudovi];
        for(int i=0;i<brojTrudovi;i++)
        {
            trudovi[i]=p.trudovi[i];
        }
    }
public:
    PhDStudent()
    {
        trudovi=NULL;
        brojTrudovi=0;
    }
    PhDStudent(PhDStudent &p)
    {
        copy_phd(p);
    }
    PhDStudent &operator=(PhDStudent &p)
    {
        if(this!=&p)
        {
            delete [] trudovi;
            copy_phd(p);
        }
        return *this;
    }
    PhDStudent(char *ime,int indeks,int godinaUpis,int *ocenki,int brojOcenki,Trud *trudovi,int brojTrudovi):Student(ime,indeks,godinaUpis,ocenki,brojOcenki)
    {
        int k=0;
        this->trudovi=new Trud[brojTrudovi];
        for(int i=0;i<brojTrudovi;i++)
        {
            if(getGodinaUpis()>trudovi[i].getGodinaIzdavanje())
            {
                try
                {
                    throw Exception();
                }
                catch(Exception &e)
                {
                    e.message();
                }
            }
            else
            {
                this->trudovi[k++]=trudovi[i];
            }


        }
        this->brojTrudovi=k;
    }
    ~PhDStudent()
    {
        delete [] trudovi;
    }
    PhDStudent(const PhDStudent &p)
    {

    }
    double rang()
    {
        double total=0;
        for(int i=0;i<brojTrudovi;i++)
        {
            if(trudovi[i].getTip()=='c' || trudovi[i].getTip()=='C')
            {
                total+=poeniKonferenciski;
            }
            else
            {
                total+=poeniSpisanie;
            }
        }
        return total+Student::rang();
    }

    PhDStudent &operator+=(Trud &t)
    {
        if(t.getGodinaIzdavanje()<getGodinaUpis())
        {
            throw Exception();
        }
        else
        {
            Trud *tmp=new Trud[brojTrudovi+1];
            for(int i=0;i<brojTrudovi;i++)
            {
                tmp[i]=trudovi[i];
            }
            tmp[brojTrudovi]=t;
            brojTrudovi++;
            delete [] trudovi;

            trudovi=tmp;
        }
        return *this;
    }
    static void setPoeniKonferenciski(int num)
    {
        poeniKonferenciski=num;
    }
    static void setPoeniSpisanie(int num)
    {
        poeniSpisanie=num;
    }

    void dodadiTrud(int indeks,Trud &t)
    {
        if(getIndeks()==indeks)
        {
            *this+=t;
        }
    }

};
int PhDStudent::poeniKonferenciski=1;
int PhDStudent::poeniSpisanie=3;


int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndeks()==indeks)
            {

                PhDStudent *pd=dynamic_cast<PhDStudent *>(niza[i]);
                if(pd!=0)
                {
                    try
                    {
                        *pd+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }
            }
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;


		for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndeks()==indeks)
            {

                PhDStudent *pd=dynamic_cast<PhDStudent *>(niza[i]);
                if(pd!=0)
                {
                    try
                    {
                        *pd+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }
            }
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndeks()==indeks)
            {

                PhDStudent *pd=dynamic_cast<PhDStudent *>(niza[i]);
                if(pd!=0)
                {
                    try
                    {
                        *pd+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }
            }
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        PhDStudent::setPoeniKonferenciski(conf);
        PhDStudent::setPoeniSpisanie(journal);

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}

