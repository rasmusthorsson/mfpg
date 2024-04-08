#include "MFPG_Frame.h"
#include "conf_cmake.h"
#include <wx/docview.h>
#include <wx/textctrl.h>
#include <wx/choicebk.h>
#include <wx/valtext.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>

#define WIDTH 1280
#define HEIGHT 900

MFPG_Frame::MFPG_Frame() : wxFrame(nullptr, wxID_ANY, "MFPG", wxDefaultPosition, wxSize(WIDTH, HEIGHT),
		wxDEFAULT_FRAME_STYLE, wxFrameNameStr) {
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_MenuNewScore, "&Select Score","");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	
	wxMenu *menuConfig = new wxMenu;
	menuConfig->Append(ID_MenuNewConfig, "&New Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveConfig, "&Save Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveAsConfig, "&Save Config As");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuDeleteConfig, "&Delete Config");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	menuBar->Append(menuConfig, "&Configs");

	SetMenuBar( menuBar );

	CreateStatusBar();
	std::string status("MFPG -- Version: ");
	status += VERSION_MFPG;
	SetStatusText(status);
	
	config_book = new MFPG_Choicebook(this, ID_CBOOKChange);
	MFPG_Panel *config_panel = new MFPG_Panel(config_book);
	
	current_panel = config_panel;
	config_book->AddPage(config_panel, _T("Config1"), true, 0);
}

wxBEGIN_EVENT_TABLE(MFPG_Frame, wxFrame)
	EVT_MENU(wxID_EXIT, MFPG_Frame::MenuExit)
	EVT_MENU(wxID_ABOUT, MFPG_Frame::MenuAbout)
	EVT_MENU(ID_MenuNewScore, MFPG_Frame::MenuNewScore)
	EVT_MENU(ID_MenuNewConfig, MFPG_Frame::MenuNewConfig)
	EVT_MENU(ID_MenuSaveConfig, MFPG_Frame::MenuSaveConfig)
	EVT_MENU(ID_MenuSaveAsConfig, MFPG_Frame::MenuSaveAsConfig)
	EVT_MENU(ID_MenuDeleteConfig, MFPG_Frame::MenuDeleteConfig)

	EVT_CHOICEBOOK_PAGE_CHANGED(ID_CBOOKChange, MFPG_Frame::CBOOKChange)

	EVT_COMBOBOX(ID_CBNoteMapper, MFPG_Frame::CBNoteMapper)
	EVT_COMBOBOX(ID_CBInstrument, MFPG_Frame::CBInstrument)
	EVT_COMBOBOX(ID_CBActionSet, MFPG_Frame::CBActionSet)
	EVT_COMBOBOX(ID_CBSolver, MFPG_Frame::CBSolver)

	EVT_CHECKBOX(ID_CHBSPSOpt1, MFPG_Frame::CHBSPSOpt1)
	EVT_CHECKBOX(ID_CHBSPSOpt2, MFPG_Frame::CHBSPSOpt2)
wxEND_EVENT_TABLE()

void MFPG_Frame::MenuExit(wxCommandEvent& event) {
	Close(true);
}

