#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Déclarations globales
pthread_t* phil;               // Tableau de threads
pthread_mutex_t* baguette;      // Tableau de mutex représentant les baguettes
int cmpt = 0;                  // Compteur pour suivre les actions des philosophes

// Fonction représentant le philosophe en train de manger
void mange(int id) {
    cmpt++;
    // Simulez ici un délai si nécessaire, ex. : usleep(100);
}

// Fonction exécutée par chaque thread
void* philosophe(void* arg) {
    int id = *(int*)arg;                // Récupère l'ID du philosophe
    int left = id;                      // Baguette gauche
    int right = (id + 1) % cmpt;        // Baguette droite (table circulaire)

    for (int i = 0; i < 1000000; i++) { // Boucle d'actions penser/manger
        if (left < right) {             // Ordre pour éviter un interblocage
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);
        } else {
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }

        mange(id); // Philosophe mange

        pthread_mutex_unlock(&baguette[left]);  // Libère la baguette gauche
        pthread_mutex_unlock(&baguette[right]); // Libère la baguette droite
    }

    return NULL;
}

// Fonction principale
int main(int argc, char* argv[]) {
    if (argc != 2) { // Vérification des arguments
        fprintf(stderr, "Usage: %s <nombre_de_philosophes>\n", argv[0]);
        return 1;
    }

    int PHILOSOPHES = atoi(argv[1]); // Nombre de philosophes
    if (PHILOSOPHES <= 0) {
        fprintf(stderr, "Le nombre de philosophes doit être un entier positif.\n");
        return 1;
    }

    cmpt = PHILOSOPHES; // Met à jour le compteur global

    // Allocation dynamique des ressources
    phil = malloc(PHILOSOPHES * sizeof(pthread_t));
    baguette = malloc(PHILOSOPHES * sizeof(pthread_mutex_t));
    int* ids = malloc(PHILOSOPHES * sizeof(int));

    if (!phil || !baguette || !ids) {
        perror("Erreur d'allocation");
        free(phil);
        free(baguette);
        free(ids);
        return 1;
    }

    // Initialisation des mutex
    for (int i = 0; i < PHILOSOPHES; i++) {
        if (pthread_mutex_init(&baguette[i], NULL) != 0) {
            perror("Erreur lors de l'initialisation d'un mutex");
            free(phil);
            free(baguette);
            free(ids);
            return 1;
        }
    }

    // Création des threads
    for (int i = 0; i < PHILOSOPHES; i++) {
        ids[i] = i; // ID unique pour chaque philosophe
        if (pthread_create(&phil[i], NULL, philosophe, &ids[i]) != 0) {
            perror("Erreur lors de la création du thread");
            free(phil);
            free(baguette);
            free(ids);
            return 1;
        }
    }

    // Attente de la fin des threads
    for (int i = 0; i < PHILOSOPHES; i++) {
        pthread_join(phil[i], NULL);
    }

    // Destruction des mutex
    for (int i = 0; i < PHILOSOPHES; i++) {
        pthread_mutex_destroy(&baguette[i]);
    }

    // Libération des ressources
    free(phil);
    free(baguette);
    free(ids);

    return 0;
}
