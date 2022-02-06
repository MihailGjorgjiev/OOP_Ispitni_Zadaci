#include <iostream>
#include <cstring>
using namespace std;

class Book
{
protected:
    char isbn[15];
    char title[50];
    char author[30];
    double price;
public:
    Book(){}
    Book(char *isbn,char *title,char *author,double price)
    {
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;

    }
    virtual ~Book(){}

    virtual double bookPrice()=0;

    friend ostream &operator<<(ostream &out,Book &b)
    {
        out<<b.isbn<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice()<<endl;
        return out;
    }

    void setISBN(char *isbn)
    {
        strcpy(this->isbn,isbn);
    }
};

class OnlineBook:public Book
{
protected:
    char *url;
    int size;

    void copy_func(const OnlineBook &ob)
    {
        url=new char[strlen(ob.url)+1];

        strcpy(isbn,ob.isbn);
        strcpy(title,ob.title);
        strcpy(author,ob.author);
        strcpy(url,ob.url);

        price=ob.price;
        size=ob.size;
    }
public:
    OnlineBook()
    {
        url=NULL;
    }
    OnlineBook(char *isbn,char *title,char *author,double price,char *url,double size):Book(isbn,title,author,price)
    {
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);

        this->size=size;
    }
    ~OnlineBook()
    {
        delete [] url;
    }
    OnlineBook(const OnlineBook &ob)
    {
        copy_func(ob);
    }
    OnlineBook &operator=(const OnlineBook &ob)
    {
        delete [] url;
        copy_func(ob);

        return *this;
    }

    double bookPrice()
    {
        if(size>20)
        {
            return price*1.2;
        }
        return price;
    }
//    friend ostream &operator<<(ostream &out,OnlineBook &ob)
//    {
//        out<<ob.isbn<<": "<<ob.title<<", "<<ob.author<<" "<<ob.price;
//
//        return out;
//    }
};




class PrintBook:public Book
{
protected:
    double weight;
    bool inStock;
public:
    PrintBook(){}
    PrintBook(char *isbn,char *title,char *author,double price,double weight,bool inStock):Book(isbn,title,author,price)
    {
        this->weight=weight;
        this->inStock=inStock;
    }
    ~PrintBook(){}

    double bookPrice()
    {
        if(weight>0.7)
        {
            return price*1.15;
        }
        return price;
    }
//    friend ostream &operator<<(ostream &out,PrintBook &pb)
//    {
//        out<<pb.isbn<<": "<<pb.title<<", "<<pb.author<<" "<<pb.price;
//
//        return out;
//    }
};


bool operator>(Book &b1,Book &b2)
{
    if(b1.bookPrice()>b2.bookPrice())
    {
        return true;
    }
    return false;
}

void mostExpensiveBook(Book **books,int n)
{
    int online,printed,inx;
    online=printed=inx=0;
    for(int i=0;i<n;i++)
    {
        OnlineBook *o=dynamic_cast<OnlineBook *>(books[i]);
        if(o!=0)
        {
            online++;
        }
        PrintBook *p=dynamic_cast<PrintBook *>(books[i]);
        if(p!=0)
        {
            printed++;
        }

    }
    for(int i=1;i<n;i++)
    {
        if(books[i]->bookPrice()>books[inx]->bookPrice())
        {
            inx=i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*books[inx]<<endl;

}



int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
