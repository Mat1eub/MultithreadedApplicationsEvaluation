# Multithreaded Applications Evaluation

The main goal of this project is to analyze the overall impact of threads and POSIX's syncronizations. The project was articulated in 2 phases, we first coded 3 famous problems related to synchronization with classic mutex and semaphore and analyse their performance. Then for the second phase, we implemented polling on those problems. All this is going to be descripted in details with our reasonment behind every issues we faced.

## How to use this project

This section is here to explain how to run the project.

### Folders

* `headers` folder, contains the fonctions' signatures and their documentation (make sure to enable IntelliSense to get function documentation on hover)
* `results` folder which contains graphs for the evaluation of performance
* `scripts` folder will contains the python scripts to make graphs and calculation of the evaluation
* `src` folder is where we put all our code, every task is separated in a single file with the name of the problem and the main file centralizes all the functions and is responsible for launching the threads for each problem.

### Makefile

We then have a makefile to compile and facilitate your navigation

the make file is compose of 13 comand:

make ph : run the phylosopher algoritm

make phts : run the phylosopher algoritm with the mutex using the test and set priciple

make phtts : run the phylosopher algoritm with the mutex using the test and test and set priciple

make pc : run the producteur consomateur algoritm

make pcts : run the producteur consomateur algoritm with the mutex using the test and set priciple

make pctts : run the producteur consomateur algoritm with the mutex using the test and test and set priciple

make le : run the reader writer (in french : lecteur ecrivain) algoritm

make lets : run the reader writer (in french : lecteur ecrivain) algoritmwith the mutex using the test and set priciple

make letts : run the reader writer (in french : lecteur ecrivain) algoritm with the mutex using the test and test and set priciple

make ts : run the test and set algoritm with basis concurence

make tts : run the test and set algoritm with basis concurence

for all the program above the output wil be locate in results an be name output.csv 

make graf: to plot all result that is locate in output.csv

make clean : remove all the file .o

| Command                        | What does it really do                                                                   | Default value of parameters |
| ------------------------------ | ---------------------------------------------------------------------------------------- | --------------------------- |
| `make philosophers N=...`    | Compile and execute of the philosophers' problem  with N philosphers                    | N=5                         |
| `make prodcons P=... C=...`  | Compile and execute the producers-consummers' problem with P producers and C consummers | P=5, C=5                    |
| `make readwrite R=... W=...` | Compile and execute the readers-writers' problem with R readers and W writers            | R=5, W=5                    |
| `make clean`                 | Clean all the object and compiled files                                                  |                             |
|                                |                                                                                          |                             |

We decided to make a single main file and compile everything from this main.

## Problème des philosophes

Le problème du philosophe met en lumière les difficultés de synchronisation liées à la programmation en parallèle. Pour résumé, on a N (e.g. 5) philosophes autour d'une table. Ils peuvent soit penser, soit manger. Mais pour manger, il faut 2 fourchettes. Or, entre 2 assiettes il n'y a qu'un couvert (e.g. 5 fourchettes à table). Il faut donc pour manger que la fourchette à la droite et à la gauche du philosophe soient libres : les fourchettes sont des ressources partagées (sémaphores) et le problème est de réguler l'accès à celles-ci pour que chaque philosophe puisse tout le temps alterner entre manger et penser.

Un premier problème apparait assez rapidement en analysant la situation. Si tous les philosophes décident d'abord de prendre chacun la fourchette du même côté de l'assiette alors chaque philosophe serait bloqué à attendre qu'un autre philosophe lâche une fourchette. En code, cette première version quelque peu naïve mènerait à un deadlock.

> **Deadlock :** *Etat d'un système qui ne peut plus évoluer.*

Si le problème est que chaque philosophe doive prendre 2 ressources et le faire :

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
## Problème des lecteurs-écrivains

Le problème peut être grossièrement résumé par la situation suivante : Il y a 2 types de processus : les lecteurs qui lisent uniquement l'information et peuvent simultanément avoir accès à la section critique sans problème. Les écrivains qui écrivent/modifient l'information et s'y voient imposer une exclusion mutuelle stricte.

Qui pourrait-on retrouver avec l'accès à la section critique :

- plusieurs lecteurs avec 0 écrivains,
- 0 lecteur avec 1 seul écrivain.

Lorsqu'un écrivain modifie la structure de données, gardons en tête que cette dernière n'est pas accessible à un lecteur car ceci entraverait la concurrence et ne donnerait pas un bon résulat.

On veut donc un accès **partagé** en lecture et un accès **exclusif** en écriture, une première esquisse de solution apparaît :

- il faut que le premier lecteur gagne l'accès avec un sémaphore pour que les prochains lecteurs puissent accéder à la structure de donnée tant qu'il reste au moins un lecteur. Il faut donc aussi garder une trace du nombre de lecteur en jeu,
- chaque rédacteur doit gagner l'accès avec un sémaphore.

# TO DO

* [ ] Maybe too much, but a simulation of philosophers problem ?
* [ ] Translate to english, pour l'intro et comment exécuter mais le reste c'est plus sympa à lire en français
* [ ] Illustrations for problems
* [ ] Finish how to execute
* [ ] Peux-etre afficher un premier pseudo code pour montrer la reflexion derrière la version finale
* [ ] Rappel sémaphore et mutex : Semaphore vs Mutex dans la partie philosphers
