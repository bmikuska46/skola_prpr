// Branislav Mikuška
// FIIT
// Pracovanie so záznamami so zvieratkami

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam
{
    char meno[52];
    long long int rodc;
    char kod[5];
    char nazov_prispevnku[152];
    char mena_autorov[202];
    char typ[4];
    char cas[6];
    long int datum;
    struct zaznam *dalsi;

} ZAZNAM;

int fzaznamy(FILE **fr)
{ // FUNKCIA NA ZISŤOVANIE POČTU ZÁZNAMOV
    int riadky = 1;
    int zaznamy = 0;
    char riadok;
    int cur_riadok = 0;
    fseek(*fr, 0, SEEK_SET);
    while (riadok != EOF)
    {
        riadok = fgetc(*fr);
        if (riadok == '\n')
        {
            riadky++;
        }
    }
    while (cur_riadok <= riadky)
    {
        if ((cur_riadok % 9) == 8)
        {
            zaznamy++;
        }
        cur_riadok++;
    }
    return zaznamy;
}

void n(FILE **fr, ZAZNAM **zaciatok)
{

    if (*zaciatok != NULL)
    { // uvolňovanie prvkov ak už spájaný zoznam bol vytvorený
        ZAZNAM *aktualny = *zaciatok;
        while ((*zaciatok) != NULL)
        {
            aktualny = *zaciatok;
            *zaciatok = (*zaciatok)->dalsi;
            free(aktualny);
        }
    }

    *fr = fopen("konferencny_zoznam.txt", "r"); // otvorenie subora a následné overenie či bol otvorený
    if (*fr == NULL)
    {
        printf("Zaznamy neboli nacitane!");
        exit(0);
    }

    int pocet_z = fzaznamy(&(*fr));
    char buffer[202];
    fseek(*fr, 0, SEEK_SET);
    for (int i = 1; i <= pocet_z; i++)
    { // pridávanie do spájaného zoznamu
        ZAZNAM *novy_prvok = (ZAZNAM *)malloc(sizeof(ZAZNAM));
        ZAZNAM *posledny = *zaciatok;
        for (int j = 0; j < 9; j++)
        {
            if ((j % 9) == 0)
            {
                fgets(buffer, 202, *fr);
            }

            else if ((j % 9) == 1)
            {
                fgets(buffer, 52, *fr);
                for (int k = 0; k < 52; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->meno), buffer);
            }

            else if ((j % 9) == 2)
            {
                fscanf(*fr, "%lld", &(novy_prvok->rodc));
                fgets(buffer, 202, *fr);
            }

            else if ((j % 9) == 3)
            {
                fgets(buffer, 5, *fr);
                for (int k = 0; k < 5; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->kod), buffer);
            }

            else if ((j % 9) == 4)
            {
                fgets(buffer, 152, *fr);
                for (int k = 0; k < 152; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->nazov_prispevnku), buffer);
            }

            else if ((j % 9) == 5)
            {
                fgets(buffer, 202, *fr);
                for (int k = 0; k < 202; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->mena_autorov), buffer);
            }

            else if ((j % 9) == 6)
            {
                fgets(buffer, 4, *fr);
                for (int k = 0; k < 4; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->typ), buffer);
            }

            else if ((j % 9) == 7)
            {
                fgets(buffer, 6, *fr);
                for (int k = 0; k < 6; k++)
                {
                    if (buffer[k] == '\n')
                    {
                        buffer[k] = '\0';
                        break;
                    }
                }
                strcpy((novy_prvok->cas), buffer);
            }
            else if ((j % 9) == 8)
            {
                fscanf(*fr, "%ld", &(novy_prvok->datum));
                fgets(buffer, 10, *fr);

                novy_prvok->dalsi = NULL; // posuvanie na ďalší prvok
                if ((*zaciatok) == NULL)
                {
                    *zaciatok = novy_prvok;
                    continue;
                }
                while (posledny->dalsi != NULL)
                {
                    posledny = posledny->dalsi;
                }
                posledny->dalsi = novy_prvok;
            }
        }
    }
    if (*zaciatok != NULL)
    {
        printf("Nacitalo sa %d zaznamov\n", pocet_z);
    }
}

