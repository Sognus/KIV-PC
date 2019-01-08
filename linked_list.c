#include "linked_list.h"

/* Vytvori novy node spojoveho seznamu */
list_node *create_list_node(char *string, int count)
{
    /* Deklarace */
    list_node *node = NULL;

    /* Overeni existence retezce */
    if(string == NULL)
    {
        return NULL;
    }

    if(count < 0)
    {
        /* Nesmyslna hodnota */
        return NULL;
    }

    /* Alokace a inicializace prvku */
    node = calloc(1, sizeof(list_node));
    node->content = calloc(strlen(string)+1, sizeof(char));
    strcpy(node->content, string);
    node->next = NULL;
    node->count = count;

    /* Navraceni vytvoreneho prvku   */
    return node;


}

/* Ze retezce vytvori prvek seznamu a pokusi se o jeho vlozeni do seznamu*/
void insert_list_string(list_node *root,char *string, int count)
{
    /* Deklarace promenne */
    list_node *node = NULL;

    /* Pozn. overeni se neprovadi vzhledem k tomu, ze funkce prakticky
     * jen predava parametry - overeni je provedeno v nasleduji func */
    node = create_list_node(string, count);
    insert_list_node(root,node);
}
/* Vlozi novy node do aktualniho spojoveho seznamu */
void insert_list_node(list_node *root, list_node *item)
{
    /* Deklarace iteracni promenne */
    list_node *crawl = NULL;

    if(root == NULL)
    {
        /* Neni kam vlozit prvek */
        return;
    }

    if(item == NULL)
    {
        /* Neni co vkladat */
        return;
    }

    crawl = root;

    while(crawl->next != NULL)
    {


        /* Zadany klic jiz existuje v listu, preskakuji duplicitni zaznam */
        if(strcmp(item->content, crawl->content) == 0)
        {

            return;
        }
        crawl = crawl->next;
    }
    /* Vlozime odkaz na novy prvek za posledni prvek */
    crawl->next = item;

}

/* Vypise cely linked list */
void print_list(list_node *root)
{
    /* Deklarace iteracni promenne */
    list_node *crawl = NULL;

    if(root == NULL)
    {
        /* List je prazdny nevypisuji nic */
        return;
    }

    crawl = root;

    while(crawl != NULL)
    {

        printf("%s\n", crawl->content);
        crawl = crawl->next;
    }
}

/* Uvolni pamet alokovanou pro cely spojovy seznam */
void free_list(list_node *root)
{
    list_node *crawl = NULL;
    list_node *temp = NULL;

    if(root == NULL)
    {
        /* Neni co uvolnit */
        return;
    }

    crawl = root;

    while(crawl != NULL)
    {
        temp = crawl;
        crawl = crawl->next;
        free(temp->content);
        free(temp);
    }



}
