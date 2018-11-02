/**
  ******************************************************************************
  * @file    ascii.h
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Plik nag³ówkowy procedur przetwarzaj¹cych znaki ASCII
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */


#ifndef __ASCII_H__
#define __ASCII_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CTRL_C 0x03
#define CTRL_M  0x0d
#define NUL_KEY 0x00
#define SOH_KEY 0x01
#define STX_KEY 0x02
#define ETX_KEY 0x03
#define EOT_KEY 0x04
#define ENQ_KEY 0x05
#define ACK_KEY 0x06
#define BEL_KEY 0x07
#define BS_KEY  0x08
#define TAB_KEY 0x09
#define LF_KEY  0x0a
#define VT_KEY  0x0b
#define FF_KEY  0x0c
#define CR_KEY  0x0d
#define SO_KEY  0x0e
#define SI_KEY  0x0f
#define DLE_KEY 0x10
#define DC1_KEY 0x11
#define DC2_KEY 0x12
#define DC3_KEY 0x13
#define DC4_KEY 0x14
#define CTRL_T  DC4_KEY
#define NAK_KEY 0x15
#define SYN_KEY 0x16
#define ETB_KEY 0x17
#define CAN_KEY 0x18
#define EM_KEY  0x19
#define SUB_KEY 0x1a
#define CTRL_Z  SUB_KEY
#define ESC_KEY 0x1b
#define FS_KEY  0x1c
#define GS_KEY  0x1d
#define RS_KEY  0x1e
#define US_KEY  0x1f
#define ENTER_KEY CR_KEY
#define APOSTROPHE (0x27)

int ASCIIConvertUnVisibleChar(char *buf, char c);
int ASCIIConvertUnVisibleCharBuf(char *bufd, char * buf);
char *ASCIInConvertUnVisibleCharBuf(char *bufd, char *buf, int size);

extern const char NewLineMsg[];

#ifdef __cplusplus
}
#endif

#endif /* __ASCII_H__ */
