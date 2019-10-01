/* 
 * File:   eeprom.h
 * Author: Eliel Marcos
 *
 * Created on 2 de Novembro de 2018, 13:01
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

unsigned char ler_eeprom(unsigned int address);

void escrever_eeprom(unsigned int address, unsigned char DADO_EEPROM);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

