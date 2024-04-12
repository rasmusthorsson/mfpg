#ifndef MFPG_GUI_SETTINGS_H
#define MFPG_GUI_SETTINGS_H

#include <string>

enum {
	ID_MenuNewScore = 101,
	ID_MenuNewConfig = 102,
	ID_MenuLoadConfig = 103,
	ID_MenuSaveConfig = 104,
	ID_MenuSaveAsConfig = 105,
	ID_MenuDeleteConfig = 106,
	ID_MenuGuide = 107,

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
	ID_BTClearInfo = 604
};

enum Settings {
#define X(a) a,
#include "settings.def"
#undef X
	SettingsCount
};

char const* const Settings_str[] {
#define X(a) #a,
#include "settings.def"
#undef X
	0
};

std::string _S(enum Settings s);

#endif
