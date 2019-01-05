#include "file_helper.h"

/* Projde soubor znak po znaku, v souboru najde slova a ty ulozi do trie
 *
 * Vrati zapornou hodnotu pri chybe
 * Vrati kladnou hodnotu pri uspechu - hodnota reprezentuje nejdelsi nalezene slovo
 *
 */
int file_read_words_to_trie(char *file_name, trie_node *root)
{
    FILE *file = NULL;
    unsigned char current_char = 0;
    char *buffer = NULL;
    int buffer_size = READ_BUFFER_SIZE;
    int first_char_of_word = 1;
    int buffer_used = 0;
    char *temp = NULL;
    int longest_word = 0;

    if(file_exists(file_name) == 0)
    {
        /* Soubor neexistuje */
        return -1;
    }

    if(root == NULL)
    {
        /* Korenovy prvek trie je NULL */
        return -1;
    }

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        /* Soubor nebyl otevren */
        return -1;
    }

    /* Alokace pameti pro buffer pro nacitani slov ze souboru */
    buffer = calloc((size_t )(buffer_size)+1, sizeof(char));

    /* Nacitani ze souboru znak po znaku */
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

    /* Uvolneni alokovane pameti */
    free(buffer);
    fclose(file);

    /* Vse probehlo v poradku */
    return longest_word;
}

/* Projde soubor znak po znaku, v souboru najde slova a ty ulozi do list
 *
 * Vrati zapornou hodnotu pri chybe
 * Vrati kladnou hodnotu pri uspechu - hodnota reprezentuje nejdelsi nalezene slovo
 *
 */
int file_read_words_to_list(char *file_name, list_node *root)
{
    FILE *file = NULL;
    unsigned char current_char = 0;
    char *buffer = NULL;
    int buffer_size = READ_BUFFER_SIZE;
    int first_char_of_word = 1;
    int buffer_used = 0;
    char *temp = NULL;
    int longest_word = 0;

    if(file_exists(file_name) == 0)
    {
        /* Soubor neexistuje */
        return -1;
    }

    if(root == NULL)
    {
        /* Korenovy prvek trie je NULL */
        return -1;
    }

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        /* Soubor nebyl otevren */
        return -1;
    }

    /* Alokace pameti pro buffer pro nacitani slov ze souboru */
    buffer = calloc((size_t )(buffer_size)+1, sizeof(char));

    /* Nacitani ze souboru znak po znaku */
    while((current_char = ((unsigned char)getc(file))))
    {
        /* Zastaveni cyklu v pripade dosazeni konce souboru */
        if((char)current_char == EOF)
        {
            /* Narazili jsme na konec slova */
            insert_list_string(root, buffer, 1);
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
            insert_list_string(root, buffer, 1);
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

    /* Uvolneni alokovane pameti */
    free(buffer);
    fclose(file);

    /* Vse probehlo v poradku */
    return longest_word;
}

/* Projde retezec, ziska z nej vsechny slova a ulozi jej do spojoveho seznamu
 *
 *
 * Vrati zaporne cislo pri chybe
 * Vrati kladne cislo reprezentujici nejdelsi nalezene slovo pri uspechu
 *
 */
int string_read_words_to_list(char *string, list_node *node)
{
    int longest_word = 0;
    FILE *file = NULL;

    if(string == NULL || strlen(string) < 1)
    {
        /* Retezec je NULL nebo neni dostatecne dlouhy */
        return -1;
    }

    /* Docasny soubor */
    file = fopen("tmp.txt", "w");

    if(file == NULL)
    {
        /* Docasny soubor nemohl byt vytvoren */
        return -1;
    }

    /* Vlozeni prohledavaneho retezce do souboru */
    fputs(string ,file);

    /* Uzavreni docasneho souboru */
    fclose(file);

    /* Precteni docasneho souboru do spojoveho seznamu */
    longest_word = file_read_words_to_list("tmp.txt", node);

    /* Smazani docasneho souboru */
    remove("tmp.txt");

    /* Navraceni - chyba nebo nejdelsi slovo */
    return longest_word;
}

/* Projde retezec, ziska z nej vsechny slova a ulozi jej do spojoveho seznamu
 *
 *
 * Vrati zaporne cislo pri chybe
 * Vrati kladne cislo reprezentujici nejdelsi nalezene slovo pri uspechu
 *
 */
int string_read_words_to_trie(char *string, trie_node *node)
{
    int longest_word = 0;
    FILE *file = NULL;

    if(string == NULL || strlen(string) < 1)
    {
        /* Retezec je NULL nebo neni dostatecne dlouhy */
        return -1;
    }

    /* Docasny soubor */
    file = fopen("tmp.txt", "w");

    if(file == NULL)
    {
        /* Docasny soubor nemohl byt vytvoren */
        return -1;
    }

    /* Vlozeni prohledavaneho retezce do souboru */
    fputs(string ,file);

    /* Uzavreni docasneho souboru */
    fclose(file);

    /* Precteni docasneho souboru do spojoveho seznamu */
    longest_word = file_read_words_to_trie("tmp.txt", node);

    /* Smazani docasneho souboru */
    remove("tmp.txt");

    /* Navraceni - chyba nebo nejdelsi slovo */
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
        return -1;
    }

    if(root == NULL)
    {
        /* Korenovy prvek trie je NULL */
        return -1;
    }

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        /* Soubor nebyl otevren */
        return -1;
    }

    /* BUFFER pro nacitani slov */
    buffer = calloc(1024 + 1, sizeof(char));

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
        memset(buffer, 0, sizeof(char) * 1024);
        count = 0;
    }

    /* Uvolneni alokovane pameti */
    free(buffer);
    fclose(file);

    /* Vse probehlo v poradku */
    return longest_word;
}