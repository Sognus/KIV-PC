#ifndef KIV_PC_FILE_HELPER_H
#define KIV_PC_FILE_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "context.h"
#include "trie.h"
#include "string_helper.h"
#include "lcs.h"

/* Projde soubor znak po znaku, v souboru najde slova a ty ulozi do trie
 *
 * Vrati zapornou hodnotu pri chybe
 * Vrati kladnou hodnotu pri uspechu - hodnota reprezentuje nejdelsi nalezene slovo
 *
 */
int file_read_words_to_trie(char *file_name, trie_node *root);

/* Projde soubor znak po znaku, v souboru najde slova a ty ulozi do list
 *
 * Vrati zapornou hodnotu pri chybe
 * Vrati kladnou hodnotu pri uspechu - hodnota reprezentuje nejdelsi nalezene slovo
 *
 */
int file_read_words_to_list(char *file_name, list_node *root);

/* Projde retezec, ziska z nej vsechny slova a ulozi jej do spojoveho seznamu
 *
 *
 * Vrati zaporne cislo pri chybe
 * Vrati kladne cislo reprezentujici nejdelsi nalezene slovo pri uspechu
 *
 */
int string_read_words_to_trie(char *string, trie_node *node);

/* Projde retezec, ziska z nej vsechny slova a ulozi jej do spojoveho seznamu
 *
 *
 * Vrati zaporne cislo pri chybe
 * Vrati kladne cislo reprezentujici nejdelsi nalezene slovo pri uspechu
 *
 */
int string_read_words_to_list(char *string, list_node *node);

/* Precte formatovanou databazi korenu a ulozi ji do TRIE */
int file_read_database_to_trie(char *file_name, trie_node *root, long msf);


#endif //KIV_PC_FILE_HELPER_H
