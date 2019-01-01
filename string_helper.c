#include "string_helper.h"

/* Overi jestli dany znak je oddelovacem slov v kodovani CP1250 */
cp1250_is_word_separator(unsigned char c)
{
    const unsigned char separators[] = {130, 132, 133, 139, 145, 146,147, 148, 149, 150, 151, 155, 161, 166, 167, 168, 171, 172, 173, 174, 176,177, 178, 179, 180,182, 183, 184, 187,189, 255};
    const int seperator_size = 31;
    int i = 0;

    for(i = 0; i < seperator_size; i++)
    {
        if(c == separators[i])
        {
            /* Znak je jeden ze seperatoru CP1250 */
            return 1;
        }
    }
    /* Znak neni zadnym ze separatoru CP1250 */
    return 0;
}

/* Prozkouma velikosti retezcu, vrati vetsi z nich  */
long max_strlen(char *str1, char *str2)
{
    long a = 0;
    long b = 0;

    if(str1 == NULL && str2 == NULL)
    {
        return 0;
    }

    if(str1 == NULL)
    {
        a = 0;
    }
    else
    {
        a = strlen(str1);
    }

    if(str2 == NULL)
    {
        b = 0;
    }
    else
    {
        b = strlen(str2);
    }

    return long_max(a, b);




}

/* Funkce ktera vrati vetsi cislo ze dvou  */
long long_max(long a, long b)
{

    /* ternarni operator pokud je a vetsi nez b vrat a, jinak vrat b */
    return ((a) >= (b) ? (a) : (b));
}