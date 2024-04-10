#ifndef MFPG_GUI_SETTINGS_H
#define MFPG_GUI_SETTINGS_H

enum {
	ID_MenuNewScore = 101,
	ID_MenuNewConfig = 102,
	ID_MenuSaveConfig = 103,
	ID_MenuSaveAsConfig = 104,
	ID_MenuDeleteConfig = 105,
	ID_MenuGuide = 106,

	ID_CBOOKChange = 201,
	ID_NBOOKChange = 202,

	ID_CBNoteMapper = 301,
	ID_CBInstrument = 302,
	ID_CBActionSet = 303,	
	ID_CBSolver = 304,
	ID_CBOutput = 305,

	ID_CHBSPSOpt1 = 401,
	ID_CHBSPSOpt2 = 402,
	ID_CHBOutputToFile = 403,

	ID_FPDSL = 501,
	ID_FPCSVNoteMap = 502,
	ID_FPCSVOutput = 503,

	ID_BTGenerate = 601,
	ID_BTSavetext = 602,
	ID_BTSaveastext = 603,
};

enum Settings {
	UNDEFINED,
	NOTEMAPPER_BASIC,
	NOTEMAPPER_CSV,
	INSTRUMENT_VIOLIN,
	INSTRUMENT_DSL,
	ACTIONSET_T1,
	ACTIONSET_T2,
	ACTIONSET_DSL,
	SOLVER_GREEDY,
	SOLVER_SPS,
	SOLVER_SPS_1,
	SOLVER_SPS_2,
	SOLVER_SPS_3,
	CSV_OUTPUT,
	DIRECT_OUTPUT,
	OUTPUT_TO_FILE
};

#endif
