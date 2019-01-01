#ifndef KIV_PC_TRIE_H
#define KIV_PC_TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "lcs.h"
#include "string_helper.h"
#include "linked_list.h"

/* Pocet symbolu, ktere ukladame do abecedy (8bit - 0 az 255) */
#define ALPHABET_SIZE 256
/* Prevod znaku na nezapornou ciselnou hodnotu 0-255 */
#define CHAR_TO_INDEX(c) ((unsigned char)c)

/* Struktura pro jeden prvek trie */
typedef struct trie_node
{
    /* odkaz na ostatni prvky trie */
    struct trie_node *children[ALPHABET_SIZE];
    /* pocet vyskytu daneho symbolu */
    int count;
    /* Je soucasny prvek trie koncem slova */
    int end_of_word;
} trie_node;

/* Vytvori novy prvek  */
trie_node *create_trie_node();

/* Vlozi retezec do trie v pripade ze neexistuje
 *
 * V pripade ze retezec v trii existuje, je pocitadlo
 * vyskytu zvyseno o jedna
 *
 * */
void trie_insert(trie_node *root, char *key);

/* Vrati jestli v dane trii existuje (1) nebo neexistuje (0) dane slovo */
int trie_search(trie_node *root, char *key);

/* Vraci jestli je dany node takovy, ze v nem konci nejake slovo */
int trie_is_leaf_node(trie_node *node);

/* Funkce, ktera vypise obsah trie */
void trie_display(trie_node *root, char *str, int level);

/* Vypise nenulovy obsah vnitrniho pole trie_node */
void trie_print_node(trie_node *node);

/* Rekurzivne uvolni pamet struktury trie  */
void trie_free(trie_node *root);

/* DEPRECATED: Pomocna funkce pro trie_manipulate  */
void trie_manipulate_second(trie_node *save_root,trie_node *root, char *current_word, char *str, int level);

/* DEPRECATED: Funkce, ktera vypise obsah trie */
void trie_manipulate_first(trie_node *save_root, trie_node *root, trie_node *current_node, char *str, int level, int longest_word);

/* Funkce, ktera vypise obsah trie do spojoveho seznamu */
void trie_to_list(list_node *list_root,trie_node *root, char *str, int level);

#endif //KIV_PC_TRIE_H
