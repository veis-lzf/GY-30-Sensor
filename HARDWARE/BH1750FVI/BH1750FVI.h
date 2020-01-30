#ifndef __BH1750FVI_H
#define __BH1750FVI_H

#include "I2C.h"

#define SlaveAddress 0x46
#define READ 1
#define WRITE 0

#define ACK 0
#define NOACK 1

extern unsigned char data[8];
extern unsigned char miao,fen,ge,shi,bai,qian,wan;            //œ‘ æ±‰¡ø

void init_BH1750(void);
void single_write_BHB1750(unsigned char REG_Address);
float multiple_read_BH1750(void);
unsigned char single_read_BH1750(unsigned char REG_Address);  
void conversion(unsigned int temp_data);
#endif


