#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segnalazione.h"

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
        strncpy(s->nome_cittadino, nome, 29);
        s->nome_cittadino[29] = '\0';
        strncpy(s->zona, zona, 29);
        s->zona[39] = '\0';
        strncpy(s->categoria, categoria, 29);
        s->categoria[29] = '\0';
        s->livello_urgenza = urgenza;
        s->stato = stato;
    }
    return s;
}

void libera_segnalazione(Segnalazione* s) {
    if (s != NULL) free(s);
}

int get_id_segnalazione(Segnalazione* s) { return s ? s->id : -1; }
int get_urgenza_segnalazione(Segnalazione* s) { return s ? s->livello_urgenza : -1; }
int get_stato_segnalazione(Segnalazione* s) { return s ? s->stato : -1; }

void set_stato_segnalazione(Segnalazione* s, int nuovo_stato) {
    if (s != NULL) s->stato = nuovo_stato;
}

void stampa_segnalazione(Segnalazione* s) {
    if (s != NULL) {
        printf("ID: %d | Cittadino: %s | Zona: %s | Categoria: %s | Urgenza: %d | Stato: %d\n",
               s->id, s->nome_cittadino, s->zona, s->categoria, s->livello_urgenza, s->stato);
    }
}