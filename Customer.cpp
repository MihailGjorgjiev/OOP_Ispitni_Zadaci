#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

enum typeC{standard=0,loyal,vip};

class UserExistsException
{
public:
    void message()
    {
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer
{
protected:
    char name[50];
    char email[50];
    typeC type;
    int number_products;

    static int primary_dicount;//loyal
    const static int additional_discount;//vip
public:
    Customer(){}
    Customer(char *name,char *email, typeC type,int number_products)
    {
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->type=type;
        this->number_products=number_products;
    }
    ~Customer(){}

    friend ostream &operator<<(ostream &out,Customer &c)
    {
        out<<c.name<<endl;
        out<<c.email<<endl;
        cout<<c.number_products<<endl;
        if(c.type==standard)
        {
            out<<"standard 0"<<endl;
        }
        else if(c.type==loyal)
        {
            out<<"loyal "<<primary_dicount<<endl;
        }
        else if(c.type==vip)
        {
            out<<"vip "<<primary_dicount+additional_discount<<endl;
        }
        return out;
    }

    char *getEmail()
    {
        return email;
    }

    void setType(typeC t)
    {
        type=t;
    }
    typeC getType()
    {
        return type;
    }

    int getNumberOfProducts()
    {
        return number_products;
    }

    static void setDiscount1(int x)
    {
        Customer::primary_dicount=x;
    }

};
int Customer::primary_dicount=10;
const int Customer::additional_discount=20;


class FINKI_bookstore
{
protected:
    Customer *customers;
    int number_customers;

    void copy_f(const FINKI_bookstore &fb)
    {
        number_customers=fb.number_customers;

        customers=new Customer[number_customers];

        for(int i=0;i<number_customers;i++)
        {
            customers[i]=fb.customers[i];
        }
    }
public:
    FINKI_bookstore()
    {
        customers=NULL;
        number_customers=0;
    }
    FINKI_bookstore(const FINKI_bookstore &fb)
    {
        copy_f(fb);
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &fb)
    {
        if(this!=&fb)
        {
            delete [] customers;
            copy_f(fb);
        }
        return *this;
    }

    FINKI_bookstore &operator+=(Customer &c)
    {

        for(int i=0;i<number_customers;i++)
        {
            if(strcmp(customers[i].getEmail(),c.getEmail())==0)
            {
                throw UserExistsException();
            }
        }
        Customer *temp;
        temp=new Customer[number_customers+1];

        for(int i=0;i<number_customers;i++)
        {
            temp[i]=customers[i];
        }
        temp[number_customers]=c;
        number_customers++;
        delete [] customers;
        customers=temp;

        return *this;
    }
    void update()
    {
        for(int i=0;i<number_customers;i++)
        {
            if(customers[i].getType()==standard && customers[i].getNumberOfProducts()>5)
            {
                customers[i].setType(loyal);
            }
            else if(customers[i].getType()==loyal && customers[i].getNumberOfProducts()>10)
            {
                customers[i].setType(vip);
            }

        }
    }
    friend ostream &operator<<(ostream &out,FINKI_bookstore &fb)
    {
        for(int i=0;i<fb.number_customers;i++)
        {
            out<<fb.customers[i];
        }
        return out;
    }

    void setCustomers(Customer *c,int n)
    {
        number_customers=n;
        customers=new Customer[n];
        for(int i=0;i<n;i++)
        {
            customers[i]=c[i];
        }

    }
};
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    try{
    fc+=c;
    }
    catch(UserExistsException &u)
    {
        u.message();
    }
        cout << fc;

  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;

    Customer c(name, email, (typeC) tC, numProducts);
    try{
    fc+=c;
    }
    catch(UserExistsException &u)
    {
        u.message();
    }
    cout << fc;

  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}


