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

    /* Alokace pameti pro buffer pro nacitani slov ze souboru */
    buffer = calloc((size_t )(buffer_size)+1, sizeof(char));

    /* Overeni alokace pameti pro buffer nacitani slov */
    if(buffer == NULL)
    {
        fclose(file);
        return -6;
    }

    /* Alokace pameti pro root prvek Trie */
    root = create_trie_node();

    /* Overeni alokace korenoveho prvku */
    if(root == NULL)
    {
        /* Alokace nebyla provedena spravne, uvolni veskere pouzite zdroje */
        fclose(file);
        free(buffer);
        return -6;
    }

    /* Nacitani ze souboru znak po znaku */
    while((current_char = ((unsigned char)getc(file))))
    {
        /* Nektere znaky je treba preskocit */
        if(current_char == '-')
        {
            continue;
        }

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

            /* Narazili jsme na konec slova - vlozime do trie a vynulujeme buffer */
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
            buffer[buffer_used] = cp1250_tolower(current_char);
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

    /* Ulozeni nalezenych slov do listu pro rychlejsi iteraci */

    /* Vytvoreni korenoveho prvku spojoveho seznamu */
    list_node *list_root_node = create_list_node("", 0);
    /* Deklarace promennych pro presun klicu do spojoveho seznamu */
    int level = 0;
    char *str = malloc(sizeof(char) * longest_word + 1);
    /* Presun dat z trie do spojoveho seznamu */
    trie_to_list(list_root_node, root, str, level);
    free(str);

    /* Deklarace nove trie */
    trie_node *save_root = create_trie_node();
    /* Deklarace iteracnich promennych */
    list_node *iter1 = list_root_node;
    list_node *iter2 = NULL;
    char *buf = NULL;

    /* Iterace nalezenymi slovy - vytvoreni trie pro koreny */
    while(iter1)
    {
        iter2 = iter1->next;
        while(iter2)
        {
            /* Vytvoreni nejdelsiho podretezce - ulozeni do promenne buf */
            longest_common_substring(iter1->content, iter2->content, &buf);

            /* Pridej slovo pokud existuje a pokud vyhovuje parametru -msl */
            if(strlen(buf) > 0 && strlen(buf) >= context->min_stem_length) {
                trie_insert(save_root, buf);
            }
            free(buf);
            iter2 = iter2->next;
        }
        iter1 = iter1->next;
    }

    /* Uvolneni pameti */
    free_list(list_root_node);

    /* Dump trie do stems.dat */
    int level_dump = 0;
    char *str_dump = malloc(sizeof(char) * longest_word + 1);
    FILE *file_dump = fopen("stems.dat", "w");
    trie_to_file(file_dump, save_root, str_dump, level_dump);
    free(str_dump);
    fclose(file_dump);

    /* Uvolneni pameti */
    free(buffer);
    trie_free(root);
    trie_free(save_root);

    /* Uzavreni souboru */
    fclose(file);

    /* Vse se podarilo - navratova hodnota pro main */
    return 0;
}
