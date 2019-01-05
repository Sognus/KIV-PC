#ifndef KIV_PC_CONFIG_H
#define KIV_PC_CONFIG_H

/* Zapina ci vypina debug zpravy, ktere mohou zpusobit spam na vystupu */
#define DEEP_DEBUG 0

/* Zapina ci vypina nektere zakladni debug zpravy */
#define DEBUG 1

/* Pocatecni velikost retezce pri alokaci */
#define READ_BUFFER_SIZE (int)(64*sizeof(char))
#define STRING_BUFFER_LENGTH (int)(1024*sizeof(char))

#endif //KIV_PC_CONFIG_H
