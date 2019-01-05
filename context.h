#ifndef KIV_PC_CONTEXT_H
#define KIV_PC_CONTEXT_H

#define APP_CONTEXT_PROGRAM_INDEX 0
#define APP_CONTEXT_INPUT_INDEX 1
#define APP_CONTEXT_OTHERS_START_INDEX 2

#define APP_CONTEXT_INT_BASE 10

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "config.h"


/* Struktura pro kontext aplikace */
typedef struct app_context
{
    /* Cesta k aktualne spustenemu programu */
    char *program;
    /* Detekovany vstupni soubor */
    char *input_file;
    /* Detekovany vstupni text */
    char *input_text;
    /* Minimum Stem length */
    long min_stem_length;
    /* Minimum stem freqv */
    long min_stem_freq;
    /* Chybovy kod */
    int error_code;
} app_context;

/* Na zaklade vstupu z konzole vytvori kontext pro dalsi fungovani aplikace */
app_context *create_app_context(int argc, char **argv);

/* Vypise textovou reprezentaci struktury app_context na vystup STDOUT */
void print_app_context(app_context *context);

/* Overi, zda vstup prefix je prefixem retezce string
 *
 * Vrati 1 pokud je vstup prefix prefixem.
 * Vrati 0 pokud vstup prefix neni prefixem
 *
 */
int string_starts_with(const char *prefix, const char *string);

/* Detekuje zda pri pouziti funkce strtol nastala chyba
*
* Vrati 0 pokud zadna chyba nebyla detekovana
* Vrati 1 pokud chyba byla detekovana
*/
int strtol_error_detect(char *nptr, char **endptr, long number);

/* Uvolni pamet alokovanou pro strukturu app_context */
void free_app_context(app_context *context);

/* Pokusi se otevrit soubor ke cteni
 *
 * Vrati 1 pokud soubor lze otevrit
 * Vrati 0 pokud soubor nelze otevrit nebo neexistuje
 */
int file_exists(const char *file_name);

#endif //KIV_PC_CONTEXT_H
