/* 
 * File:   eeprom.c
 * Author: Eliel Marcos
 *
 * Created on 2 de Novembro de 2018, 12:02
 * 
 * Rotinas para EEPROM
 * 
 * */

#include <pic18.h>
#include "eeprom.h"



// ==== Lê Dado da EEPROM ====

unsigned char ler_eeprom(unsigned int address)
{
unsigned char DADO_EEPROM=0;

  EEADRH = (address >> 8);      // Seleciona o Endereço High da Memória
  EEADR  = (address & 0x00FF);  // Seleciona o Endereço Low da Memória
  EEPGD  = 0;                   // Configura o Acesso a EEPROM
  CFGS   = 0;                   // Configura o Acesso a EEPROM
  FREE   = 0;                   // Desabilita a Limpeza da Memória
  RD     = 1;                   // Inicia Leitura
  DADO_EEPROM = EEDATA;         // Captura o Dado da Memória 

return DADO_EEPROM;             // Retorna resultado

}


// ==== Escreda Dado na EEPROM ====

void escrever_eeprom(unsigned int address, unsigned char DADO_EEPROM)
{

  EEADRH = (address >> 8);      // Seleciona o Endereço High da Memória
  EEADR  = (address & 0x00FF);  // Seleciona o Endereço Low da Memória
  EEDATA = DADO_EEPROM;         // Dado a ser Gravado na Memória 
  EEPGD  = 0;                   // Configura o Acesso a EEPROM
  CFGS   = 0;                   // Configura o Acesso a EEPROM
  FREE   = 0;                   // Desabilita a Limpeza da Memória
  WREN   = 1;                   // Habilita Gravação
  GIE    = 0;                   // Desabilita Interrupção Geral Para Gravação da Memória (Necessário para não gerar erro na gravação)
  PEIE   = 0;                   // Desabilita Interrupção Periféricos Para Gravação da Memória (Necessário para não gerar erro na gravação)
  EECON2 = 0x55;                // Necessario Para Gravação
  EECON2 = 0xAA;                // Necessario Para Gravação 
  WR     = 1;                   // Inicia Gravação
  while(WR);                    // Aguarda Término da Gravação
  GIE    = 1;                   // Habilita Interrupção Geral
  PEIE   = 1;                   // Habilita Interrupção Periféricos
  WREN   = 0;                   // Desabilita Gravação

return;

}