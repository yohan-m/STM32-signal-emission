#include "stm_regs.h" 
/******************************************************************************
* File Name          : ADC.h
* Author             : T Rocacher
* Version            : revu 7/09/2011
* Date               : 01/03/2011
* Description        : Module qui configure les ADC 12 bits
*                     
*******************************************************************************/


#ifndef _ADC_H__
#define _ADC_H__

//=======================================================================================
// Rappel sur les ressources 
//
//  - 2ADC 16 canaux, 12 bits
//  - Les broches :
//		- ADC_In0  PA0
//		- ADC_In1	PA1
//		- ADC_In2	PA2
//		- ADC_In3	PA3
//		- ADC_In4	PA4
//		- ADC_In5 	PA5
//		- ADC_In6	PA6
//		- ADC_In7	PA7
//		- ADC_In8	PB0
//		- ADC_In9	PB1
//		- ADC_In10	PC0
//		- ADC_In11	PC1
//		- ADC_In12	PC2
//		- ADC_In13	PC3
//		- ADC_In14	PC4
//		- ADC_In15	PC5
//
// 	-  ADCck Maxi = 14MHz
//	
//=======================================================================================



// alignement des data, quelque soit le mode
#define ALIGN_DROITE_16_0(ADC) ADC->CR2=ADC->CR2&~(ADC_ALIGN)
#define ALIGN_GAUCHE_1_15(ADC) ADC->CR2=ADC->CR2|(ADC_ALIGN)


//=======================================================================================
// ADC en mode basique, single conversion
//=======================================================================================

//_______________________________________________________________________________

float Init_ADC_Single_Conv(ADC_TypeDef * ADC, float Duree_Ech_us, char Voie_ADC);
//_______________________________________________________________________________
/*
Initialise l'ADC en mode single conversion, 
une seule voie. Le temps pass� en param�tre est la dur�e d'�chantillonnage. 
La fonction renvoie un float qui est la dur�e exacte, imm�diatement  
sup�rieure � celle sp�cifi�e (d�pend du choix des prescaler).
L'ADC est on, pr�t � fonctionner. Tous les canaux sont param�tr�s 
avec la m�me dur�e d'�chantillonnage.

ADC_TypeDef *ADC : ADC1 ou ADC2
Float Duree_Ech_us: Dur�e d'�chantillonnage exprim�e en us.
Char Voie_ADC: Pr�cise la voie de l'ADC	 

Exemple :
Init_ADC_Single_Conv(ADC1, 0.0,3);
//L'ADC1 est r�gl� avec un temps d'acquisition nul, et orient� sur la voie 3.
*/
//_______________________________________________________________________________



//_______________________________________________________________________________

void Lance_ADC(ADC_TypeDef * ADC, char Voie_ADC);
//_______________________________________________________________________________
/* 
Lance l'ADC tout simplement sur la voie sp�cifi�e
Exemple :
Lance_ADC(ADC1, 3);	Lance une conversion de l'ADC1 sur la voie 3. Le r�sultat
est stock�e dans un registre interne
*/
//_______________________________________________________________________________





//_______________________________________________________________________________

vu16 Scrute_Fin_Conv_ADC(ADC_TypeDef * ADC);
//_______________________________________________________________________________
/*
Attend que la conversion se finisse en scrutation (EOC) et renvoie la donn�e
Exemple :
Lance_ADC(ADC1, 3);
Resultat = Scrute_Fin_Conv_ADC(ADC1);
// La variable Resultat contiendra la valeur de l'ADC � la fin de la conversion

*/
//_______________________________________________________________________________




//_______________________________________________________________________________

vu16 Acquiert_ADC_Single_Conv(ADC_TypeDef * ADC, char Voie_ADC);
//_______________________________________________________________________________
/*
Lance l'ADC, pour une conversion. Attend que la conversion se finisse 
en scrutation. Associe en fait les deux fonctions pr�c�dentes
Exemple :
Resultat = Acquiert_ADC_Single_Conv(ADC1, 3);
// La variable Resultat contiendra la valeur de l'ADC � la fin de la conversion	du
canal 3
*/
//_______________________________________________________________________________






//_______________________________________________________________________________

#define Res_ADC(ADC)  ADC->DR;
/*
permet de lire le registre de donn�e
*/
//_______________________________________________________________________________







//=======================================================================================
// ADC en interruption
//=======================================================================================

//_______________________________________________________________________________

void Configure_IT_ADC_EOC(ADC_TypeDef * ADC, char Prio, void (*IT_function) (void));
//_______________________________________________________________________________


