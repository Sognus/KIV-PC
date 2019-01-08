#include "lcs.h"

/* Vytvori nejdelsi spolecny podretezec pro dva vstupni retezce */
unsigned int longest_common_substring(char *str1, char *str2, char **result) {
    unsigned int i = 0;
    unsigned int j= 0;
    unsigned int max = 0;
    size_t m = 0;
    size_t n = 0;
    lcs_entry *head = NULL;
    lcs_entry **lcstab = NULL;

    if(str1 == NULL || str2 == NULL)
    {
        /* Jeden z retezcu je NULL, vysledek bude take NULL  */
        *result = NULL;
        return 0;
    }

    m = strlen(str1);
    n = strlen(str2);

    /* Alokace pameti pro tabulku*/
    lcstab = malloc((m + 1) * sizeof(lcs_entry *));
    for (i = 0; i < m + 1; i++) {
        lcstab[i] = malloc((n + 1) * sizeof(lcs_entry));
    }

    /* Vypocet skore pro kazdy podrezec a vytvoreni cesty v tabulce*/
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                lcstab[i][j].score = 0;
                lcstab[i][j].letter = 0;
                lcstab[i][j].prev = NULL;
            } else if (str1[i - 1] == str2[j - 1]) {
                lcstab[i][j].score = lcstab[i - 1][j - 1].score + 1;
                lcstab[i][j].letter = str1[i - 1];
                lcstab[i][j].prev = &lcstab[i - 1][j - 1];
                if (lcstab[i][j].score > max) {
                    max = lcstab[i][j].score;
                    head = &lcstab[i][j];
                }
            } else {
                lcstab[i][j].score = 0;
                lcstab[i][j].letter = 0;
                lcstab[i][j].prev = NULL;
            }
        }
    }

    /* Alokace pameti pro vysledny retezec */
    *result = calloc((size_t)(max) + 1, sizeof(char));
    (*result)[max] = '\0';

    /* Postup po vytvorene ceste a naplneni vysledku  */
    if(head != NULL)
    {
        for (i = max - 1; head->prev != NULL; i--) {
            (*result)[i] = head->letter;
            head = head->prev;
        }
    }

    /* Uvolneni pameti */
    for (i = 0; i < m + 1; i++) {
        free(lcstab[i]);
    }
    free(lcstab);

    return max;
}

