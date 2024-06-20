#ifndef MFPG_GUI_SETTINGS_H
#define MFPG_GUI_SETTINGS_H

#include <string>

//Enum for events
enum {
	ID_MenuNewScore = 101,
	ID_MenuNewConfig = 102,
	ID_MenuLoadConfig = 103,
	ID_MenuSaveConfig = 104,
	ID_MenuSaveAsConfig = 105,
	ID_MenuDeleteConfig = 106,
	ID_MenuGuide = 107,
	ID_MenuAdvancedSettings = 108,

	ID_CBOOKChange = 201,
	ID_NBOOKChange = 202,

	ID_CBNoteMapper = 301,
	ID_CBInstSettings = 302,
	ID_CBInstrument = 303,
	ID_CBActionSet = 304,	
	ID_CBSolver = 305,
	ID_CBOutput = 306,

	ID_CHBSPSOpt1 = 401,
	ID_CHBSPSOpt2 = 402,
	ID_CHBOutputToFile = 403,

	ID_FPDSL = 501,
	ID_FPCSVNoteMap = 502,
	ID_FPCSVOutput = 503,

	ID_BTGenerate = 601,
	ID_BTSavetext = 602,
	ID_BTSaveastext = 603,
	ID_BTClearInfo = 604,
	ID_BTRemoveConfig = 605,
	ID_BTAddColumn = 606,
	ID_BTRemoveColumn = 607
};

//Enums and arrays used for converting settings in the string format in the XML configs file to Enums in 
//the code.
enum Settings {
#define X(a) a,
#include "settings.def"
#undef X
	SettingsCount
};

Settings const Settings_enums[] {
#define X(a) a,
#include "settings.def"
#undef X
};

char const* const Settings_str[] {
#define X(a) #a,
#include "settings.def"
#undef X
	"SettingsCount"
};

//Setting to string conversion
std::string _S(enum Settings);

//String to setting conversion
Settings S_(const std::string);

#endif
