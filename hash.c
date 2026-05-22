#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

struct Nodo {
    Item info;
    struct Nodo *next;
};

struct hash {
    int size;
    struct Nodo **table;
};

int hashFun(int key, int size) {
    return key % size;
}

hashtable newHashtable(int size) {
    hashtable h = (struct hash *) malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Nodo **) calloc(size, sizeof(struct Nodo *));
    return h;
}

int InsertHash(hashtable h, Item elem) {
    int idx;
    struct Nodo *head, *curr;
    int key = get_id_item(elem); 

    idx = hashFun(key, h->size);
    curr = head = h->table[idx];

    while (curr) {
        if (get_id_item(curr->info) == key) {
            return (0); 
        }
        curr = curr->next;
    }

    struct Nodo* nuovo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuovo->info = elem;
    nuovo->next = head;
    
    h->table[idx] = nuovo;
    return (1);
}

Item SearchHash(hashtable h, int key) {
    if (!h) return NULL;
    int idx = hashFun(key, h->size);
    struct Nodo *curr = h->table[idx];
    
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

    while (curr) {
        if (get_id_item(curr->info) == key) {
            if (curr == head) h->table[idx] = curr->next;
            else prev->next = curr->next;
            
            libera_item(curr->info);
            free(curr);
            return 1; 
        }
        prev = curr;
        curr = curr->next;
    }
    return 0; 
}

static void deleteList(struct Nodo *p) {
    if (p == NULL) return;
    deleteList(p->next);
    libera_item(p->info);
    free(p);
    return;
}

void DestroyHashtable(hashtable h) {
    int i;
    for (i = 0; i < h->size; i++) {
        deleteList(h->table[i]);
    }
    free(h->table);
    free(h);
    return;
}

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

void stampa_piu_urgenti_tabhash(hashtable h) {
    if (!h) return;
    int max_urgenza = -1;
    
    for (int i = 0; i < h->size; i++) {
        struct Nodo* curr = h->table[i];
        while (curr != NULL) {
            int urg = get_urgenza_item(curr->info);
            if (urg > max_urgenza) max_urgenza = urg;
            curr = curr->next;
        }
    }
    
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