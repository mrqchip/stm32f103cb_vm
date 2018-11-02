#ifndef BITS_H__
#define BITS_H__


#define SETBIT(byte,sbit)      byte |= (1<<(sbit))
#define RESETBIT(byte,sbit)    byte &= (~(1<<(sbit)))
#define TESTBIT(byte,sbit)     (byte & (1<<(sbit)))
#define COMPBITS(byte1,bit1,byte2,bit2) (((byte1 & (1<<bit1))>>bit1) == ((byte2 & (1<<bit2))>>bit2))
#define COMPSAMEBITS(byte1,byte2,sbit)  ((byte1 & (1<<sbit)) == (byte2 & (1<<sbit)))

#define COPYBIT(byteto,bitto,bytefrom,bitfrom) \
            if (TESTBIT(bytefrom,bitfrom))     \
						{                                  \
						 	SETBIT(byteto,bitto);            \
						}                                  \
						else                               \
						{                                  \
							RESETBIT(byteto,bitto);          \
						}
#define COPYSAMEBIT(byteto,bytefrom,sbit)   COPYBIT(byteto,bit,bytefrom,sbit)
#define INVERTBIT(byte,sbit)   byte ^= (1<<sbit) 



#endif
