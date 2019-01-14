#ifndef KIV_PC_CONFIG_H
#define KIV_PC_CONFIG_H

/*
 * Obecne konstanty programu
 */

/* Urcuje zda maji byt vypisovany specialni texty pro DEBUG programu (0 = vypnuto | >0 (1) = zapnuto) */
#define DEBUG 0
/* Standardni hodnota pro -msl v pripade nevyplneni vstupu */
#define PROGRAM_DEFAULT_MSL 3
/* Standardni hodnota pro -msf v pripade nevyplneni vstupu */
#define PROGRAM_DEFAULT_MSF 10
/* Jmeno souboru pro vystup korenu */
#define PROGRAM_STEMS_DAT_FILENAME "stems.dat"
/* Pocatecni velikost vyrovaci pameti pro nacitani textu */
#define READ_BUFFER_SIZE (int)(64*sizeof(char))

/*
 * Konstanty pro navratove kody
 */

/* Navratovy kod pro "vse v poradku" */
#define PROGRAM_RETURN_OK 0
/* Nebyl vytvoren aplikacni kontext */
#define PROGRAM_RETURN_NO_CONTEXT -1
/* Nedostatecny pocet argumentu z terminalu */
#define PROGRAM_RETURN_NOT_ENOUGH_ARGUMENTS -2
/* Ciselne hodnoty nepovinnych promenych jsou ve spatnem formatu */
#define PROGRAM_RETURN_NUMBER_CONVERSION_ERROR -3
/* Nelze urcit cil aplikace - chyba ve zpracovani vstupu */
#define PROGRAM_RETURN_UNCLEAR_OPERATION -4
/* Nelze precist soubor */
#define PROGRAM_RETURN_FILE_READ_ERROR -5
/* Neuspesna alokace pameti */
#define PROGRAM_RETURN_ALLOCATION_ERROR -6
/* Soubor stems.dat neexistuje */
#define PROGRAM_RETURN_STEMS_DAT_MISSING -7
/* Kontext aplikace neni NULL, ale data v nem obsazena jsou spatna */
#define PROGRAM_RETURN_MALFORMED_CONTEXT -8

/* Obecná chyba programu */
#define PROGRAM_RETURN_GENERIC -1


/*
 * Konstanty pro aplikacni kontext
 */

/* Index pro nazev/cestu k aktualnimu programu pole argumentu programu */
#define APP_CONTEXT_PROGRAM_INDEX 0
/* Index pro slova/soubor pole argumentu programu  */
#define APP_CONTEXT_INPUT_INDEX 1
/* Index pro nepovinne promenne */
#define APP_CONTEXT_OTHERS_START_INDEX 2
/* Definuje v jakem ciselnem zakladu budou prevadena cisla */
#define APP_CONTEXT_INT_BASE 10


#endif /* KIV_PC_CONFIG_H */
