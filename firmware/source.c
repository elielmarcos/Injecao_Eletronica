/* 
 * File:   source.c
 * Author: Eliel Marcos
 *
 * Created on 21 de Outubro de 2018, 02:09
 * 
 * Projeto Final - Curso de Microcontroladores
 * 
 * Inje��o Eletr�nica - Firmware v1.0
 * 
 * PIC18F4620 (Crystal 10MHz, com PLL para 40MHz) 
 * 
 * Compilador utilizado Hi-Tech PICC
 * 
 * */

// =============================================================
// ==========================INCLUDES===========================
// =============================================================


#include <pic18.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "setup.h"
#include "delay.h"
#include "lcd.h"
#include "adc.h"
#include "eeprom.h"
#include "teclado.h"
#include "beep.h"




// =============================================================
// ======================CONFIGURA��ES==========================
// =============================================================

__CONFIG(1, FCMDIS & IESODIS & HSPLL);
__CONFIG(2, BORV43 & WDTEN & PWRTEN & WDTPS64);
__CONFIG(3, MCLREN & LPT1DIS & PBDIGITAL);
__CONFIG(4, XINSTDIS & DEBUGDIS & LVPDIS & STVRDIS);



// =============================================================
// ==========================EEPROM=============================
// =============================================================

__EEPROM_DATA(0x04,0x03,0xE8,0x00,0x00,0x5A,0x28,0x0A);
__EEPROM_DATA(0x01,0x59,0,0,0,0,0,0);



// =============================================================
// ==================VARIAVEIS / DEFINES========================
// =============================================================

#define i_BAT                   RA0     // Entrada Bateria
#define i_MAP                   RA1     // Entrada sensor MAP (Press�o absoluta)
#define i_TPS                   RA2     // Entrada throttle position sensor (acelerador)
#define i_SONDA                 RA3     // Entrada Sonda Lambda (sensor oxig�nio)
#define i_T_MOTOR               RA4     // Entrada sensor temperatura do Motor
#define i_T_AR                  RE0     // Entrada sensor temperatura do Ar
#define i_RPM                   RB0     // Entrada sinal RPM (Rota��o motor)
#define i_B1                    RB4     // Entrada Bot�o1 (incrementa)
#define i_B2                    RB5     // Entrada Bot�o2 (decrementa)
#define i_B3                    RB6     // Entrada Bot�o3 (cancelar)
#define i_B4                    RB7     // Entrada Bot�o4 (enter)
#define o_INJETOR               RC0     // Sa�da Injetor 
#define o_B_ELET_COMB           RC1     // Sa�da Bomba El�trica de Combust�vel
#define o_VENTILADOR            RC2     // Sa�da Ventilador (resfriamento do motor)
#define o_BEEP                  RD7     // Sa�da Buzzer
 

#define MEDIA_MOVEL             50      // Valor da janela para m�dia m�vel

#define TEMPO_B_ELET_COMB       5       // Tempo para desativar Bomba El�trica de Comb.

#define GASOLINA                0       // Tipo de combust�vel
#define ALCOOL                  1       // Tipo de combust�vel

#define AGUA                    0       // Tipo de resfriamento do Motor
#define AR                      1       // Tipo de resfriamento do Motor

#define TEMP_HISTERESE          2       // Temperatura de histerese para desligar o ventilador

#define ESTEQ_GASOLINA          14.70   // Raz�o estequiom�trica da gasolina
#define ESTEQ_ALCOOL            9.00    // Raz�o estequiom�trica do alcool
#define RO_GASOLINA             0.75    // RO da gasolina (densidade)
#define RO_ALCOOL               0.80    // RO do alcool (densidade)
#define n                       28.9645 // Massa molar do Ar
#define R                       8.31    // Constante Universal dos Gases

unsigned char MENU              = 1;    // Vari�vel que define o Menu do display

unsigned char INDICE_MM         = 0;    // Indice da m�dia m�vel dos sensores

unsigned int RPM                = 0;    // Vari�vel armazena Rota��o
unsigned int RPM_MAX            = 0;    // Vari�vel armazena Rota��o M�xima

unsigned int ZERO_MAP           = 0;    // Vari�vel armazena Press�o absoluta Inicial
unsigned int MAP                = 0;    // Vari�vel armazena Press�o absoluta
unsigned int MEDIA_MAP          = 0;    // Vari�vel armazena Press�o m�dia absoluta
unsigned int MAP_MIN            = 0;    // Vari�vel armazena Press�o absoluta M�nima
unsigned int MM_MAP[MEDIA_MOVEL];       // Vetor m�dia m�vel Press�o absoluta
unsigned int MAP_ANTERIOR       = 0;    // Vari�vel armazena valor passado da Press�o absoluta
  signed int MAP_DERIVADA       = 0;    // Vari�vel armazena deriva Press�o absoluta

unsigned int LAMBDA             = 0;    // Vari�vel armazena Lambda, sensor oxig�nio
unsigned int MEDIA_LAMBDA       = 0;    // Vari�vel armazena Lambda m�dia
unsigned int MM_LAMBDA[MEDIA_MOVEL];    // Vetor m�dia m�vel Lambda 
unsigned int LAMBDA_ANTERIOR    = 0;    // Vari�vel armazena valor passado da Lambda
unsigned int LAMBDA_SET_POINT   = 499;  // Vari�vel armazena valor alvo da Lambda
  signed int LAMBDA_DERIVADA    = 0;    // Vari�vel armazena deriva Lambda
  signed int LAMBDA_PROPORCAO   = 0;    // Vari�vel armazena proporcional Lambda
  signed int LAMBDA_INTEGRAL    = 0;    // Vari�vel armazena integral Lambda
        long LAMBDA_INTEG_ERRO  = 0;    // Vari�vel armazena soma dos erros Lambda
  signed int LAMBDA_ERRO        = 0;    // Vari�vel armazena erro Lambda
unsigned int LAMBDA_ERRO_MAX    = 30000;// Vari�vel armazena limite do erro m�ximo Lambda
         bit LAMBDA_INTEG_SIG   = 0;    // Vari�vel armazena sinal da integral Lambda (positiva ou negativa)

unsigned int TEMP_MOTOR         = 0;    // Vari�vel armazena Temperatura do Motor
unsigned int MEDIA_TEMP_MOTOR   = 0;    // Vari�vel armazena Temperatura m�dia do Motor
unsigned int TEMP_MOTOR_MAX     = 0;    // Vari�vel armazena Temperatura m�xima do Motor
unsigned int MM_TEMP_MOTOR[MEDIA_MOVEL];// Vetor m�dia m�vel Temperatura do Motor 

