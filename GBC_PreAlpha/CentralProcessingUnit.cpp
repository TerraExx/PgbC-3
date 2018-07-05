#include <iostream>

#include "CentralProcessingUnit.h"
#include "InstructionSet.h"

const char ZERO_FLAG_MASK		= 0x80;
const char SUB_FLAG_MASK		= 0x40;
const char HALF_CARRY_FLAG_MASK = 0x20;
const char CARRY_FLAG_MASK		= 0x10;

const char ZERO_FLAG_OFFSET			= 0x07;
const char SUB_FLAG_OFFSET			= 0x06;
const char HALF_CARRY_FLAG_OFFSET	= 0x05;
const char CARRY_FLAG_OFFSET		= 0x04;

void CentralProcessingUnit::setFlagZ()
{
	F = (F & ~ZERO_FLAG_MASK) | ZERO_FLAG_MASK;
}

void CentralProcessingUnit::setFlagN()
{
	F = (F & ~SUB_FLAG_MASK) | SUB_FLAG_MASK;
}

void CentralProcessingUnit::setFlagH()
{
	F = (F & ~HALF_CARRY_FLAG_MASK) | HALF_CARRY_FLAG_MASK;
}

void CentralProcessingUnit::setFlagCY()
{
	F = (F & ~CARRY_FLAG_MASK) | CARRY_FLAG_MASK;
}

void CentralProcessingUnit::clearFlagZ()
{
	F &= ~ZERO_FLAG_MASK;
}

void CentralProcessingUnit::clearFlagN()
{
	F &= ~SUB_FLAG_MASK;
}

void CentralProcessingUnit::clearFlagH()
{
	F &= ~HALF_CARRY_FLAG_MASK;
}

void CentralProcessingUnit::clearFlagCY()
{
	F &= ~CARRY_FLAG_MASK;
}

char CentralProcessingUnit::getFlagZ()
{
	return (F & ZERO_FLAG_MASK) >> ZERO_FLAG_OFFSET;
}

char CentralProcessingUnit::getFlagN()
{
	return (F & SUB_FLAG_MASK) >> SUB_FLAG_OFFSET;
}

char CentralProcessingUnit::getFlagH()
{
	return (F & HALF_CARRY_FLAG_MASK) >> HALF_CARRY_FLAG_OFFSET;
}

char CentralProcessingUnit::getFlagCY()
{
	return (F & CARRY_FLAG_MASK) >> CARRY_FLAG_OFFSET;
}

