.area _CODE_2
.globl .copy_vram
.globl _draw_image_own
_draw_image_own:
;;This file is made of few functions joined together from drawing.s file from gbdk
;;Drawing.s has a few KB, but I only use one function of it
;;So this memory is quite important for me
;; Turn the screen off
LDH	A,(0xFF40); LCDC - LCD control - FF40
BIT	7,A
JR	Z,1$

;; Turn the screen off
CALL	.display_off
1$:
LD	HL,#0x8000+0x10*0x10
LD	DE,#0x1800-0x18*0x10
LD	B,#0x00
CALL	.init_vram	; Init the charset at 0x8000

;; Install interrupt routines
LD	BC,#_vbl_own
CALL	.add_VBL
LD	BC,#_lcd_own
CALL	.add_LCD

LD	A,#72		; Set line at which LCD interrupt occurs
LD	(0xFF45),A      ; LYC - ff45

LD	A,#0b01000100	; Set LCD interrupt to occur when LY = LCY
LDH	(0xFF41),A        ; LCDSTAT - FF41

LDH	A,(0xFFFF)         ; IE - Interrupt Enable - FFFF
OR	#0b00000010	; Enable LCD interrupt
LDH	(0xFFFF),A
;; (9*20) = 180 tiles are used in the upper part of the screen
;; (9*20) = 180 tiles are used in the lower part of the screen
;; => We have 24 tiles free
;; We keep 16 at 0x8000->0x80FF, and 8 at 0x9780->97FF
LD	HL,#0x9800
LD	A,#0x10		; Keep 16 tiles free
LD	BC,#12		; 12 unused columns
LD	E,#18		; 18 lines
2$:
LD	D,#20		; 20 used columns
3$:
LD	(HL+),A
INC	A
DEC	D
JR	NZ,3$
ADD	HL,BC
DEC	E
JR	NZ,2$
LDH	A,(0xFF40)       ; LCDC - LCD control - FF40
OR	#0b10010001	; LCD		= On
                        ; BG Chr	= 0x8000
                        ; BG		= On
AND	#0b11110111	; BG Bank	= 0x9800
LDH	(0xFF40),A
EI			; Enable interrupts
PUSH    BC

LDA	HL,4(SP)	; Skip return address and registers
LD	A,(HL+)	; HL = data
LD	C,A
LD	B,(HL)

LD      HL,#0x8000+0x10*0x10
LD      DE,#0x1680
CALL    .copy_vram
POP	BC
RET

