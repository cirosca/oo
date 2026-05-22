#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "item.h"

// Funzione per leggere l'input 
void finput_array(char *file_name, int a[], int n) {
    FILE *fd = fopen(file_name, "r");
    if (fd == NULL) {
        printf("Errore in apertura del file %s \n", file_name);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fscanf(fd, "%d", &a[i]);
    }
    fclose(fd);
}

// Funzione per scrivere l'output 
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

// Funzione per confrontare output e oracolo
int confronta_array(int a[], int oracle[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != oracle[i]) return 0; // Se c'è qualche differenza FAIL
    }
    return 1; // altrimenti diamo il PASS
}

int main(int argc, char *argv[]) {
    // Controllo argomenti 
    if (argc != 5) {
        printf("Numero parametri non corretto \n");
        printf("Uso: ./test_hash <n_elementi> <input.txt> <oracle.txt> <output.txt>\n");
    } else {
        int n = atoi(argv[1]);
        int *input_keys = calloc(n, sizeof(int));
        int *output_results = calloc(n, sizeof(int));
        int *oracle = calloc(n, sizeof(int));

        if (input_keys == NULL || output_results == NULL || oracle == NULL) {
            printf("Memoria insufficiente \n");
            return 1;
        }

        //leggo il file da input
        finput_array(argv[2], input_keys, n);

        //Inizializzo la  HashTable 
        hashtable h = newHashtable(5);

        for (int i = 0; i < n; i++) {
            Item elem = crea_segnalazione(input_keys[i], "nome_test", "zona_test", "cat_test", 0, 0); 
          
            InsertHash(h, elem);
        }

        // Cerchiamo gli elementi e popolo l'array dei risultati
        for (int i = 0; i < n; i++) {
            Item trovato = SearchHash(h, input_keys[i]);
            if (trovato != NULL) {
                output_results[i] = 1; //Trovato 
            } else {
                output_results[i] = 0; //Non trovato 
            }
        }

        //scrivo i risult. nel file di output
        foutput_array(argv[4], output_results, n);

        // leggo l'oracolo e confrontiamo
        finput_array(argv[3], oracle, n);
        
        if (confronta_array(output_results, oracle, n)) {
            printf("PASS \n");
        } else {
            printf("FAIL \n");
        }

        free(input_keys);
        free(output_results);
        free(oracle);
        DestroyHashtable(h);
    }
    return 0;
}