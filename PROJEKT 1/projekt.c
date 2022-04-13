//  Branislav Mikuška
//  FIIT STU
//  PROJEKT 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define rokc 2021

int friadky(FILE **fr)
{ // FUNKCIA NA ZISŤOVANIE RIADKOV

    int riadky = 1;
    char riadok;
    fseek(*fr, 0, SEEK_SET);
    while ((riadok = getc(*fr)) != EOF)
    {
        if (riadok == '\n')
        {
            riadky++;
        }
    }
    return riadky;
}

int fzaznamy(FILE **fr)
{ // FUNKCIA NA ZISŤOVANIE POČTU ZÁZNAMOV
    if (*fr == NULL)
    {
        printf("nie je otvoreny");
    }
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
        if ((cur_riadok % 9) == 1)
        {
            zaznamy++;
        }
        cur_riadok++;
    }
    return zaznamy;
}

int zenamuz(long long int rodnec)
{ // FUNKCIA na zisťovanie pohlavia pomocou rodného čísla
    int rok;
    int pohlavie;
    rok = (((rodnec - (rodnec % 10000000)) / 10000000) % 10);
    if (rok == 5 || rok == 6)
    {
        pohlavie = 1;
    }
    else
    {
        pohlavie = 0;
    }
    return pohlavie;
}

int fvek(long long int rodnec)
{ // funkcia na zisťovanie veku podľa rodného čísla
    int vek, rok;
    rok = (rodnec - (rodnec % 100000000)) / 100000000;

    if (rok == 0)
    {
        rok = (rodnec - (rodnec % 10000000)) / 10000000;
        vek = rokc - (2000 + rok);
    }
    if (54 > rok > 0)
    {
        rok = (rodnec - (rodnec % 100000000)) / 100000000;
        vek = rokc - (2000 + rok);
    }
    if (rok > 54)
    {
        rok = (rodnec - (rodnec % 100000000)) / 100000000;
        vek = rokc - (1900 + rok);
    }
    return vek;
}

int compare(const void *a, const void *b) // funkcia na qsort
{
    return (*(int *)a - *(int *)b);
}

