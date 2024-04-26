#include "MFPG_Panel.h"
#include "wx/xrc/xmlres.h"

void MFPG_Panel::InitPanel() {
#ifdef XRC
	remove_config_button = XRCCTRL(*this, "ID_BTRemoveConfig", wxButton);
	score_selected_text = XRCCTRL(*this, "SelectedScore", wxStaticText);
	instrument_area = XRCCTRL(*this, "InstrumentBox", STATIC_BOX);
	instrument_settings_box = XRCCTRL(*this, "ID_CBInstSettings", wxComboBox);
	instrument_settings_box->SetSelection(0);
	dsl_filepicker = XRCCTRL(*this, "ID_FPDSL", wxFilePickerCtrl);
	ST_INSTRUMENT_SETTING = USE_PRESETS;
	instrument_box = XRCCTRL(*this, "ID_CBInstrument", wxComboBox);
	instrument_box->SetSelection(0);
	ST_INSTRUMENT = INSTRUMENT_VIOLIN;
	actionset_box = XRCCTRL(*this, "ID_CBActionSet", wxComboBox);
	actionset_box->SetSelection(0);
	ST_ACTIONSET = ACTIONSET_T1;
	notemap_area = XRCCTRL(*this, "NoteMapperBox", STATIC_BOX);
	notemap_box = XRCCTRL(*this, "ID_CBNoteMapper", wxComboBox);
	notemap_box->SetSelection(0);
	ST_NOTEMAPPER = NOTEMAPPER_BASIC;
	notemap_filepicker = XRCCTRL(*this, "ID_FPCSV", wxFilePickerCtrl);
#ifdef STATICBOXSIZER
	solver_area = XRCCTRL(*this, "SolverBox", wxStaticBoxSizer)->GetStaticBox();
#else
	solver_area = XRCCTRL(*this, "SolverBox", wxStaticBox);
#endif
	solver_box = XRCCTRL(*this, "ID_CBSolver", wxComboBox);
	solver_box->SetSelection(0);
	ST_SOLVER = SOLVER_SPS;
	sps_opt_1 = XRCCTRL(*this, "ID_CHBSPSOpt1", wxCheckBox);
	sps_opt_2 = XRCCTRL(*this, "ID_CHBSPSOpt2", wxCheckBox);
	ST_OPT = OPT_3;
	files_area = XRCCTRL(*this, "FilesBox", STATIC_BOX);
	files_book = XRCCTRL(*this, "ID_NBOOKChange", wxNotebook);
	save_file_button = XRCCTRL(*this, "ID_BTSavetext", wxButton);
	save_as_file_button = XRCCTRL(*this, "ID_BTSaveastext", wxButton);
	//Manually adding pages since wxUiEditor can not
	output_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
		wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP|wxTE_READONLY, wxDefaultValidator, "OUTPUT_TEXT");
	output_text->Disable();
	notemapper_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
			wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, "NOTEMAPPER_TEXT");
	notemapper_text->Disable();
	dsl_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
			wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, "DSL_TEXT");
	dsl_text->Disable();

	files_book->AddPage(output_text, "Output", true, -1);
	files_book->AddPage(notemapper_text, "Notemap", false, -1);
	files_book->AddPage(dsl_text, "DSL", false, -1);

	output_settings_area = XRCCTRL(*this, "OutputBox", STATIC_BOX);
	output_selection_box = XRCCTRL(*this, "ID_CBOutput", wxComboBox);
	output_selection_box->SetSelection(0);
	ST_OUTPUTTYPE = CSV_OUTPUT;
	output_to_file = XRCCTRL(*this, "ID_CHBOutputToFile", wxCheckBox);
	ST_OUTPUTTOFILE = OUTPUT_TO_FILE;
	output_filepicker = XRCCTRL(*this, "ID_FPCSVOutput", wxFilePickerCtrl);

	generation_area = XRCCTRL(*this, "GenerationBox", STATIC_BOX);
	generate_button = XRCCTRL(*this, "ID_BTGenerate", wxButton);

	information_area = XRCCTRL(*this, "InformationBox", STATIC_BOX);
	information_text = XRCCTRL(*this, "InformationText", wxTextCtrl);
	clear_info_button = XRCCTRL(*this, "ID_BTClearInfo", wxButton);
