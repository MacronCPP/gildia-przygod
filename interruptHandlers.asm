.area _CODE
.globl _vbl_own
.globl _lcd_own
.globl _OAM_START_TRANSFER
_vbl_own:
        LDH	A,(0xFF40)
        OR	#0b00010000	; Set BG Chr to 0x8000
        LDH	(0xFF40),A       ; LCDC - LCD control - FF40

        LD	A,#72		; Set line at which LCD interrupt occurs
        LDH	(0xFF45),A      ; LYC - ff45

        RET

        ;; Is the STAT check required, as we are already in the HBL?
_lcd_own:
1$:
        LDH	A,(0xFF41)       ; LCDSTAT - FF41
        BIT	1,A
        JR	NZ,1$

        LDH	A,(0xFF40)
        AND	#0b11101111	; Set BG Chr to 0x8800
        LDH	(0xFF40),A

        RET

_OAM_START_TRANSFER:
DI
CALL #0xFF80
EI
RET
