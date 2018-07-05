#pragma once
class MemoryManagementUnit
{
private:
	bool runningBootCode = true;
	unsigned char	*BP = new unsigned char[0xFFFF];

public:
	void write(short address, unsigned char value);

	unsigned char read(unsigned short address);

	MemoryManagementUnit();
	~MemoryManagementUnit();
};

