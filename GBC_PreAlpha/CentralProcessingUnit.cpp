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

	switch (OpCode)
	{
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

	case LD_SP_d16:
		SP = fetchShort();
		break;

	case LD_IND_HL_DEC_A:
		setByte(HL,A);
		--HL;
		break;

	case XOR_A:
		A ^= A;
		(A == 0) ? setFlagZ() : clearFlagZ();
		clearFlagN();
		clearFlagH();
		clearFlagCY();
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