int compare2(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

void v(FILE **fr)
{

    char c;
    long size;
    int cur_riadok = 1;
    int limit = 202;
    char str50[202];
    char buffer[202];
    int limit_mena = 52;
    char mena[limit_mena];
    int kod_miestnosti;
    long int ldatum;
    long long int llirc;
    *fr = fopen("konferencny_zoznam.txt", "r");
    int riadky = friadky(&(*fr));
    long long int dlzkarodc;
    long int dlzkadatum;
    if (*fr == NULL)
    {
        printf("Neotvoreny subor\n");
    }
    else
    {

        fseek(*fr, 0, SEEK_SET);
        while (cur_riadok <= riadky)
        {
            if ((cur_riadok % 9) == 0)
            {
                fgets(buffer, limit, *fr);
                printf("\n");
            }
            else if ((cur_riadok % 9) == 1)
            {

                fgets(mena, limit_mena, *fr);
                for (int i = 0; i < 52; i++)
                { // overovanie korektosti mena
                    if (i > 49)
                    {
                        printf("Nekorektne zadany vstup: meno");
                        exit(0);
                    }
                    if (mena[i] == '\n')
                    {
                        break;
                    }
                    if ((mena[i] < 'a' && mena[i] > 'z') && (mena[i] < 'A' && mena[i] > 'Z') && mena[i] != ' ')
                    {
                        printf("Nekorektne zadany vstup: menoo");
                        exit(0);
                    }
                }
                printf("Prezenter: %s", mena);
            }
            else if ((cur_riadok % 9) == 2)
            {
                fscanf(*fr, "%lld", &llirc);
                fgets(buffer, 50, *fr);
                dlzkarodc = llirc % 10000000000; // overovanie korektnosti rodného čísla
                if (((llirc % 11) == 0) && (llirc == dlzkarodc) && (dlzkarodc > 2000000))
                {
                    printf("rodne cislo: %lld\n", llirc);
                }
                else
                {
                    printf("Nekorektne zadany vstup: rodne cislo");
                    exit(0);
                }
            }
            else if ((cur_riadok % 9) == 3)
            {

                fgets(buffer, 5, *fr);
                if (buffer[0] >= 'A' && buffer[0] <= 'Z' && buffer[1] >= '0' && buffer[1] <= '9' && buffer[2] >= '0' && buffer[2] <= '9' && buffer[3] == '\n')
                {
                    printf("kod prezentacnej miestnosti: %s", buffer);
                }
                else
                {
                    printf("Zle zadaný kód miestnosti \n");
                    exit(0);
                }
            }
            else if ((cur_riadok % 9) == 4)
            {

                fgets(buffer, 152, *fr);

                printf("nazov prispevku: %s", buffer);
            }
            else if ((cur_riadok % 9) == 5)
            {

                fgets(buffer, 202, *fr);
                printf("mena autorov: %s", buffer);
            }
            else if ((cur_riadok % 9) == 6)
            {
                fgets(buffer, 4, *fr);
                if (buffer[0] == 'P' || buffer[0] == 'U' && buffer[1] == 'D' || buffer[1] == 'P')
                {

                    printf("typ prezentovania: %s", buffer);
                }
                else
                {
                    printf("Zle zadaný typ prezentovania \n");
                    exit(0);
                }
            }
            else if ((cur_riadok % 9) == 7)
            {

                fgets(buffer, limit, *fr);
                printf("cas prezentovania: %s", buffer);
            }
            else if ((cur_riadok % 9) == 8)
            {
                fscanf(*fr, "%ld", &ldatum);
                fgets(buffer, limit, *fr);
                dlzkadatum = ldatum % 100000000; // overenie korektosti datum

                if (dlzkadatum > 9999999 && 100000000 > dlzkadatum && ldatum == dlzkadatum)
                {
                    printf("datum: %ld\n", ldatum);
                }
                else
                {
                    printf("Nekorektne zadany vstup: datum");
                    exit(0);
                }
            }
            cur_riadok++;
        }
    }
}

void o(FILE **fr)
{

    char c;
    long size;
    int cur_riadok = 1;
    int limit = 202;
    int pocet_zaznamov = 0;
    char buffer[202];
    char kod_miestnosti[3];
    char datum[9];
    int p_riadky = friadky(&(*fr));
    int p_zaznamy = fzaznamy(&(*fr));
    int temp = 0;

    char **meno = NULL;
    char **nazov_prispevku = NULL;
    char **typ = NULL;
    int *cas = NULL;
    int *casP = NULL;
    int *casyTotal = NULL;

    meno = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (meno)[i] = (char *)malloc(52);
    }

    nazov_prispevku = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (nazov_prispevku)[i] = (char *)malloc(152);
    }
    typ = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (typ)[i] = (char *)malloc(4);
    }
    cas = (int *)malloc(p_zaznamy * sizeof(void *));
    casP = (int *)malloc(p_zaznamy * sizeof(void *));
    casyTotal = (int *)malloc(p_zaznamy * sizeof(void *));

    int casXX;
    int pocetU = 0;
    int pocetP = 0;
    int cur_zaznam = 0;
    int isCurrentP = 0;
    int rovnakyKod = 0;
    int rovnakyDatum = 0;
    printf("Zadaj datum v tvare rrrrmmdd a číslo miestnosti: ");
    long int datumm;

    scanf("%ld %s", &datumm, &kod_miestnosti);
    itoa(datumm, datum, 10);
    fseek(*fr, 0, SEEK_SET);
    while (cur_riadok <= p_riadky)
    {

        if ((cur_riadok % 9) == 0)
        {
            fgets(buffer, limit, *fr);
        }
        else if ((cur_riadok % 9) == 1)
        {

            fgets(buffer, 52, *fr);
            for (int i = 0; i < 52; ++i)
            {
                if (buffer[i] == '\n')
                {
                    buffer[i] = '\00';
                }
            }

            for (int i = 0; i < 51; i++)
            {
                (meno)[cur_zaznam][i] = buffer[i];
            }
        }
        else if ((cur_riadok % 9) == 2)
        {
            fgets(buffer, 50, *fr);
        }
        else if ((cur_riadok % 9) == 3)
        {
            fgets(buffer, 5, *fr);
            if (buffer[0] == kod_miestnosti[0] && buffer[1] == kod_miestnosti[1] && buffer[2] == kod_miestnosti[2])

            {
                rovnakyKod = 1;
            }
        }
        else if ((cur_riadok % 9) == 4)
        {
            fgets(buffer, 152, *fr);
            for (int i = 0; i < 152; i++)
            {
                if (buffer[i] == '\n')
                {
                    buffer[i] = '\00';
                }
            }

            for (int i = 0; i < 150; i++)
            {
                (nazov_prispevku)[cur_zaznam][i] = buffer[i];
            }
        }
        else if ((cur_riadok % 9) == 5)
        {
            fgets(buffer, 202, *fr);
        }
        else if ((cur_riadok % 9) == 6)
        {
            fgets(buffer, 4, *fr);
            if (buffer[0] == 'U')
            {
                pocetU++;
            }
            if (buffer[0] == 'P')
            {
                isCurrentP = 1;
                pocetP++;
            }
            for (int i = 0; i < 4; i++)
            {
                if (buffer[i] == '\n')
                {
                    buffer[i] = '\00';
                }
            }

            for (int i = 0; i < 3; i++)
            {
                (typ)[cur_zaznam][i] = buffer[i];
            }
        }
        else if ((cur_riadok % 9) == 7)
        {
            fscanf(*fr, "%d", &casXX);
            fgets(buffer, 6, *fr);
            casyTotal[cur_zaznam] = casXX;
            if (isCurrentP == 1)
            {
                casP[pocetP - 1] = casXX;
            }
            if (isCurrentP == 0)
            {
                cas[pocetU - 1] = casXX;
            }
        }
        else if ((cur_riadok % 9) == 8)
        {
            fgets(buffer, 10, *fr);

            if (buffer[0] == datum[0] && buffer[1] == datum[1] && buffer[2] == datum[2] && buffer[3] == datum[3] && buffer[4] == datum[4] && buffer[5] == datum[5] && buffer[6] == datum[6] && buffer[7] == datum[7])
            {
                rovnakyDatum = 1;
            }

            if (rovnakyDatum == 0 || rovnakyKod == 0)
            {
                if (isCurrentP == 1)
                {
                    pocetP--;
                }
                else
                {
                    pocetU--;
                }
                cur_zaznam--;
            }

            isCurrentP = 0;
            rovnakyDatum = 0;
            rovnakyKod = 0;
            cur_zaznam++;
        }

        cur_riadok++;
    }

    qsort(cas, pocetU, sizeof(int), compare); // SORTOVANIE ČASOV
    qsort(casP, pocetP, sizeof(int), compare);

    // VYPIS U
    for (int i = 0; i < pocetU; i++)
    {
        for (int j = 0; j < p_zaznamy; j++)
        {
            if (cas[i] == casyTotal[j])
            {
                printf("%d %s %s\n", cas[i], meno[j], nazov_prispevku[j]);
            }
        }
    }
    printf("\n");
    // VYPIS P
    for (int i = 0; i < pocetP; i++)
    {
        for (int j = 0; j < p_zaznamy; j++)
        {
            if (casP[i] == casyTotal[j])
            {
                printf("%d %s %s\n", casP[i], meno[j], nazov_prispevku[j]);
            }
        }
    }
}

