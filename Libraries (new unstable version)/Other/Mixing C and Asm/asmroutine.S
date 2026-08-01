
#include "asmroutine.h"

; ===============================================================================
;
; В файлах *.S можно непосредственно описывать функции и процедуры на языке
; ассемблера. Чтобы написать функцию, вызываемую из С, необходимо знать соглашения
; AVR-GCC о вызове. Полностью их можно найти в соответствующем разделе FAQ AVR-libc.
;
; Передача и возврат аргументов происходят следующим образом:
;
; - аргументы передаются в регистрах, с R25 (первый) по R8, то, что не влезает,
;   передается в стеке. При этом очередной параметр всегда начинается в регистре с
;   чётным номером, т.е., наш байт в примере будет лежать в R24. Если бы это был
;   int - он бы расположился в R25:R24, и т.д.
;
; - результат выполнения тоже возвращается в регистрах: char в R24, int в R25:R24, и т.д.
;
; - регистры с R18 по R27, а также R30 и R31 можно использовать как угодно,
;   остальные без нужды лучше не использовать.
;
; -------------------------------------------------------------------------------
;
; *.S files can directly describe functions and procedures in assembly language.
; To write a function called from C, you need to know the AVR-GCC calling conventions.
; They can be found in full in the corresponding section of the AVR-libc FAQ.
;
; Arguments are passed and returned as follows:
;
; - arguments are passed in registers, from R25 (first) to R8, what does not
;   fit is passed on the stack. In this case, the next parameter always starts
;   in a register with an even number, i.e., our byte in the example will lie in R24.
;   If it was int, it would be located in R25:R24, etc.
;
; - the result of execution is also returned in registers: char in R24, int in R25:R24, etc.
;
; - registers from R18 to R27, as well as R30 and R31 can be used as you like, it is
;   better not to use the rest unnecessarily.
;
; ===============================================================================

Set_BitMask:
	
	; Копирование переданного указателя из регистров R25:R24 в регистровую
	; пару Z (R31:R30) и загрузка соответствующего значения в регистр R17
	; -------------------------------------------------------------------------------
	; Copying the passed pointer from registers R25:R24 to the register
	; pair Z (R31:R30) and loading the corresponding value into register R17
	MOVW R30, R24
	LD   R17, Z

	; Установка битовой маски в целевое байтовое значение
	; -------------------------------------------------------------------------------
	; Setting the bit mask to the target byte value
	OR   R17, R22

	; Загрузка обновлённого значения по указателю в регистровой паре Z
	; -------------------------------------------------------------------------------
	; Loading the updated value by pointer in the Z register pair
	ST   Z, R17

	; Возврат из процедуры
	; -------------------------------------------------------------------------------
	; Return from the procedure
	RET

Reset_BitMask:
	
	; Копирование переданного указателя из регистров R25:R24 в регистровую
	; пару Z (R31:R30) и загрузка соответствующего значения в регистр R17
	; -------------------------------------------------------------------------------
	; Copying the passed pointer from registers R25:R24 to the register
	; pair Z (R31:R30) and loading the corresponding value into register R17
	MOVW R30, R24
	LD   R17, Z

	; Сброс битовой маски в целевое байтовое значение
	; -------------------------------------------------------------------------------
	; Resetting the bit mask to the target byte value
	COM  R22
	AND  R17, R22

	; Загрузка обновлённого значения по указателю в регистровой паре Z
	; -------------------------------------------------------------------------------
	; Loading the updated value by pointer in the Z register pair
	ST   Z, R17

	; Возврат из процедуры
	; -------------------------------------------------------------------------------
	; Return from the procedure
	RET
