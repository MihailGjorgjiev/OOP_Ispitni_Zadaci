#include <stdio.h>
#include <string.h>

struct SkiLift
{
    char ime[15];
    int korisnici;
    int daliRaboti;
};
typedef struct SkiLift Skilift;

struct SkiCenter
{
    char ime[20];
    char drzava[20];
    Skilift niza[20];
    int broj;
};

typedef struct SkiCenter SkiCenter;


int br_liftovi(SkiCenter sc1,SkiCenter sc2)
{
    if(sc1.broj<sc2.broj)
    {
        return 1;
    }
    return 0;
}
int kapacitet(SkiCenter *sc,int n)
{
    int i,j;
    int inx=0;
    int suma_before=0,suma_after=0;
    for(i=0;i<n;i++)
    {
        suma_after=0;
        for(j=0;j<sc[i].broj;j++)
        {
            if(sc[i].niza[j].daliRaboti==1)
            {
                suma_after+=sc[i].niza[j].korisnici;
            }
        }
        if(suma_after>suma_before)
        {
            suma_before=suma_after;
            inx=i;
        }
        else if(suma_after==suma_before)
        {
            if(br_liftovi(sc[inx],sc[i])==1)
            {
                inx=i;
            }
        }
    }
    return inx;
}

void najgolemKapacitet(SkiCenter *sc, int n)
{
    int capacity=0;
    int inx=kapacitet(sc,n);
    printf("%s\n",sc[inx].ime);
    printf("%s\n",sc[inx].drzava);
    for(int i=0;i<sc[inx].broj;i++)
    {
        if(sc[inx].niza[i].daliRaboti==1)
        {
            capacity+=sc[inx].niza[i].korisnici;
        }
    }
    printf("%d\n",capacity);

}
int main()
{
    int n,i,j;
	scanf("%d", &n);
	SkiCenter ski[n];
	for (i = 0; i < n; i++){
    scanf("%s",&ski[i].ime);
    scanf("%s",&ski[i].drzava);
    scanf("%d",&ski[i].broj);
		for(j=0;j<ski[i].broj;j++)
        {
            scanf("%s",&ski[i].niza[j].ime);
            scanf("%d",&ski[i].niza[j].korisnici);
            scanf("%d",&ski[i].niza[j].daliRaboti);
        }


	}

    najgolemKapacitet(ski,n);

	return 0;
}