unsigned int TEMP_AR            = 0;    // Vari�vel armazena Temperatura do Ar
unsigned int MEDIA_TEMP_AR      = 0;    // Vari�vel armazena Temperatura m�dia do Ar
unsigned int TEMP_AR_MAX        = 0;    // Vari�vel armazena Temperatura m�xima do Ar
unsigned int MM_TEMP_AR[MEDIA_MOVEL];   // Vetor m�dia m�vel Temperatura do Ar 

unsigned int BATERIA            = 0;    // Vari�vel armazena tens�o da Bateria
unsigned int MEDIA_BATERIA      = 0;    // Vari�vel armazena tens�o m�dia da Bateria
unsigned int MM_BATERIA[MEDIA_MOVEL];   // Vetor m�dia m�vel Bateria 

unsigned int TPS                = 0;    // Vari�vel armazena posi��o Acelerador
unsigned int MEDIA_TPS          = 0;    // Vari�vel armazena posi��o m�dia Acelerador
unsigned int MM_TPS[MEDIA_MOVEL];       // Vetor m�dia m�vel posi��o Acelerador
unsigned int TPS_ANTERIOR       = 0;    // Vari�vel armazena posi��o passada do Acelerador
  signed int TPS_DERIVADA       = 0;    // Vari�vel armazena derivada da posi��o do Acelerador

unsigned int INJETOR_ABERTURA      = 0;    // Vari�vel armazena Porcentagem de abertuda de Inje��o
unsigned int INJETOR_ABERTURA_MAX  = 0;    // Vari�vel armazena Porcentagem de abertuda de Inje��o M�xima
unsigned int INJETOR_MS            = 0;    // Vari�vel armazena Tempo de abertuda de Inje��o
unsigned int INJETOR_MS_MAX        = 0;    // Vari�vel armazena Tempo de abertuda de Inje��o M�xima

unsigned char N_CILINDRO        = 0;    // Vari�vel armazena N�mero de cilindros do Motor
unsigned int  VOLUME_MOTOR      = 0;    // Vari�vel armazena Volume do Motor (cilindrada)
unsigned char TIPO_COMB         = 0;    // Vari�vel armazena Tipo de Combust�vel Utilizados
unsigned char TIPO_REFRIG       = 0;    // Vari�vel armazena Tipo de Refrigera��o do Motor (�gua / Ar)
unsigned char TEMP_VENTILADOR   = 0;    // Vari�vel armazena Temperatura para acionar o resfriamento
unsigned char VAZAO_INJETOR     = 0;    // Vari�vel armazena vaz�o do injetor
unsigned char DEADTIME          = 0;    // Vari�vel armazena DeadTime do injetor (Tempo motor, devido ser um indutor)
unsigned char CUT_OFF           = 0;    // Vari�vel armazena a op��o CUF-OFF 
unsigned int  EXCESSO_TEMP      = 0;    // Vari�vel armazena Temperatura Excesso de aviso para alerta
unsigned int  CONT_B_ELET_COMB  = 0;    // Vari�vel contagem para desligar Bomba El�trica de Combust�vel

unsigned char CONT_TIMER1       = 0;    // Vari�vel contabiliza tempo do TIMER 1 para calcular RPM
unsigned int  TIMER1            = 0;    // Vari�vel armazena valor TIMER 1
unsigned char T1C               = 0;    // Vari�vel armazena CONT_TIMER1 

        float RO_AR             = 0;    // Vari�vel armazena RO do Ar (densidade) [kg/m^3]
        float M_AR              = 0;    // Vari�vel armazena Massa do Ar que entra no motor [kg]
        float M_COMB            = 0;    // Vari�vel armazena Massa do Combust�vel necess�ria para inje��o [kg]
        int   p                 = 0;    // Vari�vel armazena Press�o na admiss�o do motor [kPa]
        int   T                 = 0;    // Vari�vel armazena Temperatura do Ar na admiss�o [Kelvin]
        int   CIL_MCUB          = 0;    // Vari�vel armazena Volume do motor [m^3]
        int   V_INJ             = 0;    // Vari�vel armazena Vaz�o do injetor [L/s]
        int   T_INJ             = 0;    // Vari�vel armazena Tempo de Inje��o [s]
        long  EQUACAO_A         = 0;    // Vari�vel armazena o resultado da equa��o A
                                        // EQUACAO_A = (n/R)*(50000000/18)*(VOLUME_MOTOR/N_CILINDROS)*(1/ESTEQ_COMB)*(1/RO_COMB)*(1/V_INJ)
        
       char   FLAG_EXCESSO      = 0;    // Flag para acionar alerta de excesso de temperatura
        bit   ALERTA            = 0;    // Vari�vel armazena quando deve acionar alerta de excesso de temperatura
    

// === SEPARADOR DE UNIDADES ===
unsigned char unidade           = 0;
unsigned char dezena            = 0;
unsigned char centena           = 0;
unsigned char u_milhar          = 0;
unsigned char d_milhar          = 0;
unsigned char c_milhar          = 0;
unsigned char u_bilhar          = 0;
unsigned char d_bilhar          = 0;
unsigned char c_bilhar          = 0;




// =============================================================
// ===============SEPARA UNIDADES COM ZEROS=====================
// =============================================================

void separa_unidades(long Valor)
{
    unidade=0;
    dezena=0;
    centena=0;
    u_milhar=0;
    d_milhar=0;
    c_milhar=0;
    u_bilhar=0;
    d_bilhar=0;
    c_bilhar=0;

    while(Valor>=100000000){Valor=Valor-100000000; c_bilhar++;}
    while(Valor>=10000000){Valor=Valor-10000000; d_bilhar++;}
    while(Valor>=1000000){Valor=Valor-1000000; u_bilhar++;}
    while(Valor>=100000){Valor=Valor-100000; c_milhar++;}
    while(Valor>=10000){Valor=Valor-10000; d_milhar++;}
    while(Valor>=1000){Valor=Valor-1000; u_milhar++;}
    while(Valor>=100){Valor=Valor-100; centena++;}
    while(Valor>=10){Valor=Valor-10; dezena++;}
    while(Valor>0){Valor=Valor-1; unidade++;}

    return;
}


// =============================================================
// ===============SEPARA UNIDADES SEM ZEROS=====================
// =============================================================

void separa_unidades_SZ(long Valor)
{
    unidade=0;
    dezena=0;
    centena=0;
    u_milhar=0;
    d_milhar=0;
    c_milhar=0;
    u_bilhar=0;
    d_bilhar=0;
    c_bilhar=0;

    if (Valor<10)  {dezena=240;}
    if (Valor<100) {centena=240;}
    if (Valor<1000){u_milhar=240;}
    if (Valor<10000){d_milhar=240;}
    if (Valor<100000){c_milhar=240;}
    if (Valor<1000000){u_bilhar=240;}
    if (Valor<10000000){d_bilhar=240;}
    if (Valor<100000000){c_bilhar=240;}

    while(Valor>=100000000){Valor=Valor-100000000; c_bilhar++;}
    while(Valor>=10000000){Valor=Valor-10000000; d_bilhar++;}
    while(Valor>=1000000){Valor=Valor-1000000; u_bilhar++;}
    while(Valor>=100000){Valor=Valor-100000; c_milhar++;}
    while(Valor>=10000){Valor=Valor-10000; d_milhar++;}
    while(Valor>=1000){Valor=Valor-1000; u_milhar++;}
    while(Valor>=100){Valor=Valor-100; centena++;}
    while(Valor>=10){Valor=Valor-10; dezena++;}
    while(Valor>0){Valor=Valor-1; unidade++;}

    return;
}