#else
//------------------------------------------------REMOVE_CONFIG----------------------------------------
	remove_config_button = new wxButton(this, ID_BTRemoveConfig, "Remove Config", wxPoint(25, 2),
		wxSize(120, 25), 0, wxDefaultValidator, "REMOVE_CONFIG_BUTTON");
//------------------------------------------------SELECTED SCORE---------------------------------------
	//Text: Selected Score:
	wxStaticText *score_selected_text_title = new wxStaticText(this, wxID_ANY, "Selected Score:",
		wxPoint(300, 5), wxSize(130, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "FILE_NAME_TITLE");
	//Text: Path of selected score
	score_selected_text = new wxStaticText(this, wxID_ANY, "", wxPoint(430, 5), wxSize(200, 20), 
		wxALIGN_LEFT|wxST_ELLIPSIZE_START, "FILE_NAME");


//----------------------------------------------INSTRUMENT SETTINGS-------------------------------------
	//Box: Area containing Instrument/Actionset settings
	instrument_area = new wxStaticBox(this, wxID_ANY, "Instrument Settings", wxPoint(10, 30),
		wxSize(400, 250), 0, wxStaticBoxNameStr);
	//Selection: Instrument settings
	wxString instrument_setting_choices[] = {"Presets", "DSL File"};
	instrument_settings_box = new wxComboBox(instrument_area, ID_CBInstSettings, _T("Presets"), 
		wxPoint(20, 10), wxSize(320, 40), 2, instrument_setting_choices, wxCB_READONLY, 
		wxDefaultValidator);
	ST_INSTRUMENT_SETTING = Settings::USE_PRESETS;
	//Text: DSL File:
	wxStaticBox *dsl_box = new wxStaticBox(instrument_area, wxID_ANY, "DSL File", 
		wxPoint(20, 60), wxSize(360, 80), 0, wxStaticBoxNameStr);
	//File Selection: DSL
	dsl_filepicker = new wxFilePickerCtrl(dsl_box, ID_FPDSL, wxEmptyString,
		wxFileSelectorPromptStr, _("MFPG Files (*.mfpg)|*.mfpg"), wxPoint(20, 10), wxSize(320, 40), 
		wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL|wxFLP_CHANGE_DIR, wxDefaultValidator, 
		wxFilePickerCtrlNameStr);
	dsl_filepicker->Disable();
	//Text: Instrument:
	wxStaticText *inst_text = new wxStaticText(instrument_area, wxID_ANY, "Instrument Presets", 
		wxPoint(20, 150), wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "INSTRUMENT_TEXT");
	//Selection: Instrument
	wxString inst_choices[] = {"Violin"};
	instrument_box = new wxComboBox(instrument_area, ID_CBInstrument, _T("Violin"), wxPoint(20, 170), 
		wxSize(160, 40), 1, inst_choices, wxCB_READONLY, wxDefaultValidator, wxComboBoxNameStr);
	ST_INSTRUMENT = Settings::INSTRUMENT_VIOLIN;
	//Text: ActionSet
	wxStaticText *as_text = new wxStaticText(instrument_area, wxID_ANY, "Action Set Presets", 
		wxPoint(220, 150), wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "ACTIONSET_TEXT");
	//Selection: ActionSet
	wxString actionset_choices[] = {"Test1", "Test2"};
	actionset_box = new wxComboBox(instrument_area, ID_CBActionSet, _T("Test1"), wxPoint(220, 170),
		wxSize(160, 40), 2, actionset_choices, wxCB_READONLY, wxDefaultValidator);
	ST_ACTIONSET = Settings::ACTIONSET_T1;


//-----------------------------------------NOTE MAPPER SETTINGS----------------------------------------
	//Box: Area for NoteMapper settings
	notemap_area = new wxStaticBox(this, wxID_ANY, "Note Mapper", wxPoint(10, 290), wxSize(400, 200), 
		0, wxStaticBoxNameStr);
	//Selection: NoteMapper
	wxString nm_choices[] = {"Basic", "CSV File"};
	notemap_box = new wxComboBox(notemap_area, ID_CBNoteMapper, _T("Basic"), wxPoint(20, 20), 
		wxSize(360, 40), 2, nm_choices, wxCB_READONLY, wxDefaultValidator, wxComboBoxNameStr);
	ST_NOTEMAPPER = Settings::NOTEMAPPER_BASIC;
	//Box: Area for CSV File selection
	wxStaticBox *csv_box = new wxStaticBox(notemap_area, wxID_ANY, "CSV File", wxPoint(20, 80),
		wxSize(360, 80), 0, wxStaticBoxNameStr);
	//File Selection: NoteMapper CSV
	notemap_filepicker = new wxFilePickerCtrl(csv_box, ID_FPCSVNoteMap, wxEmptyString, 
		wxFileSelectorPromptStr,_("CSV Files (*.csv)|*.csv"), wxPoint(20, 10), wxSize(320, 40), 
		wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL|wxFLP_CHANGE_DIR, wxDefaultValidator, 
		wxFilePickerCtrlNameStr);
	notemap_filepicker->Disable();


//-------------------------------------------SOLVER SETTINGS------------------------------------------
	//Box: Area for Solver selection
	solver_area = new wxStaticBox(this, wxID_ANY, "Solver", wxPoint(10, 500), wxSize(400, 260), 0, 
		wxStaticBoxNameStr);
	//Selection: Solver
	wxString solver_choices[] = {"Shortest Path", "Greedy"};
	solver_box = new wxComboBox(solver_area, ID_CBSolver, _T("Shortest Path"), wxPoint(20, 20), 
		wxSize(360, 40), 2, solver_choices, wxCB_READONLY, wxDefaultValidator);
	//Text: Opt 1 Label
	wxStaticText *opt1_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 110),
		wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT1_TEXT");
	opt1_text->SetLabel("Invalidates previous layers if a layer has been completely been visited.");
	opt1_text->Wrap(360);
	opt1_text->Refresh();
	//Checkbox: Shortest Path solver optimization 1
	sps_opt_1 = new wxCheckBox(solver_area, ID_CHBSPSOpt1, "Shortest Path Optimization 1", 
		wxPoint(20, 80), wxSize(360, 20), 0, wxDefaultValidator, "OPT1");
	//Text: Opt 1 Label
	wxStaticText *opt2_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 190),
		wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT2_TEXT");
	opt2_text->SetLabel("Stops solving after finding one solution.");
	opt2_text->Wrap(360);
	opt2_text->Refresh();
	//Checkbox: Shortest Path solver optimization 2
	sps_opt_2 = new wxCheckBox(solver_area, ID_CHBSPSOpt2, "Shortest Path Optimization 2", 
		wxPoint(20, 160), wxSize(360, 20), 0, wxDefaultValidator, "OPT2");
	sps_opt_1->SetValue(true);
	sps_opt_2->SetValue(true);
	ST_SOLVER = Settings::SOLVER_SPS;
	ST_OPT = Settings::OPT_3;

