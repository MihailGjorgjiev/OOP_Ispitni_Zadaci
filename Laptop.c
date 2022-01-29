#include <stdio.h>

struct Laptop
{
    char marka[100];
    float monitor;
    int touch;
    int cena;
};
typedef struct Laptop Laptop;

struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop dostapni[100];
    int broj;
};
typedef struct ITStore ITStore;

void print(ITStore *prodavnica,int n)
{
    for(int j=0;j<n;j++)
    {
        printf("%s %s\n",prodavnica[j].ime,prodavnica[j].lokacija);
        for(int i=0;i<prodavnica[j].broj;i++)
        {
            printf("%s %g %d\n",prodavnica[j].dostapni[i].marka,prodavnica[j].dostapni[i].monitor,prodavnica[j].dostapni[i].cena);

        }

    }
}
void najeftina_ponuda(ITStore *prodavnica,int n)
{
    int cena_min=99999;
    int inx=0;
    for(int i=0;i<n;i++)
    {

        for(int j=0;j<prodavnica[i].broj;j++)
        {
            if(prodavnica[i].dostapni[j].touch==1 && cena_min>prodavnica[i].dostapni[j].cena)
            {
                cena_min=prodavnica[i].dostapni[j].cena;
                inx=i;
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata: \n%s %s\n",prodavnica[inx].ime,prodavnica[inx].lokacija);
    printf("Najniskata cena iznesuva: %d\n",cena_min);
}
int main() {
    ITStore s[100];
    int n;
    scanf("%d",&n); //broj na IT prodavnici
    for(int i=0;i<n;i++)
    {
        scanf("%s",&s[i].ime);
        scanf("%s",&s[i].lokacija);
        scanf("%d",&s[i].broj);
        Laptop l[s[i].broj];
        for(int j=0;j<s[i].broj;j++)
        {
            scanf("%s",&s[i].dostapni[j].marka);
            scanf("%f",&s[i].dostapni[j].monitor);
            scanf("%d",&s[i].dostapni[j].touch);
            scanf("%d",&s[i].dostapni[j].cena);
        }
    }
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    print(s,n);


    //pecatenje na site prodavnici




    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}

