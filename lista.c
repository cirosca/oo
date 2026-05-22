#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

Lista* crea_lista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l) l->head = NULL;
    return l;
}

void inserisci_in_testa(Lista* l, Item val) {
    if (!l) return;
    Nodo* nuovo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuovo) return;
    nuovo->info = val;
    nuovo->next = l->head;
    l->head = nuovo;
}

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
    Nodo* prec = NULL;
    while (corr != NULL) {
        if (eq_id_item(corr->info, id)) {
            if (prec == NULL) l->head = corr->next;
            else prec->next = corr->next;
            libera_item(corr->info);
            free(corr);
            return 1;
        }
        prec = corr;
        corr = corr->next;
    }
    return 0;
}

void distruggi_lista(Lista* l) {
    if (!l) return;
    Nodo* corr = l->head;
    while (corr != NULL) {
        Nodo* temp = corr->next;
        libera_item(corr->info);
        free(corr);
        corr = temp;
    }
    free(l);
}