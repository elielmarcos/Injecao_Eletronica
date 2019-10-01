/* 
 * File:   lcd.h
 * Author: Eliel Marcos
 *
 * Created on 21 de Outubro de 2018, 03:31
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif


void envia_dados_lcd(unsigned char dado);

void caracter_lcd(unsigned char c);

void comando_lcd(unsigned char c);

void texto_lcd(const char * s);

void limpa_lcd(void);

void linha1_lcd(void);

void linha2_lcd(void);

void xy_lcd(unsigned char linha, unsigned char coluna);

void cursor_On(void);

void cursor_Off(void);

void inicializa_lcd(void);

void Grava_CGRAM(void);

void Simbolos_lcd(unsigned int letra);



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

