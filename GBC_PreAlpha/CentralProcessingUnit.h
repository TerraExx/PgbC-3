#pragma once

#include "MemoryManagementUnit.h"

class CentralProcessingUnit
{
private:
	MemoryManagementUnit &MMU;

	int CurrentClock = 0;

	//////////General Purpose Registers//////////
	union
	{
		struct {
			unsigned char _F;
			unsigned char _A;
		}S;
		unsigned short _AF;
	} __AF;
	unsigned char  &A  = __AF.S._A;
	unsigned char  &F  = __AF.S._F;
	unsigned short &AF = __AF._AF;

	union
	{
		struct {
			unsigned char _C;
			unsigned char _B;
		}S;
		unsigned short _BC;
	} __BC;
	unsigned char  &B  = __BC.S._B;
	unsigned char  &C  = __BC.S._C;
	unsigned short &BC = __BC._BC;

	union
	{
		struct {
			unsigned char _E;
			unsigned char _D;
		}S;
		unsigned short _DE;
	} __DE;
	unsigned char  &D = __DE.S._D;
	unsigned char  &E = __DE.S._E;
	unsigned short &DE = __DE._DE;

	union
	{
		struct {
			unsigned char _L;
			unsigned char _H;
		}S;
		unsigned short _HL;
	} __HL;
	unsigned char  &H = __HL.S._H;
	unsigned char  &L = __HL.S._L;
	unsigned short &HL = __HL._HL;

	unsigned short SP = 0;
	unsigned short PC = 0;

public:
	//////////////Register Manipulation//////////////
	void setFlagZ();
	void setFlagN();
	void setFlagH();
	void setFlagCY();

	void clearFlagZ();
	void clearFlagN();
	void clearFlagH();
	void clearFlagCY();

	char getFlagZ();
	char getFlagN();
	char getFlagH();
	char getFlagCY();

	void incRegSingle(unsigned char &reg);
	void decRegSingle(unsigned char &reg);

	void incRegDouble(unsigned short &reg);
	void decRegDouble(unsigned short &reg);

	void rlcReg(unsigned char &reg);
	void rrcReg(unsigned char &reg);

	void rlReg(unsigned char &reg);
	void rrReg(unsigned char &reg);

	void rlcRegA();
	void rrcRegA();

	void rlRegA();
	void rrRegA();

	void slaReg(unsigned char &reg);
	void sraReg(unsigned char &reg);

	void swapReg(unsigned char &reg);

	void srlReg(unsigned char &reg);

	void resBitReg(unsigned char &reg, const unsigned char bit);
	void setBitReg(unsigned char &reg, const unsigned char bit);
	void testBitReg(unsigned char &reg, const unsigned char bit);

	//////////////Arithmetic 8-bit/////////////////////////
	void addA(unsigned char value);
	void adcA(unsigned char value);

	void subA(unsigned char value);
	void sbcA(unsigned char value);

	//////////////Logic 8-bit/////////////////////////
	void andA(unsigned char value);
	void xorA(unsigned char value);
	void orA(unsigned char value);
	void cpA(unsigned char value);

	//////////////Arithmetic 16-bit/////////////////////////
	void addHL(unsigned short value);

	//////////////Execution////////////////////////////////
	void incrementClock(char incrementValue);

	unsigned char fetchByte();
	unsigned short fetchShort();

	void setByte(unsigned short address, unsigned char value);
	void setShort(unsigned short address, unsigned char value);

	unsigned char getByte(unsigned short address);

	void step();

	void decodeExec8bit(unsigned char &OpCode);
	void decodeExec16bit(unsigned char &OpCode);

	//////////////Constructor & Destructor/////////////////
	CentralProcessingUnit(MemoryManagementUnit &MMU);
	~CentralProcessingUnit();
};

