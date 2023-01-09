#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"

//Signatures fonctions
static void key_interrupt(void *Context);
void led_chaser();


//Variables globaux
int choice = 0;
int key;
int time = 500000;
int addr1;
int addr2;

int main(){
	// Variable pour debug
	int mask;
	
	alt_printf("In main start\n");
	
	//Lit le mask des boutons
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE);
	alt_printf("MASK = %x\n",mask);
	
	// applique un mask 0b11 afin d'activer les boutons
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE,0b11);
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE);
	alt_printf("MASK = %x\n",mask);
	
	// active la detection des boutons
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE,0b11);
	
	//Création de l'interruption
	if(alt_ic_isr_register(BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,BUTTONS_IRQ,key_interrupt,NULL,NULL) != 0){
		alt_printf("Erreur creation interruption\n");
	}
	
	//Led chaser
	while(1){
		switch(choice){
			case 0:
				break;
			case 1:
				addr1 = 0x01;
				addr2 = 0x80;
				led_chaser();
				break;
		}
	}
}

//Fonction pour gere l'interruption
static void key_interrupt(void *Context){
	
	alt_printf("INTERRUPT\n");
	// On vérifier le bouton 
	key = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
	switch(key){
		case 0b01: // On arrete le led_chaser on remet les led a 0
			choice = 0;
			IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,0x00);
			addr1 = 0x80;
			addr2 = 0x01;
			alt_printf("%x\n",key);
			break;
		case 0b10:// On lance le led_chaser
			choice = 1;
			alt_printf("%x\n",key);
			break;
		default:
			choice = 0;
			break;
		}

	//Reset la detection des boutons
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE,0b11);
}


//fonction pour gere le led_chaser
void led_chaser(){
	
	IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,addr1);
	usleep(time);
	while(choice == 1){
		while(addr1 != 0x80){
			addr1 = addr1<<1;
			IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,addr1);
			usleep(time);
		}
		while(addr2 != 0x01){
			addr2 = addr2>>1;
			IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,addr2);
			usleep(time);
		}
		addr1 = 0x01;
		addr2 = 0x80;
	}
}