//-------------------------------------------FILES AREA-------------------------------------------
	//Box: Area for opened files
	files_area = new wxStaticBox(this, wxID_ANY, "Files", wxPoint(430, 30), wxSize(400, 650), 0, 
		wxStaticBoxNameStr);
	//Button: Save file
	save_file_button = new wxButton(files_area, ID_BTSavetext, "Save File", wxPoint(100, 590), 
		wxSize(90, 30), 0, wxDefaultValidator, "SAVETEXT_BUTTON");
	//Button: Save as file
	save_as_file_button = new wxButton(files_area, ID_BTSaveastext, "Save as File", wxPoint(200, 590), 
		wxSize(90, 30), 0, wxDefaultValidator, "SAVEASTEXT_BUTTON");
	//Book: Files book
	files_book = new wxNotebook(files_area, ID_NBOOKChange, wxPoint(20, 20), wxSize(360, 560), 
		wxNB_TOP, "FILES_BOOK");
	//File Contents: Output File
	output_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
		wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP|wxTE_READONLY, wxDefaultValidator, "OUTPUT_TEXT");
	output_text->Disable();
	//File Contents: NoteMapper File
	notemapper_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
			wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, "NOTEMAPPER_TEXT");
	notemapper_text->Disable();
	//File Contents: DSL File
	dsl_text = new wxTextCtrl(files_book, wxID_ANY, "",  wxPoint(20, 10), wxSize(320, 520), 
			wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, "DSL_TEXT");
	dsl_text->Disable();
	files_book->AddPage(output_text, "Output", true, -1);
	files_book->AddPage(notemapper_text, "Notemap", false, -1);
	files_book->AddPage(dsl_text, "DSL", false, -1);

