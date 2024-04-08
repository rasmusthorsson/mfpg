#include "MFPG_Panel.h"

MFPG_Panel::MFPG_Panel(wxWindow* window) : wxPanel(window) {
	instrument_area = new wxStaticBox(this, wxID_ANY, "Instrument", wxPoint(10, 10),
			wxSize(400, 200), 0, wxStaticBoxNameStr);
	wxString inst_choices[] = {"Violin", "DSL File"};
	instrument_box = new wxComboBox(instrument_area, ID_CBInstrument, _T("Violin"), wxPoint(20, 20), 
			wxSize(160, 40), 2, inst_choices, wxCB_READONLY, wxDefaultValidator, 
			wxComboBoxNameStr);

	wxString actionset_choices[] = {"Test1", "Test2", "DSL File"};
	actionset_box = new wxComboBox(instrument_area, ID_CBActionSet, _T("Test1"), wxPoint(220, 20),
			wxSize(160, 40), 3, actionset_choices, wxCB_READONLY, wxDefaultValidator);

	wxStaticBox *dsl_box = new wxStaticBox(instrument_area, wxID_ANY, "DSL File", wxPoint(20, 80),
			wxSize(360, 80), 0, wxStaticBoxNameStr);
	dsl_file = new wxFilePickerCtrl(dsl_box, wxID_ANY, wxEmptyString,
			wxFileSelectorPromptStr, wxFileSelectorDefaultWildcardStr, wxPoint(20, 10),
			wxSize(320, 40), wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, 
			wxFilePickerCtrlNameStr);
	dsl_file->Disable();
	
	notemap_area = new wxStaticBox(this, wxID_ANY, "Note Mapper", wxPoint(10, 220),
			wxSize(400, 200), 0, wxStaticBoxNameStr);
	wxString nm_choices[] = {"Basic", "CSV File"};
	notemap_box = new wxComboBox(notemap_area, ID_CBNoteMapper, _T("Basic"), wxPoint(20, 20), 
			wxSize(360, 40), 2, nm_choices, wxCB_READONLY, wxDefaultValidator, 
			wxComboBoxNameStr);
	wxStaticBox *csv_box = new wxStaticBox(notemap_area, wxID_ANY, "CSV File", wxPoint(20, 80),
			wxSize(360, 80), 0, wxStaticBoxNameStr);
	csv_file = new wxFilePickerCtrl(csv_box, wxID_ANY, wxEmptyString,
			wxFileSelectorPromptStr, wxFileSelectorDefaultWildcardStr, wxPoint(20, 10),
			wxSize(320, 40), wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, 
			wxFilePickerCtrlNameStr);
	csv_file->Disable();

	solver_area = new wxStaticBox(this, wxID_ANY, "Solver", wxPoint(10, 440), 
			wxSize(400, 250), 0, wxStaticBoxNameStr);
	wxString solver_choices[] = {"Shortest Path", "Greedy"};
	solver_box = new wxComboBox(solver_area, ID_CBSolver, _T("Shortest Path"), wxPoint(20, 20), 
			wxSize(360, 40), 2, solver_choices, wxCB_READONLY, wxDefaultValidator);

	sps_opt_1 = new wxCheckBox(solver_area, ID_CHBSPSOpt1, "Shortest Path Optimization 1", 
			wxPoint(20, 80), wxSize(360, 20), 0, wxDefaultValidator, "OPT1");
	wxStaticText *opt1_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 110),
			wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT1_TEXT");
	opt1_text->SetLabel("Invalidates previous layers if a layer has been completely been visited (faster solver).");
	opt1_text->Wrap(360);
	opt1_text->Refresh();
	sps_opt_2 = new wxCheckBox(solver_area, ID_CHBSPSOpt2, "Shortest Path Optimization 2", 
			wxPoint(20, 160), wxSize(360, 20), 0, wxDefaultValidator, "OPT2");
	wxStaticText *opt2_text = new wxStaticText(solver_area, wxID_ANY, "", wxPoint(20, 190),
			wxSize(360, 40), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT2_TEXT");
	opt2_text->SetLabelMarkup("Stops solving after finding one solution (faster solver).");
	opt2_text->Wrap(360);
	opt2_text->Refresh();
	sps_opt_1->SetValue(true);
	sps_opt_2->SetValue(true);
}
