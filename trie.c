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
        else
        {
            //pCrawl->children[index]->count++;
        }

        /* Nastav ukazatel aktualne zpracovaneho node na node na dalsim levelu (hloubce) */
        pCrawl = pCrawl->children[index];
    }

    /* Oznaceni posledniho znaku v trii (nejhlubsiho node) jako konec slova */
    pCrawl->count++;
    pCrawl->end_of_word = 1;
}

/* Vrati jestli v dane trii existuje (1) nebo neexistuje (0) dane slovo */
int trie_search(trie_node *root, char *key)
{
    /* Deklarace */
    int level;
    size_t length = strlen(key);
    int index;
    trie_node *pCrawl = root;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(root == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        return 0;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(key == NULL)
    {
        /* Nemuzeme hledat NULL */
        return 0;
    }


    /* Prochazeni po levelech (zvysujeme hloubku) */
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        /* V pripade ze neexistuje dalsi znak, navrat nulovou hodnotu = retezec nenalezen */
        if (!pCrawl->children[index]) {
            return 0;
        }

        /* Nastav aktualne pouzivany node na node hloubeji v trii */
        pCrawl = pCrawl->children[index];
    }

    /* Pokud posledni node neni NULL a zaroven je posledni node koncem slova, vrat 1 - v odlisnych pripadech vrat 0 */
    return (pCrawl != NULL && pCrawl->end_of_word);
}

/* Vraci jestli je dany node takovy, ze v nem konci nejake slovo */
int trie_is_leaf_node(trie_node *node)
{
    return node->end_of_word;
}

/* Vypise nenulovy obsah vnitrniho pole trie_node */
void trie_print_node(trie_node *node)
{
    int i;
    int n = 0;
    /* Nedelat nic pokud neni co vypsat */
    if(node == NULL)
    {
        return;
    }

    printf("<TRIE NODE CHILDREN START>\n");
    for(i = 0; i < ALPHABET_SIZE; i++)
    {
        if(node->children[i] != NULL)
        {
            if(n > 0)
            {
                printf("%d# NULL PARTS\n", n);
            }
            printf("%d IS NOT NULL\n", i);
            /* Vyresetovani indexu */
            n = 0;
        }
        else
        {
            /* Dalsi index pole je NULL */
            n++;
        }
    }
    printf("<TRIE NODE CHILDREN END>\n");
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
        printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        if(DEEP_DEBUG)
        {
            printf("NELZE VYPSAT OBSAH TRIE, BUFFER JE NULL\n");
        }
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

/* DEPRECATED: Funkce, ktera vypise obsah trie */
void trie_manipulate_first(trie_node *save_root, trie_node *root, trie_node *current_node, char *str, int level, int longest_word)
{
    /* Deklarace */
    int i = 0;

    /* Overeni vstupu - pokud je ukazatel na node NULL, neudelej nic */
    if(current_node == NULL)
    {
        /* Technicky retezec neni, ale spise se jedna o jinou chybu */
        printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        if(DEEP_DEBUG)
        {
            printf("NELZE VYPSAT OBSAH TRIE, BUFFER JE NULL\n");
        }
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
    if (trie_is_leaf_node(current_node))
    {
        str[level] = '\0';

        int level2 = 0;
        char *str2 = calloc((size_t)(longest_word)+10,sizeof(char));
        trie_manipulate_second(save_root,root, str, str2, level2 );
        free(str2);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (current_node->children[i] != NULL)
        {
            str[level] = i;
            trie_manipulate_first(save_root, root ,current_node->children[i], str, level + 1, longest_word);
        }
    }
}

/* DEPRECATED: Pomocna funkce pro trie_manipulate  */
void trie_manipulate_second(trie_node *save_root ,trie_node *root, char *current_word, char *str, int level)
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

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        if(DEEP_DEBUG)
        {
            printf("NELZE VYPSAT OBSAH TRIE, BUFFER JE NULL\n");
        }
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
    if (trie_is_leaf_node(root))
    {
        str[level] = '\0';
        /* Ulozeni puvodnich  retezcu do trie */
        trie_insert(save_root,current_word);
        trie_insert(save_root, str);

        /* Ulozeni LCS z puvodnich retezcu do trie */
        char *result = NULL;
        longest_common_substring(current_word, str, &result);

        /* Pokud byl nalezen nejaky spolecny podretezec, pridej ho do trie */
        if(strlen(result) > 0) {
            trie_insert(save_root, result);
        }

        /* DEBUG */
        if(DEEP_DEBUG) {
            printf("LCS: %s x %s -> %s\n" , current_word, str, result);
        }

        /* Uvolneni pameti  */
        free(result);
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* Pokud nalezneme nenuloveho potomka, zavolame rekurzivne funkci tree_display */
        if (root->children[i] != NULL)
        {
            str[level] = i;
            trie_manipulate_second(save_root,root->children[i], current_word, str, level + 1);
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
        printf("NELZE VYPSAT OBSAH TRIE, ROOT JE NULL\n");
        return;
    }

    /* Overeni na vstup - pokud je retezec key NULL, neudelej nic */
    if(str == NULL)
    {
        /* Nemuzeme hledat NULL */
        if(DEEP_DEBUG)
        {
            printf("NELZE VYPSAT OBSAH TRIE, BUFFER JE NULL\n");
        }
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
        if(DEEP_DEBUG)
        {
            printf("NELZE VYPSAT OBSAH TRIE, BUFFER JE NULL\n");
        }
        return;
    }


    /* Pokud je node koncovym znakem, vypis retezec a pocet jeho vyskytu */
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