//-----------------------------------------OUTPUT SETTINGS------------------------------------------
	//Box: Area for Output settings
	output_settings_area = new wxStaticBox(this, wxID_ANY, "Output Settings", wxPoint(850, 30), 
		wxSize(400, 200), 0, wxStaticBoxNameStr);
	//Text: Output Type:
	wxStaticText *output_selection_text = new wxStaticText(output_settings_area, wxID_ANY, "Output Type",
		wxPoint(20, 10), wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OUTPUT_SELECTION_TEXT");
	//Selection: Output Type
	wxString output_choices[] = {"CSV Output", "Direct Output"};
	output_selection_box = new wxComboBox(output_settings_area, ID_CBOutput, _T("CSV Output"), 
		wxPoint(20, 35), wxSize(160, 40), 2, output_choices, wxCB_READONLY, wxDefaultValidator);
	ST_OUTPUTTYPE = Settings::CSV_OUTPUT;
	//Checkbox: Output to file
	output_to_file = new wxCheckBox(output_settings_area, ID_CHBOutputToFile, "Output to file",  
		wxPoint(220, 45), wxSize(180, 20), 0, wxDefaultValidator, "OUTPUT_TO_FILE");
	output_to_file->SetValue(true);
	ST_OUTPUTTOFILE = Settings::OUTPUT_TO_FILE;
	//Text: Output File:
	wxStaticBox *output_file_box = new wxStaticBox(output_settings_area, wxID_ANY, "Output File", 
		wxPoint(20, 80), wxSize(360, 80), 0, wxStaticBoxNameStr);
	//File Selection: Output
	output_filepicker = new wxFilePickerCtrl(output_file_box, ID_FPCSVOutput, wxEmptyString, 
		wxFileSelectorPromptStr, wxFileSelectorDefaultWildcardStr, wxPoint(20, 10), wxSize(320, 40), 
		wxFLP_SAVE|wxFLP_USE_TEXTCTRL|wxFLP_OVERWRITE_PROMPT|wxFLP_CHANGE_DIR, wxDefaultValidator, 
		wxFilePickerCtrlNameStr);


//------------------------------------------GENERATION-------------------------------------------
	//Box: Area for Generation
	generation_area = new wxStaticBox(this, wxID_ANY, "Output Generation", wxPoint(950, 250),
		wxSize(200, 100), 0, wxStaticBoxNameStr);
	//Button: Generate
	generate_button = new wxButton(generation_area, ID_BTGenerate, "Generate", wxPoint(50, 10),
		wxSize(100, 50), 0, wxDefaultValidator, "GENERATE_BUTTON");


//----------------------------------------INFORMATION--------------------------------------------
	//Box: Area for Info
	information_area = new wxStaticBox(this, wxID_ANY, "Information", wxPoint(850, 370), 
		wxSize(400, 230), 0, "INFORMATION_BOX");
	//Text: Output Info:
	wxStaticText *output_info_text = new wxStaticText(information_area, wxID_ANY, "Output Info", 
		wxPoint(20, 20), wxSize(160, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "INFO_OUT_TEXT");
	//Contents: std::cout
	information_text = new wxTextCtrl(information_area, wxID_ANY, "", wxPoint(20, 40), wxSize(360, 120),
		wxTE_LEFT|wxTE_MULTILINE|wxTE_DONTWRAP|wxTE_READONLY, wxDefaultValidator, 
		"INFORMATION_TEXT");
	//Button: Clear Info
	clear_info_button = new wxButton(information_area, ID_BTClearInfo, "Clear Info", wxPoint(20, 170),
		wxSize(80, 30), 0, wxDefaultValidator, "CLEAR_INFO_BUTTON");
#endif
}

MFPG_Panel::MFPG_Panel() : wxPanel() {
}

MFPG_Panel::MFPG_Panel(wxWindow* window) : wxPanel(window) {

}

