; file: vdc.inc
; VDC related macros and defines.
;                                                                              ;

; VDC/HuC6270 (physical page $FF, mapped into logical page $00)

; must use absolute addressing (e.g. "sta a:VDC_STATUS")
;---------------;---------------;----------------------------------------------;
.DEFINE VDC_STATUS      $0000         ; VDC Status Register
.DEFINE VDC_DATAL   	$0002         ; Data Low Byte
.DEFINE VDC_DATAH 	    $0003         ; Data High Byte and Latch

; Equates for writing to VDC_STATUS
;---------------;---------------;----------------------------------------------;
.DEFINE VDCREG_MAWR       $00           ; Memory Address Write Register (VRAM Write Address)
.DEFINE VDCREG_MARR       $01           ; Memory Address Read Register (VRAM Read Address)
.DEFINE VDCREG_VRWD       $02           ; VRAM Data Read/Write Register
; (registers $03 and $04 are not used.)
.DEFINE VDCREG_CR         $05           ; Control Register
.DEFINE VDCREG_RCR        $06           ; Raster Counter Register
.DEFINE VDCREG_BXR        $07           ; Background X Scroll Register
.DEFINE VDCREG_BYR        $08           ; Background Y Scroll Register
.DEFINE VDCREG_MWR        $09           ; Memory Width Register (BG map virtual size)
.DEFINE VDCREG_HPR        $0A           ; Horizontal Synchronous Register (contains HDS, HSW)
.DEFINE VDCREG_HDR        $0B           ; Horizontal Display Register (contains HDE, HDW)
.DEFINE VDCREG_VSR        $0C           ; Vertical Synchronous Register (contains VDS, VSW)
.DEFINE VDCREG_VDR        $0D           ; Vertical Display Register (a.k.a. VDW)
.DEFINE VDCREG_VCR        $0E           ; Vertical Display Ending Postition Register
.DEFINE VDCREG_DCR        $0F           ; DMA Control Register
.DEFINE VDCREG_SOUR       $10           ; DMA Source Address Register
.DEFINE VDCREG_DESR       $11           ; DMA Destination Address Register
.DEFINE VDCREG_LENR       $12           ; DMA Block Length Register
.DEFINE VDCREG_SATB       $13           ; Sprite Attribute Table Address

.DEFINE MAWR	$00		;Memory Access Write Reg
.DEFINE MARR	$01		;Memory Access Read Reg
.DEFINE VRWR	$02		;Vram Read/Write reg
.DEFINE VWR	 	$02		;Vram Read/Write reg
.DEFINE VRR	 	$02		;Vram Read/Write reg




.DEFINE CR	 	$05		;Control Reg
.DEFINE RCR	 	$06		;Raster Control Reg
.DEFINE BXR	 	$07		;Background X(scroll) Reg
.DEFINE BYR	 	$08		;Background Y(scroll) Reg
.DEFINE MWR	 	$09		;Memory Access Width Reg
.DEFINE HPR	 	$0a		;Horizontal Synchro Reg
.DEFINE HDR	 	$0b		;Horizontal Display Reg
.DEFINE VSR	 	$0c		;Vertical Synchro Reg
.DEFINE VDR	 	$0d		;Vertical Display Reg
.DEFINE VCR	 	$0e		;Vertical Display End Reg
.DEFINE DCR	 	$0f		;DMA Control Reg
.DEFINE SOUR	$10		;DMA Source Address Reg
.DEFINE DESR	$11		;DMA Destination Address Reg
.DEFINE LENR	$12		;DMA Block Length Reg
.DEFINE SATB	$13		;VRAM-SATB Source Address Reg 

;------------------------------------------------------------------------------;
; Reading VDC_STATUS register:
; 76543210
; ||||||||
; |||||||+- Sprite 0 Collision interrupt (CR)
; ||||||+-- Sprite Overflow interrupt (OR)
; |||||+--- Raster compare interrupt (RR)
; ||||+---- VRAM -> SAT DMA complete interrupt (DS)
; |||+----- VRAM -> VRAM DMA complete interrupt (DV)
; ||+------ VBlank interrupt (VD)
; |+------- VDC waiting for CPU access (BSY)
; +-------- always zero

