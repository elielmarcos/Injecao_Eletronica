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



// ==== L� Dado da EEPROM ====

unsigned char ler_eeprom(unsigned int address)
{
unsigned char DADO_EEPROM=0;

  EEADRH = (address >> 8);      // Seleciona o Endere�o High da Mem�ria
  EEADR  = (address & 0x00FF);  // Seleciona o Endere�o Low da Mem�ria
  EEPGD  = 0;                   // Configura o Acesso a EEPROM
  CFGS   = 0;                   // Configura o Acesso a EEPROM
  FREE   = 0;                   // Desabilita a Limpeza da Mem�ria
  RD     = 1;                   // Inicia Leitura
  DADO_EEPROM = EEDATA;         // Captura o Dado da Mem�ria 

return DADO_EEPROM;             // Retorna resultado

}


// ==== Escreda Dado na EEPROM ====

void escrever_eeprom(unsigned int address, unsigned char DADO_EEPROM)
{

  EEADRH = (address >> 8);      // Seleciona o Endere�o High da Mem�ria
  EEADR  = (address & 0x00FF);  // Seleciona o Endere�o Low da Mem�ria
  EEDATA = DADO_EEPROM;         // Dado a ser Gravado na Mem�ria 
  EEPGD  = 0;                   // Configura o Acesso a EEPROM
  CFGS   = 0;                   // Configura o Acesso a EEPROM
  FREE   = 0;                   // Desabilita a Limpeza da Mem�ria
  WREN   = 1;                   // Habilita Grava��o
  GIE    = 0;                   // Desabilita Interrup��o Geral Para Grava��o da Mem�ria (Necess�rio para n�o gerar erro na grava��o)
  PEIE   = 0;                   // Desabilita Interrup��o Perif�ricos Para Grava��o da Mem�ria (Necess�rio para n�o gerar erro na grava��o)
  EECON2 = 0x55;                // Necessario Para Grava��o
  EECON2 = 0xAA;                // Necessario Para Grava��o 
  WR     = 1;                   // Inicia Grava��o
  while(WR);                    // Aguarda T�rmino da Grava��o
  GIE    = 1;                   // Habilita Interrup��o Geral
  PEIE   = 1;                   // Habilita Interrup��o Perif�ricos
  WREN   = 0;                   // Desabilita Grava��o

return;

}