
; Этот файл содержит макросы для реализации программных задержек
; (в тактах или миллисекундах). Такие задержки НЕ ЯВЛЯЮТСЯ точными,
; поэтому если необходим отсчёт точных временных отрезков, используйте таймеры.
;
; Если вы используйте устаревшие версии микроконтроллеров линейки ATtiny
; без RAM (например, ATtiny10/11/12), то используйте только задержку в
; циклах (макросы DELAY_CLK8 и DELAY_CLK16), поскольку макрос DELAY_MS
; использует операции со стеком.
; -------------------------------------------------------------------------------
; This file contains macros for implementing program delays (in clock cycles
; or milliseconds). Such delays ARE NOT accurate, so if you need to count
; down exact time intervals, use timers.
;
; If you are using outdated versions of the ATtiny line of microcontrollers
; without RAM (for example, ATtiny10/11/12), then use only the delay in cycles
; (macros DELAY_CLK8 and DELAY_CLK16), since the DELAY_MS macro uses stack operations.
;
; ===============================================================================
; ===============================================================================


; Тактовая частота CPU в герцах (мин - 2000000 Гц (2 МГц))
; -------------------------------------------------------------------------------
; CPU clock frequency in Hz (mib - 2000000 Hz (2 MHz))
.EQU F_CPU = 16000000


; Макрос для задержки в тактах (макс - 255 тактов)
; -------------------------------------------------------------------------------
; Macro for delay in clock cycles (max - 255 clock cycles)
.MACRO DELAY_CLK8

	LDI R16, LOW(@0) - 5

	L1_DELAY_CLK8:

		SUBI R16, 4
		CPI  R16, 4

		BRSH L1_DELAY_CLK8

		CPI  R16, 1

		BREQ L2_DELAY_CLK8

		CPI  R16, 0

		BREQ L3_DELAY_CLK8_EXIT

		CPI  R16, 2

		BREQ L3_DELAY_CLK8_EXIT
		RJMP L3_DELAY_CLK8_EXIT

	L2_DELAY_CLK8:

		NOP
		NOP
		NOP

	L3_DELAY_CLK8_EXIT:

.ENDM


; Макрос для задержки в тактах (макс - 65535 тактов)
; -------------------------------------------------------------------------------
; Macro for delay in clock cycles (max - 65535 clock cycles)
.MACRO DELAY_CLK16

	LDI  R16, LOW(@0)
	CPI  R16, 17

	BRSH L1_DELAY_CLK16
			
	RJMP L2_DELAY_CLK16

	L1_DELAY_CLK16:
	
		DELAY_CLK8 LOW(@0 - 7)
	
	L2_DELAY_CLK16:

		LDI  R17, HIGH(@0)
		CPI  R17, 0
		BREQ L4_DELAY_CLK8_EXIT
	
	L3_DELAY_CLK16:

		SUBI R17, 1

		DELAY_CLK8 252

		CPI  R17, 0
		BRNE L3_DELAY_CLK16
		NOP
	
	L4_DELAY_CLK8_EXIT:

.ENDM


; Макрос для задержки в миллисекундах (макс - 65535 мс (~ 65 сек))
; -------------------------------------------------------------------------------
; Macro for delay in milliseconds (max - 65535 ms (~ 65 sec))
.MACRO DELAY_MS

	PUSH R19
	PUSH R18
	PUSH R17
	PUSH R16

	LDI  R18, LOW(@0)
	LDI  R19, HIGH(@0)

	CPI  R18, 0
	BREQ L2_DELAY_MS

	L1_DELAY_MS:

		DELAY_CLK16 (F_CPU / 1000)

		SUBI R18, 1				
		CPI  R18, 0				
		BREQ L2_DELAY_MS		
		RJMP L1_DELAY_MS		

	L2_DELAY_MS:

		CPI  R19, 0
		BREQ L3_DELAY_MS_EXIT
		SUBI R19, 1
		LDI  R18, 255

		DELAY_CLK16 ((F_CPU / 1000) - 255 * 5)

		RJMP L1_DELAY_MS

	L3_DELAY_MS_EXIT:

		POP R16
		POP R17
		POP R18
		POP R19

.ENDM