void MFPG_Frame::MenuAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MFPG_Frame::MenuNewScore(wxCommandEvent& event) {
	wxFileDialog *file_dialog = new wxFileDialog(this, _("Choose a musicXML file to open"), 
			wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), 
			wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	if (file_dialog->ShowModal() == wxID_OK) {
		score_path = file_dialog->GetPath();
	}
}
void MFPG_Frame::MenuNewConfig(wxCommandEvent& event) {
	wxString new_conf;
	wxTextEntryDialog *input_dialog = new wxTextEntryDialog(this, _("Config Name"), 
			_("New Config"), wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
	input_dialog->SetMaxLength(16);
	wxTextValidator config_names(wxFILTER_INCLUDE_CHAR_LIST);
	config_names.SetCharIncludes(config_chars);
	input_dialog->SetTextValidator(config_names);
	if (input_dialog->ShowModal() == wxID_OK) {
		new_conf = input_dialog->GetValue();
	}
	MFPG_Panel *config_panel = new MFPG_Panel(config_book);
	config_book->AddPage(config_panel, new_conf, true, 0);
	current_panel = config_panel;
}
void MFPG_Frame::MenuSaveConfig(wxCommandEvent& event) {
		
}
void MFPG_Frame::MenuSaveAsConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::MenuDeleteConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::CBOOKChange(wxBookCtrlEvent& event) {
	current_panel = config_book->getCurrentPanel();
}
void MFPG_Frame::CBNoteMapper(wxCommandEvent& event) {
	if (current_panel->notemap_box->GetCurrentSelection() == 0) {
		current_panel->csv_file->Disable();
		current_panel->notemapper = Settings::NOTEMAPPER_BASIC;
	} else if (current_panel->notemap_box->GetCurrentSelection() == 1) {
		current_panel->csv_file->Enable();
		current_panel->notemapper = Settings::NOTEMAPPER_CSV;
	} else {
		current_panel->notemapper = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBInstrument(wxCommandEvent& event) {
	if (current_panel->instrument_box->GetCurrentSelection() == 0) {
		if (current_panel->actionset_box->GetCurrentSelection() != 2) {
			current_panel->dsl_file->Disable();
		}
		current_panel->instrument = Settings::INSTRUMENT_VIOLIN;
	} else if (current_panel->instrument_box->GetCurrentSelection() == 1) {
		current_panel->dsl_file->Enable();
		current_panel->instrument = Settings::INSTRUMENT_DSL;
	} else {
		current_panel->instrument = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBActionSet(wxCommandEvent& event) {
	if (current_panel->actionset_box->GetCurrentSelection() == 0) {
		if (current_panel->instrument_box->GetCurrentSelection() != 1) {
			current_panel->dsl_file->Disable();
		}
		current_panel->actionset = Settings::ACTIONSET_T1;
	} else if (current_panel->actionset_box->GetCurrentSelection() == 1) {
		if (current_panel->instrument_box->GetCurrentSelection() != 1) {
			current_panel->dsl_file->Disable();
		}
		current_panel->actionset = Settings::ACTIONSET_T2;
	} else if (current_panel->actionset_box->GetCurrentSelection() == 2) {
		current_panel->dsl_file->Enable();
		current_panel->actionset = Settings::ACTIONSET_DSL;
	} else {
		current_panel->actionset = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBSolver(wxCommandEvent& event) {
	if (current_panel->solver_box->GetCurrentSelection() == 0) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if ((c->GetName() == "OPT1_TEXT" && current_panel->sps_opt_1->IsChecked()) ||
			     (c->GetName() == "OPT2_TEXT" && current_panel->sps_opt_2->IsChecked())) {
				c->Enable();
			}
		}
		current_panel->sps_opt_1->Enable();
		current_panel->sps_opt_2->Enable();
		current_panel->solver = Settings::SOLVER_SPS;
	} else if (current_panel->solver_box->GetCurrentSelection() == 1) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT" || c->GetName() == "OPT2_TEXT") {
				c->Disable();
			}
		}
		current_panel->sps_opt_1->Disable();
		current_panel->sps_opt_2->Disable();
		current_panel->solver = Settings::SOLVER_GREEDY;
	} else {
		current_panel->solver = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CHBSPSOpt1(wxCommandEvent& event) {
	if (current_panel->sps_opt_1->IsChecked()) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT") {
				c->Enable();
			}
		}
		if (current_panel->sps_opt_2->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_3;
		} else {
			current_panel->solver = Settings::SOLVER_SPS_1;
		}
	} else {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT") {
				c->Disable();
			}
		}
		if (current_panel->sps_opt_2->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_2;
		} else {
			current_panel->solver = Settings::SOLVER_SPS;
		}
	}

}
void MFPG_Frame::CHBSPSOpt2(wxCommandEvent& event) {
	if (current_panel->sps_opt_2->IsChecked()) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT2_TEXT") {
				c->Enable();
			}
		}
		if (current_panel->sps_opt_1->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_3;
		} else {
			current_panel->solver = Settings::SOLVER_SPS_2;
		}
	} else {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT2_TEXT") {
				c->Disable();
			}
		}
		if (current_panel->sps_opt_1->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_1;
		} else {
			current_panel->solver = Settings::SOLVER_SPS;
		}
	}
}
