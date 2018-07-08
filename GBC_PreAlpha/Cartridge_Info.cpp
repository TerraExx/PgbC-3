#include "Cartridge_Info.h"

const unsigned int GAME_TITLE_OFFSET		= 0x134;
const unsigned int GAME_TITLE_LENGTH		= 11;
const unsigned int GAME_CODE_OFFSET			= 0x13f;
const unsigned int GAME_CODE_LENGTH		    = 4;
const unsigned int GBC_SUPPORT_CODE_OFFSET	= 0x143;
const unsigned int MAKER_CODE_OFFSET		= 0x144;
const unsigned int MAKER_CODE_LENGTH		= 2;
const unsigned int SGB_SUPPORT_CODE_OFFSET	= 0x146;
const unsigned int CARTRIDGE_TYPE_OFFSET	= 0x147;
const unsigned int ROM_SIZE_OFFSET			= 0x148;
const unsigned int ERAM_SIZE_OFFSET			= 0x149;
const unsigned int DESTINATION_CODE_OFFSET	= 0x14a;
const unsigned int VERSION_CODE_OFFSET		= 0x14c;

void Cartridge_Info::initCartridgeInfo(char * cartridgeBase)
{
	gameTitle.assign(cartridgeBase + GAME_TITLE_OFFSET, GAME_TITLE_LENGTH);
	gameCode.assign(cartridgeBase + GAME_CODE_OFFSET, GAME_CODE_LENGTH);

	switch (static_cast<unsigned char>(cartridgeBase[GBC_SUPPORT_CODE_OFFSET]))
	{
	case 0x00: supportCodeGBC = CGB_Incompatible;	break;
	case 0x80: supportCodeGBC = CGB_Compatible;		break;
	case 0xc0: supportCodeGBC = CGB_Exclusive;		break;
	default: break;
	}

	makerCode.assign(cartridgeBase + MAKER_CODE_OFFSET, MAKER_CODE_LENGTH);

	switch (static_cast<unsigned char>(cartridgeBase[SGB_SUPPORT_CODE_OFFSET]))
	{
	case 0x00: supportCodeSGB = Game_Boy;				break;
	case 0x03: supportCodeSGB = Uses_SGBS_Functions;	break;
	default: break;
	}

	switch (static_cast<unsigned char>(cartridgeBase[CARTRIDGE_TYPE_OFFSET]))
	{
	case 0x00: cartridgeType = ROM_Only;					break;
	case 0x01: cartridgeType = ROM_MBC1;					break;
	case 0x02: cartridgeType = ROM_MBC1_RAM;				break;
	case 0x03: cartridgeType = ROM_MBC1_RAM_BATT;			break;
	case 0x05: cartridgeType = ROM_MBC2;					break;
	case 0x06: cartridgeType = ROM_MBC2_BATTERY;			break;
	case 0x08: cartridgeType = ROM_RAM;						break;
	case 0x09: cartridgeType = ROM_RAM_BATTERY;				break;
	case 0x0b: cartridgeType = ROM_MMM01;					break;
	case 0x0c: cartridgeType = ROM_MMM01_SRAM;				break;
	case 0x0d: cartridgeType = ROM_MMM01_SRAM_BATT;			break;
	case 0x0f: cartridgeType = ROM_MBC3_TIMER_BATT;			break;
	case 0x10: cartridgeType = ROM_MBC3_TIMER_RAM_BATT;		break;
	case 0x11: cartridgeType = ROM_MBC3;					break;
	case 0x12: cartridgeType = ROM_MBC3_RAM;				break;
	case 0x13: cartridgeType = ROM_MBC3_RAM_BATT;			break;
	case 0x19: cartridgeType = ROM_MBC5;					break;
	case 0x1a: cartridgeType = ROM_MBC5_RAM;				break;
	case 0x1b: cartridgeType = ROM_MBC5_RAM_BATT;			break;
	case 0x1c: cartridgeType = ROM_MBC5_RUMBLE;				break;
	case 0x1d: cartridgeType = ROM_MBC5_RUMBLE_SRAM;		break;
	case 0x1e: cartridgeType = ROM_MBC5_RUMBLE_SRAM_BATT;	break;
	case 0x1f: cartridgeType = Pocket_Camera;				break;
	case 0xfd: cartridgeType = Bandai_TAMA5;				break;
	case 0xfe: cartridgeType = Hudson_HuC_3;				break;
	case 0xff: cartridgeType = Hudson_HuC_1;				break;
	default: break;
	}

	switch (static_cast<unsigned char>(cartridgeBase[ROM_SIZE_OFFSET]))
	{
	case 0x00: ROMsize = S_32_KB_2_banks;	break;
	case 0x01: ROMsize = S_64_KB_4_banks;	break;
	case 0x02: ROMsize = S_128_KB_8_banks;	break;
	case 0x03: ROMsize = S_256_KB_16_banks; break;
	case 0x04: ROMsize = S_512_KB_32_banks; break;
	case 0x05: ROMsize = S_1_MB_64_banks;	break;
	case 0x06: ROMsize = S_2_MB_128_banks;	break;
	case 0x52: ROMsize = S_1_1_MB_72_banks; break;
	case 0x53: ROMsize = S_1_2_MB_80_banks; break;
	case 0x54: ROMsize = S_1_5_MB_96_banks; break;
	default: break;
	}

	switch (static_cast<unsigned char>(cartridgeBase[ERAM_SIZE_OFFSET]))
	{
	case 0x00: ERAMsize = None;				break;
	case 0x01: ERAMsize = S_2_KB_1_banks;	break;
	case 0x02: ERAMsize = S_8_KB_1_banks;	break;
	case 0x03: ERAMsize = S_32_KB_4_banks;	break;
	case 0x04: ERAMsize = S_128_KB_16_banks; break;
	default: break;
	}

	destinationCode = cartridgeBase[DESTINATION_CODE_OFFSET];
	versionNo = cartridgeBase[VERSION_CODE_OFFSET];
}

Cartridge_Info::Cartridge_Info()
	: 
	gameTitle(),
	gameCode(),
	supportCodeGBC(Ivalid_GBC_Support_Code),
	makerCode(),
	supportCodeSGB(Ivalid_SGB_Support_Code),
	cartridgeType(Invalid_Cartride_Type),
	ROMsize(Invalid_ROM_Size),
	ERAMsize(Invalid_EROM_Size),
	destinationCode(0),
	versionNo(0)
{
	
}

Cartridge_Info::~Cartridge_Info()
{
}
