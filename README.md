# kurklu_lab1

# Introduction

Dans le cadre de notre cours de conception conjointe en GE5A a Polyteh Clermont, nous sommes amenées à mettre en pratique les connaissances théoriques acquise lors de TP. Ces travaux sont réalisés sur une carte Terasic DE10 - Lite basé sur un FPGA Altera MAX 10. Pour ce premier projet notre objectif et de se refamiliariser avec les outils vus en cours et d'implémenter un led chaser en utilisant des interruptions à l'aide des Led, des switches et des boutons présents sur la carte.


# Architecture
Voici l'architecture que j'ai réaliser sur paint :

[![Lab1-jpeg.jpg](https://i.postimg.cc/76V6y378/Lab1-jpeg.jpg)](https://postimg.cc/PpChW822)

J'ai tout d'abord repris les element afin de reconstruire mon system basic. Une clock, une Ram, un nios2 et un jtag comme vue en cours.
Par la suite j'ai ajouté les PIO afin de pouvoir gere mes I/O.
* PIO sur 8 bits pour mes led
* PIO sur 2 bits pour mes keys
* PIO sur 9 bits pour mes switches

Voici le systme initialiser sur qsys :

[![Lab1-qsys.jpg](https://i.postimg.cc/y6LC91zT/Lab1-qsys.jpg)](https://postimg.cc/yW3GCzxJ)

J'ai ensuite crée mon fichier kurklu_lab1.vdh, compiler mon code, generere mon BSP et makefile afin de passer a la partie software

Mon objectif est de pouvoir réaliser le led chaser sur les leds. Activer et desactiver le led chaser a l'aide des interruption sur les boutons et enfin gere la vitesse avec des interruption sur les switches. 

# Avancement

J'ai crée 3 fichier C led_chaser.c, led_chaser_polling.c et led_chaser_interrupt.c  pour les differente version.

## led chaser simple
Afin d'implementer le led chaser j'ai tout simplement réaliser dans une boucle, des shift de bit a gauche en partant de la led0 at la led7 puis des shift a droite de led7 a led0. A chaque ecriture j'ai realiser un temps d'arret a l'aide de la fonction usleep() qui va aussi me permetre de gere la vitesse de mon led cahser dans l'etape de polling.

## led chaser polling
Pour la version avec polling j'ai rajouter un switch case au debut de ma boucle. Se switch case permet de regarder les switch activé et modifier ensuite la variable time utiliser par la fonction usleep(). Cela permet d'augmenter ou diminuer le temps d'attente entre chaque ecriture donc modifier la vitesse.

## led chaser interruption
Pour la version avec interruption j'ai mit en place mes differente fonctions pour gere les interuptions. key_interrupt() pour les keys et sw_interrupt() pour les switches. J'ai ensuite dans mon main, intialiser mes interruption en indiquant les mask, les edge capture et l'enregistrement des interruptions. Dans la fonction key_interrupt() on vien regarder le bouton appuyer en fonction de ce bouton on lance le led_chaser ou on le renitialise en renitialisant aussi les varible qui permet de le gerer. 



https://user-images.githubusercontent.com/24780090/211770355-d795e951-f325-4e74-9b45-989a813e43c5.mov



Dans la fonction sw_interrupt() on vien d'abord lire le registe sur lequel est ecrit les switches. Ensuite je fait appel a ma fonction nombre_bits_a_1() qui va me retourne le nombre de bit a 1 dans le registe. En fonction de ce nombre je vais venir modifier ma variable time afin de modifier la vitesse de mon led chaser.



https://user-images.githubusercontent.com/24780090/211770309-9cf0fed9-7302-426b-9a08-b7b0f3c441d1.mov



Le lab1 est alors terminée.


# Conclusion
