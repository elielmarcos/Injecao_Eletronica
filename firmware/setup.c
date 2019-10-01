/* 
 * File:   setup.c
 * Author: Eliel Marcos
 *
 * Created on 21 de Outubro de 2018, 02:18
 * 
 * Configurações do PIC18F4620
 * 
 * */


#include <pic18.h>
#include "setup.h"

void SETUP(void){

T0CON = 0x00;
INTCON = 0x00;
CMCON |= 0x07;
RBPU = 0;

PORTA=0x00;
PORTB=0x00;
PORTC=0x00;
PORTD=0x00;
PORTE=0x00;

LATA=0x00;
LATB=0x00;
LATC=0x00;
LATD=0x00;
LATE=0x00;

// 1 entrada | 0 saida

TRISA=0b00111111;
TRISB=0b11110001;
TRISC=0b00000000;
TRISD=0b00000000;
TRISE=0b1111;

PORTA=0x00;
PORTB=0x00;
PORTC=0x00;
PORTD=0x00;
PORTE=0x00;

LATA=0x00;
LATB=0x00;
LATC=0x00;
LATD=0x00;
LATE=0x00;

  GIE = 0;		// Desabilita Interrupção Geral (IPEN=1, Habilita Interrupção de Alta Prioridade)
  PEIE =0;		// Desabilita Interrupção Periféricos (IPEN=1, Habilita Interrupção de Baixa Prioridade)


// ===== CONFIGURA TIMER 0 =====

  T08BIT 		= 0; // 16bits
  T0CS 			= 0; // clock interno
  T0SE 			= 0; // L to H
  PSA			= 0; // Com prescaler
  T0PS2 		= 0; // prescaler 1:2
  T0PS1	 		= 0; // prescaler 1:2
  T0PS0 		= 0; // prescaler 1:2    
    // 10ms = 50000 (PRECALER 1:2) -> 65536 - 50000 = 15356 -> 0x3CB0
  TMR0H 		= 0x3C; // 8bits + significativos
  TMR0L		    = 0xB0; // 8bits - significativos
  TMR0IE 		= 1; // interrupção habilitada 
  TMR0IF        = 0; // flag da interrupção timer0
  TMR0ON 		= 0; // timer0 OFF

// ==============================



// ===== CONFIGURA TIMER 1 =====

  T1RD16        = 1; // 16bits
  T1OSCEN       = 0; // timer1 oscilador desabilitado
  TMR1CS        = 0; // clock interno
  T1CKPS1       = 1; // prescaler 1:8
  T1CKPS0       = 1; // prescaler 1:8
  TMR1H         = 0; // 8bits + significativos
  TMR1L         = 0; // 8bits - significativos
  TMR1IE        = 1; // interrupção habilitada
  TMR1IF        = 0; // flag da interrupção timer1
  TMR1ON        = 0; // timer1 OFF 
// ==============================




// ===== CONFIGURA TIMER 2 =====

  T2OUTPS3  = 0;
  T2OUTPS2  = 1;
  T2OUTPS1  = 0;
  T2OUTPS0  = 0;

  T2CKPS1   = 0;
  T2CKPS0   = 1;

  TMR2      = 0;
  PR2       = 0xFF;
  TMR2ON    = 0;
  TMR2IE    = 0;
  TMR2IF    = 0;


// ==============================



// ===== CONFIGURA TIMER 3 =====

  T3RD16        = 1; // 16bits
  TMR3CS        = 0; // clock interno
  T3CKPS1       = 1; // prescaler  1:4
  T3CKPS0       = 0; // prescaler  1:4
  TMR3H         = 0; // 8bits + significativos
  TMR3L         = 0; // 8bits - significativos
  T3CCP2        = 1;
  T3CCP1        = 1;
  TMR3IF        = 0; // flag da interrupção timer3 
  TMR3IE        = 1; // interrupção habilitada
  TMR3ON        = 0; // timer3 OFF 
 
// ==============================


// ===== CONFIGURA A/D =====

ADCON0 = 0b00000001;  // CH0 A/D
ADCON1 = 0b00000111;  // VREF+/- Desabilitado, e Analógico de AN0 a AN7
ADCON2 = 0b10101010;  // Justificado a Direita, A/D Aquisição 12TAD, Clock Converção FOSC/32

ADIF = 0;             // Flag de Interrupção de Final de Conversão
ADIE = 0;             // Desabilita Interrupção por A/D
// ==============================



// ===== CONFIGURA INTERRUPÇÃO EXTERNA INT0 =====
  INTEDG0=0;			 // interrupção por borda de subida do RB0
  INT0IE=1;              // interrupção habilitada RB0
  INT0IF=0;              // INT0 Interrupt Flag
// ==============================


// ===== CONFIGURA INTERRUPÇÃO EXTERNA INT1 =====
  INT1IP=0;              // INT1 External Interrupt Priority bit (High priority)
  INTEDG1=1;			 // External Interrupt 1 Edge Select bit (Interrupt on rising edge)
  INT1IE=0;              // INT1 External Interrupt Enable bit (Enables the INT2 external interrupt)
  INT1IF=0;              // INT1 Interrupt Flag
// ==============================


// ===== CONFIGURA INTERRUPÇÃO EXTERNA INT2 =====
  INT2IP=0;              // INT2 External Interrupt Priority bit (High priority)
  INTEDG2=0;			 // External Interrupt 2 Edge Select bit (Interrupt on rising edge)/ 1= Inter. na Subida, 0= Inter. na Descida.
  INT2IE=0;              // INT2 External Interrupt Enable bit (Enables the INT2 external interrupt)
  INT2IF=0;              // INT2 Interrupt Flag
// ==============================



// ===== CONFIGURA INTERRUPÇÃO ALTA/BAIXA PRIORIDADE =====
  
TMR0IP = 0; // interrupção do timer0 com baixa prioridade
TMR1IP = 1; // interrupção do timer1 com alta prioridade
TMR2IP = 0; // interrupção do timer2 com baixa prioridade
TMR3IP = 1; // interrupção do timer3 com alta prioridade
RBIP   = 0;
// INT0IP = 1; -> prioridade sempre alta RB0 (impossivel alterar))
INT1IP = 0;
INT2IP = 0;

IPEN   = 1;		// Habilita nível de Prioridade (Alta/Baixa)

GIE = 1;		// Habilita Interrupção Geral (IPEN=1, Habilita Interrupção de Alta Prioridade)
PEIE =1;		// Habilita Interrupção Periféricos (IPEN=1, Habilita Interrupção de Baixa Prioridade)

return;
}

