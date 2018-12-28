#include "main.h"


/* Vstupni bod aplikace */
int main(int argc, char *argv[]) {
    int rtn_code = 0;
    app_context *context;
    int i = 0;

    /* DEBUG */
    if(DEBUG) {
        for (i = 0; i < argc; i++) {
            printf("%d: %s\n", i, argv[i]);
        }
    }

    /* Vytvoreni aplikacniho kontextu */
    context = create_app_context(argc, argv);

    /* debug vypis app_context */
    if(DEBUG) {
        print_app_context(context);
    }

    /* Otestovani validity vytvoreni struktury app_context */
    if(context == NULL)
    {
        // Pamet neni alokovana, tudiz nemusi byt uvolnovana
        return -1;
    }

    /* Overeni, zda pri vytvareni app_context nastala chyba */
    if(context->error_code < 0)
    {
        /* Kopirovani chyboveho kodu kvuli naslednemu uvolneni pameti */
        rtn_code = context->error_code;
        /* Uvolneni alokovane pameti */
        free_app_context(context);
        /* Vraceni chyboveho kodu */
        return rtn_code;
    }

    /* Overeni na nejednoznacnou operaci */
    if((context->input_file == NULL && context->input_text == NULL) || (context->input_file != NULL && context->input_text != NULL))
    {
        /* Uvolneni alokovane pameti */
        free_app_context(context);
        return -4;

    }

    /* Zjisteni rezimu programu */
    if(context->input_file != NULL)
    {
        /* rezim uceni */
        rtn_code = learning_mode(context);
    }
    else
    {
        /* rezim zpracovani */
        rtn_code = processing_mode(context);
    }

    /* Uvolneni pameti pred ukoncenim programu  */
    free_app_context(context);

    return rtn_code;
}

/* Spusti cast aplikace v rezimu uceni
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int learning_mode(app_context *context)
{
    FILE *file;
    size_t len = 0;
    ssize_t read;
    FILE * fp;
    char * line = NULL;

    if(DEBUG)
    {
        printf("LEARNING MODE\n");
    }

    if(context == NULL)
    {
        return -1;
    }

    /* Otevreni souboru pro cteni */

    fp = fopen(context->input_file ,"r");
    if (fp == NULL) {
        exit(-5);
    }

    int used = 0;
    int arrlimit = 4;
    char **arr = (char **) malloc(sizeof(char *) * arrlimit);

    char buf[256];
    while( fscanf(fp, "%s", buf) != EOF )
    {
        arr[used] = malloc(sizeof(char) * (strlen(buf)+1));
        strcpy(arr[used], buf);
        used++;

        if(used > arrlimit)
        {
            if(DEEP_DEBUG)
            {
                printf("REALLOC NEEDED\n");
            }
            arrlimit = arrlimit * 2;
            arr = (char **) realloc(arr, (sizeof(char *) * arrlimit));
        }
    }

    /* Debug - vysledek alokace */
    if(DEEP_DEBUG)
    {
        printf("ARR (used = %d, arr_limit = %d)\n", used, arrlimit);
    }

    /* Pokus kazdy s kazdym */
    int a = 0;
    int b = 0;

    for(a = 0; a < used; a++)
    {
        for(b = 0; b < used; b++)
        {
            printf("[%dx%d]> %s x %s\n", a, b, arr[a], arr[b]);
        }
    }


    /* Uvolneni pameti */
    int t = 0;
    for(t = 0; t <= arrlimit; t++)
    {
        free(arr[t]);
    }
    free(arr);

    /* Uzavreni souboru */
    fclose(fp);

    return 0;
}

/* Spusti cast aplikace v rezimu zpracovani
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int processing_mode(app_context *context)
{
    if(DEBUG)
    {
        printf("PROCESSING MODE\n");
    }
    return 0;
}