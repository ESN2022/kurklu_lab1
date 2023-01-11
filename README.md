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
