#include <iostream>
#include <cstring>
using namespace std;

class Image
{
protected:
    char *name_image;
    char name_user[50];
    int height;
    int width;
public:
    Image(char *name_image="untitled",char *name_user="unknown",int width=800,int height=800)
    {
        this->name_image=new char[strlen(name_image)+1];
        strcpy(this->name_image,name_image);
        strcpy(this->name_user,name_user);
        this->height=height;
        this->width=width;
    }
    Image(const Image &im)
    {
        name_image=new char[strlen(im.name_image)+1];
        strcpy(name_image,im.name_image);
        strcpy(name_user,im.name_user);
        width=im.width;
        height=im.height;
    }
    virtual ~Image()
    {
        delete [] name_image;
    }
    virtual int fileSize()
    {
        return width*height*3;
    }

    friend ostream &operator<<(ostream &out,Image &im)
    {
        out<<im.name_image<<" "<<im.name_user<<" "<<im.fileSize()<<endl;
        return out;
    }
};


class TransparentImage:public Image
{
protected:
    bool isTransparent;
public:

    TransparentImage(char *name_image="untitled",char *name_user="unknown",int width=800,int height=800,bool isTransparent=true):Image(name_image,name_user,width,height)
    {
        this->isTransparent=isTransparent;
//        cout<<isTransparent<<endl;
    }
    ~TransparentImage(){}

    int fileSize()
    {
//        cout<<isTransparent<<endl;
        if(isTransparent==false)
        {
            return width*height+width*height/8;
        }
        return width*height*4;
    }
    friend ostream &operator<<(ostream &out,TransparentImage &im)
    {
        out<<im.name_image<<" "<<im.name_user<<" "<<im.fileSize()<<endl;
        return out;
    }
};

bool operator>(Image &im1,Image *im2)
{
    int size1,size2;
    TransparentImage *t=dynamic_cast<TransparentImage *>(&im1);
    if(t!=0)
    {
        size1=t->fileSize();
    }
    else
    {
        size1=im1.fileSize();
    }
    t=dynamic_cast<TransparentImage *>(im2);
    if(t!=0)
    {
        size2=t->fileSize();
    }
    else
    {
        size2=im2->fileSize();
    }
//    cout<<size1<<" "<<size2<<endl;
    if(size1>size2)
    {
        return true;
    }
    return false;
}

class Folder
{
protected:
    char folder_name[255];
    char folder_user[50];
    Image *arr[100];
    int number;
public:
    Folder()
    {
        strcpy(this->folder_user,"unknown");
        number=0;
    }
    Folder(char *folder_name,char *folder_user="unknown")
    {
        strcpy(this->folder_user,folder_user);
        strcpy(this->folder_name,folder_name);
        number=0;
    }
    ~Folder(){}
    int folderSize()
    {
        int sum=0;
        for(int i=0;i<number;i++)
        {
            sum+=arr[i]->fileSize();
        }
        return sum;
    }
    Image *getMaxFile()
    {
        int inx=0;
        for(int i=0;i<number;i++)
        {
            if(!(*arr[inx]>arr[i]))
            {
                inx=i;
            }
        }
        return arr[inx];
    }
    Folder &operator+=(Image &im)
    {
        TransparentImage *t=dynamic_cast<TransparentImage *>(&im);
        if(t!=0)
        {
            arr[number]=new TransparentImage(*t);
            number++;
            return *this;
        }

        arr[number]=new Image(im);
        number++;
        return *this;

    }

    friend ostream &operator<<(ostream &out, Folder f)
    {
        out<<f.folder_name<<" "<<f.folder_user<<endl;
        out<<"--"<<endl;
        for(int i=0;i<f.number;i++)
        {
            TransparentImage *t=dynamic_cast<TransparentImage *>(f.arr[i]);
            if(t!=0)
            {
                out<<*t;
            }
            else
            {
            out<<*f.arr[i];
            }
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }
    Image *operator[](int n)
    {
        if(n>=0 && n<number)
        {
            return arr[n];
        }
        return NULL;
    }
};

Folder max_folder_size(Folder *f,int n)
{
    int inx=0;
    for(int i=1;i<n;i++)
    {
        if(f[inx].folderSize()<f[i].folderSize())
        {
            inx=i;
        }
    }
    return f[inx];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};

