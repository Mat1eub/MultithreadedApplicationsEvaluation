# Multithreaded Applications Evaluation

The main goal of this project is to analyze the overall impact of threads and POSIX's syncronizations (e.g. mutex and semaphores for the first part of the project then active waiting locks in the second part)

Ce projet a pour but d'analyser l'impact des threads et des primitives de synchronisation POSIX (mutex et sémaphores dans un premier temps, ainsi qu'avec des verrous avec attente active dans un second temps).

## How to use this project

The root folder contains :

* `headers` folder, contains the fonctions' signatures and their documentation (make sure to enable IntelliSense to get function documentation on hover)
* `results` folder which contains graphs for the evaluation of performance
* `scripts` folder will contains the python scripts to make graphs and calculation of the evaluation
* `src` folder is where we put all our code, every task is separated in a single file with the name of the problem and the main file centralizes all the functions and is responsible for launching the threads for each problem.

Then we have the Makefile to execute everything :

| Command                     | What does it really do                                                                                                 | Default parameters |
| --------------------------- | ---------------------------------------------------------------------------------------------------------------------- | ------------------ |
| `make philosophers N=...` | Compile and execute the philosophers' problem with N philosphers (we may consider running test with this command too) | N=5                |
| `make producercons`ummer  |                                                                                                                        |                    |
|                             |                                                                                                                        |                    |
| `make clean`              |                                                                                                                        |                    |
|                             |                                                                                                                        |                    |

## Problème des philosophes

Le problème du philosophe met en lumière les difficultés de synchronisation liées à la programmation en parallèle. Pour résumé, on a N (e.g. 5) philosophes autour d'une table. Ils peuvent soit penser, soit manger. Mais pour manger, il faut 2 fourchettes. Or, entre 2 assiettes il n'y a qu'un couvert (e.g. 5 fourchettes à table). Il faut donc pour manger que la fourchette à la droite et à la gauche du philosophe soient libres : les fourchettes sont des ressources partagées (sémaphores) et le problème est de réguler l'accès à celles-ci pour que chaque philosophe puisse tout le temps alterner entre manger et penser.

Un premier problème apparait assez rapidement en analysant la situation. Si tous les philosophes décident d'abord de prendre chacun la fourchette du même côté de l'assiette alors chaque philosophe serait bloqué à attendre qu'un autre philosophe lâche une fourchette. En code, cette première version quelque peu naïve mènerait à un deadlock.

> **Deadlock :** *Etat d'un système qui ne peut plus évoluer.*

Si le problème est que chaque philosophe doive prendre 2 ressources et le faire :

Si le problème est que chaque philosphe doive prendre 2 ressources et le faire :

- en 2 étapes,
- tous dans le même ordre,
- sans retour en arrière possible,

Il suffirait de supprimer une de ces conditions pour éviter un deadlock.

Dans cette version, on a une situation binaire : un philosophe détient 0 ou 2 fourchettes mais jamais une seule (première des 3 conditions). De plus, le dernier philosophe commence par prendre la fourchette de gauche tandis que les autres commencent par la fourchette de droite (deuxième condition). Pourquoi cette deuxième condition ? Car il faut toujours garder en tête qu'un philosophe pourrait être trop lent et risquer de ne jamais avoir de fourchette disponible.

## Problème des producteurs-consommateurs


// On met l'incrémentation dans le même mutex_prodcons,

// une idée de faire autrement c'est de rajouter un mutex_prodcons pour incrémenter cette variable

// (un thread incrémentera en même temps qu'un autre produira ca peut etre pas mal)


// Parler dans le readme ou initialement que j'avais d'abord penser faire un while(1) if prodcount<10 : do else : break

// sans penser qu'en fait plusieurs threads vont verifier cette condition et acceder au bloc dans le if et donc ca va produire

// + que le seuil


# TO DO

* [ ] Maybe too much, but a simulation of philosophers problem ?
* [ ] Translate to english
* [ ] Illustrations for problems
* [ ] Finish how to execute
* [ ] Peux-etre afficher un premier pseudo code pour montrer la reflexion derrière la version finale
