# kurklu_lab1

# Introduction

Dans le cadre de notre cours de conception conjointe en GE5A a Polyteh Clermont, nous sommes amenées à mettre en pratique les connaissances théoriques acquises lors de TP. Ces travaux sont réalisés sur une carte Terasic DE10 - Lite basé sur un FPGA Altera MAX 10. Pour ce premier projet notre objectif et de se familiariser avec les outils vus en cours et d'implémenter un led chaser en utilisant des interruptions à l'aide des Led, des switches et des boutons présents sur la carte.


# Architecture
Voici l'architecture que j'ai réalisée sur paint :

[![Lab1-jpeg.jpg](https://i.postimg.cc/76V6y378/Lab1-jpeg.jpg)](https://postimg.cc/PpChW822)

J'ai tout d'abord repris les éléments afin de reconstruire mon system basic :
* Une clock
* Une RAM
* Un NIOS-2
* Un JTAG

Par la suite, j'ai ajouté les PIO afin de pouvoir gérer mes I/O :
* PIO sur 8 bits pour mes leds
* PIO sur 2 bits pour mes keys
* PIO sur 9 bits pour mes switches

Voici le système initialiser sur qsys :

[![Lab1-qsys.jpg](https://i.postimg.cc/y6LC91zT/Lab1-qsys.jpg)](https://postimg.cc/yW3GCzxJ)

J'ai ensuite créé mon fichier kurklu_lab1.vdh, réaliser le pin assignement compiler mon system sur quartus pour pouvoir passer à la partie software.

Mon objectif est de pouvoir réaliser le led chaser sur les leds. Activer et désactiver le led chaser a l'aide des interruptions sur les boutons et enfin gérer la vitesse avec des interruptions sur les switches. 

# Avancement

J'ai créé 3 fichier C led_chaser.c, led_chaser_polling.c et led_chaser_interrupt.c pour les différentes versions.

## led chaser simple
Afin d'implémenter le led chaser j'ai tout simplement réaliser dans une boucle, des shift de bit à gauche en partant de la led0 a la led7 puis des shift à droite de led7 a led0. À chaque écriture, j'ai réalisé un temps d'arrêt a l'aide de la fonction usleep(), qui va aussi me permettre de gérer la vitesse de mon led chaser dans l'étape de polling.

## led chaser polling
Pour la version avec polling, j'ai rajouté un switch case au début de ma boucle. Ce switch case permet de regarder les switches activés et modifier ensuite la variable time utiliser par la fonction usleep(). Cela permet d'augmenter ou de diminuer le temps d'attente entre chaque écriture donc modifier la vitesse.

## led chaser interruption
Pour la version avec interruption, j'ai mis en place mes différentes fonctions pour gérer les interruptions. key_interrupt() pour les keys et sw_interrupt() pour les switches. J'ai ensuite dans mon main, initialiser mes interruptions en indiquant les mask, les edge capture et l'enregistrement des interruptions. Dans la fonction key_interrupt(), on vient regarder le bouton appuyer. En fonction de ce bouton, on lance le led_chaser ou on le réinitialise en réinitialisant aussi les variables qui permet de le gérer. 


https://user-images.githubusercontent.com/24780090/211770355-d795e951-f325-4e74-9b45-989a813e43c5.mov


Dans la fonction sw_interrupt(), on vient d'abord lire le registre sur lequel est écrit les switches. Ensuite, je fais appel à ma fonction nombre_bits_a_1(), qui va me retourner le nombre de bit à 1 dans le registre. En fonction de ce nombre, je vais venir modifier ma variable time, afin de modifier la vitesse de mon led chaser.

https://user-images.githubusercontent.com/24780090/211770309-9cf0fed9-7302-426b-9a08-b7b0f3c441d1.mov


# Conclusion

J'ai réussi a términer le lab1 sans grande difictulté. C'est la premiere fois que je travail sur une vrai cible a l'aide de quartus. Ce premier tp ma permit de reprendre en main les different outil afin de travailler sur la partie hardware et la partie software. Le seul point ou j'ai perdu du tamps lors de ce tp a était les interruption. La syntaxe des fonction utiliser dans le cours me donner des warnings et ne fonctionner pas. En lisant la documentation fournit sur moddle je me suis rendu compte que ALT_ENHANCED_INTERRUPT_API_PRESENT etait défini dans mon fichier system.h. J'ai donc utiliser l'autre syntaxe pour definir les intrruption ce qui a fonctionner. 
