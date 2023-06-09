	PRESERVE8
	AREA OL_FUNC,CODE,READONLY
	IMPORT agbMemRead32
	IMPORT agbMemRead16
	IMPORT agbMemRead8
	IMPORT agbMemWrite32
	IMPORT agbMemWrite16
	IMPORT agbMemWrite8
	IMPORT agbCPUSwitchMode
	IMPORT agbCPUUpdateFlags
	IMPORT agbCPUSWI_NOPRE
	IMPORT g_nAgbCPUReg
	EXPORT FUNC_JUMP
FUNC_JUMP
	PUSH {r4,lr}
	LDR r4, =g_nAgbCPUReg + 0
	BX r0
	LTORG
INST_0x08000000
INST_0x08000000_IN_0x08000000
	LDR r0, =0x080000c0
	ADD r1, r4, #0x3c
	STR r0, [r1]
	B INST_0x080000c0_IN_0x08000000
	LTORG
	B INST_0x080000c0_IN_0x08000000
	LTORG
INST_0x080000c0_IN_0x08000000
	LDR r0, =0x00000012
	ADD r1, r4, #0x00
	STR r0, [r1]
	ADDS r0, r0, #0x00
INST_0x080000c4_IN_0x08000000
	MOV r1, #0x00
	ADD r0, r4, #0x00
	LDR r0, [r0]
	ADD r2, r4, #0xc8
	LDR r2, [r2]
	BEQ TEMP_0x00000000
	BIC r0, r0,#0x0000ff00
	BIC r0, r0,#0xff000000
TEMP_0x00000000
	ADD r2, r4, #0xb0
	STR r0, [r2]
	AND r0, r0, #0x1f
	BL agbCPUSwitchMode
	ADD r0, r4, #0xb0
	LDR r0, [r0]
	ADD r1, r4, #0x40
	STR r0, [r1]
	BL agbCPUUpdateFlags
	LDR r0, =0x080000c8
	ADD r1, r4, #0x3c
	STR r0, [r1]
	LDR r0, =0x00000000
	POP {r4}
	POP {lr}
	BX lr
	LTORG
	EXPORT INST_0x08000000
	END
