#define TABHASH_H
#include "item.h"

// Nascondo la struct per nascondere i dettagli implementativi
// chi usa la libreria sa che esiste hashtable ma non può modificarne i campi.
typedef struct hash *hashtable;

// Alloca e restituisce una nuova tabella di hash con il nnumero di slot specificato.
hashtable newHashtable(int size);

// Inserisce un elemento nella tabella per la verifica dei duplicati. 
// Ritorna 1 se l'inserimento riesce, 0 se la chiave esiste già.
int InsertHash(hashtable h, Item elem);

// Cerca un elemento tramite la sua chiave intera. Ritorna il puntatore all'Item se lo trova, 
// altrimenti restituisce NULL.
Item SearchHash(hashtable h, int key);

// Rimuove l'elemento corrispondente alla chiave, occupandosi anche di deallocare 
// sia il nodo della lista che la memoria interna dell'Item. Ritorna 1 se eliminato, 0 se non trovato.
void DestroyHashtable(hashtable h);

// Dealloca la tabella, distruggendo tutte le liste collegate 
// e azzerando la memoria per evitare qualsiasi tipo di memory leak.
int HashDelete(hashtable h, int key);
 
// Scorre l'intera struttura per individuare e stampare a video solo gli elementi 
// il cui stato interno corrisponde al valore intero passato come parametro.
void stampa_per_stato_tabhash(hashtable h, int stato);

// calcola il picco massimo di urgenza tra tutti gli elem memorizzati, poi stampa tutti quelli che lo condividono.
void stampa_piu_urgenti_tabhash(hashtable h);
