#define SEGNALAZIONE_H

// Dichiaro il tipo incompleto, nascondo la definizione reale dei campi. Chi usa questo modulo 
// sa solo che esiste il tipo Segnalazione e può manipolarlo solo tramite i puntatori e le funzioni sotto.
typedef struct Segnalazione Segnalazione;

// alloca la memoria per una nuova segnalazione e ne inizializza tutti i campi
// restituisce il puntatore all'oggetto pronto all'uso.
Segnalazione* crea_segnalazione(int id, const char* nome, const char* zona, const char* categoria, int urgenza, int stato);

// si occupa di fare la free di tutti i campi allocati dinamicamente all'interno 
// della struttura e della struttura stessa.
void libera_segnalazione(Segnalazione* s);

// permettono agli altri moduli di leggere i dati interni 
// della segnalazione in modo sicuro e controllato.
int get_id_segnalazione(Segnalazione* s);       
int get_urgenza_segnalazione(Segnalazione* s);  
int get_stato_segnalazione(Segnalazione* s);    

// l'unico modo concesso all'esterno per modificare lo stato interno 
// di una segnalazione senza accedere direttamente ai campi.
void set_stato_segnalazione(Segnalazione* s, int nuovo_stato);

// stampa a video tutti i dettagli della segnalazione con una formattazione pulita.
void stampa_segnalazione(Segnalazione* s);
