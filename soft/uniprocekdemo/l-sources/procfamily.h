#ifndef _PROCFAMILY_H_
#define _PROCFAMILY_H_

#if defined (STM32F10X_MD_VL)
#include "stm32f10x.h"
#endif

#if defined (STM32F100CB) || defined (STM32F100C8)
typedef struct{
	const uint16_t F_Size;/*!< F_ID(15:0): Flash memory size Address offset: 0x00 */
	const uint16_t RESERVED1;/*!< Address offset: 0x04 */
	const uint32_t UID31_0;/*!< UID(31:0): x and y coordinates on the wafer expressed in BCD format, address offset: 0x08 */
	const uint32_t UID63_32;/*!< UID(63:32): [63:40] lot number (ASCII encoded), [39:32] wafer number (8-bit unsigned number), address offset: 0x0C */
	const uint32_t UID95_64;/*!< UID(95:64): number (ASCII encoded), Address offset: 0x10 */
}SIGNATURE_TypeDef;
#define SIGNATURE_BASE (0x1FFFF7E0)
#define SIGNATURE      ((SIGNATURE_TypeDef *) SIGNATURE_BASE)
#endif

#if defined (STM32F10X_HD) || defined (STM32F10X_MD)
	#include "stm32f10x.h"
	typedef struct{
		const uint16_t F_Size;/*!< F_ID(15:0): Flash memory size Address offset: 0x00 */
		const uint16_t RESERVED1;/*!< Address offset: 0x04 */
		const uint16_t UID15_0;/*!<   */
		const uint16_t UID31_16;/*!<   */
		const uint32_t UID63_32;/*!< UID(63:32): [63:40] lot number (ASCII encoded), [39:32] wafer number (8-bit unsigned number)*/
		const uint32_t UID95_64;/*!< UID(95:64): number (ASCII encoded) */
	}SIGNATURE_TypeDef;

	#define SIGNATURE_BASE (0x1FFFF7E0)
	#define SIGNATURE      ((SIGNATURE_TypeDef *) SIGNATURE_BASE)
#endif

#if defined (STM32F030X6)
#include "stm32f0xx.h"
#endif
#if defined (STM32F0XX_MD)
#include "stm32f0xx.h"
typedef struct{
	const uint32_t UID31_0;/*!< UID(31:0): x and y coordinates on the wafer expressed in BCD format, address offset: 0x00 */
	const uint32_t UID63_32;/*!< UID(63:32): [63:40] lot number (ASCII encoded), [39:32] wafer number (8-bit unsigned number), address offset: 0x04 */
	const uint32_t UID95_64;/*!< UID(95:64): number (ASCII encoded), Address offset: 0x08 */
}SIGNATURE_TypeDef;

#define SIGNATURE_BASE (0x1FFFF7AC)
#define SIGNATURE      ((SIGNATURE_TypeDef *) SIGNATURE_BASE)
#endif
#if defined (STM32F4XX)
#include "stm32f4xx.h"
#define RCC_CRCClockCmd RCC_AHB1PeriphClockCmd
#define RCC_AHBPeriph_CRC RCC_AHB1Periph_CRC

typedef struct{
	const uint32_t U_ID31_0;/*!< U_ID(31:0): 31:0 unique ID bits Address offset: 0x00 */
	const uint32_t U_ID63_32;/*!< U_ID(63:32): 63:32 unique ID bits Address offset: 0x04 */
	const uint32_t U_ID95_64;/*!< U_ID(95:64): 95:64 Unique ID bits Address offset: 0x08 */
	const uint32_t RESERVED1;/*!< Address offset: 0x0C */
	const uint16_t RESERVED2;/*!< Address offset: 0x10 */
	const uint16_t F_Size;/*!< F_ID(15:0): Flash memory size Address offset: 0x12 */
}SIGNATURE_TypeDef;

#define SIGNATURE_BASE (0x1FFF7A10)
#define SIGNATURE      ((SIGNATURE_TypeDef *) SIGNATURE_BASE)
#endif

#endif
