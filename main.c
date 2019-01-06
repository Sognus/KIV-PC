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