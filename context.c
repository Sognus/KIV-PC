#include "context.h"

/* Pokusi se otevrit soubor ke cteni
 *
 * Vrati 1 pokud soubor lze otevrit
 * Vrati 0 pokud soubor nelze otevrit nebo neexistuje
 */
int file_exists(const char *file_name)
{
    FILE *file;
    if ((file = fopen(file_name, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
/* Overi, zda vstup prefix je prefixem retezce string
 *
 * Vrati 1 pokud je vstup prefix prefixem.
 * Vrati 0 pokud vstup prefix neni prefixem
 *
 */
int string_starts_with(const char *prefix, const char *string)
{
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

/* Detekuje zda pri pouziti funkce strtol nastala chyba
 *
 * Vrati 0 pokud zadna chyba nebyla detekovana
 * Vrati 1 pokud chyba byla detekovana
 */
int strtol_error_detect(char *nptr, char **endptr, long number)
{
    int err = 0;

    /* test return to number and errno values */
    if (nptr == *endptr-1) {
        if(DEEP_DEBUG) {
            printf(" number : %lu  invalid  (no digits found, 0 returned)\n", number);
        }
        err = 1;
    }
    else if (errno == ERANGE && number == LONG_MIN) {
        if(DEEP_DEBUG) {
            printf(" number : %lu  invalid  (underflow occurred)\n", number);
        }
        err = 1;
    }
    else if (errno == ERANGE && number == LONG_MAX) {
        if(DEEP_DEBUG) {
            printf(" number : %lu  invalid  (overflow occurred)\n", number);
        }
        err = 1;
    }
    else if (errno == 0 && nptr && !**endptr){
        if(DEEP_DEBUG) {
            printf(" number : %lu    valid  (and represents all characters read)\n", number);
        }
        err = 0;
    }
    else if (errno == 0 && nptr && **endptr != 0)
    {
        if(DEEP_DEBUG) {
            printf(" number : %lu    valid  (but additional characters remain)\n", number);
        }
        err = 1;
    }

    /* Vraceni zda byla nalezena chyba */
    return err;
}
/* Na zaklade vstupu z konzole vytvori kontext pro dalsi fungovani aplikace */
app_context *create_app_context(int argc, char **argv)
{
    /* Deklarace */
    app_context *context = NULL;
    size_t input_len = 0;
    int i = 0;
    long *save_ptr = NULL;
    char *num_ptr = NULL;
    char *err_ptr = NULL;
    int error_detected = 0;

    /* Alokace pameti pro strukturu */
    context = malloc(sizeof(app_context));

    /* Nastaveni starndardniho chyboveho kodu */
    context->error_code = 0;

    /* Overeni velikosti vstupniho pole */
    if(argc < 2)
    {
        /* Minimalni pocet pozadovanych vstupu je 2 */
        printf("Application is missing its required arguments!\n");
        context->error_code = -2;
        return context;
    }

    /* Vlozeni dat do struktury */
    context->program = argv[APP_CONTEXT_PROGRAM_INDEX];

    /* Detekce - text nebo soubor */
    if(file_exists(argv[APP_CONTEXT_INPUT_INDEX]))
    {
        context->input_file = argv[APP_CONTEXT_INPUT_INDEX];
        context->input_text = NULL;
    }
    else
    {
        context->input_file = NULL;
        input_len = strlen(argv[APP_CONTEXT_INPUT_INDEX]);
        /* Je-li textovy vstup viceslovny - useknout prvni a posledni znak */
        if(argv[APP_CONTEXT_INPUT_INDEX][0] == '"' && argv[APP_CONTEXT_INPUT_INDEX][input_len-1] == '"')
        {
            /* VICESLOVNY VSTUP */

            /* Pripraveni pameti pro kopirovani retezce */
            context->input_text = malloc(input_len+1-2);
            /* Kopirovani retezce do struktury pri vynechani prvniho znaku */
            stpcpy(context->input_text, &(argv[APP_CONTEXT_INPUT_INDEX][1]));
            /* Useknuti posledniho znaku vstupniho retezce */
            context->input_text[input_len-1] = '\0';
        }
        else
        {
            /* JEDNOSLOVNY VSTUP */

            /* Pripraveni pameti pro kopirovani retezce */
            context->input_text = malloc(input_len+1);
            /* Kopirovani retezce do struktury */
            stpcpy(context->input_text, argv[APP_CONTEXT_INPUT_INDEX]);
            context->input_text[input_len] = '\0';
        }

    }

    /* Nastaveni standardnich hodnot stem */
    context->min_stem_length = 0;
    context->min_stem_freq = 0;

    /* Overeni zbylych vstupu pro hodnoty stem */
    for(i = APP_CONTEXT_OTHERS_START_INDEX; i < argc; i++)
    {
        save_ptr = NULL;
        num_ptr = NULL;
        err_ptr = NULL;
        errno = 0;
        error_detected = 0;

        /* Nastaveni ukazatele kam ulozit vstup pro -msl= */
        if(string_starts_with("-msl=", argv[i]) == 1)
        {
            save_ptr = &context->min_stem_length;
        }

        /* Nastaveni ukazatele kam ulozit vstup pro -msf= */
        if(string_starts_with("-msf=", argv[i]) == 1)
        {
            save_ptr = &context->min_stem_freq;
        }

        /* Neni-li ukazatel NULL, uloz hodnotu */
        if(save_ptr != NULL)
        {
            num_ptr = strchr(argv[i], '=') + 1;
            *save_ptr = strtol(num_ptr, &err_ptr, APP_CONTEXT_INT_BASE);

            error_detected = strtol_error_detect(num_ptr, &err_ptr, *save_ptr);
            if(error_detected == 1)
            {
                context->error_code = -3;
            }
        }
    }

    /* Navrat ukazatele na strukturu */
    return context;
}

/* Vypise textovou reprezentaci struktury app_context na vystup STDOUT */
void print_app_context(app_context *context)
{
    /* Overeni ukazatele */
    if(context == NULL)
    {
        printf("APP_CONTEXT JE NULL!\n");
        return;
    }

    printf("<APP_CONTEXT>\n");
    printf("PROGRAM: %s\n", context->program);
    printf("FILE: %s\n", context->input_file);
    printf("TEXT: %s\n", context->input_text);
    printf("MIN STEM LENGTH: %ld\n", context->min_stem_length);
    printf("MIN STEM FREQ: %ld\n", context->min_stem_freq);
    printf("ERROR CODE: %d\n", context->error_code);
    printf("</APP_CONTEXT>\n");
}

/* Uvolni pamet alokovanou pro strukturu app_context */
void free_app_context(app_context *context)
{
    if(context != NULL)
    {
        free(context->input_text);
        free(context);
    }
}