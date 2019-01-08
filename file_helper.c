#include "file_helper.h"

/* Projde retezec, ziska z nej vsechny slova a ulozi jej do spojoveho seznamu
 *
 *
 * Vrati zaporne cislo pri chybe
 * Vrati kladne cislo reprezentujici nejdelsi nalezene slovo pri uspechu
 *
 */
int string_read_words_to_list(char *string, list_node *node)
{
    char *pch = NULL;
    char *delims = " ";
    int longest_word = 0;

    if(string == NULL || strlen(string) < 1)
    {
        /* Retezec je NULL nebo neni dostatecne dlouhy */
        return PROGRAM_RETURN_GENERIC;
    }

    pch = strtok(string, delims);

    while (pch != NULL)
    {
        /* Vlozeni slova do spojoveho seznamu */
        insert_list_string(node, pch, 1);
        /* Aktualizace nejdelsiho slova */
        if(strlen(pch) > longest_word)
        {
            longest_word = strlen(pch);
        }
        pch = strtok(NULL, delims);
    }

    return longest_word;
}


/* Precte formatovanou databazi korenu a ulozi ji do TRIE */
int file_read_database_to_trie(char *file_name, trie_node *root, long msf)
{
    FILE *file = NULL;
    char *buffer = NULL;
    int count = 0;
    int longest_word = 0;
    int i = 0;

    if(file_exists(file_name) == 0)
    {
        /* Soubor neexistuje */
        return PROGRAM_RETURN_GENERIC;
    }

    if(root == NULL)
    {
        /* Korenovy prvek trie je NULL */
        return PROGRAM_RETURN_GENERIC;
    }

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        /* Soubor nebyl otevren */
        return PROGRAM_RETURN_GENERIC;
    }

    /* BUFFER pro nacitani slov */
    buffer = calloc(READ_BUFFER_SIZE + 1, sizeof(char));

    while(fscanf(file, "%s %d\r\n", buffer, &count) == 2)
    {
        /* Nacti koren do trie pouze v pripade ze vyhovuje minimalni pocet */
        if(count >= msf) {

            /* Aktualizace nejdelsiho slova */
            if (strlen(buffer) > longest_word) {
                longest_word = strlen(buffer);
            }

            /* Vlozeni do trie nekolikrat */
            for (i = 0; i < count; i++) {
                trie_insert(root, buffer);
            }
        }
        /* Reset pameti - just to be sure */
        memset(buffer, 0, sizeof(char) * READ_BUFFER_SIZE);
        count = 0;
    }

    /* Uvolneni alokovane pameti */
    free(buffer);
    fclose(file);

    /* Vse probehlo v poradku */
    return longest_word;
}