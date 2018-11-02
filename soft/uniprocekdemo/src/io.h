/*
 * io.h
 *
 *  Created on: Sep 7, 2011
 *      Author: mirek
 */

#ifndef IO_H_
#define IO_H_



#define DIAG_TXD_Pin GPIO_Pin_10
#define DIAG_TXD_GPIO GPIOB

#define DIAG_RXD_Pin GPIO_Pin_11
#define DIAG_RXD_GPIO GPIOB

#define PA2_Pin GPIO_Pin_2
#define PB8_Pin GPIO_Pin_8








extern const GPIO_TypeDef *DBUSGPIOTable[12];
extern const uint32_t DBUSPinTable[12];


void DATasOutput(void);
void GPIO_Configuration(void);
void DATset(uint16_t k);

void DBUSasInput(void);

#endif /* IO_H_ */
