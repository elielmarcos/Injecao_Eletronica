/* 
 * File:   ldc.c
 * Author: Eliel Marcos
 *
 * Created on 21 de Outubro de 2018, 02:35
 * 
 * Rotinas do LCD 16x2
 * 
 * */

#include <pic18.h>
#include "lcd.h"
#include "delay.h"


//#define LCD_8BITS    // BUS MODULO 8 BITS (PORTD 0 - 7)
#define LCD_4BITS    // BUS MODULO 4 BITS (PORTD 4 - 7)

#define Back_Light    RD6               	   // Back Light
#define LCD_EN        RD5                	   // LCD Enable
#define LCD_RS        RD4               	   // LCD RS
#define LCD_D4        RD0                	   // LCD D4
#define LCD_D5        RD1               	   // LCD D5
#define LCD_D6        RD2                	   // LCD D6
#define LCD_D7        RD3               	   // LCD D7
#define	LCD_STROBE    ((LCD_EN = 1),(LCD_EN = 0))  // Pulso Enable LCD
#define BUS           PORTD			   // Porta D como Barramento de Dados LCD

// === LCD ===
bit RS=0;                               // RS do LCD, RW aterrado


// =============================================================
// =======================FUNÇÕES DO LCD========================
// =============================================================

// ======== Envio de Dados/Caracteres para o LCD  =========

void envia_dados_lcd(unsigned char dado) {
char nibbleL=0;
char nibbleH=0;

   LCD_RS = RS;                  // Seta o bit RS para instrução ou caractere
   Delay_Us(40);                // Aguarda 40 us para estabilizar o pino do LCD

////////////MODULO 8 BITS/////////////// 
#ifdef LCD_8BITS
   BUS = dado;                   // Dados no PORT D

   LCD_STROBE;                   // Gera um pulso de enable
#endif


////////////MODULO 4 BITS/////////////// 
#ifdef LCD_4BITS
   
LCD_D4 = (dado & 0b00010000) >> 4;
LCD_D5 = (dado & 0b00100000) >> 5;
LCD_D6 = (dado & 0b01000000) >> 6;
LCD_D7 = (dado & 0b10000000) >> 7;

LCD_STROBE;  

LCD_D4 = (dado & 0b00000001);
LCD_D5 = (dado & 0b00000010) >> 1;
LCD_D6 = (dado & 0b00000100) >> 2;
LCD_D7 = (dado & 0b00001000) >> 3; 

LCD_STROBE;
   
#endif


   Delay_Us(40);                 // Aguarda 40us para estabilizar o LCD
   return;

}

// ========== Envio de caractere para o LCD =============

void caracter_lcd(unsigned char c) {
   RS=1;
   envia_dados_lcd(c);      // envia caractere para o display
   return;                  // Retorna ao ponto de chamada da função
}

// =========== Envio de comando para o LCD ==============

void comando_lcd(unsigned char c) {
   RS=0;
   envia_dados_lcd(c);     // envia comando para o display
   return;                 // Retorna ao ponto de chamada da função
}

// =========== Envio de Texto/String para o LCD =========

void texto_lcd(const char * s)
{
    while(*s){caracter_lcd(*s++);}
    return;
}

// =========== Função para limpar o LCD =================

void limpa_lcd(void) {
   RS=0;
   envia_dados_lcd(0x01);      // Envia instrução para limpar o LCD
   Delay_Ms(2);                // Aguarda 2ms para estabilizar o LCD
   return;                     // Retorna ao ponto de chamada da função
}

// =========== Cursor Linha 1 ===========================

void linha1_lcd(void)
{
    comando_lcd(0x80);
    return;
}

// =========== Cursor Linha 2 ===========================

void linha2_lcd(void)
{
    comando_lcd(0xC0);
    return;
}

// =========== Posiciona o cursor na linha e coluna =====

void xy_lcd(unsigned char linha, unsigned char coluna){
	unsigned char endereco;
	endereco = linha;
	//Verificando a linha correspondente
	if (linha==1){
		endereco = 0x80;
	}
	if (linha==2){
		endereco = 0xC0;
	}
	//coluna
	endereco = endereco + coluna;
	comando_lcd(endereco);
}

// =========== Liga o cursor ============================

 void cursor_On(void) {
	comando_lcd(0x0E);
 }


// =========== Desliga o cursor =========================

 void cursor_Off(void) {
 	comando_lcd(0x0C);
 }


// =========== Inicializa LCD ===========================

void inicializa_lcd(void) {

   LCD_RS=0;                // Garante que o pino RS estão em 0
   LCD_EN=0;                // Garante que o pino ENABLE estão em 0

   Delay_Ms(50);            // Aguarda 50ms para estabilizar o LCD


////////////MODULO 8 BITS/////////////// 
#ifdef LCD_8BITS
   comando_lcd(0x38);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x38);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x06);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD
#endif


