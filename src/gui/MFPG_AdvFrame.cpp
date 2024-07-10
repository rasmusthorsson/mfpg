#include "MFPG_AdvFrame.h"

#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/panel.h>

MFPG_AdvFrame::MFPG_AdvFrame(wxWindow* parent) : wxFrame(parent, wxID_ANY, "Advanced Settings", 
		wxDefaultPosition, wxSize(600, 400), wxDEFAULT_FRAME_STYLE, wxFrameNameStr) {
	//Book for panels
	wxNotebook *advanced_book = new wxNotebook(this, wxID_ANY, wxPoint(10, 10), wxDefaultSize, wxNB_TOP,
		"NB_SETTINGS");
	//Output columns panel
	wxPanel *output_panel = new wxPanel(advanced_book, wxID_ANY, wxPoint(10, 10), wxDefaultSize, 
		wxTAB_TRAVERSAL, "ADV_OUTPUT_PANEL");
	advanced_book->AddPage(output_panel, "Output Settings", true, -1);
	//Box: Output Columns
	wxStaticBox *column_area = new wxStaticBox(output_panel, wxID_ANY, "Columns", wxPoint(10, 10), 
		wxSize(570, 300), 0, wxStaticBoxNameStr);
	//Text: Selected Output Columns
	wxStaticText *out_cols_label = new wxStaticText(column_area, wxID_ANY, "Selected Output Columns:", 
		wxPoint(20, 20), wxDefaultSize, wxALIGN_LEFT, wxStaticTextNameStr);
	//Text: [Colums Selected]
	out_cols_text = new wxStaticText(column_area, wxID_ANY, "", wxPoint(20, 45), wxSize(160, 20), 
		wxALIGN_LEFT, wxStaticTextNameStr);
	//Text Control: Column Name
	add_col_ctrl = new wxTextCtrl(column_area, wxID_ANY, "", wxPoint(20, 95), 
		wxSize(380, 20), 0, wxDefaultValidator, "ADD_COL_CTRL"); 
	//Button: Add Column in Control
	add_col_btn = new wxButton(column_area, ID_BTAddColumn, "Add Column", wxPoint(20, 135),
			wxSize(120, 30), 0, wxDefaultValidator, "ADD_COL_BTN");
	//Button: Remove Column in Control
	rem_col_btn = new wxButton(column_area, ID_BTRemoveColumn, "Remove Column", wxPoint(150, 135),
			wxSize(120, 30), 0, wxDefaultValidator, "REM_COL_BTN");
	//Button: Clear all Columns
	clear_col_btn = new wxButton(column_area, ID_BTClearColumns, "Clear Columns", wxPoint(280, 135),
			wxSize(120, 30), 0, wxDefaultValidator, "CLEAR_COL_BTN");
	//Solver panel
	wxPanel *solver_panel = new wxPanel(advanced_book, wxID_ANY, wxPoint(10, 10), wxDefaultSize, 
		wxTAB_TRAVERSAL, "ADV_SOLVER_PANEL");
	advanced_book->AddPage(solver_panel, "Solver Settings", false, -1);
	//Box: Solver
	solver_area = new wxStaticBox(solver_panel, wxID_ANY, "Solver", wxPoint(10, 10), wxSize(570, 300), 
		0, wxStaticBoxNameStr);
	//Selection: Solver
	wxString solver_choices[] = {"Shortest Path", "Greedy", "TLS"};
	solver_box = new wxComboBox(solver_area, ID_CBSolver, _T("Shortest Path"), wxPoint(20, 30), 
		wxSize(360, 40), 3, solver_choices, wxCB_READONLY, wxDefaultValidator);
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
		wxSize(360, 20), wxALIGN_LEFT|wxST_ELLIPSIZE_END, "OPT2_TEXT");
	opt2_text->SetLabel("Stops solving after finding one solution.");
	opt2_text->Wrap(360);
	opt2_text->Refresh();
	//Checkbox: Shortest Path solver optimization 2
	sps_opt_2 = new wxCheckBox(solver_area, ID_CHBSPSOpt2, "Shortest Path Optimization 2", 
		wxPoint(20, 160), wxSize(360, 20), 0, wxDefaultValidator, "OPT2");
}
