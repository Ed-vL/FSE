#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>   
#include <string.h>     //Used for UART
#include "../inc/crc.h"
#include "../inc/uart.h"

int uart0_filestream = -1;

void openUart(){
    
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    } 
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void closeUart(){
    close(uart0_filestream);
}

float getTempUart(char code, int size){
    float response = 0.0;
    unsigned char tx_buffer[200];
    tx_buffer[0] = 0x01;
    tx_buffer[1] = 0x23;
    tx_buffer[2] = code;
    tx_buffer[3] = 0x02;
    tx_buffer[4] = 0x03;
    tx_buffer[5] = 0x04;
    tx_buffer[6] = 0x03;
    short crc = calcula_CRC(tx_buffer, size);
    short responseCrc;
    
    if (uart0_filestream != -1)
    {

        int count = write(uart0_filestream, &tx_buffer[0], size);
        write(uart0_filestream,&crc,2);

        if (count < 0)
        {
            printf("UART TX error\n");
        }

    }
    usleep(100000);
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
        else
        {
            //Bytes received
            rx_buffer[rx_length] = '\0';
            memcpy(&response, &rx_buffer[3], 4);
            memcpy(&responseCrc,&rx_buffer[7],2);
        }
            //verify_CRC(rx_buffer, 9, responseCrc);
            return response;
        
        
    }
    return response;
}
