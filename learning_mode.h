#ifndef KIV_PC_LEARNING_MODE_H
#define KIV_PC_LEARNING_MODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "context.h"
#include "trie.h"
#include "string_helper.h"
#include "lcs.h"

#define READ_BUFFER_SIZE (int)64

/* Spusti cast aplikace v rezimu uceni
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int learning_mode(app_context *context);

#endif //KIV_PC_LEARNING_MODE_H
