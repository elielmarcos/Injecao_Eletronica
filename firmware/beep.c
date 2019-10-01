/* 
 * File:   beep.c
 * Author: Eliel Marcos
 *
 * Created on 2 de Novembro de 2018, 12:38
 * 
 * Rotinas do BEEP
 * 
 * */

#include <pic18.h>
#include "beep.h"
#include "delay.h"


#define BEEP       ((RD7 = 1),(Delay_Us(270)),(RD7 = 0),(Delay_Us(270)))  // Saida para Acionar Beep, gera um pulso


// =============================================================
// ============================BEEP=============================
// =============================================================

void Beep_Simples(void)
{
    char c;
    for (c=0;c<50;c++)
        BEEP; 

return;

}

void Beep_Duplo(void)
{
    char c;
    
    Delay_Ms(50);	
           
    for (c=0;c<30;c++)
        BEEP;
    
    Delay_Ms(30);
    
    for (c=0;c<30;c++)
        BEEP;

return;

}


void Beep_Alerta(void)
{
    char c;
    
    Delay_Ms(100);	
           
    for (c=0;c<30;c++)
        BEEP;
    
    Delay_Ms(30);
    
    for (c=0;c<30;c++)
        BEEP;
    
    Delay_Ms(30);
    
    for (c=0;c<30;c++)
        BEEP;

return;

}
