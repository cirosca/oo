#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

// Alloco lo spazio per la struttura  della lista. 
Lista* crea_lista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l) l->head = NULL;
    return l;
}

// Inserimento in testa. Sfrutto il fatto di avere la struttura "Lista" 
// per aggiornare la testa in modo pulito, facendo puntare il nuovo nodo alla vecchia testa
// e poi agganciando il nuovo nodo come primo elemento della lista.
void inserisci_in_testa(Lista* l, Item val) {
    if (!l) return;
    Nodo* nuovo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuovo) return; 
    
    nuovo->info = val;
    nuovo->next = l->head;
    l->head = nuovo;
}

// Scorro la lista partendo dal primo nodo.
// Uso una funzione di confronto (eq_id_item) per passare il controllo sull'ID dell'Item.
Item cerca_per_id(Lista* l, int id) {
    if (!l) return NULL;
    Nodo* corr = l->head;
    while (corr != NULL) {
        if (eq_id_item(corr->info, id)) return corr->info;
        corr = corr->next;
    }
    return NULL; 
}

int elimina_per_id(Lista* l, int id) {
    if (!l) return 0;
    Nodo* corr = l->head;
    Nodo* prec = NULL; // Mi serve per non rompere la lista quando sfilo il nodo.

    while (corr != NULL) {
        if (eq_id_item(corr->info, id)) {
            // Gestione del caso critico: se elimino il primo nodo, sposto direttamente la testa della lista.
            // altrimenti, scavalco il nodo corrente collegando il precedente al successivo.
            if (prec == NULL) l->head = corr->next;
            else prec->next = corr->next;
            
            // svuoto i dati interni dell'Item e libero il nodo.
            libera_item(corr->info);
            free(corr);
            return 1;
        }
        prec = corr; // Avanzo il puntatore d'appoggio
        corr = corr->next; // e avanzo il puntatore corrente.
    }
    return 0;
}

// Svuoto completamente la lista in modo iterativo.
// Uso un puntatore temporaneo per salvare il riferimento al nodo successivo 
// prima di distruggere quello corrente, altrimenti perderei il filo della lista in memoria.
void distruggi_lista(Lista* l) {
    if (!l) return;
    Nodo* corr = l->head;
    while (corr != NULL) {
        Nodo* temp = corr->next; // Salvo il salto al prossimo nodo
        libera_item(corr->info); // Pulisco l'Item
        free(corr);              // Pulisco il blocco Nodo attuale
        corr = temp;             // Passo al prossimo salvato
    }
    free(l); 
}