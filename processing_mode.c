#include "processing_mode.h"

/* Spusti cast aplikace v rezimu zpracovani
 *
 * Vraci 0 pokud nenastane chyba, jine cislo pri chybe
 */
int processing_mode(app_context *context)
{
    trie_node *database = NULL;
    list_node *input_list = NULL;
    list_node *iterator = NULL;
    int longest_word = 0;
    int longest_word_input = 0;
    long max_word = 0;

    /* Neexistuje soubor stems.dat, bez nej nelze dale pracovat  */
    if(file_exists(PROGRAM_STEMS_DAT_FILENAME) == 0)
    {
        printf("Unable to find stems.dat. Please try to run program in learning mode before.\n");
        return PROGRAM_RETURN_STEMS_DAT_MISSING;
    }

    /* Aplikacni kontext je NULL - nelze dale pokracovat */
    if(context == NULL)
    {
        return PROGRAM_RETURN_NO_CONTEXT;
    }

    /* Ukazatel na text v kontextu je NULL - nelze dále pokračovat */
    if(context->input_text == NULL)
    {
        return PROGRAM_RETURN_MALFORMED_CONTEXT;
    }

    /* Vytvoreni korenoveho prvku trie */
    database = create_trie_node();
    /* Vytvoreni korenoveho prvku spojoveho seznamu */
    input_list = create_list_node("", 1);

    /* Precteni souboru a ulozeni jeho slov do TRIE */
    longest_word = file_read_database_to_trie(PROGRAM_STEMS_DAT_FILENAME, database, context->min_stem_freq);

    /* Zjisteni slov ze vstupniho retezce */
    longest_word_input = string_read_words_to_list(context->input_text, input_list);

    /* Vypis nalezenych slov v DEBUG mode */
    if(DEBUG) {
        print_list(input_list);
    }

    /* Maximalni delka slova */
    max_word = long_max(longest_word, longest_word_input);

    /* Hledani korenu pro slova detekovana na vstupu */
    iterator = input_list->next;
    while(iterator != NULL)
    {
        char *buffer = calloc(max_word + 1, sizeof(char));
        char *output = calloc(max_word + 1, sizeof(char));
        int level = 0;

        /* Nalezeni nejdelsiho korene */
        trie_find_longest_stem(database, iterator->content, buffer, level, output);

        /* Vypis nejdelsiho korene */
        if(strlen(output) > 0) {
            /* Nalezen koren nenulove delky */
            printf("%s -> %s\r\n", iterator->content, output);
        }
        else
        {
            /* Koren nebyl nalezen */
            printf("%s -> 0\r\n", iterator->content);
        }

        /* Uvolneni pameti */
        free(buffer);
        free(output);

        /* Posun na dalsi clen spojoveho seznamu */
        iterator = iterator->next;
    }

    /* Uvolneni pameti */
    trie_free(database);
    free_list(input_list);

    /* Vse v poradku - navrat do main */
    return PROGRAM_RETURN_OK;
}