void n(FILE **fr, char ***meno, long long int **rodc, char ***kod_miestnosti, char ***nazov_prispevku, char ***mena_autorov, char ***typ, char ***cas, long int **datum)
{

    int p_zaznamy = fzaznamy(&(*fr));
    int p_riadky = friadky(&(*fr));

    *meno = NULL;
    *rodc = NULL;
    *kod_miestnosti = NULL;
    *nazov_prispevku = NULL;
    *mena_autorov = NULL;
    *typ = NULL;
    *cas = NULL;
    *datum = NULL;

    // alokácia 2 a 1 rozmerných polí
    *meno = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*meno)[i] = (char *)malloc(52);
    }

    *rodc = (long long int *)malloc(p_zaznamy * sizeof(long long int));

    *kod_miestnosti = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*kod_miestnosti)[i] = (char *)malloc(4);
    }
    *nazov_prispevku = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*nazov_prispevku)[i] = (char *)malloc(152);
    }
    *mena_autorov = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*mena_autorov)[i] = (char *)malloc(202);
    }
    *typ = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*typ)[i] = (char *)malloc(4);
    }
    *cas = (char **)malloc(p_zaznamy * sizeof(void *));
    for (int i = 0; i < (p_zaznamy); i++)
    {
        (*cas)[i] = (char *)malloc(6);
    }

    *datum = (long int *)malloc(p_zaznamy * sizeof(long int));

    int limit = 202;
    char str50[202];
    int cur_riadok = 1;
    int diag = 0;
    int cur_zaznam = 0;
    long long int rodcx;
    double vysledokx;
    long int datumx;

    fseek(*fr, 0, SEEK_SET);
    while (cur_riadok <= p_riadky)
    {
        if ((cur_riadok % 9) == 0)
        {
            fgets(str50, limit, *fr);
        }
        else if ((cur_riadok % 9) == 1)
        {
            fgets(str50, 52, *fr);
            for (int i = 0; i < 52; ++i)
            {
                // VYMAZANIE ENTERU A NAHRADENIM NULL CHARAKTERU
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 51; i++)
            {
                (*meno)[cur_zaznam][i] = str50[i];
            }
        }
        else if ((cur_riadok % 9) == 2)
        {
            fscanf(*fr, "%lld", &rodcx);
            fgets(str50, 50, *fr);
            (*rodc)[cur_zaznam] = rodcx;
        }
        else if ((cur_riadok % 9) == 3)
        {
            fgets(str50, 5, *fr);
            for (int i = 0; i < 4; i++)
            {
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 4; i++)
            {
                (*kod_miestnosti)[cur_zaznam][i] = str50[i];
            }
        }
        else if ((cur_riadok % 9) == 4)
        {
            fgets(str50, 152, *fr);
            for (int i = 0; i < 152; i++)
            {
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 150; i++)
            {
                (*nazov_prispevku)[cur_zaznam][i] = str50[i];
            }
        }
        else if ((cur_riadok % 9) == 5)
        {
            fgets(str50, 202, *fr);
            for (int i = 0; i < 202; i++)
            {
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 201; i++)
            {
                (*mena_autorov)[cur_zaznam][i] = str50[i];
            }
        }
        else if ((cur_riadok % 9) == 6)
        {
            fgets(str50, 4, *fr);
            for (int i = 0; i < 4; i++)
            {
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 3; i++)
            {
                (*typ)[cur_zaznam][i] = str50[i];
            }
        }

        else if ((cur_riadok % 9) == 7)
        {
            fgets(str50, limit, *fr);
            for (int i = 0; i < 6; i++)
            {
                if (str50[i] == '\n')
                {
                    str50[i] = '\00';
                }
            }

            for (int i = 0; i < 5; i++)
            {
                (*cas)[cur_zaznam][i] = str50[i];
            }
        }
        else if ((cur_riadok % 9) == 8)
        {
            fscanf(*fr, "%ld", &datumx);
            fgets(str50, 10, *fr);
            (*datum)[cur_zaznam] = datumx;
            cur_zaznam++;
        }
        cur_riadok++;
    }
}

