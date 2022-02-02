#include <stdio.h>


typedef struct Pacient
{
    char ime[100];
    int zdrastveno;
    int pregledi;
}Pacient;
//
typedef struct MaticenDoktor
{
    char ime[100];
    int br_pac;
    Pacient niza[200];
    float cena;
}doktor;

float zarabotka(doktor md)
{
    float pari=0;
    for(int i=0;i<md.br_pac;i++)
    {
        if(md.niza[i].zdrastveno==0)
        {
            pari+=md.cena*md.niza[i].pregledi;
        }
    }
    return pari;
}

int pregledi_mesecno(doktor md)
{
    int broj=0;
    for(int i=0;i<md.br_pac;i++)
    {
        broj+=md.niza[i].pregledi;
    }
    return broj;
}

void najuspesen_doktor(doktor *md,int n)
{
    int inx=0;
    for(int i=1;i<n;i++)
    {
        if(zarabotka(md[inx])<zarabotka(md[i]))
        {
            inx=i;
        }
        else if(zarabotka(md[inx])==zarabotka(md[i]))
        {
            if(pregledi_mesecno(md[inx])<pregledi_mesecno(md[i]))
            {
                inx=i;
            }
        }
    }
    printf("%s %.2f %d",md[inx].ime,zarabotka(md[inx]),pregledi_mesecno(md[inx]));
}
int main()
{
	int i, j, n;
	scanf("%d", &n);
	doktor md[n];
	for (i = 0; i < n; i++){
		scanf("%s", &md[i].ime);
		scanf("%d", &md[i].br_pac);
		scanf("%f", &md[i].cena);

		for (j = 0; j < md[i].br_pac; j++){
			scanf("%s", &md[i].niza[j].ime);
			scanf("%d", &md[i].niza[j].zdrastveno);
			scanf("%d", &md[i].niza[j].pregledi);
		}
	}
	najuspesen_doktor(md, n);

	return 0;
}

