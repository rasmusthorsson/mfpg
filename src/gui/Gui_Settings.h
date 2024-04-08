#ifndef MFPG_GUI_SETTINGS_H
#define MFPG_GUI_SETTINGS_H

enum {
	ID_MenuNewScore = 101,
	ID_MenuNewConfig = 102,
	ID_MenuSaveConfig = 103,
	ID_MenuSaveAsConfig = 104,
	ID_MenuDeleteConfig = 105,

	ID_CBOOKChange = 201,

	ID_CBNoteMapper = 301,
	ID_CBInstrument = 302,
	ID_CBActionSet = 303,	
	ID_CBSolver = 304,

	ID_CHBSPSOpt1 = 401,
	ID_CHBSPSOpt2 = 402,
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
	SOLVER_SPS_3
};

#endif
