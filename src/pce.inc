; file: pce.inc
; PC Engine/TG16 hardware defines/equates.
;
; Note: These mappings assume the $FF bank is in page $00 ($0000-$1FFF).
;                                                                              ;
	.include "vdc.inc"
	.include "vce.inc"
	.include "psg.inc"
;                                                                              ;
; Timer (on HuC6280)

.DEFINE TIMER_MAIN        $0C00
;---------------;---------------;----------------------------------------------;
.DEFINE TIMER_COUNTER     TIMER_MAIN    ; Timer Counter (read)/latch (write)
.DEFINE TIMER_CONTROL     TIMER_MAIN+1  ; Timer Control

;                                                                              ;
; Joypad (on HuC6280)

.DEFINE JOYPAD            $1000 ; Joypad I/O (yes, all through one port.)

;------------------------------------------------------------------------------;
; The joypad works by reading this port multiple times, as needed.
; The values are typically active low (0 toggle on; 1 toggle off)

; (typically these are for reads; d0 and d1 are for writes too)
; 76543210
; ||||||||
; |||||||+-- Joypad pin 2 (R)/6(W)
; ||||||+--- Joypad pin 3 (R)/7(W)
; |||||+---- Joypad pin 4 (R)
; ||||+----- Joypad pin 5 (R)
; ||++------ (both bits are always 1)
; |+-------- Country bit (0 TG16/Export; 1 PCE/Domestic)
; +--------- CD-ROM base sense bit (0 attached; 1 not attached)

; Pin 2   D0
; Pin 3   D1
; Pin 4   D2
; Pin 5   D3
; Pin 6   SEL (select)
; Pin 7   CLR (clear)

;------------------------------------------------------------------------------;
; two-button controller read process
;       | d3 d2 d1 d0
;-------+-------------
; SEL 1 | Lf Rt Dn Up
; SEL 0 | Rn Se II I
;-------+-------------

; What should be done:
; 1) read first four values
; 2) values << 4 (upper half)
; 3) read next four values
; 4) 2-button controller read complete

;------------------------------------------------------------------------------;
; six-button controller read process
;         | d3 d2 d1 d0
;---------+-------------
; 1 SEL 1 | Lf Rt Dn Up
; 1 SEL 0 | Rn Se II I
;---------+-------------
; 2 SEL 1 | -  -  -  -
; 2 SEL 0 |III IV  V VI
;---------+-------------

; The 6 button controller, when in 6 button mode, sends writes differently.

;------------------------------------------------------------------------------;
; mouse read process
; (this is awkward as hell, but...)
; Mouse data is read four times
;         | d3 d2 d1 d0
;---------+-------------
; 1 SEL 1 | ?? ?? ?? ??
; 1 SEL 0 | ?? ?? ?? ??
;---------+-------------
; 2 SEL 1 | ?? ?? ?? ??
; 2 SEL 0 | ?? ?? ?? ??
;---------+-------------

; values are deltas; reading mouse every vsync is normal
; vertical movement:   up +, down -
; horizontal movement: left +, right -
; 0x25 seems to be the maximum delta you can get within 1 vsync
; (todo)

;------------------------------------------------------------------------------;
; turboexpress/pce gt link stuff
; (a lack of information on this subject since there's no real way to debug it...)

;------------------------------------------------------------------------------;
; button defines for combined input byte

;-- Read 1 --;
.DEFINE JOY_I       $01 ; I Button
.DEFINE JOY_II      $02 ; II Button
.DEFINE JOY_SEL     $04 ; Select Button
.DEFINE JOY_RUN     $08 ; Run Button
;-- Read 2 --;
.DEFINE JOY_UP      $10
.DEFINE JOY_RIGHT   $20
.DEFINE JOY_DOWN    $40
.DEFINE JOY_LEFT    $80

; xxx: fix the below defines

.DEFINE JOY_TYPE6         $50 ; mask for 6-button joypads
.DEFINE JOY_III           $01 ; III Button
.DEFINE JOY_IV            $02 ; IV Button
.DEFINE JOY_V             $04 ; V Button
.DEFINE JOY_VI            $08 ; VI Button

;                                                                              ;
; IRQ stuff

.DEFINE IRQ_DISABLE		  $1402			; IRQ Disable toggle
.DEFINE IRQ_STATUS		  $1403			; IRQ Status (Read); Acknowledge Timer interrupt (write)

; IRQ disable register write (1 inhibit/disable; 0 enable)
; 76543210
; |___||||
;   |  ||+- IRQ2/External
;   |  |+-- IRQ1/VDC
;   |  +--- Timer
;   +------ unused
; e.g. write $FC to enable IRQ1 and IRQ2; disable Timer IRQ

; IRQ status read (1 interrupt waiting)
; 76543210
; |___||||
;   |  ||+- IRQ2/External
;   |  |+-- IRQ1/VDC
;   |  +--- Timer
;   +------ unused

;                                                                              ;
; todo:
; * CDROM port at $1800 (also used for BRAM lock/unlock?)

;                                                                              ;
; Arcade Card (expansion card for CD games)

;---------------;---------------;----------------------------------------------;
.DEFINE ARCARD_PORT1      $1A00         ; Arcade Card Port 1 ($1A00-$1A0A)
.DEFINE ARCARD_PORT2      $1A10         ; Arcade Card Port 2 ($1A10-$1A1A)
.DEFINE ARCARD_PORT3      $1A20         ; Arcade Card Port 3 ($1A20-$1A2A)
.DEFINE ARCARD_PORT4      $1A30         ; Arcade Card Port 4 ($1A30-$1A3A)
;---------------;---------------;----------------------------------------------;
.DEFINE ARCARD_32BREG1    $1AE0         ; 32-bit register part 1/4 (LSB)
.DEFINE ARCARD_32BREG2    $1AE1         ; 32-bit register part 2/4
.DEFINE ARCARD_32BREG3    $1AE2         ; 32-bit register part 3/4
.DEFINE ARCARD_32BREG4    $1AE3         ; 32-bit register part 4/4 (MSB) + latch
.DEFINE ARCARD_SHIFT32    $1AE4         ; Value to shift the 32-bit register by
.DEFINE ARCARD_ROTATE32   $1AE5         ; Value to rotate the 32-bit register by
.DEFINE ARCARD_VERSION    $1AEE         ; version of the Arcade Card
.DEFINE ARCARD_IDPORT     $1AEF         ; Should always read as $51

;                                                                              ;
; Bank defines (incomplete)

.DEFINE BANK_REGISTERS    $FF           ; hardware I/O etc.
.DEFINE BANK_RAM          $F8           ; work ram, including zero page and stack
.DEFINE BANK_BRAM         $F7           ; backup ram

;                                                                              ;
; todo: VRAM addresses

; $0000 - BAT (BAT size depends on screen size)
; (width/8)*(height/8) required BAT size for given screen dimensions