////////////MODULO 4 BITS///////////////  
#ifdef LCD_4BITS
   comando_lcd(0x03);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD  

   comando_lcd(0x03);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x03);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x02);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x28);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   comando_lcd(0x08);       // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   limpa_lcd();             // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   limpa_lcd();             // Envia comando para inicializar o display
   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD
#endif


   comando_lcd(0x0C);       // CURSOR HOME - Envia comando para zerar o contador de

   Delay_Ms(15);            // Aguarda 15ms para estabilizar o LCD

   limpa_lcd();             // Limpa LCD

   linha1_lcd();            // Coloca cursor na linha 1, primeiro digito


   return;                  // Retorna ao ponto de chamada da função
}


// =============================================================
// ============Grava Caracteres na CGRAM do LCD=================
// =============================================================

void Grava_CGRAM(void) {

comando_lcd(0x40);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x00);
caracter_lcd(0x00);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x10);
caracter_lcd(0x10);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x18);
caracter_lcd(0x18);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x1C);
caracter_lcd(0x1C);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x1E);
caracter_lcd(0x1E);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);

caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x1F);
caracter_lcd(0x00);
caracter_lcd(0x1F);
caracter_lcd(0x00);


   return;                  // Retorna ao ponto de chamada da função
}



// =============================================================
// ==============Grava Simbolos na CGRAM do LCD=================
// =============================================================

void Simbolos_lcd(unsigned int letra) {


// ã
if (letra == 'ã'){
comando_lcd(0x70);
caracter_lcd(0b00001010);
caracter_lcd(0b00010100);
caracter_lcd(0b00000000);
caracter_lcd(0b00001101);
caracter_lcd(0b00010011);
caracter_lcd(0b00010011);
caracter_lcd(0b00001101);
caracter_lcd(0b00000000);
}

// á
if (letra == 'á'){
comando_lcd(0x78);
caracter_lcd(0b00000010);
caracter_lcd(0b00000100);
caracter_lcd(0b00000000);
caracter_lcd(0b00001101);
caracter_lcd(0b00010011);
caracter_lcd(0b00010011);
caracter_lcd(0b00001101);
caracter_lcd(0b00000000);
}

// é
if (letra == 'é'){
comando_lcd(0x70);
caracter_lcd(0b00000010);
caracter_lcd(0b00000100);
caracter_lcd(0b00001110);
caracter_lcd(0b00010001);
caracter_lcd(0b00011111);
caracter_lcd(0b00010000);
caracter_lcd(0b00001110);
caracter_lcd(0b00000000);
}

// Ã
if (letra == 'Ã'){
comando_lcd(0x78);
caracter_lcd(0b00001010);
caracter_lcd(0b00010100);
caracter_lcd(0b00001110);
caracter_lcd(0b00010001);
caracter_lcd(0b00011111);
caracter_lcd(0b00010001);
caracter_lcd(0b00010001);
caracter_lcd(0b00000000);
}

// Á
if (letra == 'Á'){
comando_lcd(0x78);
caracter_lcd(0b00000010);
caracter_lcd(0b00000100);
caracter_lcd(0b00001110);
caracter_lcd(0b00010001);
caracter_lcd(0b00011111);
caracter_lcd(0b00010001);
caracter_lcd(0b00010001);
caracter_lcd(0b00000000);
}

// õ
if (letra == 'õ'){
comando_lcd(0x70);
caracter_lcd(0b00001010);
caracter_lcd(0b00010100);
caracter_lcd(0b00000000);
caracter_lcd(0b00001110);
caracter_lcd(0b00010001);
caracter_lcd(0b00010001);
caracter_lcd(0b00001110);
caracter_lcd(0b00000000);
}

// í
if (letra == 'í'){
comando_lcd(0x70);
caracter_lcd(0b00000010);
caracter_lcd(0b00000100);
caracter_lcd(0b00000000);
caracter_lcd(0b00001100);
caracter_lcd(0b00000100);
caracter_lcd(0b00000100);
caracter_lcd(0b00001110);
caracter_lcd(0b00000000);
}


// ^ flecha
if (letra == '^'){
comando_lcd(0x70);
caracter_lcd(0b00000000);
caracter_lcd(0b00000100);
caracter_lcd(0b00001110);
caracter_lcd(0b00011111);
caracter_lcd(0b00000100);
caracter_lcd(0b00000100);
caracter_lcd(0b00000100);
caracter_lcd(0b00000000);
}

// v flecha
if (letra == 'v'){
comando_lcd(0x78);
caracter_lcd(0b00000000);
caracter_lcd(0b00000100);
caracter_lcd(0b00000100);
caracter_lcd(0b00000100);
caracter_lcd(0b00011111);
caracter_lcd(0b00001110);
caracter_lcd(0b00000100);
caracter_lcd(0b00000000);
}


   return;                  // Retorna ao ponto de chamada da função
}




