        ORG 0000H          ; Reset vector
        LJMP MAIN          ; Jump to main program

;---------------------------------------------------
; Interrupt Vector Table
;---------------------------------------------------
        ORG 0003H          ; External Interrupt 0 vector address
        LJMP EX0_ISR       ; Jump to External INT0 ISR

;---------------------------------------------------
; Bit flag in bit-addressable RAM
; TOGFLAG = 0 ? normal (P2 = P1)
; TOGFLAG = 1 ? inverted (P2 = ~P1)
;---------------------------------------------------
TOGFLAG BIT 20H            ; Use bit-addressable RAM location 20H

;---------------------------------------------------
; Main Program
;---------------------------------------------------
        ORG 0030H
MAIN:
        MOV P1, #0FFH      ; Port 1 as INPUT (switches)
        MOV P2, #00H       ; Port 2 as OUTPUT (LEDs initially OFF)

        CLR TOGFLAG        ; Start with normal display (no invert)

        MOV IE, #81H       ; EA=1 (global enable), EX0=1 (enable INT0)
        MOV TCON, #01H     ; IT0=1 (edge trigger on INT0), IE0=0

MAIN_LOOP:
        MOV A, P1          ; Read switches from Port 1

        JNB TOGFLAG, NO_INVERT  ; If TOGFLAG = 0, skip inversion
        CPL A              ; If TOGFLAG = 1 ? invert whole pattern
NO_INVERT:
        MOV P2, A          ; Output pattern on Port 2 LEDs

        SJMP MAIN_LOOP     ; Repeat forever

;---------------------------------------------------
; External Interrupt 0 ISR (INT0 - P3.2)
;---------------------------------------------------
EX0_ISR:
        CPL TOGFLAG        ; Toggle flag on every button press
        RETI               ; Return from interrupt

        END
