#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame
{
public:
    void message()
    {
        cout<<"The game is already in the collection"<<endl;
    }
};
int monthDifference(int month1,int year1,int month2=5,int year2=2018)
{
    int k=1;
    while(month1 != month2 || year1!=year2)
    {
        k++;
        month1++;
        if(month1==12)
        {
            month1=0;
            year1++;
        }
    }
    k--;
    return k;
}

class Game
{
protected:
    char name[100];
    float price;
    bool forSale;
public:
    Game(){}
    Game(char *name,float price,bool forSale)
    {
        strcpy(this->name,name);
        this->price=price;
        this->forSale=forSale;
    }
    virtual ~Game(){}

    friend istream &operator>>(istream &in, Game &g)
    {
        in.get();
        in.getline(g.name,100);
        in>>g.price;
        in>>g.forSale;

        return in;
    }

    friend ostream &operator<<(ostream &out,Game &g)
    {
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.forSale==true)
        {
            out<<", bought on sale";
        }
        out<<endl;
        return out;
    }
    bool operator==(Game &g)
    {
        if(strcmp(name,g.name)==0)
        {
            return true;
        }
        return false;
    }
    virtual float getPrice()
    {
        if(forSale==true)
        {
            return price*0.7;
        }
        return price;
    }
};

class SubscriptionGame:public Game
{
protected:
    float monthlyRevenue;
    int month;
    int year;
public:
    SubscriptionGame(){}
    SubscriptionGame(char *name,float price,bool forSale,float monthlyRevenue,int month,int year):Game(name,price,forSale)
    {
        this->monthlyRevenue=monthlyRevenue;
        this->month=month;
        this->year=year;
    }
    ~SubscriptionGame(){}

    friend istream &operator>>(istream &in, SubscriptionGame &g)
    {
        in.get();
        in.getline(g.name,100);
        in>>g.price;
        in>>g.forSale;
        in>>g.monthlyRevenue;
        in>>g.month;
        in>>g.year;

        return in;
    }

    friend ostream &operator<<(ostream &out,SubscriptionGame &g)
    {
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.forSale==true)
        {
            out<<", bought on sale";
        }
        out<<", monthly fee: $"<<g.monthlyRevenue<<", purchased: "<<g.month<<"-"<<g.year<<endl;
        return out;
    }
    bool operator==(SubscriptionGame &g)
    {
        if(strcmp(name,g.name)==0)
        {
            return true;
        }
        return false;
    }
    float getPrice()
    {
        float total=Game::getPrice();
        total+=monthlyRevenue*monthDifference(month,year);
        return total;
    }
};

class User
{
protected:
    char username[100];
    Game **games;
    int numberGames;
public:
    User(char *username)
    {
        strcpy(this->username,username);
        games=NULL;
        numberGames=0;
    }
    ~User()
    {
        delete [] games;
    }
    User &operator+=(Game &g)
    {
      for(int i=0;i<numberGames;i++)
      {
          if(g==*games[i])
          {
              throw ExistingGame();
          }
      }
      Game **tmp;
      tmp=new Game*[numberGames+1];
      for(int i=0;i<numberGames;i++)
      {
          tmp[i]=games[i];
      }
      tmp[numberGames]=&g;
      numberGames++;
      delete [] games;
      games=tmp;
      return *this;
    }
    float total_spent()
    {
        float total=0;
        for(int i=0;i<numberGames;i++)
        {
            SubscriptionGame *s=dynamic_cast<SubscriptionGame *>(games[i]);
            if(s!=0)
            {
                total+=s->getPrice();
            }
            else
            {
                total+=games[i]->getPrice();
            }
        }
        return total;
    }
    friend ostream &operator<<(ostream &out,User &u)
    {
        out<<"\nUser: "<<u.username<<endl;
        for(int i=0;i<u.numberGames;i++)
        {
            out<<"- ";
            SubscriptionGame *s=dynamic_cast<SubscriptionGame *>(u.games[i]);
            if(s!=0)
            {
                out<<*s;
            }
            else
            {
                out<<*u.games[i];
            }
        }
        return out;
    }
};

int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"\nTotal money spent: $"<<u.total_spent()<<endl;
  }
}

