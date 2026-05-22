#include "item.h"

void stampa_item(Item val) { stampa_segnalazione(val); }
void libera_item(Item val) { libera_segnalazione(val); }
int get_stato_item(Item val) { return get_stato_segnalazione(val); }
int get_urgenza_item(Item val) { return get_urgenza_segnalazione(val); }
int get_id_item(Item val) { return get_id_segnalazione(val); }