void s(FILE **fr, long int **datum, char ***typ_prezentovania, char ***meno, char ***cas, char ***nazov_prispevku)
{

    if ((*datum == NULL) && (*typ_prezentovania == NULL))
    {
        printf("Polia nie su vytvorene\n\n");
    }
    else
    {

        int p_zaznamy = fzaznamy(&(*fr));
        long int datum_input;
        long int dlzkadatum;
        char typ_prezentovania_input[3];
        printf("Zadaj datum v tvare rrrrmmdd a typ prezentovania (vo formáte {PD, UD, PP, UP}): ");
        scanf("%ld %s", &datum_input, &typ_prezentovania_input);
        dlzkadatum = datum_input % 100000000;

        while (1)
        {
            if (((datum_input == dlzkadatum)))
            { // korektnosť zadaného dátumu
                break;
            }
            else
            {
                printf("\nZle zadany datum\n");
                printf("Zadaj datum v tvare rrrrmmdd a typ prezentovania (vo formáte {PD, UD, PP, UP}): ");
                scanf("%ld %s", &datum_input, &typ_prezentovania_input);
                dlzkadatum = datum_input % 100000000;
            }
        }

        for (int i = 0; i < p_zaznamy; i++)
        {
            if (datum_input == (*datum)[i] && strcmp(typ_prezentovania_input, (*typ_prezentovania)[i]) == 0)
            {
                printf("%s %s %s\n", (*cas)[i], (*meno)[i], (*nazov_prispevku)[i]);
            }
        }
    }
}

