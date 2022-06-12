
; Это пример на языке ассемблера реализует программу Blink, суть которой
; мигать светодиодом с помощью порта GPIO с определённой периодичностью.
; Этот код является шаблоном проекта с закомментированными строками является
; своего рода шпаргалкой, которая всегда под рукой.
;
; Помните: язык ассемблера очень прост, хотя писать на нём несколько сложнее, чем на Си :)
; -------------------------------------------------------------------------------
; This example in assembly language implements the Blink program,
; the essence of which is to flash the LED using the GPIO port with a
; certain frequency. This code is a project template with commented-out lines
; is a kind of cheat sheet that is always at hand.
;
; Remember: the assembly language is very simple,
; although it is somewhat more difficult to write in it than in C :)

; ===============================================================================
; ===============================================================================


; Директива LIST указывает компилятору на необходимость создания листинга.
; Листинг представляет из себя комбинацию ассемблерного кода, адресов и кодов
; операций. По умолчанию генерация листинга включена, однако данная директива
; используется совместно с директивой NOLIST для получения листингов отдельных
; частей исходных файлов
; -------------------------------------------------------------------------------
; The LIST directive tells the compiler to create a listing. The listing is a
; combination of assembly code, addresses, and opcodes. By default, listing
; generation is enabled, but this directive is used in conjunction with the
; NOLIST directive to obtain listings of individual parts of the source files
.LIST

; С помощью директивы .DEF задаём регистру R16 псевдоним T0_OVF_Counter
; -------------------------------------------------------------------------------
; With the help of a directive .DEF we set the case R16 alias T0_OVF_Counter
.DEF T0_OVF_Counter = R17

; Директива DSEG определяет начало сегмента данных. Исходный файл
; может состоять из нескольких сегментов данных, которые объединяются в
; один сегмент при компиляции. Сегмент данных обычно состоит только из
; директив BYTE и меток. Сегменты данных имеют свои собственные побайтные
; счётчики положения. Директива ORG может быть использована для размещения
; переменных в необходимом месте ОЗУ
; -------------------------------------------------------------------------------
; The CSEG directive defines the beginning of a data segment. The source
; file may consist of several data segments that are combined into one segment
; during compilation. A data segment usually consists only of BYTE directives
; and labels. Data segments have their own byte-by-byte position counters.
; The ORG directive can be used to place variables in the required RAM location
.DSEG

; ===============================================================================

; Сегмент кода. После директивы CSEG идёт описание кода программы
; или данных, хранящихся во флеш памяти
; -------------------------------------------------------------------------------
; Code segment. After the CSEG directive there is a description
; of the program code or data stored in flash memory
.CSEG

; Директива ORG устанавливает счётчик положения равным заданной величине,
; которая передаётся как параметр. Для сегмента данных она устанавливает
; счётчик положения в SRAM (ОЗУ), для сегмента программ это программный счётчик,
; а для сегмента EEPROM это положение в EEPROM. Если директиве предшествует метка
; (в той же строке) то метка размещается по адресу указанному в параметре директивы.
; Перед началом компиляции программный счётчик и счётчик EEPROM равны нулю,
; а счётчик ОЗУ равен 32 (поскольку адреса 0-31 заняты регистрами).
; Обратите внимание что для ОЗУ и EEPROM используются побайтные счётчики,
; а для программного сегмента - пословный
; -------------------------------------------------------------------------------
; The ORG directive sets the position counter equal to the specified value,
; which is passed as a parameter. For the data segment, it sets the position
; counter in SRAM (RAM), for the program segment it is the program counter,
; and for the EEPROM segment it is the position in the EEPROM. If the directive
; is preceded by a label (in the same line), then the label is placed at the
; address specified in the directive parameter. Before compilation begins,
; the program counter and the EEPROM counter are zero, and the RAM counter
; is 32 (since addresses 0-31 are occupied by registers). Note that byte-by-byte
; counters are used for RAM and EEPROM, and for the program segment - word-by-word
.ORG 0x0000

; Переход к основной метке (точке входа в программу)
; Transition to the main label (entry point to the program)
RJMP Main



; ======================= INTERRUPT VECTORS TABLE ==============================

; Здесь описаны используемые вектора прерываний и адреса
; -------------------------------------------------------------------------------
; The interrupt vectors and addresses used are described here


; Адрес вектора прерывания по переполнению счётчика T0 и метка на его обработчик
; -------------------------------------------------------------------------------
; Address of the interrupt vector for the overflow of the counter T0
; and the label on it is handler
.ORG 0x009
	RJMP TIMER0_OVF

; ===============================================================================



; ========================== INTERRUPT HANDLERS =================================

; Здесь описаны используемые вектора прерываний и адреса
; -------------------------------------------------------------------------------
; The handlers of the interrupts used are described here


