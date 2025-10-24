
.LIST
.DSEG
.CSEG

.INCLUDE "delay.inc"

.ORG 0x0000

Main:
	
	SEI

	LDI  R16,  (1 << 7)
	OUT  DDRD, R16

	Main_Loop:

		; Задержка составляет 32000 тактов => F_CPU (16000000) / 32000 = 500 Гц
		; (2 мс) на одно переключение светодиода или 250 Гц (4 мс) на один цикл мигания
		; -------------------------------------------------------------------------------
		; The delay is 32000 clock cycles => F_CPU (16000000) / 32000 = 500 Hz (2 ms)
		; for one LED switching or 250 Hz (4 ms) for one flashing cycle
		DELAY_CLK16 32000

		IN  R16,   PORTD
		LDI R17,   (1 << 7)
		EOR R16,   R17
		OUT PORTD, R16

    RJMP Main_Loop
