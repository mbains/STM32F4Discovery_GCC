/* 
 * File:   usart.h
 * Author: mannyb
 *
 * Created on November 23, 2013, 11:51 PM
 */

#ifndef USART_H
#define	USART_H



int usart_init();
int usart_TxTest();

int usart_getc(void);
int usart_putc(int c);

int usart_write_arr(char *p, int len);
int usart_read_arr(char *p, int len);


#endif	/* USART_H */

