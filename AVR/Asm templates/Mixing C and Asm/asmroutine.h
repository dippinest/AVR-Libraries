
#ifndef ASMROUTINE_H_
#define ASMROUTINE_H_

// И в ассемблерной секции, и в секции языка Си определяем функции
// как глобальные (могут быть использованы вне файла реализации)
// -------------------------------------------------------------------------------
// Both in the assembly section and in the C language section,
// we define functions as global (can be used outside the implementation file)
#ifdef __ASSEMBLER__

// Для регистров используем смещение 0
// -------------------------------------------------------------------------------
// For registers we use offset 0
#define __SFR_OFFSET 0

#include <avr/io.h>
.global Set_BitMask
.global Reset_BitMask

#else

extern void Set_BitMask(volatile void* port, uint8_t bit_pos);
extern void Reset_BitMask(volatile void* port, uint8_t bit_pos);

#endif

#endif
