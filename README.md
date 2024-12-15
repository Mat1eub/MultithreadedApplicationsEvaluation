# Multithreaded Applications Evaluation

The main goal of this project is to analyze the overall impact of threads and tool for syncronizations. The project was articulated in 2 phases, we first coded 3 famous problems related to synchronization with mutex and semaphore from the POSIX library. Then for the second phase, we implemented our version of busy waiting synchronization using atomic exchange on those problems. All this is going to be descripted in details with our reasonment behind every issues we faced.

## How to use this project

This section is here to explain how to run the project.

You will need a python environment with matplotlib to display graphs.

### Folders

* `include` folder, contains headers with the fonctions' signatures and their documentation,
* `results` folder which contains data files, graphs from our execution and the python program we used to make those graphs (don't forget to change the path to `your_graphs` directory),
* `scripts` folder will contains the python scripts to make graphs and calculation of the evaluation,
* `src` folder is where we put all our code, you can inspect the code and see comments where we thought one would need a quick explanation for a better comprehension.

### Makefile

We then have some Makefile rules to facilitate your navigation.

- **`make`**
Compile and excecute all the problems. Show on 4 different graphs the performance of our synchronization tools.

- **`make valgrind`**
Perform a valgrind test on each problem.

- **`make clean`**
Delete all the objects and executable files generated.

#### Philosophers
- **`make philo`**
Compile and generate the executable for the Philosophers' problem with classic implementation.

- **`make philots`**
Same but with our semaphores and Test-and-Set (TS) mechanism.

- **`make philotts`**
Same but with Test-and-Test-and-Set (TTS) mechanism.

Usage of the Philosophers executable
```bash
./<philo_executable_name> <number_of_philosophers>
```

#### Producers & consummers

- **`make prodcons`**
Compile and generate the executable for the Producers and consummers' problem with classic implementation.

- **`make prodconsts`**
Same but with our semaphores and Test-and-Set (TS) mechanism.

- **`make prodconstts`**
Same but with Test-and-Test-and-Set (TTS) mechanism.

If you want to execute the problem, you can with:
```bash
./<prodcons_executable_name> <total_number_of_threads>
```
But it will by default seperate your total number given in 2. However, if you want to specify how many producers and how many consummers you want, you can with:
- **`make prodconsperso`**
- **`make prodconspersots`**
- **`make prodconspersotts`**
And executing with:
```bash
./<prodconsperso_executable_name> <number_of_producers> <number_of_consummers>
```
#### Readers & writers

- **`make readwrite`**
Compile and generate the executable for the Readers and writers' problem with classic implementation.

- **`make readwritets`**
Same but with our semaphores and Test-and-Set (TS) mechanism.

- **`make readwritetts`**
Same but with Test-and-Test-and-Set (TTS) mechanism.


If you want to see graphs only for one problem you can make those commands:
```bash
make test_philosophers
make test_prodcons
make test_readerswriters
```

We will now look in detail at all the problems and our reflexion behind our code. As this is not a substantial part of understanding the result of our work, we shall continue in French to make it easier to read and write. We will then switch back to English for the performance evaluation of the whole project and the conclusion.

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

On a remarqué, vous le verrez dans la section d'analyse de performances, qu'utiliser uniquement des sémaphores augmentait le temps d'exécution. Il est en fait important de prendre le temps de réfléchir aux différentes options entre sémaphores et mutex afin d'optimiser au mieux le temps d'exécution d'un problème de nos machines. Nous avons finalement opté pour une version impliquant 2 mutex et 1 sémaphore.

## Problème des producteurs-consommateurs

Ici, on a un **producteur** qui tente d'envoyer (produire) de l'information sur un *buffer* qu'un **consommateur** va consommer. Ce *buffer* qu'on modélise avec un tableau partagé contient 8 places dans lesquelles le producteur va devoir écrire son *identifiant* (ici, son numéro de 0 à P-1).

S'il y a au moins une case vide dans le tempon, le producteur va produire dans une case libre. Le consommateur lui doit attendre qu'une case soit remplie pour consommer. Il est alors convenu qu'on peut modéliser ces cases remplies et vides par 2 sémaphores (je vous renvoie sur la section des sémaphores pour une meilleure compréhension). 

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

## Les différents types de verrous

### POSIX locks

#### Sémaphore

Un sémaphore est avant tout une variable qui sera partagée entre les threads. C'est un entier qui ne peut prendre que des valeurs positives ou nulle.

Deux uniques opérations peuvent leur être appliquées (fonctions de la librairie POSIX):

- [sem_post(3)](https://man7.org/linux/man-pages/man3/sem_post.3.html): incrémente (déverouille) une fois le sémaphore,
- [sem_wait(3)](https://man7.org/linux/man-pages/man3/sem_wait.3.html): décrémente (verouille) une fois le sémaphore.

Donc un thread peut exécuter sem_wait(s) si s>0, sinon l'appel suspend le thread et il attend. Si un autre thread execute sem_post(s) (sur le même sémaphore s!) la valeur du sémaphore augmente de 1 et le thread qui attendait depuis tout à l'heure pourra bel et bien utiliser sem_wait(s) et avoir accès, généralement, à une section critique.

#### Performance des primitives POSIX sur ces problèmes de synchronisation

### Test-And-Set (TAS) lock

On remarque que toutes ces requêtes d'invaldiation du cache etc font rapidement baisser la performance du verrous. 
GRAPHE DE PERFORMANCE TAS

### Test and Test-And-Set (TTAS) lock

#### Comparaison des performances

## Conclusion 

Let's conclude in english 
# TO DO
