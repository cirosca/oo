#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

// per gestire le collisioni nella tabella.
// Uso il concatenamento, ogni cella della tabella punta a una lista collegata di nodi.
struct Nodo {
    Item info;
    struct Nodo *next;
};

// controllo la dimensione massima e uso un doppio puntatore 
// per allocare dinamicamente un array di puntatori a struct Nodo.
struct hash {
    int size;
    struct Nodo **table;
};

int hashFun(int key, int size) {
    return key % size;
}

// Inizializzo la tabella allocando prima la struttura principale e poi l'array di puntatori.
hashtable newHashtable(int size) {
    hashtable h = (struct hash *) malloc(sizeof(struct hash));
    h->size = size;
    // Uso calloc così l'array viene azzerato automaticamente.
    h->table = (struct Nodo **) calloc(size, sizeof(struct Nodo *));
    return h;
}

int InsertHash(hashtable h, Item elem) {
    int idx;
    struct Nodo *head, *curr;
    int key = get_id_item(elem); 

    idx = hashFun(key, h->size);
    curr = head = h->table[idx];

    // Prima di inserire, scorro la lista nella cella per assicurarmi che non ci siano duplicati.
    while (curr) {
        if (get_id_item(curr->info) == key) {
            return (0); // Chiave già presente, evito l'inserimento e fallisco.
        }
        curr = curr->next;
    }

    // Se la chiave è nuova, faccio un inserimento in testa alla lista.
    struct Nodo* nuovo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuovo->info = elem;
    nuovo->next = head; // Il nuovo nodo punta alla vecchia testa
    
    h->table[idx] = nuovo; // Aggiorno la testa della cella con il nuovo nodo
    return (1);
}

Item SearchHash(hashtable h, int key) {
    if (!h) return NULL;
    int idx = hashFun(key, h->size);
    struct Nodo *curr = h->table[idx];
    
    // cerco l'elemento linearmente nella sua lista.
    while (curr) {
        if (get_id_item(curr->info) == key) return curr->info;
        curr = curr->next;
    }
    return NULL;
}

int HashDelete(hashtable h, int key) {
    int idx;
    struct Nodo *prev, *curr, *head;

    idx = hashFun(key, h->size);
    prev = curr = head = h->table[idx];

    // Scorro la lista.
    while (curr) {
        if (get_id_item(curr->info) == key) {
            // se elimino la testa, la cella deve puntare al secondo nodo.
            // altrimenti, scavalco il nodo corrente collegando il precedente direttamente al successivo.
            if (curr == head) h->table[idx] = curr->next;
            else prev->next = curr->next;
            
            // libero prima la memoria interna dell'Item e poi il nodo.
            libera_item(curr->info);
            free(curr);
            return 1; 
        }
        prev = curr;
        curr = curr->next;
    }
    return 0; 
}

// Funzione ricorsiva di supporto per distruggere una lista.
static void deleteList(struct Nodo *p) {
    if (p == NULL) return;
    deleteList(p->next);
    libera_item(p->info);
    free(p);
    return;
}

// Libero l'intera tabella, prima svuoto ogni singola lista collegata, poi l'array di puntatori 
// e infine la struttura della tabella stessa. Per i memory leak.
void DestroyHashtable(hashtable h) {
    int i;
    for (i = 0; i < h->size; i++) {
        deleteList(h->table[i]);
    }
    free(h->table);
    free(h);
    return;
}

// Scorro  tutta la tabella per stampare solo gli elementi 
// che corrispondono a uno specifico stato passato come parametro.
void stampa_per_stato_tabhash(hashtable h, int stato) {
    if (!h) return;
    for (int i = 0; i < h->size; i++) {
        struct Nodo* curr = h->table[i];
        while (curr != NULL) {
            if (get_stato_item(curr->info) == stato) {
                stampa_item(curr->info);
            }
            curr = curr->next;
        }
    }
}

// Faccio una prima passata completa per trovare qual è il valore massimo di urgenza presente.
// Faccio una seconda passata per stampare tutti gli elementi che hanno quel livello massimo.
void stampa_piu_urgenti_tabhash(hashtable h) {
    if (!h) return;
    int max_urgenza = -1;
    
    // Ricerca del massimo 
    for (int i = 0; i < h->size; i++) {
        struct Nodo* curr = h->table[i];
        while (curr != NULL) {
            int urg = get_urgenza_item(curr->info);
            if (urg > max_urgenza) max_urgenza = urg;
            curr = curr->next;
        }
    }
    
    // Stampa dei nodi con urgenza pari al massimo trovato
    if (max_urgenza != -1) {
        for (int i = 0; i < h->size; i++) {
            struct Nodo* curr = h->table[i];
            while (curr != NULL) {
                if (get_urgenza_item(curr->info) == max_urgenza) {
                    stampa_item(curr->info);
                }
                curr = curr->next;
            }
        }
    }
}