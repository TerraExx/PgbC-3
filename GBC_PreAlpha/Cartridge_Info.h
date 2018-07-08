#pragma once
#include <string>

using e_gbc_support = enum
{
	CGB_Incompatible,
	CGB_Compatible,
	CGB_Exclusive,
	Ivalid_GBC_Support_Code
};

using e_sgb_support = enum
{
	Game_Boy,
	Uses_SGBS_Functions,
	Ivalid_SGB_Support_Code
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
	Hudson_HuC_1,
	Invalid_Cartride_Type
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
	S_1_5_MB_96_banks,
	Invalid_ROM_Size
};

using e_EROM_size = enum
{
	None,
	S_2_KB_1_banks,
	S_8_KB_1_banks,
	S_32_KB_4_banks,
	S_128_KB_16_banks,
	Invalid_EROM_Size
};

class Cartridge_Info
{
public:
	std::string    gameTitle;
	std::string    gameCode;
	e_gbc_support  supportCodeGBC;
	std::string    makerCode;
	e_sgb_support  supportCodeSGB;
	e_cartridge_t  cartridgeType;
	e_ROM_size     ROMsize;
	e_EROM_size    ERAMsize;
	char           destinationCode;
	char           versionNo;

	void initCartridgeInfo(char *cartridgeBase);

	Cartridge_Info();
	~Cartridge_Info();
};

