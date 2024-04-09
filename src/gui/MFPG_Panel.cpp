#include "MFPG_Panel.h"

MFPG_Panel::MFPG_Panel(wxWindow* window) : wxPanel(window) {
	wxStaticText *file_name_title = new wxStaticText(this, wxID_ANY, "Selected Score:",
			wxPoint(300, 5), wxSize(130, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, 
			"FILE_NAME_TITLE");
	file_name = new wxStaticText(this, wxID_ANY, "", wxPoint(430, 5), 
			wxSize(200, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_START, "FILE_NAME");
//----------------------------------------------INSTRUMENT SETTINGS-------------------------------------
	instrument_area = new wxStaticBox(this, wxID_ANY, "Instrument Settings", wxPoint(10, 30),
			wxSize(400, 200), 0, wxStaticBoxNameStr);
	wxString inst_choices[] = {"Violin", "DSL File"};
	//Instrument Selection
	instrument_box = new wxComboBox(instrument_area, ID_CBInstrument, _T("Violin"), wxPoint(20, 35), 
			wxSize(160, 40), 2, inst_choices, wxCB_READONLY, wxDefaultValidator, 
			wxComboBoxNameStr);
	wxStaticText *inst_text = new wxStaticText(instrument_area, wxID_ANY, "Instrument", wxPoint(20, 10),
			wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "INSTRUMENT_TEXT");
	inst_text->Wrap(360);
	inst_text->Refresh();
	wxString actionset_choices[] = {"Test1", "Test2", "DSL File"};
	//ActionSet Selection
	actionset_box = new wxComboBox(instrument_area, ID_CBActionSet, _T("Test1"), wxPoint(220, 35),
			wxSize(160, 40), 3, actionset_choices, wxCB_READONLY, wxDefaultValidator);
	wxStaticText *as_text = new wxStaticText(instrument_area, wxID_ANY, "Action Set", wxPoint(220, 10),
			wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "INSTRUMENT_TEXT");
	as_text->Wrap(360);
	as_text->Refresh();
	//DSL File Selection
	wxStaticBox *dsl_box = new wxStaticBox(instrument_area, wxID_ANY, "DSL File", wxPoint(20, 80),
			wxSize(360, 80), 0, wxStaticBoxNameStr);
	dsl_file = new wxFilePickerCtrl(dsl_box, ID_FPDSL, wxEmptyString,
			wxFileSelectorPromptStr, _("MFPG Files (*.mfpg)|*.mfpg"), wxPoint(20, 10),
			wxSize(320, 40), wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL|wxFLP_CHANGE_DIR, 
			wxDefaultValidator, wxFilePickerCtrlNameStr);
	dsl_file->Disable();
	

//-----------------------------------------NOTE MAPPER SETTINGS----------------------------------------
	notemap_area = new wxStaticBox(this, wxID_ANY, "Note Mapper", wxPoint(10, 240),
			wxSize(400, 200), 0, wxStaticBoxNameStr);
	wxString nm_choices[] = {"Basic", "CSV File"};
	//Note Mapper Selection
	notemap_box = new wxComboBox(notemap_area, ID_CBNoteMapper, _T("Basic"), wxPoint(20, 20), 
			wxSize(360, 40), 2, nm_choices, wxCB_READONLY, wxDefaultValidator, 
			wxComboBoxNameStr);
	//CSV File Selection
	wxStaticBox *csv_box = new wxStaticBox(notemap_area, wxID_ANY, "CSV File", wxPoint(20, 80),
			wxSize(360, 80), 0, wxStaticBoxNameStr);
	csv_file = new wxFilePickerCtrl(csv_box, ID_FPCSVNoteMap, wxEmptyString, wxFileSelectorPromptStr,
			_("CSV Files (*.csv)|*.csv"), wxPoint(20, 10), wxSize(320, 40), 
			wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL|wxFLP_CHANGE_DIR, wxDefaultValidator, 
			wxFilePickerCtrlNameStr);
	csv_file->Disable();


//-------------------------------------------SOLVER SETTINGS------------------------------------------
	solver_area = new wxStaticBox(this, wxID_ANY, "Solver", wxPoint(10, 450), wxSize(400, 260), 0, 
			wxStaticBoxNameStr);
	wxString solver_choices[] = {"Shortest Path", "Greedy"};
	//Solver Selection
	solver_box = new wxComboBox(solver_area, ID_CBSolver, _T("Shortest Path"), wxPoint(20, 20), 
			wxSize(360, 40), 2, solver_choices, wxCB_READONLY, wxDefaultValidator);
	//SPS Optimization 1 Checkbox
	sps_opt_1 = new wxCheckBox(solver_area, ID_CHBSPSOpt1, "Shortest Path Optimization 1", 
			wxPoint(20, 80), wxSize(360, 20), 0, wxDefaultValidator, "OPT1");
	wxStaticText *opt1_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 110),
			wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT1_TEXT");
	opt1_text->SetLabel("Invalidates previous layers if a layer has been completely been visited.");
	opt1_text->Wrap(360);
	opt1_text->Refresh();
	//SPS Optimization 2 Checkbox
	sps_opt_2 = new wxCheckBox(solver_area, ID_CHBSPSOpt2, "Shortest Path Optimization 2", 
			wxPoint(20, 160), wxSize(360, 20), 0, wxDefaultValidator, "OPT2");
	wxStaticText *opt2_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 190),
			wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT2_TEXT");
	opt2_text->SetLabel("Stops solving after finding one solution.");
	opt2_text->Wrap(360);
	opt2_text->Refresh();
	sps_opt_1->SetValue(true);
	sps_opt_2->SetValue(true);


//-------------------------------------------OUTPUT AREA-------------------------------------------
	output_area = new wxStaticBox(this, wxID_ANY, "Output", wxPoint(430, 30), wxSize(400, 600),
			0, wxStaticBoxNameStr);
	output_text = new wxTextCtrl(output_area, wxID_ANY, "",  wxPoint(20, 10), wxSize(360, 560), 
			wxTE_LEFT|wxTE_READONLY|wxTE_MULTILINE, wxDefaultValidator, "OUTPUT_TEXT");
	*output_text << _T("HELLO HELLO HELLO");
	output_text->Refresh();

//-----------------------------------------OUTPUT SETTINGS------------------------------------------
	output_settings_area = new wxStaticBox(this, wxID_ANY, "Output Settings", wxPoint(850, 30), 
			wxSize(400, 200), 0, wxStaticBoxNameStr);
	//Output Type Selection
	wxStaticText *output_selection_text = new wxStaticText(output_settings_area, wxID_ANY, 
			"Output Type",  wxPoint(20, 10), wxSize(160, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, 
			"OUTPUT_SELECTION_TEXT");
	output_selection_text->Wrap(360);
	output_selection_text->Refresh();
	wxString output_choices[] = {"CSV Output", "Direct Output"};
	output_selection_box = new wxComboBox(output_settings_area, ID_CBOutput, _T("CSV Output"), 
			wxPoint(20, 35), wxSize(160, 40), 2, output_choices, wxCB_READONLY, 
			wxDefaultValidator);
	//Output To File Checkbox
	output_to_file = new wxCheckBox(output_settings_area, ID_CHBOutputToFile, "Output to file",  
			wxPoint(220, 45), wxSize(180, 20), 0, wxDefaultValidator, "OUTPUT_TO_FILE");
	output_to_file->SetValue(true);
	//Output file selection
	wxStaticBox *output_file_box = new wxStaticBox(output_settings_area, wxID_ANY, "Output File", 
			wxPoint(20, 80), wxSize(360, 80), 0, wxStaticBoxNameStr);
	output_file = new wxFilePickerCtrl(output_file_box, ID_FPCSVOutput, wxEmptyString, 
			wxFileSelectorPromptStr, wxFileSelectorDefaultWildcardStr, wxPoint(20, 10), 
			wxSize(320, 40), 
			wxFLP_SAVE|wxFLP_USE_TEXTCTRL|wxFLP_OVERWRITE_PROMPT|wxFLP_CHANGE_DIR, 
			wxDefaultValidator, wxFilePickerCtrlNameStr);


//------------------------------------------GENERATION-------------------------------------------
	generation_area = new wxStaticBox(this, wxID_ANY, "Output Generation", wxPoint(950, 250),
			wxSize(200, 100), 0, wxStaticBoxNameStr);
	generate = new wxButton(generation_area, ID_BTGenerate, "Generate", wxPoint(50, 10)
			, wxSize(100, 50), 0, wxDefaultValidator, "GENERATE_BUTTON");
}
