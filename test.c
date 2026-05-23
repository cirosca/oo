#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "item.h"
 
// Questa funzione mi serve sia per caricare le chiavi di input sia per leggere il file dell'oracolo.
void finput_array(char *file_name, int a[], int n) {
    FILE *fd = fopen(file_name, "r");
    if (fd == NULL) {
        printf("Errore in apertura del file %s \n", file_name);
        exit(1); // Blocco l'esecuzione se manca il file di test.
    }
    for (int i = 0; i < n; i++) {
        fscanf(fd, "%d", &a[i]);
    }
    fclose(fd);
}

// Scrivo i risultati dei miei test su un file di output, memorizzando riga per riga 
// se l'elemento corrispondente è stato trovato 1 altrimenti 0.
void foutput_array(char *file_name, int a[], int n) {
    FILE *fd = fopen(file_name, "w");
    if (fd == NULL) {
        printf("Errore in apertura del file %s \n", file_name);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fd, "%d\n", a[i]);
    }
    fclose(fd);
}

// confronto l'array dei risultati generati dal mio codice con l'array oracle.
int confronta_array(int a[], int oracle[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != oracle[i]) return 0; 
    }
    return 1;
}

// Strutturo il main per ricevere i percorsi dei file direttamente da riga di comando, se l'utente non capisce.
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Numero parametri non corretto \n");
        printf("Uso: ./test_runner.exe <n_elementi> <input.txt> <oracle.txt> <output.txt>\n");
    } else {
        int n = atoi(argv[1]); // Converto il primo argomento in intero per sapere quanti record fare.
        
        // Alloco dinamicamente i vettori di supporto azzerandoli con calloc.
        int *input_keys = calloc(n, sizeof(int));
        int *output_results = calloc(n, sizeof(int));
        int *oracle = calloc(n, sizeof(int));

        if (input_keys == NULL || output_results == NULL || oracle == NULL) {
            printf("Memoria insufficiente \n");
            return 1;
        }

        // Carico le chiavi numeriche dal file di input.
        finput_array(argv[2], input_keys, n);

        // Creo una tabella piccola per forzare l'algoritmo 
        // a gestire le collisioni e testare le liste concatenate.
        hashtable h = newHashtable(5);

        // Popolo la tabella generando segnalazioni fittizie basate sulle chiavi di input.
        for (int i = 0; i < n; i++) {
            Item elem = crea_segnalazione(input_keys[i], "nome_test", "zona_test", "cat_test", 0, 0); 
            InsertHash(h, elem);
        }

        // cerco ogni singola chiave nell'hash. 
        // Se SearchHash risponde correttamente col puntatore salvo 1, altrimenti 0.
        for (int i = 0; i < n; i++) {
            Item trovato = SearchHash(h, input_keys[i]);
            if (trovato != NULL) {
                output_results[i] = 1; 
            } else {
                output_results[i] = 0; 
            }
        }

        // Salvo i risultati su file per poterli ispezionare.
        foutput_array(argv[4], output_results, n);

        // Carico i risultati attesi e vedo se il test é passto o fallito.
        finput_array(argv[3], oracle, n);
        
        if (confronta_array(output_results, oracle, n)) {
            printf("PASS \n"); // La tabella si comporta come previsto.
        } else {
            printf("FAIL \n"); // C'è un bug.
        }

        // Pulisco tutta la memoria per non lasciare residui al termine del test.
        free(input_keys);
        free(output_results);
        free(oracle);
        DestroyHashtable(h);
    }
    return 0;
}