// =============================================================
// ================ BARRA GR�FICA DA SONDA =====================
// =============================================================

void Grafico(long Valor, long Max)
{
    char coluna,caracter=0;

    Valor = (Valor * 100) / Max;
    Valor = (Valor * 80) / 100;

    linha2_lcd();

    for (coluna=0;coluna<=15;coluna++)
    {
        if (Valor==0) {caracter=0;}
        if (Valor==1) {Valor=Valor-1; caracter=1;}
        if (Valor==2) {Valor=Valor-2; caracter=2;}
        if (Valor==3) {Valor=Valor-3; caracter=3;}
        if (Valor==4) {Valor=Valor-4; caracter=4;}
        if (Valor>=5) {Valor=Valor-5; caracter=5;}

        caracter_lcd(caracter);
    }

    return;
}




// =============================================================
// ============================MENUS============================
// =============================================================


// ===== RPM / MAXIMO =====

void MENU_01(void)
{
    linha1_lcd();
    texto_lcd("Rotac");

    Simbolos_lcd('�');   // �
    xy_lcd(1,5);
    caracter_lcd(6);

    texto_lcd("o "); 
    separa_unidades_SZ(RPM);
    caracter_lcd(d_milhar+48);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("rpm");

    linha2_lcd();
    texto_lcd("M");

    Simbolos_lcd('�'); // �
    xy_lcd(2,1);
    caracter_lcd(7);

    texto_lcd("x.    ");
    separa_unidades_SZ(RPM_MAX);
    caracter_lcd(d_milhar+48);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("rpm");

    return;
}




// ===== TEMPERATURA MOTOR / MAXIMO =====