void h(FILE **fr, long long int **rodc, char ***kod_miestnosti, char ***typ_prezentovania)
{
    if ((*rodc == NULL) && (*kod_miestnosti == NULL) && (*typ_prezentovania == NULL))
    {
        printf("Polia nie su vytvorene\n");
    }
    else
    {
        // ALOKÁCIA POLÍ
        int p_zaznamy = fzaznamy(&(*fr));
        int *muzi0_9 = calloc(4, sizeof(long long int));
        int *muzi10_19 = calloc(4, sizeof(long long int));
        int *muzi20_29 = calloc(4, sizeof(long long int));
        int *muzi30_39 = calloc(4, sizeof(long long int));
        int *muzi40_49 = calloc(4, sizeof(long long int));
        int *muzi50_59 = calloc(4, sizeof(long long int));
        int *muzi60_69 = calloc(4, sizeof(long long int));
        int *muzi70_79 = calloc(4, sizeof(long long int));
        int *muzi80_89 = calloc(4, sizeof(long long int));
        int *muzi90_99 = calloc(4, sizeof(long long int));
        int *zeny0_9 = calloc(4, sizeof(long long int));
        int *zeny10_19 = calloc(4, sizeof(long long int));
        int *zeny20_29 = calloc(4, sizeof(long long int));
        int *zeny30_39 = calloc(4, sizeof(long long int));
        int *zeny40_49 = calloc(4, sizeof(long long int));
        int *zeny50_59 = calloc(4, sizeof(long long int));
        int *zeny60_69 = calloc(4, sizeof(long long int));
        int *zeny70_79 = calloc(4, sizeof(long long int));
        int *zeny80_89 = calloc(4, sizeof(long long int));
        int *zeny90_99 = calloc(4, sizeof(long long int));

        for (int i = 0; i < p_zaznamy; i++)
        {
            int rodne_cislo = (*rodc)[i];
            int vek = fvek((*rodc)[i]);
            if (zenamuz(rodne_cislo) == 0)
            { // CHLAP
                if (strcmp((*typ_prezentovania)[i], "UP") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        muzi0_9[0]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        muzi10_19[0]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        muzi20_29[0]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        muzi30_39[0]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        muzi40_49[0]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        muzi50_59[0]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        muzi60_69[0]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        muzi70_79[0]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        muzi80_89[0]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        muzi90_99[0]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "UD") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        muzi0_9[1]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        muzi10_19[1]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        muzi20_29[1]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        muzi30_39[1]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        muzi40_49[1]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        muzi50_59[1]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        muzi60_69[1]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        muzi70_79[1]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        muzi80_89[1]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        muzi90_99[1]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "PP") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        muzi0_9[2]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        muzi10_19[2]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        muzi20_29[2]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        muzi30_39[2]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        muzi40_49[2]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        muzi50_59[2]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        muzi60_69[2]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        muzi70_79[2]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        muzi80_89[2]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        muzi90_99[2]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "PD") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        muzi0_9[3]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        muzi10_19[3]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        muzi20_29[3]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        muzi30_39[3]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        muzi40_49[3]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        muzi50_59[3]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        muzi60_69[3]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        muzi70_79[3]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        muzi80_89[3]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        muzi90_99[3]++;
                    }
                }
            }
            else if (zenamuz(rodne_cislo) == 1)
            { // ZENA
                if (strcmp((*typ_prezentovania)[i], "UP") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        zeny0_9[0]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        zeny10_19[0]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        zeny20_29[0]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        zeny30_39[0]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        zeny40_49[0]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        zeny50_59[0]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        zeny60_69[0]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        zeny70_79[0]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        zeny80_89[0]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        zeny90_99[0]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "UD") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        zeny0_9[1]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        zeny10_19[1]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        zeny20_29[1]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        zeny30_39[1]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        zeny40_49[1]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        zeny50_59[1]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        zeny60_69[1]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        zeny70_79[1]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        zeny80_89[1]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        zeny90_99[1]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "PP") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        zeny0_9[2]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        zeny10_19[2]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        zeny20_29[2]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        zeny30_39[2]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        zeny40_49[2]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        zeny50_59[2]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        zeny60_69[2]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        zeny70_79[2]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        zeny80_89[2]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        zeny90_99[2]++;
                    }
                }
                else if (strcmp((*typ_prezentovania)[i], "PD") == 0)
                {
                    if (vek >= 0 && vek < 10)
                    {
                        zeny0_9[3]++;
                    }
                    else if (vek >= 10 && vek < 20)
                    {
                        zeny10_19[3]++;
                    }
                    else if (vek >= 20 && vek < 30)
                    {
                        zeny20_29[3]++;
                    }
                    else if (vek >= 30 && vek < 40)
                    {
                        zeny30_39[3]++;
                    }
                    else if (vek >= 40 && vek < 50)
                    {
                        zeny40_49[3]++;
                    }
                    else if (vek >= 50 && vek < 60)
                    {
                        zeny50_59[3]++;
                    }
                    else if (vek >= 60 && vek < 70)
                    {
                        zeny60_69[3]++;
                    }
                    else if (vek >= 70 && vek < 80)
                    {
                        zeny70_79[3]++;
                    }
                    else if (vek >= 80 && vek < 90)
                    {
                        zeny80_89[3]++;
                    }
                    else if (vek >= 90 && vek < 100)
                    {
                        zeny90_99[3]++;
                    }
                }
            }
        }
        printf("Muzi UP UD PP PD\n0r -9r: %d %d %d %d\n 10r - 19r: %d %d %d %d\n 20r - 29r: %d %d %d %d\n 30r - 39r: %d %d %d %d\n 40r - 49r: %d %d %d %d\n 50r - 59r: %d %d %d %d\n 60r - 69r: %d %d %d %d\n 70r - 79r: %d %d %d %d\n 80r - 89r: %d %d %d %d\n 90r - 99r: %d %d %d %d\n\n Zeny UP UD PP PD\n 0r - 9r: %d %d %d %d\n 10r - 19r: %d %d %d %d\n 20r - 29r: %d %d %d %d\n 30r - 39r: %d %d %d %d\n 40r - 49r: %d %d %d %d\n 50r - 59r: %d %d %d %d\n 60r - 69r: %d %d %d %d\n 70r - 79r: %d %d %d %d\n 80r - 89r: %d %d %d %d\n 90r - 99r: %d %d %d %d\n ",

               muzi0_9[0],
               muzi0_9[1], muzi0_9[2], muzi0_9[3],
               muzi10_19[0], muzi10_19[1], muzi10_19[2], muzi10_19[3],
               muzi20_29[0], muzi20_29[1], muzi20_29[2], muzi20_29[3],
               muzi30_39[0], muzi30_39[1], muzi30_39[2], muzi30_39[3],
               muzi40_49[0], muzi40_49[1], muzi40_49[2], muzi40_49[3],
               muzi50_59[0], muzi50_59[1], muzi50_59[2], muzi50_59[3],
               muzi60_69[0], muzi60_69[1], muzi60_69[2], muzi60_69[3],
               muzi70_79[0], muzi70_79[1], muzi70_79[2], muzi70_79[3],
               muzi80_89[0], muzi80_89[1], muzi80_89[2], muzi80_89[3],
               muzi90_99[0], muzi90_99[1], muzi90_99[2], muzi90_99[3],
               zeny0_9[0], zeny0_9[1], zeny0_9[2], zeny0_9[3],
               zeny10_19[0], zeny10_19[1], zeny10_19[2], zeny10_19[3],
               zeny20_29[0], zeny20_29[1], zeny20_29[2], zeny20_29[3],
               zeny30_39[0], zeny30_39[1], zeny30_39[2], zeny30_39[3],
               zeny40_49[0], zeny40_49[1], zeny40_49[2], zeny40_49[3],
               zeny50_59[0], zeny50_59[1], zeny50_59[2], zeny50_59[3],
               zeny60_69[0], zeny60_69[1], zeny60_69[2], zeny60_69[3],
               zeny70_79[0], zeny70_79[1], zeny70_79[2], zeny70_79[3],
               zeny80_89[0], zeny80_89[1], zeny80_89[2], zeny80_89[3],
               zeny90_99[0], zeny90_99[1], zeny90_99[2], zeny90_99[3]);
    }
}

