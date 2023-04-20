#ifndef USART_H
#define USART_H

#include <avr/io.h>

void USART_Init(unsigned int baudrate);
void USART_InitBT(unsigned int baudrate);
void USART_TransmitStringBT(char* data);
int USART_AvailableBT(void);
void USART_ReadBytesUntilBT(char terminator, char* buffer, int max_length);
void USART_TransmitString(char* data);
void USART_TransmitIntBT(int num);


#endif // USART_H