void v(ZAZNAM **zaciatok)
{
    ZAZNAM *aktualny = *zaciatok;
    int i = 1;
    while (aktualny != NULL)
    {
        printf("%d.\n", i);
        printf("Prezenter: %s\n", aktualny->meno);
        printf("Rodne cislo: %lld\n", aktualny->rodc);
        printf("Kod prezentacnej miestnosti: %s\n", aktualny->kod);
        printf("Nazov prispevku: %s\n", aktualny->nazov_prispevnku);
        printf("Mena autorov: %s\n", aktualny->mena_autorov);
        printf("Typ prezentovania: %s\n", aktualny->typ);
        printf("Cas prezentovania: %s\n", aktualny->cas);
        printf("Datum: %ld\n", aktualny->datum);
        aktualny = aktualny->dalsi;
        i++;
    }
}

void p(FILE **fr, ZAZNAM **zaciatok)
{
    ZAZNAM *novy = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    ZAZNAM *aktualny = *zaciatok;
    ZAZNAM *predosli = *zaciatok;
    int pocet_z = fzaznamy(&(*fr));
    int pozicia = 1;
    printf("Zadaj poziciu: ");
    scanf("%d", &pozicia);
    while (pozicia < 1 || pozicia > pocet_z + 1)
    {
        printf("Zadaj poziciu: ");
        scanf("%d", &pozicia);
    }

    int momentalna_pozicia = 1;
    char buffer[202];
    int temp = 1;
    fgets(buffer, 52, stdin);
    printf("Zadaj meno: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->meno), buffer);

    printf("Zadaj rodne cislo: ");
    scanf("%lld", &(novy->rodc));

    fgets(buffer, 5, stdin);
    printf("Zadaj kod miestnosti: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->kod), buffer);

    fgets(buffer, 152, stdin);
    printf("Zadaj nazov prispevku: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->nazov_prispevnku), buffer);

    fgets(buffer, 202, stdin);
    printf("Zadaj mena prezentujucich: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->mena_autorov), buffer);

    fgets(buffer, 4, stdin);
    printf("Zadaj typ prezentovania: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->typ), buffer);

    fgets(buffer, 6, stdin);
    printf("Zadaj cas: ");
    scanf("%[^\n]*c", buffer);
    strcpy((novy->cas), buffer);

    printf("Zadaj datum: ");
    scanf("%ld", &(novy->datum));
    novy->dalsi = NULL;

    while (aktualny != NULL)
    {
        if (pozicia == 1)
        { // pridanie na začiatok
            novy->dalsi = aktualny;
            *zaciatok = novy;
            break;
        }
        if (aktualny->dalsi == NULL)
        { // pridavanie na koniec
            aktualny->dalsi = novy;
            break;
        }
        if (pozicia == temp)
        { // pridavanie do stredu
            predosli->dalsi = novy;
            novy->dalsi = aktualny;
            aktualny = novy;
            break;
        }
        else
        {
            if (temp != 1)
            {
                predosli = predosli->dalsi;
            }
            aktualny = aktualny->dalsi;
            temp++;
        }
    }
}

void z(ZAZNAM **zaciatok)
{
    ZAZNAM *aktualny = *zaciatok;
    ZAZNAM *temp_zaciatok;
    ZAZNAM *predosli = *zaciatok;
    long long int zadane_rodc;
    printf("Zadaj rodne cislo: ");
    scanf("%lld", &zadane_rodc);
    int temp = 1;
    while (aktualny != NULL)
    {

        if (aktualny->rodc == zadane_rodc)
        {
            if (temp == 1)
            { // odstraňovanie prvého
                printf("Prezenter s menom %s bol vymazany.\n", aktualny->meno);
                temp_zaciatok = *zaciatok;
                *zaciatok = (*zaciatok)->dalsi;
                aktualny = aktualny->dalsi;
                predosli = predosli->dalsi;
                free(temp_zaciatok);
                continue;
            }

            if (aktualny->dalsi == NULL)
            { // Odstránenie posledného
                predosli->dalsi = NULL;
                printf("Prezenter s menom %s bol vymazany.\n", aktualny->meno);
                free(aktualny);
                break;
            }

            else
            { // odstraňovanie hociktorého v strede
                predosli->dalsi = aktualny->dalsi;
                printf("Prezenter s menom %s bol vymazany.\n", aktualny->meno);
                aktualny = aktualny->dalsi;
                continue;
            }
        }
        else
        {
            if (temp != 1)
            {
                predosli = aktualny;
            }
            aktualny = aktualny->dalsi;
            temp++;
        }
    }
}

void h(ZAZNAM **zaciatok)
{
    ZAZNAM *aktualny = *zaciatok;
    char buffer[5];
    printf("Zadaj miestnost: ");
    scanf("%s", &buffer);

    int i = 1;
    while (aktualny != NULL)
    {
        if (strcmp(buffer, aktualny->kod) == 0)
        {
            printf("%d.\n", i);
            printf("Prezenter: %s\n", aktualny->meno);
            printf("Rodne cislo: %lld\n", aktualny->rodc);
            printf("Kod prezentacnej miestnosti: %s\n", aktualny->kod);
            printf("Nazov prispevku: %s\n", aktualny->nazov_prispevnku);
            printf("Mena autorov: %s\n", aktualny->mena_autorov);
            printf("Typ prezentovania: %s\n", aktualny->typ);
            printf("Cas prezentovania: %s\n", aktualny->cas);
            printf("Datum: %ld\n", aktualny->datum);
            aktualny = aktualny->dalsi;
            i++;
        }
        else
        {
            aktualny = aktualny->dalsi;
        }
    }
    if (i == 1)
    {
        printf("Pre prezentacnu miestnost %s niesu prezentujuce osoby.\n", buffer);
    }
}

void a(ZAZNAM **zaciatok)
{
    ZAZNAM *aktualny = *zaciatok;
    char zadany_typ[4];
    long long int zadane_rodc;
    printf("Zadaj rodne cislo a novy typ prezentovania: ");
    scanf("%lld %s", &zadane_rodc, &zadany_typ);
    printf("\n");
    while (aktualny != NULL)
    {
        if (aktualny->rodc == zadane_rodc)
        {
            strcpy(aktualny->typ, zadany_typ);
            printf("Prezenter s menom %s bude prezentovat prispevok %s : %s\n", aktualny->meno, aktualny->nazov_prispevnku, aktualny->typ);
            aktualny = aktualny->dalsi;
        }
        else
        {
            aktualny = aktualny->dalsi;
        }
    }
}

void r(ZAZNAM **zaciatok)
{
    ZAZNAM *aktualny = *zaciatok;
    int c1, c2;
    printf("Zadaj 2 cele cisla na prehodenie pozicie: ");
    scanf("%d %d", &c1, &c2);
    printf("\n");
    while (aktualny != NULL)
    {
        if (aktualny->rodc == zadane_rodc)
        {
            strcpy(aktualny->typ, zadany_typ);
            printf("Prezenter s menom %s bude prezentovat prispevok %s : %s\n", aktualny->meno, aktualny->nazov_prispevnku, aktualny->typ);
            aktualny = aktualny->dalsi;
        }
        else
        {
            aktualny = aktualny->dalsi;
        }
    }
}

void k(FILE **subor, ZAZNAM **zaciatok)
{
    if (*zaciatok != NULL)
    { // uvolňovanie prvkov
        ZAZNAM *aktualny = *zaciatok;
        while ((*zaciatok) != NULL)
        {
            aktualny = *zaciatok;
            *zaciatok = (*zaciatok)->dalsi;
            free(aktualny);
        }
    }
    fclose(*subor); // uzatvaranie suboru
}

int main(void)
{
    FILE *subor;
    ZAZNAM *zaciatok = NULL;
    char input;
    while (input != 'k')
    {
        scanf("%c", &input);
        switch (input)
        {
        case 'n':
            n(&subor, &zaciatok);
            break;
        case 'v':
            v(&zaciatok);
            break;

        case 'p':
            p(&subor, &zaciatok);
            break;

        case 'z':
            z(&zaciatok);
            break;

        case 'h':
            h(&zaciatok);
            break;

        case 'a':
            a(&zaciatok);
            break;
        case 'r':
            r(&zaciatok);
            break;

        case 'k':
            k(&subor, &zaciatok);
            ZAZNAM *zaciatok = NULL;
            FILE *subor = NULL;
        }
    }
}