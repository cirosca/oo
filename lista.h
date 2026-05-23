#include "item.h"

// Definisco la struct Nodo 
typedef struct Nodo {
    Item info;
    struct Nodo* next;
} Nodo;

// Creo una struttura per la lista. Inserendo la testa dentro un tipo "Lista",
// posso passare il puntatore alla struttura alle funzioni e modificarne la testa 
// senza dover usare i doppi puntatori.
typedef struct Lista {
    Nodo* head;
} Lista;

// Alloca la struttura di controllo della lista e ne azzera la testa per indicare che è vuota.
Lista* crea_lista();

// Inserisce un nuovo elemento in cima alla lista. 
void inserisci_in_testa(Lista* l, Item val);

// Scorrela lista partendo dalla testa fino a trovare l'Item con l'ID richiesto.
// Se non lo trova, restituisce NULL.
Item cerca_per_id(Lista* l, int id_cercato);

// Cerca l'elemento da rimuovere. Se lo trova, aggiorna i puntatori 
// del nodo precedente, libera la memoria dell'Item e del Nodo e ritorna 1, altrimenti 0.
int elimina_per_id(Lista* l, int id_da_eliminare);

// Svuota completamente la lista deallocando tutti i nodi rimasti e i relativi Item, 
// per poi liberare la struttura  principale.
void distruggi_lista(Lista* l);