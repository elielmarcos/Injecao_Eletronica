/* 
 * File:   teclado.c
 * Author: Eliel Marcos
 *
 * Created on 2 de Novembro de 2018, 12:33
 * 
 * Rotinas do TECLADO
 * 
 * */

#include <pic18.h>
#include "teclado.h"
#include "beep.h"


#define Botao_1         !RB4     // Entrada Botão 1 (INC)
#define Botao_2         !RB5     // Entrada Botão 2 (DEC)
#define Botao_3         !RB6     // Entrada Botão 3 (CNL)
#define Botao_4         !RB7     // Entrada Botão 4 (ENT)



bit old_B1=0;          		// guarda ultimo valor de Botao_1
bit old_B2=0;         		// guarda ultimo valor de Botao_2
bit old_B3=0;          		// guarda ultimo valor de Botao_3
bit old_B4=0;          		// guarda ultimo valor de Botao_4

unsigned char TIMER_BOTAO_AGUARDA1=0;
unsigned char TIMER_BOTAO_ACIONA1=0;
unsigned char TIMER_BOTAO_AGUARDA2=0;
unsigned char TIMER_BOTAO_ACIONA2=0;
unsigned char TIMER_BOTAO_AGUARDA3=0;
unsigned char TIMER_BOTAO_ACIONA3=0;
unsigned char TIMER_BOTAO_AGUARDA4=0;
unsigned char TIMER_BOTAO_ACIONA4=0;


// =============================================================
// ==========================BOTÕES=============================
// =============================================================

// ==== Botão Para Cima ===
bit Botao_INC(void)
{

   if ( (Botao_1 && (!old_B1)) || ((!Botao_1) && old_B1) ){   // testa se a entrada mudou de valor
       if ( Botao_1 && (!old_B1) ) {                        // Se mudou e esta apertado
        old_B1 = Botao_1;
        Beep_Simples();
        return(1);                                         // Retorna Verdadeiro
        }
        old_B1 = Botao_1;                                  // guarda "novo valor antigo"
       }
  return(0);                                               // Se não, retorna Falso

}

// ==== Botão Para Baixo ===
bit Botao_DEC(void)
{

   if ( (Botao_2 && (!old_B2)) || ((!Botao_2) && old_B2) ){   // testa se a entrada mudou de valor
       if ( Botao_2 && (!old_B2) ) {                        // Se mudou e esta apertado
        old_B2 = Botao_2;
        Beep_Simples();
        return(1);                                         // Retorna Verdadeiro
        }
        old_B2 = Botao_2;                                  // guarda "novo valor antigo"
       }
  return(0);                                               // Se não, retorna Falso

}

// ==== Botão Para Esquerda ===
bit Botao_CNL(void)
{

   if ( (Botao_3 && (!old_B3)) || ((!Botao_3) && old_B3) ){   // testa se a entrada mudou de valor
       if ( Botao_3 && (!old_B3) ) {                        // Se mudou e esta apertado
        old_B3 = Botao_3;
        Beep_Simples();
        return(1);                                         // Retorna Verdadeiro
        }
        old_B3 = Botao_3;                                  // guarda "novo valor antigo"
       }
  return(0);                                               // Se não, retorna Falso

}

// ==== Botão Para Direita ===
bit Botao_ENT(void)
{

   if ( (Botao_4 && (!old_B4)) || ((!Botao_4) && old_B4) ){   // testa se a entrada mudou de valor
       if ( Botao_4 && (!old_B4) ) {                        // Se mudou e esta apertado
        old_B4 = Botao_4;
        Beep_Simples();
        return(1);                                         // Retorna Verdadeiro
        }
        old_B4 = Botao_4;                                  // guarda "novo valor antigo"
       }
  return(0);                                               // Se não, retorna Falso

}



// ==== Botão Para Cima Automatico ====
bit Botao_INC_Auto(void)
{

   if (!Botao_1) {TIMER_BOTAO_AGUARDA1=0; TIMER_BOTAO_ACIONA1=0; }

   if (Botao_1)  { if (TIMER_BOTAO_AGUARDA1!=200) {TIMER_BOTAO_AGUARDA1++;}
                   else{ if (TIMER_BOTAO_ACIONA1!=2) {TIMER_BOTAO_ACIONA1++;}
                   else{TIMER_BOTAO_ACIONA1=0; Beep_Simples(); return(1);} }}

  return(0);
}


// ==== Botão Para Baixo Automatico ====
bit Botao_DEC_Auto(void)
{

   if (!Botao_2) {TIMER_BOTAO_AGUARDA2=0; TIMER_BOTAO_ACIONA2=0; }

   if (Botao_2)  { if (TIMER_BOTAO_AGUARDA2!=200) {TIMER_BOTAO_AGUARDA2++;}
                   else{ if (TIMER_BOTAO_ACIONA2!=2) {TIMER_BOTAO_ACIONA2++;}
                   else{TIMER_BOTAO_ACIONA2=0; Beep_Simples(); return(1);} }}

  return(0);
}



// ==== Botão Para Esquerda Automatico ====
bit Botao_CNL_Auto(void)
{

   if (!Botao_3) {TIMER_BOTAO_AGUARDA3=0; TIMER_BOTAO_ACIONA3=0; }

   if (Botao_3)  { if (TIMER_BOTAO_AGUARDA3!=200) {TIMER_BOTAO_AGUARDA3++;}
                   else{ if (TIMER_BOTAO_ACIONA3!=2) {TIMER_BOTAO_ACIONA3++;}
                   else{TIMER_BOTAO_ACIONA3=0; Beep_Simples(); return(1);} }}

  return(0);
}



// ==== Botão Para Direita Automatico ====
bit Botao_ENT_Auto(void)
{

   if (!Botao_4) {TIMER_BOTAO_AGUARDA4=0; TIMER_BOTAO_ACIONA4=0; }

   if (Botao_4)  { if (TIMER_BOTAO_AGUARDA4!=200) {TIMER_BOTAO_AGUARDA4++;}
                   else{ if (TIMER_BOTAO_ACIONA4!=2) {TIMER_BOTAO_ACIONA4++;}
                   else{TIMER_BOTAO_ACIONA4=0; Beep_Simples(); return(1);} }}

  return(0);
}

