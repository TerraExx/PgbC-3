#pragma once
#include <string>

using e_gbc_support = enum
{
	CGB_Incompatible,
	CGB_Compatible,
	CGB_Exclusive
};

using e_sgb_support = enum
{
	Game_Boy,
	Uses_SGBS_Functions
};

using e_cartridge_t = enum
{
	ROM_Only,                
	ROM_MBC1,                
	ROM_MBC1_RAM,
	ROM_MBC1_RAM_BATT,
	ROM_MBC2,
	ROM_MBC2_BATTERY,
	ROM_RAM,
	ROM_RAM_BATTERY,
	ROM_MMM01,
	ROM_MMM01_SRAM,
	ROM_MMM01_SRAM_BATT,
	ROM_MBC3_TIMER_BATT,
	ROM_MBC3_TIMER_RAM_BATT,
	ROM_MBC3,
	ROM_MBC3_RAM,
	ROM_MBC3_RAM_BATT,
	ROM_MBC5,
	ROM_MBC5_RAM,
	ROM_MBC5_RAM_BATT,
	ROM_MBC5_RUMBLE,
	ROM_MBC5_RUMBLE_SRAM,
	ROM_MBC5_RUMBLE_SRAM_BATT,
	Pocket_Camera,
	Bandai_TAMA5,
	Hudson_HuC_3,
	Hudson_HuC_1
};

using e_ROM_size = enum
{
	S_32_KB_2_banks,
	S_64_KB_4_banks,
	S_128_KB_8_banks,
	S_256_KB_16_banks,
	S_512_KB_32_banks,
	S_1_MB_64_banks,
	S_2_MB_128_banks,
	S_1_1_MB_72_banks,
	S_1_2_MB_80_banks,
	S_1_5_MB_96_banks
};

using e_EROM_size = enum
{
	S_2_KB_1_banks,
	S_8_KB_1_banks,
	S_32_KB_4_banks,
	S_128_KB_6_banks
};

class Cartridge_Info
{
private:
	std::string    gameTitle;
	std::string    gameCode;
	e_gbc_support  supportCodeGBC;
	std::string    makerCode;
	e_sgb_support  supportCodeSBC;
	e_cartridge_t  cartridgeType;
	e_ROM_size     ROMsize;
	e_EROM_size    EROMsize;
	char           destinationCode;
	char           versionNo;

public:
	std::string    getGameTitile();
	std::string    getGameCode();
	e_gbc_support  getSupportCodeGBC();
	std::string    getMakerCode();
	e_sgb_support  getSupportCodeSBC();
	e_cartridge_t  getCartridgeType();
	e_ROM_size     getROMsize();
	e_EROM_size    getEROMsize();
	char           getDestinationCode();
	char           getVersionNo();

	Cartridge_Info(char *cartridgeROMbase);

	~Cartridge_Info();
};