void CentralProcessingUnit::incRegSingle(unsigned char & reg)
{
	++reg;
	(reg == 0x0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	((reg & 0x0f) == 0) ? setFlagH() : clearFlagH();
}

void CentralProcessingUnit::decRegSingle(unsigned char & reg)
{
	--reg;
	(reg == 0x0) ? setFlagZ() : clearFlagZ();
	setFlagN();
	((reg & 0x0f) == 0x0f) ? setFlagH() : clearFlagH();
}

void CentralProcessingUnit::incRegDouble(unsigned short & reg)
{
	++reg;
	incrementClock(4);
}

void CentralProcessingUnit::decRegDouble(unsigned short & reg)
{
	--reg;
	incrementClock(4);
}

void CentralProcessingUnit::incrementClock(char incrementValue)
{
	CurrentClock += incrementValue;
}

unsigned char CentralProcessingUnit::fetchByte()
{
	unsigned char byte = MMU.read(PC);
	++PC;

	incrementClock(4);

	return byte;
}

unsigned short CentralProcessingUnit::fetchShort()
{
	unsigned short word = fetchByte() | (fetchByte() << 8);

	return word;
}

void CentralProcessingUnit::setByte(unsigned short address, unsigned char value)
{
	MMU.write(address, value);
	incrementClock(4);
}

void CentralProcessingUnit::setShort(unsigned short address, unsigned char value)
{
}

unsigned char CentralProcessingUnit::getByte(unsigned short address)
{
	unsigned char byte = MMU.read(address);
	incrementClock(4);

	return byte;
}

void CentralProcessingUnit::testBit(unsigned char &reg, const unsigned char bit)
{
	((reg & (0x1<<bit)) == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	setFlagH();
}

void CentralProcessingUnit::step()
{
	// fetch
	unsigned char OpCode = fetchByte();

	// decode and execute
	if (OpCode == PREFIX_16_BIT)
	{
		OpCode = fetchByte();
		decodeExec16bit(OpCode);
	}
	else
	{
		decodeExec8bit(OpCode);
	}
}

void CentralProcessingUnit::decodeExec8bit(unsigned char &OpCode)
{
	unsigned char d8;
	unsigned char d16;

	// execute
	switch (OpCode)
	{
	case LD_BC_d16:
		BC = fetchShort();
		break;

	case LD_IND_BC_A:
		setByte(BC, A);
		break;

	case INC_BC:
		incRegDouble(BC);
		break;

	case INC_B:
		incRegSingle(B);
		break;

	case DEC_B:
		decRegSingle(B);
		break;

	case LD_B_d8:
		B = fetchByte();
		break;

	case LD_A_IND_BC:
		A = getByte(BC);
		break;

	case DEC_BC:
		decRegDouble(BC);
		break;

	case INC_C:
		incRegSingle(C);
		break;

	case DEC_C:
		decRegSingle(C);
		break;

	case LD_C_d8:
		C = fetchByte();
		break;

	case LD_DE_d16:
		DE = fetchShort(); 
		break;

	case LD_IND_DE_A:
		setByte(DE, A);
		break;

	case INC_DE:
		incRegDouble(DE);
		break;

	case INC_D:
		incRegSingle(D);
		break;

	case DEC_D:
		decRegSingle(D);
		break;

	case LD_D_d8:
		D = fetchByte();
		break;

	case LD_A_IND_DE:
		A = getByte(DE);
		break;

	case DEC_DE:
		decRegDouble(DE);
		break;

	case INC_E:
		incRegSingle(E);
		break;

	case DEC_E:
		decRegSingle(E);
		break;

	case LD_E_d8:
		E = fetchByte();
		break;

	case JR_NZ_r8:
		d8 = fetchByte();
		if (getFlagZ() == 0)
		{
			PC += static_cast<char>(d8);
			incrementClock(4);
		}
		break;

	case LD_HL_d16:
		HL = fetchShort();
		break;

	case LD_IND_HL_INC_A:
		setByte(HL, A);
		++HL;
		break;

	case INC_HL:
		incRegDouble(HL);
		break;

	case INC_H:
		incRegSingle(H);
		break;

	case DEC_H:
		decRegSingle(H);
		break;

	case LD_H_d8:
		H = fetchByte();
		break;

	case LD_A_IND_HL_INC:
		A = getByte(HL);
		++HL;
		break;

	case DEC_HL:
		decRegDouble(HL);
		break;

	case INC_L:
		incRegSingle(L);
		break;

	case DEC_L:
		decRegSingle(L);
		break;

	case LD_L_d8:
		L = fetchByte();
		break;

	case LD_SP_d16:
		SP = fetchShort();
		break;

	case LD_IND_HL_DEC_A:
		setByte(HL,A);
		--HL;
		break;

	case INC_SP:
		incRegDouble(SP);
		break;

	case INC_IND_HL:
		d8 = getByte(HL);
		++d8;
		setByte(HL, d8);
		(d8 == 0x0) ? setFlagZ() : clearFlagZ();
		clearFlagN();
		((d8 & 0x0f) == 0) ? setFlagH() : clearFlagH();
		break;

	case DEC_IND_HL:
		d8 = getByte(HL);
		++d8;
		setByte(HL, d8);
		(d8 == 0x0) ? setFlagZ() : clearFlagZ();
		setFlagN();
		((d8 & 0x0f) == 0x0f) ? setFlagH() : clearFlagH();
		break;

	case LD_IND_HL_d8:
		d8 = fetchByte();
		setByte(HL, d8);
		break;

	case LD_A_IND_HL_DEC:
		A = getByte(HL);
		--HL;
		break;

	case DEC_SP:
		decRegDouble(SP);
		break;

	case INC_A:
		incRegSingle(A);
		break;

	case DEC_A:
		decRegSingle(A);
		break;

	case LD_A_d8:
		A = fetchByte();
		break;

	case LD_B_B:
		B = B;
		break;

	case LD_B_C:
		B = C;
		break; 

	case LD_B_D:
		B = D;
		break;
		
	case LD_B_E:
		B = E;
		break; 
		
	case LD_B_H:
		B = H;
		break; 
		
	case LD_B_L:
		B = L;
		break; 
		
	case LD_B_IND_HL:
		B = getByte(HL);
		break; 
		
	case LD_B_A:
		B = A;
		break; 
		
	case LD_C_B:
		C = B;
		break; 
		
	case LD_C_C:
		C = C;
		break; 
		
	case LD_C_D:
		C = D;
		break;
		
	case LD_C_E:
		C = E;
		break; 
	case LD_C_H:
		C = H;
		break; 
		
	case LD_C_L:
		C = L;
		break; 
		
	case LD_C_IND_HL:
		C = getByte(HL);
		break; 

	case LD_C_A:
		C = A;
		break;

	case LD_D_B:
		D = B;
		break; 
		
	case LD_D_C:
		D = C;
		break; 
		
	case LD_D_D:
		D = D;
		break; 
		
	case LD_D_E:
		D = E;
		break; 
		
	case LD_D_H:
		D = H;
		break; 
		
	case LD_D_L:
		D = L;
		break; 
		
	case LD_D_IND_HL:
		D = getByte(HL);
		break;

	case LD_D_A:
		D = A;
		break;

	case LD_E_B:
		E = B;
		break;
				
	case LD_E_C:
		E = C;
		break; 
		
	case LD_E_D:
		E = D;
		break; 

	case LD_E_E:
		E = E;
		break;
		
	case LD_E_H:
		E = H;
		break; 
		
	case LD_E_L:
		E = L;
		break; 
		
	case LD_E_IND_HL:
		E = getByte(HL);
		break; 
		
	case LD_E_A:
		E = A;
		break;

	case LD_H_B:
		H = B;
		break;
		
	case LD_H_C:
		H = C;
		break; 
		
	case LD_H_D:
		H = D;
		break; 
		
	case LD_H_E:
		H = E;
		break; 
		
	case LD_H_H:
		H = H;
		break; 
		
	case LD_H_L:
		H = L;
		break; 
		
	case LD_H_IND_HL:
		H = getByte(HL);
		break; 
		
	case LD_H_A:
		H = A;
		break; 
		
	case LD_L_B:
		L = B;
		break; 
		
	case LD_L_C:
		L = C;
		break; 
		
	case LD_L_D:
		L = D;
		break; 
		
	case LD_L_E:
		L = E;
		break; 
		
	case LD_L_H:
		L = H;
		break; 
		
	case LD_L_L:
		L = L;
		break; 
		
	case LD_L_IND_HL:
		L = getByte(HL);
		break; 
		
	case LD_L_A:
		L = A;
		break;

	case LD_IND_HL_B:
		setByte(HL, B);
		break; 
		
	case LD_IND_HL_C:
		setByte(HL, C);
		break; 
		
	case LD_IND_HL_D:
		setByte(HL, D);
		break; 
		
	case LD_IND_HL_E:
		setByte(HL, E);
		break; 
		
	case LD_IND_HL_H:
		setByte(HL, H);
		break; 
		
	case LD_IND_HL_L:
		setByte(HL, L);
		break;  

	case LD_A_B:
		A = B;
		break; 
		
	case LD_A_C:
		A = C;
		break; 
		
	case LD_A_D:
		A = D;
		break; 
		
	case LD_A_E:
		A = E;
		break; 
		
	case LD_A_H:
		A = H;
		break; 
		
	case LD_A_L:
		A = L;
		break; 
		
	case LD_A_IND_HL:
		A = getByte(HL);
		break; 
		
	case LD_A_A:
		A = A;
		break;

	case LD_IND_HL_A:
		setByte(HL, A);
		break;

	case XOR_A:
		A ^= A;
		(A == 0) ? setFlagZ() : clearFlagZ();
		clearFlagN();
		clearFlagH();
		clearFlagCY();
		break;

	case LDH_IND_a8_A:
		d8 = fetchByte();
		setByte(0xff00 + d8, A);
		break;

	case LD_IND_C_A:
		setByte(0xff00 + C, A);
		break;

	default:
		std::cout << "Unknown 8_bit OpCode: " << OpCode << "\n";

	}
}

void CentralProcessingUnit::decodeExec16bit(unsigned char &OpCode)
{
	unsigned char d8;
	unsigned char d16;

	// execute
	switch (OpCode)
	{
	case BIT_0_H:
		testBit(H, 0);
		break;

	case BIT_1_H:
		testBit(H, 1);
		break;

	case BIT_2_H:
		testBit(H, 2);
		break;

	case BIT_3_H:
		testBit(H, 3);
		break;

	case BIT_4_H:
		testBit(H, 4);
		break;

	case BIT_5_H:
		testBit(H, 5);
		break;

	case BIT_6_H:
		testBit(H, 6);
		break;

	case BIT_7_H:
		testBit(H,7);
		break;

	default:
		std::cout << "Unknown 16_bit OpCode: " << OpCode << "\n";
		break;
	}
}

CentralProcessingUnit::CentralProcessingUnit(MemoryManagementUnit & MMU) 
	: MMU(MMU)
{
	AF = 0;
	BC = 0;
	DE = 0;
	HL = 0;
}

CentralProcessingUnit::~CentralProcessingUnit()
{
}
