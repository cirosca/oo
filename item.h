#define ITEM_H
#include "segnalazione.h"

typedef Segnalazione* Item;

void stampa_item(Item val);
void libera_item(Item val);
int get_stato_item(Item val);
int get_urgenza_item(Item val);
int get_id_item(Item val);

