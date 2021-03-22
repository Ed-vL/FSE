#ifndef _CRC_
#define _CRC_


short CRC16(short crc, char data);
short calcula_CRC(unsigned char *commands, int size);
int verify_CRC(unsigned char *commands, int size, short crc);

#endif