/* Configure l'ADC de mani�re � rentrer en interruption lors de 
la fin de conversion. Le nom de la fonction est pass� en param�tre 
ainsi que la priorit� d'interruption associ�e.
Voir fonction  Init_ADC_Trig_Timer pour les options de compilation de cette fonction.

Exemple :
Configure_IT_ADC_EOC(ADC1, 1, IT_ADC);
// Provoque une interruption de priorit� 1, d�s que l'ADC a termin� sa conversion.
La fonction IT_ADC est alors lanc�e.
*/
//_______________________________________________________________________________


//=======================================================================================
// ADC en d�marrage sur d�bordement timer (lancement automatique, mat�rielle)
// N�cessite dont un Timer associ� pour trigger l'ADC.
//=======================================================================================


//_______________________________________________________________________________

#define  TIMER_ADC_EN_MODE_TOGGLE
/*
Option de compilation
- si d�fini, alors le trig de l'ADC se fera en mode toggle (un cycle sur deux
du timer d�clenche l'IT via OC1ref)
- sinon, le trig se fait � chaque cycle timer, mais alors dans l'IT ADC, OC1ref
est remis � 0 (g�r� par soft ds le handler ADC, le user n'a pas � s'en soucier)
*/
//_______________________________________________________________________________


//_______________________________________________________________________________

char Init_ADC_Trig_Timer(ADC_TypeDef * ADC, float Duree_Ech_us,char Source, char Voie_ADC);
//_______________________________________________________________________________

/*
Configure l'ADC de mani�re � ce qu'il soit d�clench� par un timer directement. 
Les sources sont multiples et limit�es � celles propos�es dans la liste (ci-dessous).
Cette fonction appelle  Init_ADC_Single_Conv.

Deux options possibles  (option de compilation):
- le timer active sa sortie Ocref en toggle : chaque d�bordement inverse 
la sortie et donc l'ADC est lanc� un d�bordement sur deux. Pour cela d�finir 
TIMER_ADC_EN_MODE_TOGGLE 
- si cette definition est mise en commentaire le timer fait passer Ocref � 1, 
et c'est dans l'interruption ADC que Ocref est mis � 0. Cela prend un peu de 
tps dans l'IT ADC.
NB: peut sans doute �tre am�lior� en pla�ant Ocref en PWM....
a voir pour une prochaine mise � jour.

Liste des sources
  - Sources de trig possible :
      -  0  TIM1_CC1 event
      -  1  TIM1_CC2 event
      -  2  TIM1_CC3 event
      -  3  TIM2_CC2 event
      -  5  TIM4_CC4 event
   NB, d'autres sources sont pr�vu par le constructeur, mais non
   utilis�s dans cette routine
*/

// Les sources de d�clenchement :
#define TIM1_CC1 0
#define TIM1_CC2 1
#define TIM1_CC3 2
#define TIM2_CC2 3
#define TIM4_CC4 5

//_______________________________________________________________________________





//=======================================================================================
// ADC en DMA
//=======================================================================================

float Init_ADC1_DMA(char Nb_Canaux, char Seq_Canaux[], float Duree_Ech_us);
/*
- Nb_Canaux : de 1 � 16, c'est le nombre de canaux scann�s
- Seq_Canaux[] Table de s�quence qui doit avoir la taille Nb_Canaux. Rlle contient
l'ordre d'�chantillonnage des diverses voies
- Seq_Canaux[0] = 0 � 15 c'est le rang du scan pour la voie 0
- Seq_Canaux[n] = 0 � 15 c'est le rang du scan pour la voie n
- T_samp_us : Temps de fermeture de l'IT (echantillonnage de la capa ADC) en �s
- Freq_ADC_kHz : fr�quence d'attaque de l'ADC en MHz, maxi 14 MHz
- La fonction renvoie la valeur recalcul�e de la p�riode d'�chantillonnage Te en us
*/

vu16 ADC_Lire_DMA(int Voie);

/*
- Voie de 0 � 15 num�ro de la voie ADC � lire
- Attention Voie n'est pas la voie ADC, c'est le rang de la table DMA.
Quelque soit les canaux ADC, si par exemple on en choisit 6, si on veut lire la premi�re valeur sampl�e, on indiquera Voie = 0, pour la derni�re Voie = 5.

Exemple d'appli user :
Seq_Canaux[3]={1,6,4}; // 1-6-4-1-6-4-1-6-4-....
Init_ADC1_DMA( 3,Seq_Canaux,2.0);
val = ADC_Lire_DMA[1] ; (canal 6 de l'ADC1)
*/


#endif
