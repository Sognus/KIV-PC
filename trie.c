#include "trie.h"



/* Vytvori novy prvek  */
trie_node *create_trie_node()
{
    /* Deklarace ukazatele na node */
    trie_node *node = NULL;
    /* Alokace pameti pro node */
    node = (trie_node *)malloc(sizeof(trie_node));

    /* Proved akci pouze pokud ukazatel node neni NULL (tj. adresa je vetsi jak 0) */
    if (node)
    {
        /* Deklarace pro iteracni promennou */
        int i;
        /* Standardne nastavit ze node neni koncem slova  */
        node->end_of_word = 0;
        /* Inicializace vsech potomku aktualni node na NULL ukazatel */
        for (i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
        node->count = 0;
    }
    /* Navrat vytvorene struktury nebo NULL ukazatele */
    return node;
}

/* Vlozi retezec do trie v pripade ze neexistuje
 *
 * V pripade ze retezec v trii existuje, je pocitadlo
 * vyskytu zvyseno o jedna
 *
 * */
void trie_insert(trie_node *root, char *key)
{
    /* Deklarace promennych */
    int level = 0;
    long length = 0;
    int index = 0;
    trie_node *pCrawl = NULL;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(root == NULL)
    {
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(key == NULL)
    {
        return;
    }

    /* Zjisteni delky vstupniho klice */
    length = strlen(key);

    /* Delka retezce je prilis mala na vlozeni */
    if(length < 1)
    {
        return;
    }

    /* Pocatecni ukazatel na korenovy node */
    pCrawl = root;

    /* Prochazeni retezce znak po znaku - znak = hloubka trie */
    for (level = 0; level < length; level++)
    {
        /* Zjisteni kam se v aktualnim levelu ulozi znak */
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index]) {
            pCrawl->children[index] = create_trie_node();
        }

        /* Nastav ukazatel aktualne zpracovaneho node na node na dalsim levelu (hloubce) */
        pCrawl = pCrawl->children[index];
    }

    /* Oznaceni posledniho znaku v trii (nejhlubsiho node) jako konec slova */
    pCrawl->count++;
    pCrawl->end_of_word = 1;
}


/* Vraci jestli je dany node takovy, ze v nem konci nejake slovo */
int trie_is_leaf_node(trie_node *node)
{
    return node->end_of_word;
}

/* Rekurzivne uvolni pamet struktury trie  */
void trie_free(trie_node *root)
{
    int x = 0;
    if(root == NULL)
    {
        /* Neni co uvolnovat */
        return;
    }

    for(x = 0; x < ALPHABET_SIZE; x++){
        if(root->children[x] != NULL)
        {
            trie_free(root->children[x]);
        }
    }
    free(root);
}

/* Funkce, ktera vypise obsah trie */
void trie_display(trie_node *root, char *str, int level)
{
    /* Deklarace */
    int i;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(root == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        /*printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");*/
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
    if (trie_is_leaf_node(root))
    {
        str[level] = '\0';
        printf("%s %d\n", str, root->count);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (root->children[i] != NULL)
        {
            str[level] = i;
            trie_display(root->children[i], str, level + 1);
        }
    }
}

/* Funkce, ktera vypise obsah trie do spojoveho seznamu */
void trie_to_list(list_node *list_root,trie_node *root, char *str, int level)
{
    /* Deklarace */
    int i;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(root == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        /*printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");*/
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
    if (trie_is_leaf_node(root))
    {
        str[level] = '\0';
        insert_list_string(list_root, str, root->count);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (root->children[i] != NULL)
        {
            str[level] = i;
            trie_to_list(list_root,root->children[i], str, level + 1);
        }
    }
}

/* Funkce, ktera vypise obsah trie do souboru*/
void trie_to_file(FILE *file,trie_node *root, char *str, int level)
{
    /* Deklarace */
    int i;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(root == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");
        return;
    }

    /* Overeni otevreni souboru */
    if(file == NULL)
    {
        /* Soubor je NULL */
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu do souboru */
    if (trie_is_leaf_node(root))
    {
        str[level] = '\0';
        /* Formatovany vystup do souboru */
        fprintf(file,"%s %d\r\n", str, root->count);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (root->children[i] != NULL)
        {
            str[level] = i;
            trie_to_file(file,root->children[i], str, level + 1);
        }
    }
}

/* V dane strukture Trie najde nejdelsi koren a ulozi jej do promenne output */
void trie_find_longest_stem(trie_node *node, char *word, char *buffer, int level, char *output)
{
    /* Deklarace */
    int i;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(node == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(buffer == NULL)
    {
        /* Nemuzeme hledat NULL */
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
    if (trie_is_leaf_node(node))
    {
        char *result = NULL;
        buffer[level] = '\0';

        /* Ulozeni LCS z puvodnich retezcu do trie */
        longest_common_substring(buffer, word, &result);

        if(result != NULL)
        {
            if(strlen(result) > strlen(output) && strlen(result) == strlen(buffer))
            {
                strcpy(output, buffer);
            }
        }

        free(result);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (node->children[i] != NULL)
        {
            buffer[level] = i;
            trie_find_longest_stem(node->children[i], word, buffer, level + 1, output);
        }
    }
}

