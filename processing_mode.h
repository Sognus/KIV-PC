#ifndef KIV_PC_PROCESSING_MODE_H
#define KIV_PC_PROCESSING_MODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "context.h"
#include "trie.h"
#include "file_helper.h"

/* Spusti cast aplikace v rezimu zpracovani
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int processing_mode(app_context *context);

#endif //KIV_PC_PROCESSING_MODE_H
