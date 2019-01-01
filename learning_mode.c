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
    trie_node *root = NULL;
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

    /* Alokace pameti pro buffer */
    buffer = calloc((size_t )(buffer_size+1), sizeof(char));

    /* Overeni alokace */
    if(buffer == NULL)
    {
        fclose(file);
        return -6;
    }

    /* Alokace pameti pro root prvek Trie */
    root = create_trie_node();

    if(root == NULL)
    {
        fclose(file);
        free(buffer);
        return -6;
    }

    while((current_char = ((unsigned char)getc(file))))
    {
        /* Zastaveni cyklu v pripade dosazeni konce souboru */
        if((char)current_char == EOF)
        {
            /* Narazili jsme na konec slova */
            trie_insert(root, buffer);
            break;
        }

        /* Pokud znak rozdeluje slova */
        if(isdigit(current_char) || ispunct(current_char) || isspace(current_char) || cp1250_is_word_separator(current_char))
        {
            /* Nenalezli jsme zadny znak - tj. vice rozdelovacu za sebou, ignorujeme */
            if(first_char_of_word)
            {
                continue;
            }

            /* Narazili jsme na konec slova */
            trie_insert(root, buffer);
            memset(buffer, 0, sizeof(char) * buffer_size);
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

    /* Provedeni LCS na prectenych slovech */

    /* Vytvoreni TRIE pro ulozeni vysledku - kvuli iteraci skrz starou trii */
    trie_node *save = create_trie_node();

    int level = 0;
    char *str_buffer = calloc((size_t)(longest_word)+1, sizeof(char));
    trie_manipulate_first(save,root,root, str_buffer, level, longest_word);
    free(str_buffer);

    /* */
    if(DEBUG)
    {
        int level = 0;
        char *str = malloc(sizeof(char) * longest_word + 1);
        trie_display(save, str, level);
        free(str);
    }

    /* Uvolneni pameti */
    free(buffer);
    trie_free(root);
    trie_free(save);

    /* Uzavreni souboru */
    fclose(file);

    return 0;
}