;------------------------------------------------------------------------------;
; CR/Control register write:
; FEDCBA9876543210
; ||||||||||||||||
; |||||||||||||||+- enable sprite 0 collision interrupt
; ||||||||||||||+-- enable sprite overflow interrupt
; |||||||||||||+--- enable raster compare interrupt
; ||||||||||||+---- enable vblank interrupt/IRQ1
; ||||||||||++----- external sync
; |||||||||+------- sprite enable
; ||||||||+-------- background enable
; ||||||++--------- DISP terminal
; |||||+----------- DRAM refresh enable
; |||++------------ Increment value (00 +1; 01 +32; 10 +64; 11 +128)
; ||+-------------- ??????
; ++--------------- unused

;                FEDCBA9876543210
.DEFINE VDC_CR_SP0COL   %0000000000000001
.DEFINE VDC_CR_SPROVR   %0000000000000010
.DEFINE VDC_CR_RCR      %0000000000000100
.DEFINE VDC_CR_VBL      %0000000000001000
.DEFINE VDC_CR_SPR      %0000000001000000
.DEFINE VDC_CR_BG       %0000000010000000
.DEFINE VDC_CR_DRAM     %0000010000000000

;                 FEDCBA9876543210
.DEFINE VDC_CR_INC_1     %0000000000000000
.DEFINE VDC_CR_INC_32    %0000100000000000
.DEFINE VDC_CR_INC_64    %0001000000000000
.DEFINE VDC_CR_INC_128   %0001100000000000


;------------------------------------------------------------------------------;
; MWR/Memory Width register write:
; FEDCBA9876543210
; |______|||||||||
;     |   ||||||++- VRAM dot width; should use mode 0. (see pcetech.txt)
;     |   ||||++--- Sprite dot period
;     |   ||++----- Virtual screen width (00 32; 01 64; 10 128; 11 128)
;     |   |+------- Virtual screen height (0 32; 1 64)
;     |   +-------- "CG mode" (0 use bp0/1, zero bp2/3; 1 zero bp0/1, use bp2/3)
;     +------------ unused

;------------------------------------------------------------------------------;
; DCR/DMA Control register write:
; FEDCBA9876543210
; |_________||||||
;       |    ||||+-- DSC
;       |    |||+--- DVC
;       |    ||+---- 
;       |    |+----- 
;       |    +------ 
;       +----------- unused

;------------------------------------------------------------------------------;
; video register names used in a lot of references typically go unexplained...
; the names actually come from a table in the Develo assembler book.

; the below table is an ascii representation of the data, slightly modified.
; (lowercase names are unofficial, since they were blank in the develo book)

;Reg|Name| bits and stuff
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$00|MAWR| MAWR                                                          |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$01|MARR| MARR                                                          |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$02| VWR| VWR                                                           |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$02| VRR| VRR                                                           |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$05|  CR|xxxxxxxxxxx|   IW  | DR|   TE  | BB| SB|   EX  |      IE       |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$06| RCR|xxxxxxxxxxxxxxxxxxxxxxx|RCR                                    |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$07| BXR|xxxxxxxxxxxxxxxxxxxxxxx|BXR                                    |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$08| BYR|xxxxxxxxxxxxxxxxxxxxxxxxxxx|BYR                                |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$09| MWR|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx| CM|   SCREEN  |spr dot|vramdot|
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0A| HSR|xxx|HDS                        |xxxxxxxxxxx|HSW                |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0B| HDR|xxx|HDE                        |xxx|HDW                        |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0C| VPR|VDS                            |xxxxxxxxxxx|VSW                |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0D| VDW|xxxxxxxxxxxxxxxxxxxxxxxxxxx|VDW                                |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0E| VCR|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|VCR                            |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$0F| DCR|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx| DV| DS| RR| OC| CR|
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$10|SOUR| SOUR                                                          |
;---+----+-F-+-E-+-D-+-C-+-B-+-A-+-9-+-8-+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
;$11|DESR| DESR                                                          |
;---+----+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
; $12 (DMA Length) and $13 (VRAM-SATB Source Addr.) don't show up in the
; develo asm book's table. they're word length like MAWR, MARR, etc.

.MACRO PCE_VDC
	st0 #\1
	st1 #<\2
	st2 #>\2
	

.ENDM

.MACRO PCE_VDCS
	st1 #<\1
	st2 #>\1
.ENDM