void MENU_02(void)
{
    linha1_lcd();
    texto_lcd(" Temp. do Motor ");

    linha2_lcd();

    separa_unidades_SZ(TEMP_MOTOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C (M");

    Simbolos_lcd('�');   // �
    xy_lcd(2,8);
    caracter_lcd(7);

    texto_lcd("x");

    separa_unidades_SZ(TEMP_MOTOR_MAX);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C)");

    return;
}



// ===== TEMPERATURA AR / MAXIMO =====

void MENU_03(void)
{
    linha1_lcd();
    texto_lcd("  Temp. do Ar   ");

    linha2_lcd();

    separa_unidades_SZ(TEMP_AR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C (M");

    Simbolos_lcd('�');   // �
    xy_lcd(2,8);
    caracter_lcd(7);

    texto_lcd("x");

    separa_unidades_SZ(TEMP_AR_MAX);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C)");

    return;
}




// ===== SONDA LAMBDA (SENSOR DE OXIG�NIO) =====

void MENU_04(void)
{
    Grava_CGRAM();	

    linha1_lcd();

    texto_lcd("S. Lambda ");
    separa_unidades(LAMBDA); // milivolts
    caracter_lcd(u_milhar+48);
    texto_lcd(".");
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("v");

    linha2_lcd();
    Grafico(LAMBDA,1000);  // Mostra barra gr�fica

    return;
}



// ===== SENSOR DE PRESS�O (MAP - Manifold Absolute Pressure) / MAXIMO =====

void MENU_05(void)
{
    linha1_lcd();
    texto_lcd("P. MAP   ");
    separa_unidades_SZ(MAP);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("kPa");

    linha2_lcd();
    texto_lcd("M");
    
    Simbolos_lcd('�');   // �
    xy_lcd(2,1);
    caracter_lcd(6);
    
    texto_lcd("n.     ");
    separa_unidades_SZ(MAP_MIN);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("kPa");

    return;
}





// ===== TENS�O BATERIA / TPS =====

void MENU_06(void)
{
    linha1_lcd();

    texto_lcd("Bateria    ");

    separa_unidades_SZ(BATERIA);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    texto_lcd(".");
    caracter_lcd(unidade+48);
    texto_lcd("V");

    linha2_lcd();

    texto_lcd("TPS       ");
    separa_unidades_SZ(TPS);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    texto_lcd(".");
    caracter_lcd(unidade+48);
    texto_lcd("%");

    return;
}



// ===== INJETOR ms E % / MAX ms E % =====

void MENU_07(void)
{
    linha1_lcd();

    texto_lcd("INJ ");
    separa_unidades(INJETOR_MS);

    if (INJETOR_MS<=999)
    {
        texto_lcd(" ");
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }else{
        caracter_lcd(u_milhar+48);
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }
    
    texto_lcd("ms ");
    separa_unidades_SZ(INJETOR_ABERTURA);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("%");

    linha2_lcd();

    texto_lcd("M");
    Simbolos_lcd('�');  // �
    xy_lcd(2,1);
    caracter_lcd(7);

    texto_lcd("x.");
    separa_unidades(INJETOR_MS_MAX);

    if (INJETOR_MS_MAX<=999)
    {
        texto_lcd(" ");
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }else{
        caracter_lcd(u_milhar+48);
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }
    
    texto_lcd("ms ");
    separa_unidades_SZ(INJETOR_ABERTURA_MAX);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("%");

    return;
}



// ===== INJETOR / RPM / MAP / SONDA LAMBDA =====

void MENU_08(void)
{
    linha1_lcd();
    separa_unidades(INJETOR_MS);

    if (INJETOR_MS<=999)
    {
        texto_lcd(" ");
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }else{
        caracter_lcd(u_milhar+48);
        caracter_lcd(centena+48);
        texto_lcd(".");
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
    }

    texto_lcd("ms ");

    separa_unidades_SZ(RPM);
    caracter_lcd(d_milhar+48);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("rpm");

    linha2_lcd();

    separa_unidades_SZ(MAP);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("kPa   ");

    separa_unidades(LAMBDA); // milivolts
    caracter_lcd(u_milhar+48);
    texto_lcd(".");
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("v");

    return;
}



// ===== CONFIGURAR =====

void MENU_09(void)
{
    linha1_lcd();
    texto_lcd("   Configurar   ");
    linha2_lcd();
    texto_lcd("    (ENTER)    ~");

    return;
}




// ===== CONFIGURAR / CILINDROS DO MOTOR =====

void MENU_21(void)
{
    linha1_lcd();
    texto_lcd("N. de Cilindros ");
    linha2_lcd();
    texto_lcd("Motor:         ");
    separa_unidades_SZ(N_CILINDRO);
    caracter_lcd(unidade+48);

    return;
}



// ===== CONFIGURAR / VOLUME MOTOR =====

void MENU_22(void)
{
    linha1_lcd();
    texto_lcd("Motor Cilindrada");
    linha2_lcd();
    texto_lcd("Total:   ");
    separa_unidades_SZ(VOLUME_MOTOR);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("cm3");

    return;
}



// ===== CONFIGURAR / TIPO DE COMBUSTIVEL =====

void MENU_23(void)
{
    linha1_lcd();
    texto_lcd("Tipo Combust");
    
    Simbolos_lcd('�');   // �
    xy_lcd(1,12);
    caracter_lcd(6);
    
    texto_lcd("vel");
    linha2_lcd();
    
    if (TIPO_COMB == ALCOOL)
    {
        texto_lcd("     ");
        Simbolos_lcd('�');   // �
        xy_lcd(2,5);
        caracter_lcd(7);
        texto_lcd("lcool     ");  
    }else
        texto_lcd("    Gasolina    ");

    return;
}



// ===== CONFIGURAR / REFRIGERA��O =====

void MENU_24(void)
{
    linha1_lcd();
    texto_lcd("  Refrigerac");
    Simbolos_lcd('�');   // �
    xy_lcd(1,12);
    caracter_lcd(6);
    texto_lcd("o  ");
    linha2_lcd();

    if (TIPO_REFRIG == AR)
        texto_lcd("       Ar       ");
    else{
        texto_lcd("      ");
        Simbolos_lcd('�');   // �
        xy_lcd(2,6);
        caracter_lcd(7);
        texto_lcd("gua      ");
    }

    return;
}


// ===== CONFIGURAR / TEMPERATURA DO VENTILADOR =====

void MENU_25(void)
{
    linha1_lcd();
    texto_lcd("   Ventilador   ");
    linha2_lcd();
    texto_lcd("Acionar:   ");
    separa_unidades_SZ(TEMP_VENTILADOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C");

    return;
}


// ===== CONFIGURAR / VAZ�O INJETOR  (libras/hora)=====

void MENU_26(void)
{
    linha1_lcd();
    texto_lcd("    Injetor     ");
    linha2_lcd();
    texto_lcd("Vaz");
    Simbolos_lcd('�');   // �
    xy_lcd(2,3);
    caracter_lcd(6);
    texto_lcd("o:   ");
    separa_unidades_SZ(VAZAO_INJETOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("lb/h"); // lb/h = 0,00018 L/s

    return;
}



// ===== CONFIGURAR / INJETOR DEADTIME =====

void MENU_27(void)
{
    linha1_lcd();
    texto_lcd("    DeadTime    ");
    linha2_lcd();
    texto_lcd("Injetor:   ");
    separa_unidades(DEADTIME);
    caracter_lcd(dezena+48);
    texto_lcd(".");
    caracter_lcd(unidade+48);
    texto_lcd("ms");

    return;
}


// ===== CONFIGURAR / CUT-OFF =====

void MENU_28(void)
{
    linha1_lcd();
    texto_lcd("    Cut-Off     ");
    linha2_lcd();

    if (CUT_OFF)
        texto_lcd("       ON       ");
    else
        texto_lcd("      OFF       ");

    return;
}


// ===== CONFIGURAR / EXCESSO TEMP MOTOR =====

void MENU_29(void)
{
    linha1_lcd();
    texto_lcd(" Excesso Temp.  ");
    
    linha2_lcd();
    
    if (EXCESSO_TEMP >= 90)
    {
        texto_lcd("Motor:     ");        
        separa_unidades_SZ(EXCESSO_TEMP);
        caracter_lcd(centena+48);
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
        caracter_lcd(0xDF);
        texto_lcd("C");
        
    }else
        texto_lcd("Motor:       OFF"); 
    

    return;
}





// ===== ALTERAR / CILINDROS DO MOTOR =====

void MENU_41(void)
{
    if (Botao_INC() && N_CILINDRO<4) N_CILINDRO++;
    if (N_CILINDRO==3) N_CILINDRO=4;
    if (Botao_DEC() && N_CILINDRO>1) N_CILINDRO--;
    if (N_CILINDRO==3) N_CILINDRO=2;
    if (Botao_CNL()) {N_CILINDRO=ler_eeprom(0); MENU=21;}         // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(0,N_CILINDRO); MENU = 21;}  // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("N. de Cilindros ");
    linha2_lcd();
    texto_lcd("Motor:       ~ ");
    separa_unidades_SZ(N_CILINDRO);
    caracter_lcd(unidade+48);

    if (TIPO_COMB == ALCOOL)
        EQUACAO_A = ((1344714 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR));
    else
        EQUACAO_A = ((878181 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR)); 

    return;
}



// ===== ALTERAR / VOLUME DO MOTOR =====

void MENU_42(void)
{    
    if ((Botao_INC() || Botao_INC_Auto()) && VOLUME_MOTOR<4000) VOLUME_MOTOR+=5;
    if ((Botao_DEC() || Botao_DEC_Auto()) && VOLUME_MOTOR>5) VOLUME_MOTOR-=5;
    if (Botao_CNL()) {VOLUME_MOTOR = (ler_eeprom(1)<<8) + ler_eeprom(2); MENU=22;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(1,(VOLUME_MOTOR >> 8)); escrever_eeprom(2,(VOLUME_MOTOR & 0x00FF)); MENU = 22;}// Grava dados na eeprom 

    linha1_lcd();
    texto_lcd("Motor Cilindrada");
    linha2_lcd();
    texto_lcd("Total: ~ ");
    separa_unidades_SZ(VOLUME_MOTOR);
    caracter_lcd(u_milhar+48);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("cm3");

    if (TIPO_COMB == ALCOOL)
        EQUACAO_A = ((1344714 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR));
    else
        EQUACAO_A = ((878181 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR)); 

    return;
}



// ===== ALTERAR / TIPO DE COMBUSTIVEL =====

void MENU_43(void)
{    
    if (Botao_INC() && TIPO_COMB<1) TIPO_COMB++;
    if (Botao_DEC() && TIPO_COMB>0) TIPO_COMB--;
    if (Botao_CNL()) {TIPO_COMB = ler_eeprom(3); MENU=23;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(3,TIPO_COMB); MENU = 23;} // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("Tipo Combust");
    Simbolos_lcd('�');   // �
    xy_lcd(1,12);
    caracter_lcd(6);
    texto_lcd("vel");

    linha2_lcd();
    
    if (TIPO_COMB == ALCOOL)
    {
        texto_lcd("~    ");
        Simbolos_lcd('�');   // �
        xy_lcd(2,5);
        caracter_lcd(7);
        texto_lcd("lcool     ");  
    }
    else
        texto_lcd("~   Gasolina    ");

    if (TIPO_COMB == ALCOOL)
        EQUACAO_A = ((1344714 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR));
    else
        EQUACAO_A = ((878181 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR)); 

    return;
}



// ===== ALTERAR / REFRIGERA��O =====

void MENU_44(void)
{
    if (Botao_INC() && TIPO_REFRIG<1) TIPO_REFRIG++;
    if (Botao_DEC() && TIPO_REFRIG>0) TIPO_REFRIG--;
    if (Botao_CNL()) {TIPO_REFRIG = ler_eeprom(4); MENU=24;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(4,TIPO_REFRIG); MENU = 24;} // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("  Refrigerac");
    Simbolos_lcd('�');   // �
    xy_lcd(1,12);
    caracter_lcd(6);
    texto_lcd("o  ");
    linha2_lcd();
    
    if (TIPO_REFRIG == AR)
        texto_lcd("~      Ar       ");
    else{
        texto_lcd("~     ");
        Simbolos_lcd('�');   // �
        xy_lcd(2,6);
        caracter_lcd(7);
        texto_lcd("gua      ");
    }

    return;
}

    



// ===== ALTERAR / TEMPERATURA DO VENTILADOR =====

void MENU_45(void)
{    
    if ((Botao_INC() || Botao_INC_Auto()) && TEMP_VENTILADOR<110) TEMP_VENTILADOR++;
    if ((Botao_DEC() || Botao_DEC_Auto()) && TEMP_VENTILADOR>80) TEMP_VENTILADOR--;
    if (Botao_CNL()) {TEMP_VENTILADOR = ler_eeprom(5); MENU=25;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(5,TEMP_VENTILADOR); MENU = 25;} // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("   Ventilador   ");
    linha2_lcd();
    texto_lcd("Acionar: ~ ");
    separa_unidades_SZ(TEMP_VENTILADOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C");

    return;
}


// ===== ALTERAR / VAZ�O INJETOR  (libras/hora)=====

void MENU_46(void)
{    
    if ((Botao_INC() || Botao_INC_Auto()) && VAZAO_INJETOR<250) VAZAO_INJETOR+=5;
    if ((Botao_DEC() || Botao_DEC_Auto()) && VAZAO_INJETOR>5) VAZAO_INJETOR-=5;
    if (Botao_CNL()) {VAZAO_INJETOR = ler_eeprom(6); MENU=26;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(6,VAZAO_INJETOR); MENU = 26;} // Grava dados na eeprom 

    linha1_lcd();
    texto_lcd("    Injetor     ");
    linha2_lcd();
    texto_lcd("Vaz");
    Simbolos_lcd('�');   // �
    xy_lcd(2,3);
    caracter_lcd(6);
    texto_lcd("o: ~ ");
    separa_unidades_SZ(VAZAO_INJETOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    texto_lcd("lb/h"); // lb/h = 0,00018 L/s
    
    if (TIPO_COMB == ALCOOL)
        EQUACAO_A = ((1344714 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR));
    else
        EQUACAO_A = ((878181 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR)); 

    return;
}



// ===== ALTERAR / INJETOR DEADTIME =====

void MENU_47(void)
{    
    if ((Botao_INC() || Botao_INC_Auto()) && DEADTIME<50) DEADTIME++;
    if ((Botao_DEC() || Botao_DEC_Auto()) && DEADTIME>1) DEADTIME--;
    if (Botao_CNL()) {DEADTIME = ler_eeprom(7); MENU=27;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(7,DEADTIME); MENU = 27;} // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("    DeadTime    ");
    linha2_lcd();
    texto_lcd("Injetor: ~ ");
    separa_unidades(DEADTIME);
    caracter_lcd(dezena+48);
    texto_lcd(".");
    caracter_lcd(unidade+48);
    texto_lcd("ms");

    return;
}


// ===== ALTERAR / CUT-OFF =====

void MENU_48(void)
{   
    if (Botao_INC() && CUT_OFF<1) CUT_OFF++;
    if (Botao_DEC() && CUT_OFF>0) CUT_OFF--;
    if (Botao_CNL()) {CUT_OFF = ler_eeprom(8);  MENU=28;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(8,CUT_OFF); MENU=28;} // Grava dados na eeprom

    linha1_lcd();
    texto_lcd("    Cut-Off     ");
    linha2_lcd();

    if (CUT_OFF)
        texto_lcd("~      ON       ");
    else
        texto_lcd("~     OFF       ");

    return;
}


// ===== ALTERAR / EXCESSO TEMP MOTOR =====

void MENU_49(void)
{
    if ((Botao_INC() || Botao_INC_Auto()) && EXCESSO_TEMP<110) EXCESSO_TEMP++;
    if ((Botao_DEC() || Botao_DEC_Auto()) && EXCESSO_TEMP>89) EXCESSO_TEMP--;
    if (Botao_CNL()) {EXCESSO_TEMP = ler_eeprom(9); MENU=29;} // L� dados da eeprom
    if (Botao_ENT()) {escrever_eeprom(9,EXCESSO_TEMP); MENU = 29;} // Grava dados na eeprom
    
    linha1_lcd();
    texto_lcd(" Excesso Temp.  ");
    linha2_lcd();
    
    if (EXCESSO_TEMP >= 90)
    {
        texto_lcd("Motor:   ~ ");        
        separa_unidades_SZ(EXCESSO_TEMP);
        caracter_lcd(centena+48);
        caracter_lcd(dezena+48);
        caracter_lcd(unidade+48);
        caracter_lcd(0xDF);
        texto_lcd("C");
        
    }else
        texto_lcd("Motor:   ~   OFF"); 

    return;
}



// =============================================================
// ========================ALERTA!!!============================
// =============================================================

void ALERTA_MENU(void)
{
    linha1_lcd();
    texto_lcd("ALERTA - EXCESSO");

    linha2_lcd();

    texto_lcd("   TEMP.");
    separa_unidades_SZ(TEMP_MOTOR);
    caracter_lcd(centena+48);
    caracter_lcd(dezena+48);
    caracter_lcd(unidade+48);
    caracter_lcd(0xDF);
    texto_lcd("C   ");
    
    if (Botao_ENT() || Botao_CNL() || Botao_DEC() || Botao_INC())
    {
        ALERTA = 0;
        FLAG_EXCESSO = 0;
    }
    
    Beep_Alerta();

    return;
}


// =============================================================
// ================ INICIALIZA��O DO SISTEMA ===================
// =============================================================


void inicializa_sistema(void)
{
    unsigned int ADC_MAP = 0;
    unsigned char CONT = 0;

    for (CONT = 0; CONT < MEDIA_MOVEL; CONT++) // Zera todos os vetores da M�dia M�vel 
    {
        MM_BATERIA[CONT] = 0;
        MM_TEMP_MOTOR[CONT] = 0;
        MM_TEMP_AR[CONT] = 0;
        MM_TPS[CONT] = 0;
        MM_LAMBDA[CONT] = 0;
        MM_MAP[CONT] = 0;
    }

    SETUP();            // Realiza as configura��es no Microcontrolador

    CLRWDT();           // Limpa Watchdog Timer
    
    inicializa_lcd();   // Inicializa o LCD 16x2
    limpa_lcd();
    
    CLRWDT();               // Limpa Watchdog Timer

    /* Inicializa as vari�veis com os valores da EEPROM */
    
    N_CILINDRO = ler_eeprom(0);
    VOLUME_MOTOR = (ler_eeprom(1)<<8) + ler_eeprom(2);
    TIPO_COMB = ler_eeprom(3);
    TIPO_REFRIG = ler_eeprom(4);
    TEMP_VENTILADOR = ler_eeprom(5);
    VAZAO_INJETOR = ler_eeprom(6);
    DEADTIME = ler_eeprom(7);
    CUT_OFF = ler_eeprom(8);
    EXCESSO_TEMP = ler_eeprom(9);
    
    /****************************************************/

    if (TIPO_COMB == ALCOOL)        // Calcula a equa��o A conforme o Tipo de Combust�vel
        EQUACAO_A = ((1344714 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR));
    else
        EQUACAO_A = ((878181 * VOLUME_MOTOR) / (N_CILINDRO * VAZAO_INJETOR)); 

    CONT = 0;

    while(CONT!=20){                // Faz a leitura da press�o absoluta inicial
        Delay_Ms(5);
        ADC_MAP += VALOR_ADC(1);
        CONT++;
    }

    ZERO_MAP = (int)((((long)(ADC_MAP / CONT)*250) /1023) + 10); // Registra a press�o atmosferica para considerar como Press�o zero do MAP
    MAP_MIN = ZERO_MAP;

    o_B_ELET_COMB = 1;      // Aciona a Bomba El�trica de Combust�vel
    
    FLAG_EXCESSO = 1;       // Aciona a Flag de alerta de excesso de Temperatura do motor 
    
    TMR0ON = 1;             // Liga TIMER 0 para iniciar as leituras dos sensores
    
    CLRWDT();               // Limpa Watchdog Timer

    return;
}



// =============================================================
// =====================ROTINA PRINCIPAL========================
// =============================================================


int main(void)
{
    CLRWDT();               // Limpa Watchdog Timer
    
    inicializa_sistema();
    
    
    
    while(1)
    {
    
        CLRWDT();           // Limpa Watchdog Timer
        
        if (ALERTA) { ALERTA_MENU(); }      // Se ocorreu excesso de temperatura, chama a rotina
        else                                // Se n�o, mostra os menus
            {
                if (MENU==1)  {MENU_01();   if(Botao_DEC()){MENU=2;}   if(Botao_INC()){MENU=9;}}
                if (MENU==2)  {MENU_02();   if(Botao_DEC()){MENU=3;}   if(Botao_INC()){MENU=1;}}
                if (MENU==3)  {MENU_03();   if(Botao_DEC()){MENU=4;}   if(Botao_INC()){MENU=2;}}
                if (MENU==4)  {MENU_04();   if(Botao_DEC()){MENU=5;}   if(Botao_INC()){MENU=3;}}
                if (MENU==5)  {MENU_05();   if(Botao_DEC()){MENU=6;}   if(Botao_INC()){MENU=4;}}
                if (MENU==6)  {MENU_06();   if(Botao_DEC()){MENU=7;}   if(Botao_INC()){MENU=5;}}
                if (MENU==7)  {MENU_07();   if(Botao_DEC()){MENU=8;}   if(Botao_INC()){MENU=6;}}
                if (MENU==8)  {MENU_08();   if(Botao_DEC()){MENU=9;}   if(Botao_INC()){MENU=7;}}
                if (MENU==9)  {MENU_09();   if(Botao_DEC()){MENU=1;}   if(Botao_INC()){MENU=8;}    if(Botao_ENT()){MENU=21;}}

                if (MENU==21) {MENU_21();   if(Botao_DEC()){MENU=22;}  if(Botao_INC()){MENU=29;}   if(Botao_ENT()){MENU=41;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==22) {MENU_22();   if(Botao_DEC()){MENU=23;}  if(Botao_INC()){MENU=21;}   if(Botao_ENT()){MENU=42;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==23) {MENU_23();   if(Botao_DEC()){MENU=24;}  if(Botao_INC()){MENU=22;}   if(Botao_ENT()){MENU=43;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==24) {MENU_24();   if(Botao_DEC()){MENU=25;}  if(Botao_INC()){MENU=23;}   if(Botao_ENT()){MENU=44;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==25) {MENU_25();   if(Botao_DEC()){MENU=26;}  if(Botao_INC()){MENU=24;}   if(Botao_ENT()){MENU=45;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==26) {MENU_26();   if(Botao_DEC()){MENU=27;}  if(Botao_INC()){MENU=25;}   if(Botao_ENT()){MENU=46;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==27) {MENU_27();   if(Botao_DEC()){MENU=28;}  if(Botao_INC()){MENU=26;}   if(Botao_ENT()){MENU=47;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==28) {MENU_28();   if(Botao_DEC()){MENU=29;}  if(Botao_INC()){MENU=27;}   if(Botao_ENT()){MENU=48;}  if(Botao_CNL()){MENU=9;}}
                if (MENU==29) {MENU_29();   if(Botao_DEC()){MENU=21;}  if(Botao_INC()){MENU=28;}   if(Botao_ENT()){MENU=49;}  if(Botao_CNL()){MENU=9;}}

                if (MENU==41) {MENU_41();   }
                if (MENU==42) {MENU_42();   }
                if (MENU==43) {MENU_43();   }
                if (MENU==44) {MENU_44();   }
                if (MENU==45) {MENU_45();   }
                if (MENU==46) {MENU_46();   }
                if (MENU==47) {MENU_47();   }
                if (MENU==48) {MENU_48();   }
                if (MENU==49) {MENU_49();   }
            }
        
        if ((TEMP_MOTOR >= EXCESSO_TEMP) && (EXCESSO_TEMP >= 90) && FLAG_EXCESSO) // Ocorreu excesso e Flag � verdadeira 
        {
            ALERTA = 1;
        }
        
        if (TEMP_MOTOR < EXCESSO_TEMP)  // Se temperatura do motor � menor que a configura para temp. Excesso
        {                               // Ent�o seta flag de excesso e desliga o alerta.
            FLAG_EXCESSO = 1;
            ALERTA = 0;
        }
    }
    return 0;
}



// =============================================================
// ===================ROTINAS DE INTERRUP��ES===================
// =============================================================



// =============================================================
// ========= B A I X A   P R I O R I D A D E ===================
// =============================================================
void low_priority interrupt my_isr_low(void)
{

    CLRWDT();               // Limpa Watchdog Timer
    
    // =============================================================
    // ========= INTERRUP��O INT1 ========== N�O UTILIZADA =========
    // =============================================================

    if(INT1IF && INT1IE)            
    {
        INT1IF = 0;

    }



    // =============================================================
    // =====  +++ INTERRUP��O TIMER0 +++  LEITURA DOS SENSORES =====
    // =============================================================
    // ======== LEITURA DOS SENSORES (MEDIA MOVEL) CADA 10ms =======
    // =============================================================
    // = PID (PROPORCIONAL - INTEGRAL - DERIVADA) DO SENSOR LAMBDA =
    // =============================================================
    // ============== DERIVADA DOS SENSORES TPS e MAP ==============
    // =============================================================
    // ====================== CALCULO DO RPM =======================
    // =============================================================
    // ==== CONTADOR PARA DESLIGAR BOMBA ELETRICA DE COMBUSTIVEL ===
    // =============================================================

    if(TMR0IF && TMR0IE)      // Interrup��o a cada 10ms      
    {
        TMR0IF = 0;
        // 10ms = 50000 (PRECALER 1:2) -> 65536 - 50000 = 15356 -> 0x3CB0
        TMR0H = 0x3C; // 8bits + significativos
        TMR0L = 0xB0; // 8bits - significativos

        if (CONT_B_ELET_COMB < (TEMPO_B_ELET_COMB*100) ) // Se Contador da Bomba eletrica
        {                                                // for menor que o tempo estabelecido
            CONT_B_ELET_COMB++;                          // ent�o, incrementa contador
        }else{
            o_B_ELET_COMB = 0;                           // Se n�o, desliga Bomba Eletrica de Comb.
        }

        /* leitura dos sensores a cada 10ms (para ter base de tempo) */
        
        MEDIA_MAP -= MM_MAP[INDICE_MM];                  // M�dia M�vel do MAP
        MM_MAP[INDICE_MM] = VALOR_ADC(1);
        MEDIA_MAP += MM_MAP[INDICE_MM];

        MEDIA_TPS -= MM_TPS[INDICE_MM];                  // M�dia M�vel do TPS
        MM_TPS[INDICE_MM] = VALOR_ADC(2);
        MEDIA_TPS += MM_TPS[INDICE_MM];

        MEDIA_LAMBDA -= MM_LAMBDA[INDICE_MM];            // M�dia M�vel da Sonda Lambda
        MM_LAMBDA[INDICE_MM] = VALOR_ADC(3);
        MEDIA_LAMBDA += MM_LAMBDA[INDICE_MM];

        MEDIA_BATERIA -= MM_BATERIA[INDICE_MM];          // M�dia M�vel da Bateria
        MM_BATERIA[INDICE_MM] = VALOR_ADC(0);
        MEDIA_BATERIA += MM_BATERIA[INDICE_MM];

        MEDIA_TEMP_MOTOR -= MM_TEMP_MOTOR[INDICE_MM];    // M�dia M�vel da Temperatura do Motor
        MM_TEMP_MOTOR[INDICE_MM] = VALOR_ADC(4);
        MEDIA_TEMP_MOTOR += MM_TEMP_MOTOR[INDICE_MM];

        MEDIA_TEMP_AR -= MM_TEMP_AR[INDICE_MM];          // M�dia M�vel da Temperatura do Ar
        MM_TEMP_AR[INDICE_MM] = VALOR_ADC(5);
        MEDIA_TEMP_AR += MM_TEMP_AR[INDICE_MM];

        BATERIA = (int)(((long)(MEDIA_BATERIA / MEDIA_MOVEL)*300)/1023)+8;      // Converte ADC para Tens�o da Bateria [V]

        TEMP_MOTOR = (int)(((long)(MEDIA_TEMP_MOTOR / MEDIA_MOVEL)*500)/1023);  // Converte ADC para Temp. Motor [�C]

        TEMP_AR = (int)(((long)(MEDIA_TEMP_AR / MEDIA_MOVEL)*500)/1023);        // Converte ADC para Temp. Ar [�C]

        MAP_ANTERIOR = MAP;

        MAP = (int)((((long)(MEDIA_MAP / MEDIA_MOVEL)*250)/1023) + 10);         // Converte ADC para Press�o Absoluta [kPa]

        MAP_DERIVADA = (MAP - MAP_ANTERIOR) * 100;                              // Calcula derivada MAP d(M)/d(t) = (M - M') / t

        TPS_ANTERIOR = TPS;

        TPS = (int)(((long)(MEDIA_TPS / MEDIA_MOVEL)*1000)/1023);               // Converte ADC para TPS [V]

        TPS_DERIVADA = (TPS - TPS_ANTERIOR) * 100;                              // Calcula derivada MAP d(TPS)/d(t) = (TPS - TPS') / t

        LAMBDA_ANTERIOR = LAMBDA;

        LAMBDA = (int)(((long)(MEDIA_LAMBDA / MEDIA_MOVEL)*1000)/1023);         // Converte ADC para Lambda [V]

        LAMBDA_DERIVADA = (LAMBDA - LAMBDA_ANTERIOR) * 100;                     // Calcula derivada MAP d(LBD)/d(t) = (LBD - LBD') / t

        LAMBDA_ERRO = LAMBDA_SET_POINT - LAMBDA;                                // Calcula erro da Lambda em rela��o ao SetPoint

        LAMBDA_PROPORCAO = LAMBDA_ERRO;                                         // Lambda Proporcional

        LAMBDA_INTEG_ERRO += LAMBDA_ERRO;                                       // Aculuma o erro da Lambda

        if (LAMBDA_INTEG_ERRO & 0b10000000000000000000000000000000)             // Verifica o sinal do erro acumulado (positivo / negativo)
            LAMBDA_INTEG_SIG=1;
        else
            LAMBDA_INTEG_SIG=0;

        if (LAMBDA_INTEG_ERRO < 0) LAMBDA_INTEG_ERRO = -LAMBDA_INTEG_ERRO;      // Tira o m�dulo do erro acumulado

        if (LAMBDA_INTEG_ERRO >= LAMBDA_ERRO_MAX) LAMBDA_INTEG_ERRO = LAMBDA_ERRO_MAX; // Seta o limite do erro acumulado

        if (LAMBDA_INTEG_SIG) LAMBDA_INTEG_ERRO = -LAMBDA_INTEG_ERRO;           // Devolve o sinal do erro acumulado

        LAMBDA_INTEGRAL = LAMBDA_INTEG_ERRO;                                    // Lambda Integral (soma dos erros)

        if ((TEMP_MOTOR >= TEMP_VENTILADOR) && (TIPO_REFRIG == AGUA)) o_VENTILADOR = 1; // Aciona ventilador se atingir temperatura
                                                                                        // e se tipo de refrigera��o for �gua
        if (TEMP_MOTOR < (TEMP_VENTILADOR - TEMP_HISTERESE)) o_VENTILADOR = 0;  // Desliga ventilador com a subtra��o da hiterese

        if (TEMP_MOTOR > TEMP_MOTOR_MAX) TEMP_MOTOR_MAX = TEMP_MOTOR;           // Verifica temperatura m�xima do motor

        if (TEMP_AR > TEMP_AR_MAX) TEMP_AR_MAX = TEMP_AR;                       // Verifica temperatura m�xima do ar

        RPM = (150000000)/(((T1C * 65536) + TIMER1)*N_CILINDRO);                // Calcula o RPM = 120/(PERIODO * N_CILINDROS)
                                                                                // 150000000 => 120/(PRESCALER_TIMER1/CLOCK)            
        if (RPM>20000 || RPM<500) {RPM=0;}

        INDICE_MM++;

        if (INDICE_MM == MEDIA_MOVEL) INDICE_MM = 0;

    }


    // =============================================================
    // ======= INTERRUP��O TIMER2 ========== N�O UTILIZADA =========
    // =============================================================

    if(TMR2IF && TMR2IE)          
    {
        TMR2IF=0; 
    }



    // =============================================================
    // ========= INTERRUP��O INT2 ========== N�O UTILIZADA =========
    // =============================================================

    if(INT2IF && INT2IE)
    {
        INT2IF=0;
        INT2IE=0;
    }

}





// =============================================================
// =========== A L T A   P R I O R I D A D E ===================
// =============================================================
 
void interrupt my_isr(void)
{

    CLRWDT();               // Limpa Watchdog Timer

    // =============================================================
    // =====  +++ INTERRUP��O INT0 +++ =ENTRADA DO SINAL DE IGNI��O=
    // =============================================================

    if(INT0IF && INT0IE)           
    {
        INT0IF = 0;
        
        TMR1ON = 0;
        TIMER1 = TMR1;
        T1C = CONT_TIMER1;
        TMR1IF = 0;                            
        TMR1H  = 0;
        TMR1L  = 0;
        TMR1   = 0;
        CONT_TIMER1 = 0;
        TMR1ON = 1;

        if ((RPM>1800) && (TPS<50) && CUT_OFF)      // Se CUT-OFF estiver ligado, desliga a inje��o
        { 
            T_INJ = 0;
        }else{
            
            
/*  Equa��es utilizados, onde as constantes simplificadas para reduzir tempo de processamento
 * 
 *            n * p
 *   RO_AR = -------
 *            R * T
 * 
 *   
 *           RO_AR * CILINDRADA[m^3]                           VOLUME_MOTOR(cm^3)
 *   M_AR = -------------------------       CILINDRADA[m^3] = --------------------
 *                N_CILINDRO                                       10000000
 * 
 * 
 *             M_AR * FATOR_CORRE��O(LAMBDA)
 *   M_COMB = -------------------------------
 *             ESTEQUIOMETRICO_COMBUSTIVEL
 *  
 * 
 *                 M_COMB                    
 *   T_INJ = -----------------              V_INJ[l/s] = VAZAO_INJETOR[lb/h] * 0,00018
 *            V_INJ * RO_COMB
 * 
 * 
 *   T_INJ = T_INJ + PID(LAMBDA) + DERIVADA(TPS) + DERIVADA(MAP) + DEADTIME
 * 
 * 
 *                             n * VOLUME_MOTOR * 50000000
 *   EQUACAO_A = -------------------------------------------------------------
 *                R * ESTEQ_COMB * RO_COMB * VAZAO_INJETOR * N_CILINDROS * 18
 * 
 *            
 */ 
            
            o_INJETOR=1;

            if (MAP > ZERO_MAP)                     // M�dulo do MAP e soma com a diferen�a
                p = (MAP - ZERO_MAP) + ZERO_MAP; 
            else
                p = (ZERO_MAP - MAP) + ZERO_MAP;

            T = 273 + TEMP_AR;                      // Converte temperatura de [�C] para [K]
                    
            // TEMPO DE INJE��O DADOS EM MICRO SEGUNDOS
            
            T_INJ = (((EQUACAO_A  / LAMBDA) * p) / T) +
                    + (LAMBDA_INTEGRAL * 0.02) +
                    + ((TPS_DERIVADA + MAP_DERIVADA) * 1.6) +
                    + ((LAMBDA_DERIVADA + LAMBDA_PROPORCAO) * 2) +
                    + (DEADTIME * 100);

            if (T_INJ > 25000) T_INJ = 25000;       // Limita o tempo de inje��o
            if (T_INJ < 1200)   T_INJ = 1200;

            TMR3IF = 0;
            TMR3 = 65536 - (int)((T_INJ - 1140) * 2.5);   // Converte o tempo de inje��o de microsegundos para TIMER 3
           
            TMR3ON = 1;
            

        }

        CONT_B_ELET_COMB = 0;
        o_B_ELET_COMB = 1;                          // Aciona a bomba el�trica cada vez que recebe um pulso de igni��o
        
        INJETOR_MS = (int)(T_INJ / 10);             // Converte o tempo de inje��o para milisegundos
        INJETOR_ABERTURA = INJETOR_MS / (120000 / (RPM * N_CILINDRO)); // PWM em rela��o a rota��o do motor
        
        if (MAP_MIN > MAP) MAP_MIN = MAP;           // Verifica os valore m�nimos e m�ximos
        if (RPM > RPM_MAX) RPM_MAX = RPM;
        if (INJETOR_MS > INJETOR_MS_MAX) INJETOR_MS_MAX = INJETOR_MS;
        if (INJETOR_ABERTURA > INJETOR_ABERTURA_MAX) INJETOR_ABERTURA_MAX = INJETOR_ABERTURA;
        
    }



    // =============================================================
    // =====  +++ INTERRUP��O TIMER1 +++  TEMPORIZADOR P/ RPM ======
    // =============================================================

    if(TMR1IF && TMR1IE)            
    {   
        TMR1IF = 0;

        CONT_TIMER1++;

        if (CONT_TIMER1==5)
        {
            TMR1ON = 0;
            TMR1H  = 0;
            TMR1L  = 0;
            CONT_TIMER1 = 0;
            TIMER1 = 0;
            RPM = 0;
            T_INJ = 0;
            INJETOR_MS = 0;
            INJETOR_ABERTURA = 0;
        }


    }


    // =============================================================
    // =====  +++ INTERRUP��O TIMER3 +++ ==== TEMPO DE INJE��O =====
    // =============================================================

    if(TMR3IF && TMR3IE)            
    {
        TMR3IF = 0;
        TMR3ON = 0;   
        o_INJETOR = 0;

    }



    return;
}