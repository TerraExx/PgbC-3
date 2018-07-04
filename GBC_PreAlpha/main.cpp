#include "CentralProcessingUnit.h"

int main(int argc, char* argv[]) {

	MemoryManagementUnit MMU;
	CentralProcessingUnit CPU(MMU);

	while (1)
	{
		CPU.step();
	}

	return 0;
}
