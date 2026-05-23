#include "item.h"

// Questo file funge da item generico usato dalla tabella di hash e lo collego direttamente
// alle funzioni specifiche della mia struttura "Segnalazione" così, se domani dovessi 
// cambiare il tipo di dati da salvare nella tabella, mi basterà modificare solo questo file.

void stampa_item(Item val) { 
    stampa_segnalazione(val); 
}

// demando la liberazione della memoria interna dell'oggetto alla sua specifica funzione di pulizia.
void libera_item(Item val) { 
    libera_segnalazione(val); 
}

// Estraggo lo stato dell'elemento nascondendo i campi interni della struttura.
int get_stato_item(Item val) { 
    return get_stato_segnalazione(val); 
}

// Recupero il livello di urgenza, fondamentale per la funzione di ricerca dei massimi nella tabella.
int get_urgenza_item(Item val) { 
    return get_urgenza_segnalazione(val); 
}

// estraggo l'ID numerico della segnalazione in modo che 
//la funzione di hash possa usarlo come chiave per calcolare l'indice.
int get_id_item(Item val) { 
    return get_id_segnalazione(val); 
}