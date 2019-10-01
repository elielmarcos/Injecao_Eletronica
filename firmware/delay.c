/* 
 * File:   delay.c
 * Author: Eliel Marcos
 *
 * Created on 21 de Outubro de 2018, 11:48
 * 
 * Rotinas para Delay
 * 
 * */

#include "delay.h"



// =============================================================
// ============================DELAY'S==========================
// =============================================================

// =============== DelayUs ================

void Delay_Us(unsigned int Us)
{
  while(Us){Us--;}
  
return;
}

// =============== DelayMs ================

void Delay_Ms(unsigned int Ms)
{
  while(Ms){Ms--; Delay_Us(720);}
return;
}
