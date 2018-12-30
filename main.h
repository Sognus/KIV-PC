#ifndef KIV_PC_MAIN_H
#define KIV_PC_MAIN_H

/* Standardni knihovny a soucasti */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* Uzivatelske knihovny a soucasti */
#include "config.h"
#include "context.h"
#include "trie.h"

/* Ostatni casti aplikace */
#include "learning_mode.h"


/* Vstupni bod aplikace */
int main(int argc, char *argv[]);


/* Spusti cast aplikace v rezimu zpracovani
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int processing_mode(app_context *context);

#endif //KIV_PC_MAIN_H
