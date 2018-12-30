#include "learning_mode.h"

/* Spusti cast aplikace v rezimu uceni
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int learning_mode(app_context *context)
{
    /* Deklarace promennych */
    FILE *file;
    char *buffer = NULL;
    int buffer_size = READ_BUFFER_SIZE;
    int buffer_used = 0;
    trie_node *root;
    unsigned char current_char;
    int first_char_of_word = 1;
    char *temp = NULL;
    int longest_word = 0;

    if(DEBUG)
    {
        printf("LEARNING MODE\n");
    }

    /* Aplikacni kontext je NULL - nelze dale pokracovat */
    if(context == NULL)
    {
        return -1;
    }

    /* Otevreni souboru pro cteni */

    file = fopen(context->input_file ,"r");
    if (file == NULL) {
        /* Chybi opravneni ke cteni souboru nebo se jej nepodarilo otevrit */
        return -5;
    }

    /* Alokace pameti pro buffer a trii */
    buffer = malloc((READ_BUFFER_SIZE * sizeof(char)) + 1);
    root = create_trie_node();

    /* Overeni alokace */
    if(buffer == NULL || root == NULL)
    {
        return -6;
    }

    while((current_char = ((unsigned char)getc(file))))
    {
        /* Zastaveni cyklu v pripade dosazeni konce souboru */
        if((char)current_char == EOF)
        {
            break;
        }

        /* Pokud znak rozdeluje slova */
        if(isdigit(current_char) || ispunct(current_char) || isspace(current_char))
        {
            /* Nenalezli jsme zadny znak - tj. vice rozdelovacu za sebou, ignorujeme */
            if(first_char_of_word)
            {
                continue;
            }

            /* Narazili jsme na konec slova */
            trie_insert(root, buffer);
            free(buffer);
            buffer = malloc((READ_BUFFER_SIZE * sizeof(char)) + 1);
            buffer_size = READ_BUFFER_SIZE;
            buffer_used = 0;
            first_char_of_word = 1;
        }
        else
        {
            /* V pripade ze jsme nalezli prvni znak slova, nastav priznak na prvni znak nalezen */
            if(first_char_of_word)
            {
                first_char_of_word = 0;
            }

            /* Slovo pokracuje, pridame znak do bufferu */
            /* TODO CP1250_tolower */
            buffer[buffer_used] = current_char;
            buffer_used++;

            /* Zjisteni nejdelsiho prectenoho slova */
            if(buffer_used > longest_word)
            {
                longest_word = buffer_used;
            }

            /* Detekce preteceni buffer - pripadne zvetseni */
            if(buffer_used > buffer_size)
            {
                /* Realloc se nelibi valgrindu - tj. zalozit, nove misto v pameti, zkopirovat, uvolnit stare, nastavit */
                buffer_size = buffer_size * 2;
                temp = malloc((buffer_size * sizeof(char)) + 1);
                strcpy(temp, buffer);
                free(buffer);
                buffer = temp;
                temp = NULL;
            }
        }
    }

    /* */
    if(DEEP_DEBUG)
    {
        int level = 0;
        char str[longest_word];
        trie_display(root, str, level);
    }

    /* TODO: čti soubor znak po znaku a hledej oddelovace znaku (X)
     * TODO: vsechna nalezena slova vloz do trie (X)
     * TODO: Vsechna slova se vsemi slovy dej do algoritmu LCS a uloz do trie
     * TODO: vyplivni obsah trie do souboru
     *
     * */

    /* Uzavreni souboru */
    fclose(file);

    return 0;
}
