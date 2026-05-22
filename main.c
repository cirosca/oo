#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "segnalazione.h"

#define HASH_SIZE 11

void stampa_comunesa() {
    printf("caricamento....\n");
    printf("\n1. --(INSERISCI SEGNALAZIONE)--\n");
    printf("2. --(RICERCA PER ID)--\n");
    printf("3. --(AGGIORNA STATO SEGNALAZIONE)--\n");
    printf("4. --(VISUALIZZA PER STATO))--\n");
    printf("5. --(VISUALIZZA PIU' URGENTI)--\n");
    printf("6. --(ELIMINA SEGNALAZIONE))--\n");
    printf("0. --(ESCI))--\n");
    printf("Scelta: ");
}

int main() {
    hashtable archivio = newHashtable(HASH_SIZE);
    int scelta;

    do {
        stampa_comunesa();
        if (scanf("%d", &scelta) != 1) {
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch(scelta) {
            case 1: {
                int id, urgenza;
                char nome[30], zona[30], cat[30];

                printf("ID: "); scanf("%d", &id); getchar();
                printf("Cittadino: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
                printf("Zona (Quartiere/Via): "); fgets(zona, sizeof(zona), stdin); zona[strcspn(zona, "\n")] = 0;
                printf("Categoria: "); fgets(cat, sizeof(cat), stdin); cat[strcspn(cat, "\n")] = 0;
                printf("Urgenza (1-5): "); scanf("%d", &urgenza);

                Segnalazione* s = crea_segnalazione(id, nome, zona, cat, urgenza, 0);
                if (InsertHash(archivio, s)) {
                    printf("Inserimento completato.\n");
                } else {
                    printf("Errore: ID gia' presente.\n");
                    libera_segnalazione(s);
                }
                break;
            }
            case 2: {
                int id;
                printf("ID da cercare: "); scanf("%d", &id);
                Item trovato = SearchHash(archivio, id);
                if (trovato) stampa_item(trovato);
                else printf("Non trovata.\n");
                break;
            }
            case 3: {
                int id, nuovo_stato;
                printf("ID da aggiornare: "); scanf("%d", &id);
                Item da_modificare = SearchHash(archivio, id);
                if (da_modificare) {
                    printf("Nuovo stato (0, 1, 2): "); scanf("%d", &nuovo_stato);
                    set_stato_segnalazione(da_modificare, nuovo_stato);
                    printf("Stato aggiornato.\n");
                } else {
                    printf("Segnalazione non trovata.\n");
                }
                break;
            }
            case 4: {
                int stato;
                printf("Stato da filtrare: "); scanf("%d", &stato);
                stampa_per_stato_tabhash(archivio, stato);
                break;
            }
            case 5: {
                stampa_piu_urgenti_tabhash(archivio);
                break;
            }
            case 6: {
                int id;
                printf("ID da eliminare: "); scanf("%d", &id);
                if (HashDelete(archivio, id)) printf("Eliminata.\n");
                else printf("Non trovata.\n");
                break;
            }
            case 0:
                DestroyHashtable(archivio);
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 0);

    return 0;
}