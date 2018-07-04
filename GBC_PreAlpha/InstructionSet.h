#pragma once

const unsigned char PREFIX_16_BIT = 0xCB;

using Set_8_bit = enum
{
	NOP,			LD_BC_d16,		LD_IND_BC_A,		INC_BC,			INC_B,			DEC_B,			LD_B_d8,		RLCA,			LD_IND_a16_SP,		ADD_HL_BC,	LD_A_IND_BC,		DEC_BC,		INC_C,		DEC_C,		LD_C_d8,		RRCA,
	STOP_0,			LD_DE_d16,		LD_IND_DE_A,		INC_DE,			INC_D,			DEC_D,			LD_D_d8,		RLA,			JR_r8,				ADD_HL_DE,	LD_A_IND_DE,		DEC_DE,		INC_E,		DEC_E,		LD_E_d8,		RRA,
	JR_NZ_r8,		LD_HL_d16,		LD_IND_HL_INC_A,	INC_HL,			INC_H,			DEC_H,			LD_H_d8,		DAA,			JR_Z_r8,			ADD_HL_HL,	LD_A_IND_HL_INC,	DEC_HL,		INC_L,		DEC_L,		LD_L_d8,		CPL,
	JR_NC_r8,		LD_SP_d16,		LD_IND_HL_DEC_A,	INC_SP,			INC_IND_HL,		DEC_IND_HL,		LD_IND_HL_d8,	SCF,			JR_C_r8,			ADD_HL_SP,	LD_A_IND_HL_DEC,	DEC_SP,		INC_A,		DEC_A,		LD_A_d8,		CCF,
	LD_B_B,			LD_B_C,			LD_B_D,				LD_B_E,			LD_B_H,			LD_B_L,			LD_B_IND_HL,	LD_B_A,			LD_C_B,				LD_C_C,		LD_C_D,				LD_C_E,		LD_C_H,		LD_C_L,		LD_C_IND_HL,	LD_C_A,
	LD_D_B,			LD_D_C,			LD_D_D,				LD_D_E,			LD_D_H,			LD_D_L,			LD_D_IND_HL,	LD_D_A,			LD_E_B,				LD_E_C,		LD_E_D,				LD_E_E,		LD_E_H,		LD_E_L,		LD_E_IND_HL,	LD_E_A,
	LD_H_B,			LD_H_C,			LD_H_D,				LD_H_E,			LD_H_H,			LD_H_L,			LD_H_IND_HL,	LD_H_A,			LD_L_B,				LD_L_C,		LD_L_D,				LD_L_E,		LD_L_H,		LD_L_L,		LD_L_IND_HL,	LD_L_A,
	LD_IND_HL_B,	LD_IND_HL_C,	LD_IND_HL_D,		LD_IND_HL_E,	LD_IND_HL_H,	LD_IND_HL_L,	HALT,			LD_IND_HL_A,	LD_A_B,				LD_A_C,		LD_A_D,				LD_A_E,		LD_A_H,		LD_A_L,		LD_A_IND_HL,	LD_A_A,
	ADD_A_B,		ADD_A_C,		ADD_A_D,			ADD_A_E,		ADD_A_H,		ADD_A_L,		ADD_A_IND_HL,	ADD_A_A,		ADC_A_B,			ADC_A_C,	ADC_A_D,			ADC_A_E,	ADC_A_H,	ADC_A_L,	ADC_A_IND_HL,	ADC_A_A,
	SUB_B,			SUB_C,			SUB_D,				SUB_E,			SUB_H,			SUB_L,			SUB_IND_HL,		SUB_A,			SBC_A_B,			SBC_A_C,	SBC_A_D,			SBC_A_E,	SBC_A_H,	SBC_A_L,	SBC_A_IND_HL,	SBC_A_A,
	AND_B,			AND_C,			AND_D,				AND_E,			AND_H,			AND_L,			AND_IND_HL,		AND_A,			XOR_B,				XOR_C,		XOR_D,				XOR_E,		XOR_H,		XOR_L,		XOR_IND_HL,		XOR_A,
	OR_B,			OR_C,			OR_D,				OR_E,			OR_H,			OR_L,			OR_IND_HL,		OR_A,			CP_B,				CP_C,		CP_D,				CP_E,		CP_H,		CP_L,		CP_IND_HL,		CP_A,
	RET_NZ,			POP_BC,			JP_NZ_a16,			JP_a16,			CALL_NZ_a16,	PUSH_BC,		ADD_A_d8,		RST_00H,		RET_Z,				RET,		JP_Z_a16,			PREFIX_CB,	CALL_Z_a16,	CALL_a16,	ADC_A_d8,		RST_08H,
	RET_NC,			POP_DE,			JP_NC_a16,			NaN_0,			CALL_NC_a16,	PUSH_DE,		SUB_d8,			RST_10H,		RET_C,				RETI,		JP_C_a16,			NaN_1,		CALL_C_a16,	NaN_2,		SBC_A_d8,		RST_18H,
	LDH_IND_a8_A,	POP_HL,			LD_IND_C_A,			NaN_3,			NaN_4,			PUSH_HL,		AND_d8,			RST_20H,		ADD_SP_r8,			JP_IND_HL,	LD_IND_a16_A,		NaN_5,		NaN_6,		NaN_7,		XOR_d8,			RST_28H,
	LDH_A_IND_a8,	POP_AF,			LD_A_IND_C,			DI,				NaN_8,			PUSH_AF,		OR_d8,			RST_30H,		LD_HL_SP_INC_r8,	LD_SP_HL,	LD_A_IND_a16,		EI,			NaN_9,		NaN_10,		CP_d8,			RST_38H
};

