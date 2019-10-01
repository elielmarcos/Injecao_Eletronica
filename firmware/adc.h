/* 
 * File:   adc.h
 * Author: Eliel Marcos
 *
 * Created on 2 de Novembro de 2018, 03:39
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

long VALOR_ADC(unsigned char CH);

void VREF_NEGATIVA(unsigned char LD);

void VREF_POSITIVA(unsigned char LD);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

