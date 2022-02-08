#include <stdio.h>
//using namespace std;

struct Vozenje
{
    char ime[100];
    int traenje;
    float cena;
    int daliPopust;
};
typedef struct Vozenje Vozenje;
struct ZabavenPark
{
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int n;
};
typedef struct ZabavenPark ZabavenPark;
void print(ZabavenPark *z,int broj)
{
    for(int k=0;k<broj;k++)
    {
    printf("%s %s\n",z[k].ime,z[k].lokacija);
//    cout<<z.ime<<" "<<z.lokacija<<endl;
    for(int i=0;i<z[k].n;i++)
    {
        printf("%s %d %.2f\n",z[k].niza[i].ime,z[k].niza[i].traenje,z[k].niza[i].cena);
//        cout<<z.niza[i].ime<<" "<<z.niza[i].traenje<<" "<<z.niza[i].cena<<endl;
    }

    }

}
void najdobar_park(ZabavenPark *z,int n)
{
    int inx=0;
    int vreme_max=0;
    int pop_max=0;
    for(int i=0;i<n;i++)
    {
    int vreme=0;
    int voz_pop=0;
        for(int j=0;j<z[i].n;j++)
        {
            if(z[i].niza[j].daliPopust==1)
            {

                voz_pop++;
            }
                vreme+=z[i].niza[j].traenje;
        }
        if(voz_pop>pop_max)
        {
            pop_max=voz_pop;
            vreme_max=vreme;
            inx=i;
        }
        else if(voz_pop==pop_max)
        {
            if(vreme>vreme_max)
            {
                vreme_max=vreme;
                inx=i;
            }
        }
//                printf("%d %d\n",vreme,voz_pop);
    }
    printf("Najdobar park: %s %s\n",z[inx].ime,z[inx].lokacija);
}
int main()
{
	int i, j, n, broj;
	//kreiraj niza od maksimum 100 zabavni parkovi
	ZabavenPark ff[100];
	scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
		//ime na festivalot
		scanf("%s", ff[i].ime);
        //mesto
		scanf("%s", ff[i].lokacija);
		//broj na filmovi
		scanf("%d", &ff[i].n);

		for (j = 0; j < ff[i].n; j++){
			scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
			scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
			scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

		}


			}
    print(ff,n);
    najdobar_park(ff,n);

	return 0;
}



