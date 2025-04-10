#include "hal_uart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#define MYUBRR F_CPU/16/UART_BAUD-1

char rx_buffer[UART_RX_BUFFER_SIZE];
uint8_t rx_index = 0;
volatile uint8_t command_ready = 0;

int uart_putchar(char c, FILE *stream) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

ISR(USART_RX_vect) {
    char received = UDR0;

    if (rx_index < UART_RX_BUFFER_SIZE - 1) {
        rx_buffer[rx_index++] = received;

        if (received == '\n') {
            rx_buffer[rx_index] = '\0';
            command_ready = 1;
            rx_index = 0;
        }
    } else {
        rx_index = 0;
    }
}

void HAL_UART_Init(void)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)((MYUBRR) >> 8);
    UBRR0L = (unsigned char)(MYUBRR);
    
    /* Enable UART receiver and transmitter */
    SET_BIT(UCSR0B, RXEN0);
    SET_BIT(UCSR0B, TXEN0);
    
    /* Enable RX complete interrupt enable*/
#if UART_RX_INTERRUPT
    SET_BIT(UCSR0B, RXCIE0);
#endif
    
    /* Set data bit*/
#if UART_DATA_BITS == 5
    CLEAR_BIT(UCSR0B, UCSZ02);
    CLEAR_BIT(UCSR0C, UCSZ01);
    CLEAR_BIT(UCSR0C, UCSZ00); 
#elif UART_DATA_BITS == 6
    CLEAR_BIT(UCSR0B, UCSZ02);
    CLEAR_BIT(UCSR0C, UCSZ01);
    SET_BIT(UCSR0C, UCSZ00); 
#elif UART_DATA_BITS == 7
    CLEAR_BIT(UCSR0B, UCSZ02);
    SET_BIT(UCSR0C, UCSZ01);
    CLEAR_BIT(UCSR0C, UCSZ00); 
#elif UART_DATA_BITS == 8
    CLEAR_BIT(UCSR0B, UCSZ02);
    SET_BIT(UCSR0C, UCSZ01);
    SET_BIT(UCSR0C, UCSZ00); 
#elif UART_DATA_BITS == 9
    SET_BIT(UCSR0B, UCSZ02);
    SET_BIT(UCSR0C, UCSZ01);
    SET_BIT(UCSR0C, UCSZ00); 
#else
#error UART_DATA_BITS unsupported value
#endif
    
    /* Set parity*/
#if UART_PARITY == 0
    CLEAR_BIT(UCSR0C, UPM01);
    CLEAR_BIT(UCSR0C, UPM00);
#elif UART_PARITY == 1
    SET_BIT(UCSR0C, UPM01);
    SET_BIT(UCSR0C, UPM00);
#elif UART_PARITY == 2
    SET_BIT(UCSR0C, UPM01);
    CLEAR_BIT(UCSR0C, UPM00);
#else
#error UART_PARITY unsupported value
#endif
    
    /* Set stop bits*/
#if UART_STOP_BITS == 1
    CLEAR_BIT(UCSR0C, USBS0);
#elif UART_STOP_BITS == 2
    SET_BIT(UCSR0C, USBS0);
#else
#error UART_STOP_BITS unsupported value
#endif
    stdout = &uart_output;
    
    printf("uart init\r\n");
}

void HAL_UART_Process(void)
{
    if (command_ready) {
        HAL_UART_CommandHandler(rx_buffer);
        command_ready = 0;
    }
}
