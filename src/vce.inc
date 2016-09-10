; file: vce.inc
; VCE related macros and defines.
;                                                                              ;

; VCE/HuC6260 (physical page $FF, mapped into logical page $00)

.DEFINE VCE_MAIN          $0400
;---------------;---------------;----------------------------------------------;
.DEFINE VCE_CONTROL   VCE_MAIN      ; VCE Control Register
.DEFINE CTAL	      VCE_MAIN+2    ; Color Table Address Register
.DEFINE CTAH	      VCE_MAIN+3    ; Color Table Address Register
.DEFINE CTWL	      VCE_MAIN+4    ; Color Table Read/Write Register
.DEFINE CTWH	      VCE_MAIN+5    ; Color Table Read/Write Register

;------------------------------------------------------------------------------;
; VCE control:
; 76543210
; ||__||||
; |  | |++- dot clock (see below)
; |  | +--- blur edges of sprites/bg chars
; |  +----- no effect
; +-------- monochrome (0 color; 1 monochrome)

.DEFINE VCE_DOTCLOCK_5MHZ      %00 ; 00 - 5MHz
.DEFINE VCE_DOTCLOCK_7MHZ      %01 ; 01 - 7MHz
.DEFINE VCE_DOTCLOCK_10MHZ_B   %10 ; 10 - 10MHz, less artifacts (B   "better")
.DEFINE VCE_DOTCLOCK_10MHZ_W   %11 ; 11 - 10MHz, more artifacts (W   "worse")

.DEFINE VCE_BLUR_ON    1<<2
.DEFINE VCE_BLUR_OFF   0<<2

.DEFINE VCE_MODE_COLOR   $00 ; color mode
.DEFINE VCE_MODE_MONO    $80 ; monochrome mode

;------------------------------------------------------------------------------;
; VCE palette locations
.DEFINE VCE_BGPAL	    $000 ; first 256 colors are BG
.DEFINE VCE_SPRPAL		$100 ; second 256 colors are SPR
.DEFINE VCE_PALSET_SIZE	16   ; 16 colors per palette set

.MACRO PCE_VCE_ADDR
	ldx #<\1
	ldy #>\1
	stx CTAL
	sty CTAH
.ENDM

.MACRO PCE_VCE_DATA
	ldx #<\1
	ldy #>\1
	stx CTWL
	sty CTWH
.ENDM

.MACRO PCE_VCE_CONTROL
	lda #\1
	sta VCE_CONTROL
.ENDM

