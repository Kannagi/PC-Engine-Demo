; file: psg.inc
; PSG related macros and defines.
;                                                                              ;

; PSG stuff at $0800 area

.DEFINE PSG_MAIN          $0800
;---------------;---------------;----------------------------------------------;
.DEFINE PSG_CHANSELECT    PSG_MAIN+0    ; PSG Channel Select
.DEFINE PSG_GLOBALVOL     PSG_MAIN+1    ; Global Sound Volume (Left/Right)
.DEFINE PSG_FREQLO        PSG_MAIN+2    ; Fine Fr ency Adjust (LSB)
.DEFINE PSG_FREQHI        PSG_MAIN+3    ; Coarse Fr ency Adjust (4 MSB)
.DEFINE PSG_CHANCTRL      PSG_MAIN+4    ; Channel on/off, DDA on/off, Channel volume
.DEFINE PSG_CHANPAN       PSG_MAIN+5    ; Channel Sound Balance (Left/Right)
.DEFINE PSG_CHANDATA      PSG_MAIN+6    ; Channel sound data (5 bits)
.DEFINE PSG_NOISE         PSG_MAIN+7    ; Noise enable, Noise fr ency
.DEFINE PSG_LFOFREQ       PSG_MAIN+8    ; LFO fr ency
.DEFINE PSG_LFOCONTROL    PSG_MAIN+9    ; LFO trigger, LFO control

;------------------------------------------------------------------------------;
; Channel Control:
; 76543210
; ||||___|
; |||  |
; |||  +--- Channel Volume
; ||+------ unused
; |+------- DDA output (0 off; 1 on)
; +-------- Channel Enable (0 off; 1 on)

; channel states (d7,d6)
.DEFINE PSG_CHSTATE_WRITE   %00<<6 ; 00 - write to PSG_CHANDATA/$0806 stores value in waveform buffer, advances waveform write index
.DEFINE PSG_CHSTATE_RESET   %01<<6 ; 01 - reset waveform write index to 0
.DEFINE PSG_CHSTATE_OUT     %10<<6 ; 10 - waveform output enabled
.DEFINE PSG_CHSTATE_RAW     %11<<6 ; 11 - direct d/a enabled, raw writes to PSG_CHANDATA/$0806

;------------------------------------------------------------------------------;
; Noise control:
; 76543210
; ||||___|
; |||  |
; |||  +--- Noise fr ency
; |++------ unused
; +-------- Noise Enable (0 off; 1 on)

;------------------------------------------------------------------------------;
; LFO trigger, control:
; 76543210
; ||___|||
; |  |  ++- LFO control
; |  +----- unused
; +-------- LFO trigger (0 on; 1 off/reset)

; LFO control:
.DEFINE PSG_LFOTYPE_NONE    %00 ; 00 - no fr ency modulation
.DEFINE PSG_LFOTYPE_ADD     %01 ; 01 - add FM data directly
.DEFINE PSG_LFOTYPE_ADDS4   %10 ; 10 - FM data << 4, add to fr ency
.DEFINE PSG_LFOTYPE_ADDS8   %11 ; 11 - FM data << 8, add to fr ency
