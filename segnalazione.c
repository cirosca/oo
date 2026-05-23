#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segnalazione.h"

// definisco concretamente i campi della struttura Segnalazione. Uso dstringhe a dim fissa 
// per semplificare la gestione della memoria ed evitare varie allocazioni dinamiche.
struct Segnalazione {
    int id;
    char nome_cittadino[30];
    char zona[30];
    char categoria[30];
    int livello_urgenza;
    int stato;
};

Segnalazione* crea_segnalazione(int id, const char* nome, const char* zona, const char* categoria, int urgenza, int stato) {
    Segnalazione* s = (Segnalazione*) malloc(sizeof(Segnalazione));
    if (s != NULL) {
        s->id = id;
        
        // Uso strncpy per evitare buffer overflow se la stringa in input è troppo lunga.
        strncpy(s->nome_cittadino, nome, 29);
        s->nome_cittadino[29] = '\0'; 
        
        strncpy(s->zona, zona, 29);
        s->zona[29] = '\0'; 
        
        strncpy(s->categoria, categoria, 29);
        s->categoria[29] = '\0';
        
        s->livello_urgenza = urgenza;
        s->stato = stato;
    }
    return s;
}

// libero il puntatore alla struttura principale con un free().
void libera_segnalazione(Segnalazione* s) {
    if (s != NULL) free(s);
}

// Implemento i metodi introducendo un operatore ternario di controllo: 
// se il puntatore s è NULL evito crash restituendo un errore.
int get_id_segnalazione(Segnalazione* s) { return s ? s->id : -1; }
int get_urgenza_segnalazione(Segnalazione* s) { return s ? s->livello_urgenza : -1; }
int get_stato_segnalazione(Segnalazione* s) { return s ? s->stato : -1; }

// Il setter mi permette di variare lo stato dell'oggetto tenendo protetta la struct.
void set_stato_segnalazione(Segnalazione* s, int nuovo_stato) {
    if (s != NULL) s->stato = nuovo_stato;
}

// Stampo tutti i campi formattandoli su una sola riga ben chiara.
void stampa_segnalazione(Segnalazione* s) {
    if (s != NULL) {
        printf("ID: %d -|- Cittadino: %s -|- Zona: %s -|- Categoria: %s -|- Urgenza: %d -|- Stato: %d\n",
               s->id, s->nome_cittadino, s->zona, s->categoria, s->livello_urgenza, s->stato);
    }
}