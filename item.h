#include "segnalazione.h"

// definisco il tipo generico Item come un alias a un puntatore a Segnalazione. Per la tabella di hash, 
// tutto ciò che passa è un Item, rendendo la struttura dati indipendente dall'oggetto reale.
typedef Segnalazione* Item;

// Esporto le funzioni di interfaccia che permettono ai moduli esterni 
// di interagire con l'Item senza conoscere i dettagli di Segnalazione.

// Prototipo per la stampa dell'elemento.
void stampa_item(Item val);

// Prototipo per la gestione della memoria, notifica la necessità di distruggere l'oggetto.
void libera_item(Item val);

// Funzioni per esporre all'esterno solo le proprietà necessarie dell'Item:
int get_stato_item(Item val);     // Restituisce lo stato.
int get_urgenza_item(Item val);   // Restituisce l'urgenza per il calcolo dei massimi.
int get_id_item(Item val);        // Restituisce l'ID numerico usato come chiave di hashing.
