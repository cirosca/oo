#define LISTA_H
#include "item.h"

// Espongo i nodi per permettere iterazioni più semplici per l'hash
typedef struct Nodo {
    Item info;
    struct Nodo* next;
} Nodo;

typedef struct Lista {
    Nodo* head;
} Lista;

Lista* crea_lista();
void inserisci_in_testa(Lista* l, Item val);
Item cerca_per_id(Lista* l, int id_cercato);
int elimina_per_id(Lista* l, int id_da_eliminare);
void distruggi_lista(Lista* l);