using Set_16_bit = enum
{
	RLC_B,		RLC_C,		RLC_D,		RLC_E,		RLC_H,		RLC_L,		RLC_IND_HL,		RLC_A,		RRC_B,		RRC_C,		RRC_D,		RRC_E,		RRC_H,		RRC_L,		RRC_IND_HL,		RRC_A,
	RL_B,		RL_C,		RL_D,		RL_E,		RL_H,		RL_L,		RL_IND_HL,		RL_A,		RR_B,		RR_C,		RR_D,		RR_E,		RR_H,		RR_L,		RR_IND_HL,		RR_A,
	SLA_B,		SLA_C,		SLA_D,		SLA_E,		SLA_H,		SLA_L,		SLA_IND_HL,		SLA_A,		SRA_B,		SRA_C,		SRA_D,		SRA_E,		SRA_H,		SRA_L,		SRA_IND_HL,		SRA_A,
	SWAP_B,		SWAP_C,		SWAP_D,		SWAP_E,		SWAP_H,		SWAP_L,		SWAP_IND_HL,	SWAP_A,		SRL_B,		SRL_C,		SRL_D,		SRL_E,		SRL_H,		SRL_L,		SRL_IND_HL,		SRL_A,
	BIT_0_B,	BIT_0_C,	BIT_0_D,	BIT_0_E,	BIT_0_H,	BIT_0_L,	BIT_0_IND_HL,	BIT_0_A,	BIT_1_B,	BIT_1_C,	BIT_1_D,	BIT_1_E,	BIT_1_H,	BIT_1_L,	BIT_1_IND_HL,	BIT_1_A,
	BIT_2_B,	BIT_2_C,	BIT_2_D,	BIT_2_E,	BIT_2_H,	BIT_2_L,	BIT_2_IND_HL,	BIT_2_A,	BIT_3_B,	BIT_3_C,	BIT_3_D,	BIT_3_E,	BIT_3_H,	BIT_3_L,	BIT_3_IND_HL,	BIT_3_A,
	BIT_4_B,	BIT_4_C,	BIT_4_D,	BIT_4_E,	BIT_4_H,	BIT_4_L,	BIT_4_IND_HL,	BIT_4_A,	BIT_5_B,	BIT_5_C,	BIT_5_D,	BIT_5_E,	BIT_5_H,	BIT_5_L,	BIT_5_IND_HL,	BIT_5_A,
	BIT_6_B,	BIT_6_C,	BIT_6_D,	BIT_6_E,	BIT_6_H,	BIT_6_L,	BIT_6_IND_HL,	BIT_6_A,	BIT_7_B,	BIT_7_C,	BIT_7_D,	BIT_7_E,	BIT_7_H,	BIT_7_L,	BIT_7_IND_HL,	BIT_7_A,
	RES_0_B,	RES_0_C,	RES_0_D,	RES_0_E,	RES_0_H,	RES_0_L,	RES_0_IND_HL,	RES_0_A,	RES_1_B,	RES_1_C,	RES_1_D,	RES_1_E,	RES_1_H,	RES_1_L,	RES_1_IND_HL,	RES_1_A,
	RES_2_B,	RES_2_C,	RES_2_D,	RES_2_E,	RES_2_H,	RES_2_L,	RES_2_IND_HL,	RES_2_A,	RES_3_B,	RES_3_C,	RES_3_D,	RES_3_E,	RES_3_H,	RES_3_L,	RES_3_IND_HL,	RES_3_A,
	RES_4_B,	RES_4_C,	RES_4_D,	RES_4_E,	RES_4_H,	RES_4_L,	RES_4_IND_HL,	RES_4_A,	RES_5_B,	RES_5_C,	RES_5_D,	RES_5_E,	RES_5_H,	RES_5_L,	RES_5_IND_HL,	RES_5_A,
	RES_6_B,	RES_6_C,	RES_6_D,	RES_6_E,	RES_6_H,	RES_6_L,	RES_6_IND_HL,	RES_6_A,	RES_7_B,	RES_7_C,	RES_7_D,	RES_7_E,	RES_7_H,	RES_7_L,	RES_7_IND_HL,	RES_7_A,
	SET_0_B,	SET_0_C,	SET_0_D,	SET_0_E,	SET_0_H,	SET_0_L,	SET_0_IND_HL,	SET_0_A,	SET_1_B,	SET_1_C,	SET_1_D,	SET_1_E,	SET_1_H,	SET_1_L,	SET_1_IND_HL,	SET_1_A,
	SET_2_B,	SET_2_C,	SET_2_D,	SET_2_E,	SET_2_H,	SET_2_L,	SET_2_IND_HL,	SET_2_A,	SET_3_B,	SET_3_C,	SET_3_D,	SET_3_E,	SET_3_H,	SET_3_L,	SET_3_IND_HL,	SET_3_A,
	SET_4_B,	SET_4_C,	SET_4_D,	SET_4_E,	SET_4_H,	SET_4_L,	SET_4_IND_HL,	SET_4_A,	SET_5_B,	SET_5_C,	SET_5_D,	SET_5_E,	SET_5_H,	SET_5_L,	SET_5_IND_HL,	SET_5_A,
	SET_6_B,	SET_6_C,	SET_6_D,	SET_6_E,	SET_6_H,	SET_6_L,	SET_6_IND_HL,	SET_6_A,	SET_7_B,	SET_7_C,	SET_7_D,	SET_7_E,	SET_7_H,	SET_7_L,	SET_7_IND_HL,	SET_7_A
};