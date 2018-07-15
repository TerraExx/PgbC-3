#include <iostream>
#include <sstream>
#include <iomanip>

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

void CentralProcessingUnit::rlcReg(unsigned char & reg)
{
	(reg >> 7) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();

	reg = (reg << 1) | (reg >> 7);

	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::rrcReg(unsigned char & reg)
{
	(reg & 0x01) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();

	reg = (reg >> 1) | (reg << 7);

	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::rlRegA()
{
	unsigned char tempBit = A & 0x80;

	A = (A << 1) | getFlagCY();
	(tempBit > 0) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();
	clearFlagZ();
}

void CentralProcessingUnit::rrRegA()
{
	unsigned char tempBit = A & 0x01;

	A = (A >> 1) | (getFlagCY() << 7);
	(tempBit > 0) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();
	clearFlagZ();
}

void CentralProcessingUnit::rlReg(unsigned char & reg)
{
	unsigned char tempBit = reg & 0x80;

	reg = (reg << 1) | getFlagCY();
	(tempBit > 0) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();
	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::rrReg(unsigned char & reg)
{
	unsigned char tempBit = reg & 0x01;

	reg = (reg >> 1) | (getFlagCY() << 7);
	(tempBit > 0) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();
	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::rlcRegA()
{
	clearFlagZ();
	clearFlagN();
	clearFlagH();
	(A >> 7) ? setFlagCY() : clearFlagCY();

	A = (A << 1) | (A >> 7);
}

void CentralProcessingUnit::rrcRegA()
{
	clearFlagZ();
	clearFlagN();
	clearFlagH();
	(A & 0x01) ? setFlagCY() : clearFlagCY();

	A = (A >> 1) | (A << 7);
}

void CentralProcessingUnit::slaReg(unsigned char & reg)
{
	(reg & 0x80) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();

	reg = reg << 1;

	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::sraReg(unsigned char & reg)
{
	(reg & 0x01) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();

	reg = (reg >> 1) | reg & 0x80;

	(reg == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::swapReg(unsigned char & reg)
{
	reg = (reg << 4) | (reg >> 4);

	(reg == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	clearFlagH();
	clearFlagCY();
}

void CentralProcessingUnit::srlReg(unsigned char & reg)
{
	(reg & 0x01) ? setFlagCY() : clearFlagCY();
	clearFlagN();
	clearFlagH();

	reg = reg >> 1;

	(reg == 0) ? setFlagZ() : clearFlagZ();
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

unsigned char CentralProcessingUnit::getByte(unsigned short address)
{
	unsigned char byte = MMU.read(address);
	incrementClock(4);

	return byte;
}

void CentralProcessingUnit::push(unsigned short &reg)
{
	setByte(SP - 1, static_cast<unsigned char>(reg >> 0x8));
	setByte(SP - 2, static_cast<unsigned char>(reg));
	SP -= 2;

	incrementClock(12);
}

void CentralProcessingUnit::pop(unsigned short &reg)
{
	reg = (getByte(SP + 1) << 0x8) | getByte(SP);
	SP += 2;

	incrementClock(12);
}

void CentralProcessingUnit::call()
{
	unsigned short a16 = fetchShort();
	push(PC);
	PC = a16;
}

void CentralProcessingUnit::resBitReg(unsigned char & reg, const unsigned char bit)
{
	reg &= ~(0x1 << bit);
}

void CentralProcessingUnit::setBitReg(unsigned char & reg, const unsigned char bit)
{
	reg |= 0x1 << bit;
}

void CentralProcessingUnit::testBitReg(unsigned char &reg, const unsigned char bit)
{
	((reg & (0x1<<bit)) == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	setFlagH();
}

void CentralProcessingUnit::addA(unsigned char value)
{
	unsigned short sum = A + value;
	((sum & 0xff) == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	(sum & 0x0f) < (value & 0x0f) ? setFlagH() : clearFlagH();
	(sum > 0xff) ? setFlagCY() : clearFlagCY();

	A = static_cast<unsigned char>(sum & 0xff);
}

void CentralProcessingUnit::adcA(unsigned char value)
{
	unsigned short sum = A + value + getFlagCY();
	((sum & 0xff) == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	(sum & 0x0f) < (value & 0x0f) ? setFlagH() : clearFlagH();
	(sum > 0xff) ? setFlagCY() : clearFlagCY();

	A = static_cast<unsigned char>(sum & 0xff);
}

void CentralProcessingUnit::subA(unsigned char value)
{
	(A & 0x0f) < (value & 0x0f) ? setFlagH() : clearFlagH();
	(A & 0xf0) < ((value & 0xf0) + getFlagH()) ? setFlagCY() : clearFlagCY();
	setFlagN();

	A -= value;
	(A == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::sbcA(unsigned char value)
{
	(A & 0x0f) < ((value & 0x0f) + getFlagCY()) ? setFlagH() : clearFlagH();
	(A & 0xf0) < ((value & 0xf0) + getFlagH()) ? setFlagCY() : clearFlagCY();
	setFlagN();

	A -= value + getFlagCY();
	(A == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::andA(unsigned char value)
{
	A &= value;
	(A == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	setFlagH();
	clearFlagCY();
}

void CentralProcessingUnit::xorA(unsigned char value)
{
	A ^= value;
	(A == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	clearFlagH();
	clearFlagCY();
}

void CentralProcessingUnit::orA(unsigned char value)
{
	A |= value;
	(A == 0) ? setFlagZ() : clearFlagZ();
	clearFlagN();
	clearFlagH();
	clearFlagCY();
}

void CentralProcessingUnit::cpA(unsigned char value)
{
	(A & 0x0f) < (value & 0x0f) ? setFlagH() : clearFlagH();
	(A & 0xf0) < ((value & 0xf0) + getFlagH()) ? setFlagCY() : clearFlagCY();
	setFlagN();

	((A - value) == 0) ? setFlagZ() : clearFlagZ();
}

void CentralProcessingUnit::addHL(unsigned short value)
{
	unsigned short sumLower = L + static_cast<unsigned char>(value);
	unsigned char lowerCarry = (sumLower > 0xff) ? 1 : 0;

	unsigned short sumHigher = H + static_cast<unsigned char>(value >> 0x8) + lowerCarry;
	clearFlagN();
	(sumHigher & 0x0f) < ((static_cast<unsigned char>(value >> 0x8) & 0x0f) + lowerCarry) ? setFlagH() : clearFlagH();
	(sumHigher > 0xff) ? setFlagCY() : clearFlagCY();

	HL += value;

	incrementClock(4);
}

void CentralProcessingUnit::addHL_SP(char value)
{
	if (value >= 0)
	{
		unsigned short sumLower = P + value;
		unsigned char lowerCarry = (sumLower > 0xff) ? 1 : 0;

		unsigned short sumHigher = S + lowerCarry;
		clearFlagZ();
		clearFlagN();
		((lowerCarry == 1) && ((sumHigher & 0x0f) == 0)) ? setFlagH() : clearFlagH();
		(sumHigher > 0xff) ? setFlagCY() : clearFlagCY();
	}
	else
	{
		unsigned short diffLower = P - value;
		unsigned char lowerCarry = (diffLower > P) ? 1 : 0;

		unsigned short diffHigher = S - lowerCarry;
		clearFlagZ();
		clearFlagN();
		((lowerCarry == 1) && ((diffHigher & 0x0f) == 0x0f)) ? setFlagH() : clearFlagH();
		((lowerCarry == 1) && ((diffHigher & 0xf0) == 0xf0)) ? setFlagCY() : clearFlagCY();
	}

	HL = SP + value;

	incrementClock(4);
}

void CentralProcessingUnit::addSP(unsigned char value)
{
	unsigned short sumLower = P + value;
	unsigned char lowerCarry = (sumLower > 0xff) ? 1 : 0;

	unsigned short sumHigher = S + lowerCarry;
	clearFlagZ();
	clearFlagN();
	((lowerCarry == 1) && ((sumHigher & 0x0f) == 0)) ? setFlagH() : clearFlagH();
	(sumHigher > 0xff) ? setFlagCY() : clearFlagCY();

	SP += value;

	incrementClock(8);
}

unsigned short CBP = 0x0040;

void CentralProcessingUnit::step()
{
	//DEBUG - BP
	if (PC == CBP)
	{
		unsigned char proba = 1;
		proba++;
	}

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
	case NOP:
		break;

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

	case RLCA:
		rlcReg(A);
		break;

	case LD_IND_a16_SP:
		d16 = fetchShort();
		setByte(d16, P);
		setByte(d16 + 1, S);
		break;

	case ADD_HL_BC:
		addHL(BC);
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

	case RRCA:
		rrcReg(A);
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

	case RLA:
		rlReg(A);
		break;

	case JR_r8:
		d8 = fetchByte();
		PC += static_cast<char>(d8);
		incrementClock(4);
		break;

	case ADD_HL_DE:
		addHL(DE);
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

	case RRA:
		rrReg(A);
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

	case JR_Z_r8:
		d8 = fetchByte();
		if (getFlagZ() == 1)
		{
			PC += static_cast<char>(d8);
			incrementClock(4);
		}
		break;

	case ADD_HL_HL:
		addHL(HL);
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

	case CPL:
		A = ~A;
		setFlagN();
		setFlagH();
		break;

	case JR_NC_r8:
		d8 = fetchByte();
		if (getFlagCY() == 0)
		{
			PC += static_cast<char>(d8);
			incrementClock(4);
		}
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

	case SCF:
		clearFlagCY();
		break;

	case JR_C_r8:
		d8 = fetchByte();
		if (getFlagCY() == 1)
		{
			PC += static_cast<char>(d8);
			incrementClock(4);
		}
		break;

	case ADD_HL_SP:
		addHL(SP);
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

	case CCF:
		(getFlagCY()) ? clearFlagCY() : setFlagCY();
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

	case ADD_A_B:
		addA(B);
		break; 
		
	case ADD_A_C:
		addA(C);
		break; 

	case ADD_A_D:
		addA(D);
		break; 
		
	case ADD_A_E:
		addA(E);
		break;
		
	case ADD_A_H:
		addA(H);
		break; 
		
	case ADD_A_L:
		addA(L);
		break; 
		
	case ADD_A_IND_HL:
		d8 = getByte(HL);
		addA(d8);
		break; 

	case ADD_A_A:
		addA(A);
		break;

	case ADC_A_B:
		adcA(B);
		break; 
		
	case ADC_A_C:
		adcA(C); 
		break;
		
	case ADC_A_D:
		adcA(D);
		break; 
		
	case ADC_A_E:
		adcA(E);
		break; 
		
	case ADC_A_H:
		adcA(H);
		break;

	case ADC_A_L:
		adcA(L);
		break; 
		
	case ADC_A_IND_HL:
		d8 = getByte(HL);
		adcA(d8);
		break; 
		
	case ADC_A_A:
		adcA(A);
		break;

	case SUB_B:
		subA(B);
		break; 

	case SUB_C:
		subA(C);
		break;

	case SUB_D:
		subA(D);
		break;

	case SUB_E:
		subA(E);
		break;

	case SUB_H:
		subA(H);
		break;

	case SUB_L:
		subA(L);
		break;

	case SUB_IND_HL:
		d8 = getByte(HL);
		subA(d8);
		break;

	case SUB_A:
		subA(A);
		break;

	case SBC_A_B:
		sbcA(B);
		break;

	case SBC_A_C:
		sbcA(C);
		break;

	case SBC_A_D:
		sbcA(D);
		break;

	case SBC_A_E:
		sbcA(E);
		break;

	case SBC_A_H:
		sbcA(H);
		break;

	case SBC_A_L:
		sbcA(L);
		break;

	case SBC_A_IND_HL:
		d8 = getByte(HL);
		sbcA(d8);
		break;

	case SBC_A_A:
		sbcA(A);
		break;

	case LD_IND_HL_A:
		setByte(HL, A);
		break;

	case AND_B:
		andA(B);
		break;

	case AND_C:
		andA(C);
		break;

	case AND_D:
		andA(D);
		break;

	case AND_E:
		andA(E);
		break;

	case AND_H:
		andA(H);
		break;

	case AND_L:
		andA(L);
		break;

	case AND_IND_HL:
		d8 = getByte(HL);
		andA(d8);
		break;

	case AND_A:
		andA(A);
		break;

	case XOR_B:
		xorA(B);
		break;

	case XOR_C:
		xorA(C);
		break;

	case XOR_D:
		xorA(D);
		break;

	case XOR_E:
		xorA(E);
		break;

	case XOR_H:
		xorA(H);
		break;

	case XOR_L:
		xorA(L);
		break;

	case XOR_IND_HL:
		d8 = getByte(HL);
		xorA(d8);
		break;

	case XOR_A:
		xorA(A);
		break;

	case OR_B:
		orA(B);
		break;

	case OR_C:
		orA(C);
		break;

	case OR_D:
		orA(D);
		break;

	case OR_E:
		orA(E);
		break;

	case OR_H:
		orA(H);
		break;

	case OR_L:
		orA(L);
		break;

	case OR_IND_HL:
		d8 = getByte(HL);
		orA(d8);
		break;

	case OR_A:
		orA(A);
		break;

	case CP_B:
		cpA(B);
		break;

	case CP_C:
		cpA(C);
		break;

	case CP_D:
		cpA(D);
		break;

	case CP_E:
		cpA(E);
		break;

	case CP_H:
		cpA(H);
		break;

	case CP_L:
		cpA(L);
		break;

	case CP_IND_HL:
		d8 = getByte(HL);
		cpA(d8);
		break;

	case CP_A:
		cpA(A);
		break;

	case RET_NZ:
		if (getFlagZ() == 0)
		{
			pop(PC);
			incrementClock(4);
		}
		else
		{
			incrementClock(4);
		}
		break;

	case POP_BC:
		pop(BC);
		break;

	case JP_NZ_a16:
		d16 = fetchShort();
		if (getFlagZ() == 0)
		{
			PC = d16;
			incrementClock(4);
		}
		break;

	case JP_a16:
		d16 = fetchShort();
		PC = d16;
		incrementClock(4);
		break;

	case CALL_NZ_a16:
		if (getFlagZ() == 0)
		{
			call();
		}
		else
		{
			d16 = fetchShort();
		}
		break;

	case PUSH_BC:
		push(BC);
		break;

	case ADD_A_d8:
		d8 = fetchByte();
		addA(d8);
		break;

	case RST_00H:
		push(PC);
		PC = 0x0000;
		break;

	case RET_Z:
		if (getFlagZ() == 1)
		{
			pop(PC);
			incrementClock(4);
		}
		else
		{
			incrementClock(4);
		}
		break;

	case RET:
		pop(PC);
		break;

	case JP_Z_a16:
		d16 = fetchShort();
		if (getFlagZ() == 1)
		{
			PC = d16;
			incrementClock(4);
		}
		break;

	case PREFIX_CB:
		break;

	case CALL_Z_a16:
		if (getFlagZ() == 1)
		{
			call();
		}
		else
		{
			d16 = fetchShort();
		}
		break;

	case CALL_a16:
		call();		
		break;

	case ADC_A_d8:
		d8 = fetchByte();
		adcA(d8);
		break;

	case RST_08H:
		push(PC);
		PC = 0x0008;
		break;

	case RET_NC:
		if (getFlagZ() == 1)
		{
			pop(PC);
			incrementClock(4);
		}
		else
		{
			incrementClock(4);
		}
		break;

	case POP_DE:
		pop(DE);
		break;

	case JP_NC_a16:
		d16 = fetchShort();
		if (getFlagCY() == 0)
		{
			PC = d16;
			incrementClock(4);
		}
		break;

	case CALL_NC_a16:
		if (getFlagCY() == 0)
		{
			call();
		}
		else
		{
			d16 = fetchShort();
		}
		break;

	case PUSH_DE:
		push(DE);
		break;

	case SUB_d8:
		d8 = fetchByte();
		subA(d8);
		break;

	case RST_10H:
		push(PC);
		PC = 0x0010;
		break;

	case RET_C:
		if (getFlagCY() == 1)
		{
			pop(PC);
			incrementClock(4);
		}
		else
		{
			incrementClock(4);
		}
		break;

	case JP_C_a16:
		d16 = fetchShort();
		if (getFlagCY() == 1)
		{
			PC = d16;
			incrementClock(4);
		}
		break;

	case CALL_C_a16:
		if (getFlagCY() == 1)
		{
			call();
		}
		else
		{
			d16 = fetchShort();
		}
		break;

	case SBC_A_d8:
		d8 = fetchByte();
		sbcA(d8);
		break;

	case RST_18H:
		push(PC);
		PC = 0x0018;
		break;

	case LDH_IND_a8_A:
		d8 = fetchByte();
		setByte(0xff00 + d8, A);
		break;

	case POP_HL:
		pop(HL);
		break;

	case LD_IND_C_A:
		setByte(0xff00 + C, A);
		break;

	case PUSH_HL:
		push(HL);
		break;

	case AND_d8:
		d8 = fetchByte();
		andA(d8);
		break;

	case RST_20H:
		push(PC);
		PC = 0x0020;
		break;

	case ADD_SP_r8:
		d8 = fetchByte();
		addSP(d8);
		break;

	case JP_IND_HL:
		PC = HL;
		break;

	case LD_IND_a16_A:
		d16 = fetchShort();
		setByte(d16, A);
		break;

	case PUSH_AF:
		push(AF);
		break;

	case XOR_d8:
		d8 = fetchByte();
		xorA(d8);
		break;

	case RST_28H:
		push(PC);
		PC = 0x0028;
		break;

	case LDH_A_IND_a8:
		d8 = fetchByte();
		A = getByte(0xff00 + d8);
		break;

	case POP_AF:
		pop(AF);
		break;

	case LD_A_IND_C:
		A = getByte(0xff00 + C);
		break;

	case DI:
		IME = false;
		break;

	case OR_d8:
		d8 = fetchByte();
		orA(d8);
		break;

	case LD_HL_SP_INC_r8:
		d8 = fetchByte();
		addHL_SP(static_cast<signed char>(d8));
		break;

	case LD_SP_HL:
		SP = HL;
		incrementClock(4);
		break;

	case LD_A_IND_a16:
		d16 = fetchShort();
		A = getByte(d16);
		break;

	case EI:
		IME = true;
		break;

	case CP_d8:
		d8 = fetchByte();
		cpA(d8);
		break;

	case RST_38H:
		push(PC);
		PC = 0x0038;
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
	case RLC_B:
		rlcReg(B);
		break;

	case RLC_C:
		rlcReg(C);
		break;

	case RLC_D:
		rlcReg(D);
		break;

	case RLC_E:
		rlcReg(E);
		break;

	case RLC_H:
		rlcReg(H);
		break;

	case RLC_L:
		rlcReg(L);
		break;

	case RLC_IND_HL:
		break;

	case RLC_A:
		rlcReg(A);
		break;

	case RRC_B:
		rrcReg(B);
		break;

	case RRC_C:
		rrcReg(C);
		break;

	case RRC_D:
		rrcReg(D);
		break;

	case RRC_E:
		rrcReg(E);
		break;

	case RRC_H:
		rrcReg(H);
		break;

	case RRC_L:
		rrcReg(L);
		break;

	case RRC_IND_HL:
		break;

	case RRC_A:
		rrcReg(A);
		break;

	case RL_B:
		rlReg(B);
		break;

	case RL_C:
		rlReg(C);
		break;

	case RL_D:
		rlReg(D);
		break;

	case RL_E:
		rlReg(E);
		break;

	case RL_H:
		rlReg(H);
		break;

	case RL_L:
		rlReg(L);
		break;

	case RL_IND_HL:
		break;

	case RL_A:
		rlReg(A);
		break;

	case RR_B:
		rrReg(B);
		break;

	case RR_C:
		rrReg(C);
		break;

	case RR_D:
		rrReg(D);
		break;

	case RR_E:
		rrReg(E);
		break;

	case RR_H:
		rrReg(H);
		break;

	case RR_L:
		rrReg(L);
		break;

	case RR_IND_HL:
		break;

	case RR_A:
		rrReg(A);
		break;

	case SLA_B:
		slaReg(B);
		break;

	case SLA_C:
		slaReg(C);
		break;

	case SLA_D:
		slaReg(D);
		break;

	case SLA_E:
		slaReg(E);
		break;

	case SLA_H:
		slaReg(H);
		break;

	case SLA_L:
		slaReg(L);
		break;

	case SLA_IND_HL:
		break;

	case SLA_A:
		slaReg(A);
		break;

	case SRA_B:
		sraReg(B);
		break;

	case SRA_C:
		sraReg(C);
		break;

	case SRA_D:
		sraReg(D);
		break;

	case SRA_E:
		sraReg(E);
		break;

	case SRA_H:
		sraReg(H);
		break;

	case SRA_L:
		sraReg(L);
		break;

	case SRA_IND_HL:
		break;

	case SRA_A:
		sraReg(A);
		break;

	case SWAP_B:
		swapReg(B);
		break;

	case SWAP_C:
		swapReg(C);
		break;

	case SWAP_D:
		swapReg(D);
		break;

	case SWAP_E:
		swapReg(E);
		break;

	case SWAP_H:
		swapReg(H);
		break;

	case SWAP_L:
		swapReg(L);
		break;

	case SWAP_IND_HL:
		break;

	case SWAP_A:
		swapReg(A);
		break;

	case SRL_B:
		srlReg(B);
		break;

	case SRL_C:
		srlReg(C);
		break;

	case SRL_D:
		srlReg(D);
		break;

	case SRL_E:
		srlReg(E);
		break;

	case SRL_H:
		srlReg(H);
		break;

	case SRL_L:
		srlReg(L);
		break;

	case SRL_IND_HL:
		break;

	case SRL_A:
		srlReg(A);
		break;

	case BIT_0_B:
		testBitReg(B, 0);
		break;

	case BIT_0_C:
		testBitReg(C, 0);
		break;

	case BIT_0_D:
		testBitReg(D, 0);
		break;

	case BIT_0_E:
		testBitReg(E, 0);
		break;

	case BIT_0_H:
		testBitReg(H, 0);
		break;

	case BIT_0_L:
		testBitReg(L, 0);
		break;

	case BIT_0_IND_HL:
		break;

	case BIT_0_A:
		testBitReg(A, 0);
		break;

	case BIT_1_B:
		testBitReg(B, 1);
		break;

	case BIT_1_C:
		testBitReg(C, 1);
		break;

	case BIT_1_D:
		testBitReg(D, 1);
		break;

	case BIT_1_E:
		testBitReg(E, 1);
		break;

	case BIT_1_H:
		testBitReg(H, 1);
		break;

	case BIT_1_L:
		testBitReg(L, 1);
		break;

	case BIT_1_IND_HL:
		break;

	case BIT_1_A:
		testBitReg(A, 1);
		break;

	case BIT_2_B:
		testBitReg(B, 2);
		break;

	case BIT_2_C:
		testBitReg(C, 2);
		break;

	case BIT_2_D:
		testBitReg(D, 2);
		break;

	case BIT_2_E:
		testBitReg(E, 2);
		break;

	case BIT_2_H:
		testBitReg(H, 2);
		break;

	case BIT_2_L:
		testBitReg(L, 2);
		break;

	case BIT_2_IND_HL:
		break;

	case BIT_2_A:
		testBitReg(A, 2);
		break;

	case BIT_3_B:
		testBitReg(B, 3);
		break;

	case BIT_3_C:
		testBitReg(C, 3);
		break;

	case BIT_3_D:
		testBitReg(D, 3);
		break;

	case BIT_3_E:
		testBitReg(E, 3);
		break;

	case BIT_3_H:
		testBitReg(H, 3);
		break;

	case BIT_3_L:
		testBitReg(L, 3);
		break;

	case BIT_3_IND_HL:
		break;

	case BIT_3_A:
		testBitReg(A, 3);
		break;

	case BIT_4_B:
		testBitReg(B, 4);
		break;

	case BIT_4_C:
		testBitReg(C, 4);
		break;

	case BIT_4_D:
		testBitReg(D, 4);
		break;

	case BIT_4_E:
		testBitReg(E, 4);
		break;

	case BIT_4_H:
		testBitReg(H, 4);
		break;

	case BIT_4_L:
		testBitReg(L, 4);
		break;

	case BIT_4_IND_HL:
		break;

	case BIT_4_A:
		testBitReg(A, 4);
		break;

	case BIT_5_B:
		testBitReg(B, 5);
		break;

	case BIT_5_C:
		testBitReg(C, 5);
		break;

	case BIT_5_D:
		testBitReg(D, 5);
		break;

	case BIT_5_E:
		testBitReg(E, 5);
		break;

	case BIT_5_H:
		testBitReg(H, 5);
		break;

	case BIT_5_L:
		testBitReg(L, 5);
		break;

	case BIT_5_IND_HL:
		break;

	case BIT_5_A:
		testBitReg(A, 5);
		break;

	case BIT_6_B:
		testBitReg(B, 6);
		break;

	case BIT_6_C:
		testBitReg(C, 6);
		break;

	case BIT_6_D:
		testBitReg(D, 6);
		break;

	case BIT_6_E:
		testBitReg(E, 6);
		break;

	case BIT_6_H:
		testBitReg(H, 6);
		break;

	case BIT_6_L:
		testBitReg(L, 6);
		break;

	case BIT_6_IND_HL:
		break;

	case BIT_6_A:
		testBitReg(A, 6);
		break;

	case BIT_7_B:
		testBitReg(B, 7);
		break;

	case BIT_7_C:
		testBitReg(C, 7);
		break;

	case BIT_7_D:
		testBitReg(D, 7);
		break;

	case BIT_7_E:
		testBitReg(E, 7);
		break;

	case BIT_7_H:
		testBitReg(H, 7);
		break;

	case BIT_7_L:
		testBitReg(L, 7);
		break;

	case BIT_7_IND_HL:
		break;

	case BIT_7_A:
		testBitReg(A, 7);
		break;

	case RES_0_B:
		resBitReg(B, 0);
		break;

	case RES_0_C:
		resBitReg(C, 0);
		break;

	case RES_0_D:
		resBitReg(D, 0);
		break;

	case RES_0_E:
		resBitReg(E, 0);
		break;

	case RES_0_H:
		resBitReg(H, 0);
		break;

	case RES_0_L:
		resBitReg(L, 0);
		break;

	case RES_0_IND_HL:
		break;

	case RES_0_A:
		resBitReg(A, 0);
		break;

	case RES_1_B:
		resBitReg(B, 1);
		break;

	case RES_1_C:
		resBitReg(C, 1);
		break;

	case RES_1_D:
		resBitReg(D, 1);
		break;

	case RES_1_E:
		resBitReg(E, 1);
		break;

	case RES_1_H:
		resBitReg(H, 1);
		break;

	case RES_1_L:
		resBitReg(L, 1);
		break;

	case RES_1_IND_HL:
		break;

	case RES_1_A:
		resBitReg(A, 1);
		break;

	case RES_2_B:
		resBitReg(B, 2);
		break;

	case RES_2_C:
		resBitReg(C, 2);
		break;

	case RES_2_D:
		resBitReg(D, 2);
		break;

	case RES_2_E:
		resBitReg(E, 2);
		break;

	case RES_2_H:
		resBitReg(H, 2);
		break;

	case RES_2_L:
		resBitReg(L, 2);
		break;

	case RES_2_IND_HL:
		break;

	case RES_2_A:
		resBitReg(A, 2);
		break;

	case RES_3_B:
		resBitReg(B, 3);
		break;

	case RES_3_C:
		resBitReg(C, 3);
		break;

	case RES_3_D:
		resBitReg(D, 3);
		break;

	case RES_3_E:
		resBitReg(E, 3);
		break;

	case RES_3_H:
		resBitReg(H, 3);
		break;

	case RES_3_L:
		resBitReg(L, 3);
		break;

	case RES_3_IND_HL:
		break;

	case RES_3_A:
		resBitReg(A, 3);
		break;

	case RES_4_B:
		resBitReg(B, 4);
		break;

	case RES_4_C:
		resBitReg(C, 4);
		break;

	case RES_4_D:
		resBitReg(D, 4);
		break;

	case RES_4_E:
		resBitReg(E, 4);
		break;

	case RES_4_H:
		resBitReg(H, 4);
		break;

	case RES_4_L:
		resBitReg(L, 4);
		break;

	case RES_4_IND_HL:
		break;

	case RES_4_A:
		resBitReg(A, 4);
		break;

	case RES_5_B:
		resBitReg(B, 5);
		break;

	case RES_5_C:
		resBitReg(C, 5);
		break;

	case RES_5_D:
		resBitReg(D, 5);
		break;

	case RES_5_E:
		resBitReg(E, 5);
		break;

	case RES_5_H:
		resBitReg(H, 5);
		break;

	case RES_5_L:
		resBitReg(L, 5);
		break;

	case RES_5_IND_HL:
		break;

	case RES_5_A:
		resBitReg(A, 5);
		break;

	case RES_6_B:
		resBitReg(B, 6);
		break;

	case RES_6_C:
		resBitReg(C, 6);
		break;

	case RES_6_D:
		resBitReg(D, 6);
		break;

	case RES_6_E:
		resBitReg(E, 6);
		break;

	case RES_6_H:
		resBitReg(H, 6);
		break;

	case RES_6_L:
		resBitReg(L, 6);
		break;

	case RES_6_IND_HL:
		break;

	case RES_6_A:
		resBitReg(A, 6);
		break;

	case RES_7_B:
		resBitReg(B, 7);
		break;

	case RES_7_C:
		resBitReg(C, 7);
		break;

	case RES_7_D:
		resBitReg(D, 7);
		break;

	case RES_7_E:
		resBitReg(E, 7);
		break;

	case RES_7_H:
		resBitReg(H, 7);
		break;

	case RES_7_L:
		resBitReg(L, 7);
		break;

	case RES_7_IND_HL:
		break;

	case RES_7_A:
		resBitReg(A, 7);
		break;

	case SET_0_B:
		setBitReg(B, 0);
		break;

	case SET_0_C:
		setBitReg(C, 0);
		break;

	case SET_0_D:
		setBitReg(D, 0);
		break;

	case SET_0_E:
		setBitReg(E, 0);
		break;

	case SET_0_H:
		setBitReg(H, 0);
		break;

	case SET_0_L:
		setBitReg(L, 0);
		break;

	case SET_0_IND_HL:
		break;

	case SET_0_A:
		setBitReg(A, 0);
		break;

	case SET_1_B:
		setBitReg(B, 1);
		break;

	case SET_1_C:
		setBitReg(C, 1);
		break;

	case SET_1_D:
		setBitReg(D, 1);
		break;

	case SET_1_E:
		setBitReg(E, 1);
		break;

	case SET_1_H:
		setBitReg(H, 1);
		break;

	case SET_1_L:
		setBitReg(L, 1);
		break;

	case SET_1_IND_HL:
		break;

	case SET_1_A:
		setBitReg(A, 1);
		break;

	case SET_2_C:
		setBitReg(C, 2);
		break;

	case SET_2_D:
		setBitReg(D, 2);
		break;

	case SET_2_E:
		setBitReg(E, 2);
		break;

	case SET_2_H:
		setBitReg(H, 2);
		break;

	case SET_2_L:
		setBitReg(L, 2);
		break;

	case SET_2_IND_HL:
		break;

	case SET_2_A:
		setBitReg(A, 2);
		break;

	case SET_3_B:
		setBitReg(B, 3);
		break;

	case SET_3_C:
		setBitReg(C, 3);
		break;

	case SET_3_D:
		setBitReg(D, 3);
		break;

	case SET_3_E:
		setBitReg(E, 3);
		break;

	case SET_3_H:
		setBitReg(H, 3);
		break;

	case SET_3_L:
		setBitReg(L, 3);
		break;

	case SET_3_IND_HL:
		break;

	case SET_3_A:
		setBitReg(A, 3);
		break;

	case SET_4_C:
		setBitReg(C, 4);
		break;

	case SET_4_D:
		setBitReg(D, 4);
		break;

	case SET_4_E:
		setBitReg(E, 4);
		break;

	case SET_4_H:
		setBitReg(H, 4);
		break;

	case SET_4_L:
		setBitReg(L, 4);
		break;

	case SET_4_IND_HL:
		break;

	case SET_4_A:
		setBitReg(A, 4);
		break;

	case SET_5_B:
		setBitReg(B, 5);
		break;

	case SET_5_C:
		setBitReg(C, 5);
		break;

	case SET_5_D:
		setBitReg(D, 5);
		break;

	case SET_5_E:
		setBitReg(E, 5);
		break;

	case SET_5_H:
		setBitReg(H, 5);
		break;

	case SET_5_L:
		setBitReg(L, 5);
		break;

	case SET_5_IND_HL:
		break;

	case SET_5_A:
		setBitReg(A, 5);
		break;

	case SET_6_C:
		setBitReg(C, 6);
		break;

	case SET_6_D:
		setBitReg(D, 6);
		break;

	case SET_6_E:
		setBitReg(E, 6);
		break;

	case SET_6_H:
		setBitReg(H, 6);
		break;

	case SET_6_L:
		setBitReg(L, 6);
		break;

	case SET_6_IND_HL:
		break;

	case SET_6_A:
		setBitReg(A, 6);
		break;

	case SET_7_B:
		setBitReg(B, 7);
		break;

	case SET_7_C:
		setBitReg(C, 7);
		break;

	case SET_7_D:
		setBitReg(D, 7);
		break;

	case SET_7_E:
		setBitReg(E, 7);
		break;

	case SET_7_H:
		setBitReg(H, 7);
		break;

	case SET_7_L:
		setBitReg(L, 7);
		break;

	case SET_7_IND_HL:
		break;

	case SET_7_A:
		setBitReg(A, 7);
		break;

	default:
		std::cout << "Unknown 16_bit OpCode: " << OpCode << "\n";
		break;
	}
}

void CentralProcessingUnit::printGPR()
{
	std::cout << std::string(100,'\n') << std::endl;
	std::cout << "AF: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << AF << std::endl;
	std::cout << "DE: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << DE << std::endl;
	std::cout << "BC: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << BC << std::endl;
	std::cout << "HL: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << HL << std::endl;
	std::cout << std::endl;
	std::cout << "SP: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << SP << std::endl;
	std::cout << "PC: 0x" << std::setfill('0') << std::setw(sizeof(unsigned short) * 2) << std::hex << PC << std::endl;
	
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
