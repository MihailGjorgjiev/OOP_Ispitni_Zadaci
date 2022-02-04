#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

typedef struct RabotnaNedela
{
    int casovi[5];
    int br_nedela;
}RN;

typedef struct Rabotnik
{
    char ime[50];
    RN nedela[4];
}R;
int suma_ned(RN temp)
{
    int suma=0;
    for(int i=0;i<DENOVI;i++)
    {
        suma+=temp.casovi[i];
    }
    return suma;
}
int maxNedela(R *r)
{
    int inx=0;
    for(int i=1;i<NEDELI;i++)
    {
        if(suma_ned(r->nedela[inx])<suma_ned(r->nedela[i]))
        {
            inx=i;
        }
    }
    return (inx+1);
}

void table(R *r, int n)
{
    int vkupno;
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0;i<n;i++)
    {
        vkupno=0;
        printf("%s\t",r[i].ime);
        for(int j=0;j<NEDELI;j++)
        {
            vkupno+=suma_ned(r[i].nedela[j]);
            printf("%d\t",suma_ned(r[i].nedela[j]));
        }
        printf("%d\n",vkupno);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedela[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}

