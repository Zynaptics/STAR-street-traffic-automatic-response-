.include "m328pdef.inc"

.def temp = r16        ; Temporary register for operations

.org 0x0000

; I/O Pins Configuration
    CBI     DDRB, 0         ; Set PB0 (D8) as input for sensor 1
    SBI     PORTB, 0        ; Enable pull-up resistor on PB0
    
    CBI     DDRB, 1         ; Set PB1 (D9) as input for sensor 2
    SBI     PORTB, 1        ; Enable pull-up resistor on PB1
    
    SBI     DDRD, 7         ; Set PD7 (D7) as output for LED
    CBI     PORTD, 7        ; Initially turn LED off

main_loop:
    ; Read both sensors
    IN      temp, PINB      ; Read all PORTB pins at once
    
    ; Invert PB0 (D8) bit (XOR with 0b00000001)
    LDI     r17, 0b00000001 ; Load mask for PB0
    EOR     temp, r17       ; Invert PB0 bit
    
    ; Check if both sensors are HIGH (after inversion of PB0)
    ANDI    temp, 0b00000011 ; Mask for PB0 and PB1
    CPI     temp, 0b00000011 ; Compare with both HIGH
    
    BREQ    turn_on         ; If equal (both HIGH), turn on LED
    RJMP    turn_off        ; Otherwise turn off LED

turn_on:
    SBI     PORTD, 7        ; Turn LED ON
    RJMP    main_loop

turn_off:
    CBI     PORTD, 7        ; Turn LED OFF
    RJMP    main_loop