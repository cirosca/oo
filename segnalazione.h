#define SEGNALAZIONE_H

typedef struct Segnalazione Segnalazione;

Segnalazione* crea_segnalazione(int id, const char* nome,const char* zona, const char* categoria, int urgenza, int stato);
void libera_segnalazione(Segnalazione* s);
int get_id_segnalazione(Segnalazione* s);
int get_urgenza_segnalazione(Segnalazione* s);
int get_stato_segnalazione(Segnalazione* s);
void set_stato_segnalazione(Segnalazione* s, int nuovo_stato);
void stampa_segnalazione(Segnalazione* s);