; Обработчик прерывания по вектору TIMER0_OVF
; -------------------------------------------------------------------------------
; Interrupt handler by TIMER0_OVF vector
TIMER0_OVF:

	; Задаём начальное значение счётного регистра
	; -------------------------------------------------------------------------------
	; Setting the initial value of the counting register
	LDI  R16,   255 - 250
	OUT  TCNT0, R16

	; Сравниваем счётчик прерываний с вычисленным константным значением и если он
	; больше или равен, то переходим на метку LED_SWITCH
	; -------------------------------------------------------------------------------
	; Compare the interrupt counter with the calculated constant value and
	; if it is greater than or equal to, then switch to the LED_SWITCH label
	CPI  T0_OVF_Counter, 125
	BREQ LED_SWITCH

	; Иначе - инкрементируем счётчик и выходим из прерывания
	; -------------------------------------------------------------------------------
	; Else increment the counter and exit the interrupt
	INC  T0_OVF_Counter
	RETI

	LED_SWITCH:

		; Обнуляем счётчик
		; -------------------------------------------------------------------------------
		; Counter reset
		LDI T0_OVF_Counter, 0x00

		; Читаем значение из порта PORTD и сравниваем его с целевым битом
		; -------------------------------------------------------------------------------
		; Read the value from the PORTD port and compare it with the target bit
		IN   R16, PORTD
		CPI  R16, (1 << PORTD7)

		; Если предыдущее сравнение истинно (флаг C=0 в регистр SREG),
		; то переходим на метку LED_OFF, иначе - на метку LED_ON
		; -------------------------------------------------------------------------------
		; If the previous comparison is true (flag C=0 in the SREG register),
		; then switch to the LED_OFF label, otherwise to the LED_ON label
		BRSH LED_OFF
		RJMP LED_ON

		LED_OFF:
			; Устанавливаем целевой бит регистра R16 в 0 и переходим на метку WRITE_BIT_TO_PORT
			; -------------------------------------------------------------------------------
			; Set the target bit of the R16 register to 0 and switch to the WRITE_BIT_TO_PORT label
			ANDI R16, ~(1 << PORTD7)
			RJMP WRITE_BIT_TO_PORT

		LED_ON:
			; Устанавливаем целевой бит регистра R16 в 1
			; -------------------------------------------------------------------------------
			; Set the target bit of the R16 register to 1
			ORI  R16, (1 << PORTD7)

		WRITE_BIT_TO_PORT:
			; Записываем значение регистра R16 в регистр PORTD
			; -------------------------------------------------------------------------------
			; Write the value of the R16 register to the PORTD register
			OUT PORTD, R16

	; Выходим из прерывания
	; -------------------------------------------------------------------------------
	; Exiting the interrupt
	RETI

; ===============================================================================



; ================================ MACROS =======================================

; Здесь описаны используемые макросы
; -------------------------------------------------------------------------------
; The macros used are described here


; Макрос для инициализации стека
; -------------------------------------------------------------------------------
; Macro for stack initializing
.MACRO STACK_POINTER_INITIALIZE
	
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	LDI R16, LOW(RAMEND)
	OUT SPL, R16

.ENDM

; ===============================================================================



; ============================== PROCEDURES =====================================

; Здесь описаны используемые процедуры и функции (для их использования
; необходимо проинициализировать стек, чтобы сохранять контекст при вызове)
; -------------------------------------------------------------------------------
; The procedures and functions used are described here (to use them,
; you need to initialize the stack in order to preserve the context when calling)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; ===============================================================================



; Точка входа в программу (аналог функции main в Си)
; -------------------------------------------------------------------------------
; The entry point to the program (analogous to the main function in C)
Main:
	
	; В данной программе стек не нужен, поэтому инициализировать его не будем
	; -------------------------------------------------------------------------------
	; In this program, the stack is not needed, so we will not initialize it
	; STACK_POINTER_INITIALIZE

	; включаем глобальные прерывания
	; -------------------------------------------------------------------------------
	; global interrupt enable
	SEI

	; настройка 7 бита порта PORTD на выход
	; -------------------------------------------------------------------------------
	; setting the 7 bits of the PORTD port to output
	LDI  R16,  (1 << PORTD7)
	OUT  DDRD, R16

	; Будем переключать светодиод 1 раз в 500 мс. Для этого организуем задержку с
	; помощью счётчика T0 (8 bit) и его прерывания по переполнению.
	; Таймер настраиваем так:
	;
	; Предделитель = 255
	; Значение загружаемого значения в счётный регистр = (255 - 250) = 500
	; F_CPU (16 MHz) / Prescaler (255) / 250 = 250
	;
	; За 1 секунду произойдёт 250 прерываний по переполнению => за 500 мс произойдёт 125 прерываний
	; -------------------------------------------------------------------------------
	; We will switch the LED 1 time in 500 ms. To do this, we organize the delay using the counter T0 (8 bit) and its overflow interrupts.
	;
	; The timer is configured as follows:
	; Preddelitel = 255
	; The value of the loaded value in the counting register = (255 - 250) = 500
	;
	; F_CPU (16 MHz) / Prescaler (255) / 250 = 250
	;
	; 250 overflow interrupts will occur in 1 second => 125 interrupts will occur in 500 ms
	LDI  R16,   (1 << CS02)
	OUT  TCCR0, R16
	LDI  R16,   255 - 250
	OUT  TCNT0, R16

	; Разрешаем прерывания по переполнению счетчика T0
	; -------------------------------------------------------------------------------
	; Allow interrupts on the overflow of the counter T0
	LDI  R16,   (1 << TOIE0)
	OUT  TIMSK, R16

	Main_Loop:

	; В бесконечном цикле ничего не делаем
	; -------------------------------------------------------------------------------
	; In an infinite loop, we do nothing

    rjmp Main_Loop