void p(FILE **fr, char ***meno, long long int **rodc, char ***kod_miestnosti, char ***nazov_prispevku, char ***mena_autorov, char ***typ, char ***cas, long int **datum)
{
    if ((*rodc == NULL) && (*kod_miestnosti == NULL) && (*cas == NULL) && (*mena_autorov == NULL) && (*typ == NULL))
    {
        printf("Polia nie su vytvorene\n");
    }
    else
    {
        int p_zaznamy = fzaznamy(&(*fr));
        long long int zadanerodc;
        long int zadanydatum;
        char kod_miestnosti_input[4];
        char typ_prezentovania_input[3];
        char cas_input[5];
        int vyhovujuce_indexy[p_zaznamy];
        int poradove_cislo_input;
        int poradove_cisla = 1;
        int vyhovujuce = 0;
        while (1)
        {
            if (vyhovujuce == 1)
            {
                break;
            }
            else
            {
                printf("Zadaj rodne cislo: ");
                scanf("%lld", &zadanerodc);

                for (int i = 0; i < p_zaznamy; i++)
                {

                    if ((*rodc)[i] == zadanerodc)
                    {
                        vyhovujuce_indexy[poradove_cisla - 1] = i;
                        printf("%d %s %s\n", poradove_cisla, (*meno)[i], (*nazov_prispevku)[i]);
                        poradove_cisla++;
                        vyhovujuce = 1;
                    }
                }
            }
        }

        printf("\nZadaj poradove cislo, kod miestnosti, typ prezentoavnia, cas prezentovania, datum: ");
        scanf("%d %s %s %s %ld", &poradove_cislo_input, &kod_miestnosti_input, &typ_prezentovania_input, &cas_input, &zadanydatum);

        int dlzkadatum = zadanydatum % 100000000;

        while (1)
        {
            // ZAISTENIE POREKTNOSTI
            if ((poradove_cislo_input <= poradove_cisla && poradove_cislo_input > 0) && (zadanydatum == dlzkadatum) && (kod_miestnosti_input[0] >= 'A' && kod_miestnosti_input[0] <= 'Z' && kod_miestnosti_input[1] >= '0' && kod_miestnosti_input[1] <= '9' && kod_miestnosti_input[2] >= '0' && kod_miestnosti_input[2] <= '9') || strcmp(typ_prezentovania_input, "UP") == 0 || strcmp(typ_prezentovania_input, "UD") == 0 || strcmp(typ_prezentovania_input, "PP") == 0 || strcmp(typ_prezentovania_input, "PD") == 0 && (cas_input[0] >= '0' && cas_input[0] <= '9' && cas_input[1] >= '0' && cas_input[1] <= '9' && cas_input[2] >= '0' && cas_input[2] <= '9' && cas_input[3] >= '0' && cas_input[3] <= '9'))
            {
                (*kod_miestnosti)[poradove_cislo_input - 1] = kod_miestnosti_input;
                (*typ)[poradove_cislo_input - 1] = typ_prezentovania_input;
                (*cas)[poradove_cislo_input - 1] = cas_input;
                (*datum)[poradove_cislo_input - 1] = zadanydatum;
                break;
            }
            else
            {
                printf("\nZadane udaje nie su korektne, zadaj novy retazec: ");
                scanf("%d %s %s %s %ld", &poradove_cislo_input, &kod_miestnosti_input, &typ_prezentovania_input, &cas_input, &zadanydatum);
                dlzkadatum = zadanydatum % 100000000;
            }
        }
        fclose(*fr);
        // UZATVORENIE SÚBORU NA ČÍTANIE A OTVORENIE NA ZÁPIS
        FILE *asd = fopen("konferencny_zoznam.txt", "w");
        fseek(*fr, 0, SEEK_SET);
        for (int i = 0; i < p_zaznamy; i++)
        {
            fprintf(asd, "%s\n", (*meno)[i]);
            fprintf(asd, "%lld\n", (*rodc)[i]);
            fprintf(asd, "%s\n", (*kod_miestnosti)[i]);
            fprintf(asd, "%s\n", (*nazov_prispevku)[i]);
            fprintf(asd, "%s\n", (*mena_autorov)[i]);
            fprintf(asd, "%s\n", (*typ)[i]);
            fprintf(asd, "%s\n", (*cas)[i]);
            fprintf(asd, "%ld\n", (*datum)[i]);
            if (i < (p_zaznamy - 1))
            {
                fprintf(asd, "\n");
            }
        }
        fclose(asd);

        *fr = fopen("konferencny_zoznam.txt", "r");
        printf("Aktualizacia udajov prebehla v poriadku.\n");
    }
}

