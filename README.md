# Multithreaded Applications Evaluation

The project is to analyze the overall impact of threads and POSIX's syncronizations (e.g. mutex and semaphores for the first part of the project then active waiting locks in the second part)

Ce projet a pour but d'analyser l'impact des threads et des primitives de synchronisation POSIX (mutex et sémaphores dans un premier temps, ainsi qu'avec des verrous avec attente active dans un second temps).

## Problème des philosophes

Le problème du philosophe met en lumière les difficultés liés à la programmation en parallèle. Pour résumé, on a N (e.g. 5) philosophes autour d'une table. Ils peuvent soit penser, soit manger. Mais pour manger, il faut 2 fourchettes. Or, entre 2 assiettes il n'y a qu'un couvert (e.g. 5 fourchettes à table). Il faut donc pour manger que la fourchette à la droite et à la gauche du philosophe soient libres : les fourchettes sont des ressources partagées et le problème est de réguler l'accès à celles=ci.

Un premier problème apparait assez rapidement en analysant la situation. Si tous les philosophes décident de d'abord prendre la fourchette du même côté de l'assiette alors chaque philosophe serait bloqué à attendre qu'un autre philosophe lâche une fourchette. En code, cette première version quelque peu naïve mènerait à un deadlock.

Si le problème est que chaque philosphe doive prendre 2 ressources et le faire :
- en 2 étapes,
- tous dans le même ordre,
- sans retour en arrière possible,
il suffirait de supprimer une de ces conditions pour éviter un deadlock.

Dans cette version, on a une situation binaire : un philosophe détient 0 ou 2 fourchettes mais jamais une seule. De plus, le dernier philosophe commence par prendre la fourchette de gauche tandis que les autres commencent par la fourchette de droite. Pourquoi cette deuxième condition ? Car il faut toujours garder en tête qu'un philosophe pourrait être trop lent et risquer de ne jamais avoir de fourchette disponible.