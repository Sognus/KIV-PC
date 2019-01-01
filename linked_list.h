#ifndef KIV_PC_LINKED_LIST_H
#define KIV_PC_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Datova struktura - jeden z prvku spojoveho seznamu */
typedef struct list_node
{
    char *content;
    int count;
    struct list_node *next;

} list_node;

/* Vytvori novy node spojoveho seznamu */
list_node *create_list_node(char *string, int count);

/* Vlozi novy node do aktualniho spojoveho seznamu */
void insert_list_node(list_node *root, list_node *item);

/* Ze retezce vytvori prvek seznamu a pokusi se o jeho vlozeni do seznamu*/
void insert_list_string(list_node *root,char *string, int count);

/* Vypise cely linked list */
void print_list(list_node *root);

/* Uvolni pamet alokovanou pro cely spojovy seznam */
void free_list(list_node *root);




#endif //KIV_PC_LINKED_LIST_H