void z(FILE **fr, char ***meno, long long int **rodc, char ***kod_miestnosti, char ***nazov_prispevku, char ***mena_autorov, char ***typ, char ***cas, long int **datum)
{
    if ((*rodc == NULL) && (*kod_miestnosti == NULL) && (*cas == NULL) && (*mena_autorov == NULL) && (*typ == NULL))
    {
        printf("Polia nie su vytvorene\n");
    }
    else
    {
        int p_zaznamy = fzaznamy(&(*fr));
        int vymazane_zaznamy = 0;
        long long int zadanerodc;
        printf("Zadaj rodne cislo: ");
        scanf("%lld", &zadanerodc);
        for (int i = 0; i < p_zaznamy; i++)
        { // MAZANIE ZÁZNAMOV = NAHRADENIE 0
            if ((*rodc)[i] == zadanerodc)
            {
                (*meno)[i] = "0";
                (*rodc)[i] = 0;
                (*kod_miestnosti)[i] = "0";
                (*typ)[i] = "0";
                (*cas)[i] = "0";
                (*datum)[i] = 0;
                (*mena_autorov)[i] = "0";
                (*nazov_prispevku)[i] = "0";
                vymazane_zaznamy++;
            }
        }
        printf("Vymazalo sa: %d zaznamov !", vymazane_zaznamy);
    }
}

