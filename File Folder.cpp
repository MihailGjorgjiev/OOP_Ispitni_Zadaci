#include <iostream>
#include <string.h>
using namespace std;

enum Extension{pdf=0,txt,exe};
class File
{
private:
    char *datoteka;
    Extension tip;
    char *ime;
    int golemina;
public:
    File()
    {
        datoteka=NULL;
        ime=NULL;
        golemina=0;
    }
    File(char *datoteka,char *ime,int golemina,Extension tip)
    {
        this->datoteka=new char[strlen(datoteka)+1];
        strcpy(this->datoteka,datoteka);
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->golemina=golemina;
        this->tip=tip;
    }
    File(const File &f)
    {
        datoteka=new char[strlen(f.datoteka)+1];
        strcpy(datoteka,f.datoteka);
        ime=new char[strlen(f.ime)+1];
        strcpy(ime,f.ime);
        golemina=f.golemina;
        tip=f.tip;
    }
    ~File()
    {
        delete [] ime;
        delete [] datoteka;
    }
    File &operator=(const File &f)
    {
        if(this!=&f)
        {
            delete [] datoteka;
            datoteka=new char[strlen(f.datoteka)+1];
            strcpy(datoteka,f.datoteka);

            delete [] ime;
            ime=new char[strlen(f.ime)+1];
            strcpy(ime,f.ime);

            golemina=f.golemina;
            tip=f.tip;
        }
        return *this;
    }
    void print()
    {
        cout<<"File name: "<<datoteka;
        if(tip==0)
        {
            cout<<".pdf"<<endl;

        }
        else if(tip==1)
        {
            cout<<".txt"<<endl;

        }
        else if(tip==2)
        {

            cout<<".exe"<<endl;
        }
        cout<<"File owner: "<<ime<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
    bool equals(const File & that)
    {
        if(this->tip==that.tip && strcmp(this->ime,that.ime)==0 && strcmp(this->datoteka,that.datoteka)==0)
        {
            return true;
        }
        return false;
    }
    bool equalsType(const File & that)
    {
        if(this->tip==that.tip && strcmp(this->datoteka,that.datoteka)==0)
        {
            return true;
        }
        return false;
    }

};

class Folder
{
private:
    char *ime;
    int broj;
    File *dokumenti;
public:
    Folder(const char *name)
    {
        this->ime=new char[strlen(name)+1];
        strcpy(this->ime,name);
        broj=0;
        dokumenti=NULL;
    }
    ~Folder()
    {
        delete [] ime;
        delete [] dokumenti;
    }
    void print()
    {
        cout<<"Folder name: "<<ime<<endl;
        for(int i=0;i<broj;i++)
        {
            dokumenti[i].print();
        }
    }
    void remove(const File &file)
    {
        int inx=-1;
        for(int i=0;i<broj;i++)
        {
            if(dokumenti[i].equals(file)==true)
            {
                inx=i;
                break;
            }
        }
        if(inx>-1)
        {
            File *tmp=new File[broj-1];
            for(int i=0,j=0;i<broj;i++)
            {
                if(inx==i)
                {
                    continue;
                }
                tmp[j++]=dokumenti[i];
            }
        delete [] dokumenti;
        dokumenti=tmp;
        this->broj--;
        }
    }
    void add(const File &file)
    {
        File *tmp=new File[broj+1];
        for(int i=0;i<broj;i++)
        {
            tmp[i]=dokumenti[i];
        }
        tmp[broj]=file;
        delete [] dokumenti;
        dokumenti=tmp;
        broj++;
    }
};
int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}

