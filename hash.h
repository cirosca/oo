#define TABHASH_H
#include "item.h"

typedef struct hash *hashtable;

hashtable newHashtable(int size);
int InsertHash(hashtable h, Item elem);
Item SearchHash(hashtable h, int key);
int HashDelete(hashtable h, int key);
void DestroyHashtable(hashtable h);
 
void stampa_per_stato_tabhash(hashtable h, int stato);
void stampa_piu_urgenti_tabhash(hashtable h);