int main(void)
{
    FILE *subor;
    char input;
    int xyz = 0;

    char **meno = NULL;
    long long int *rodc = NULL;
    char **kod_miestnosti = NULL;
    char **nazov_prispevku = NULL;
    char **mena_autorov = NULL;
    char **typ = NULL;
    char **cas = NULL;
    long int *datum = NULL;

    while (input != 'k')
    {
        scanf("%c", &input);
        switch (input)
        {
        case 'v':
            v(&subor);
            xyz++;
            break;
        case 'o':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                o(&subor);
                break;
            }
        case 'n':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                n(&subor, &meno, &rodc, &kod_miestnosti, &nazov_prispevku, &mena_autorov, &typ, &cas, &datum);
                break;
            }
        case 's':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                s(&subor, &datum, &typ, &meno, &cas, &nazov_prispevku);
                break;
            }
        case 'h':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                h(&subor, &rodc, &kod_miestnosti, &typ);
                break;
            }
        case 'p':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                p(&subor, &meno, &rodc, &kod_miestnosti, &nazov_prispevku, &mena_autorov, &typ, &cas, &datum);
                break;
            }
        case 'z':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                z(&subor, &meno, &rodc, &kod_miestnosti, &nazov_prispevku, &mena_autorov, &typ, &cas, &datum);
                break;
            }
        case 'k':
            if (xyz == 0)
            {
                printf("Soubor nebol otvoreny\n");
                break;
            }
            else
            {
                // DEALOKÁCIA PAMÄTE
                int p_zaznamy = fzaznamy(&subor);
                if (rodc != NULL && datum != NULL && meno != NULL && kod_miestnosti != NULL && typ != NULL && cas != NULL && nazov_prispevku != NULL && mena_autorov != NULL)
                {
                    free(rodc);
                    free(datum);
                    for (int i = 0; i < p_zaznamy; i++)
                    { // uvolňovanie 2d polí
                        free((meno)[i]);
                        free((kod_miestnosti)[i]);
                        free((typ)[i]);
                        free((cas)[i]);
                        free((mena_autorov)[i]);
                        free((nazov_prispevku)[i]);
                    }
                    free((meno));
                    free((kod_miestnosti));
                    free(typ);
                    free(cas);
                    free(mena_autorov);
                    free(nazov_prispevku);
                }
                fclose(subor);
                exit(0);
            }
        }
        printf("\n");
    }
}