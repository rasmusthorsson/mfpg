#include "MFPG_Frame.h"
#include "conf_cmake.h"
#include <wx/docview.h>
#include <wx/textctrl.h>
#include <wx/choicebk.h>
#include <wx/valtext.h>
#include <wx/statbox.h>
#include <wx/combobox.h>

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
	
	config_book = new wxChoicebook(this, 1);
	config_panel = new wxPanel(config_book);
	wxStaticBox *box = new wxStaticBox(config_panel, wxID_ANY, "Note Mapper", wxPoint(10, 10),
			wxSize(200, 200), 0, wxStaticBoxNameStr);
	wxString choices[] = {"Basic", "CSV File"};
	notemap_box = new wxComboBox(box, ID_CBNoteMapper, _T("Basic"), wxPoint(20, 20), 
			wxSize(150, 40), 2, choices, wxCB_READONLY, wxDefaultValidator, wxComboBoxNameStr);

	config_book->AddPage(config_panel, _T("Config1"), true);

}

wxBEGIN_EVENT_TABLE(MFPG_Frame, wxFrame)
	EVT_MENU(wxID_EXIT, MFPG_Frame::MenuExit)
	EVT_MENU(wxID_ABOUT, MFPG_Frame::MenuAbout)
	EVT_MENU(ID_MenuNewScore, MFPG_Frame::MenuNewScore)
	EVT_MENU(ID_MenuNewConfig, MFPG_Frame::MenuNewConfig)
	EVT_MENU(ID_MenuSaveConfig, MFPG_Frame::MenuSaveConfig)
	EVT_MENU(ID_MenuSaveAsConfig, MFPG_Frame::MenuSaveAsConfig)
	EVT_MENU(ID_MenuDeleteConfig, MFPG_Frame::MenuDeleteConfig)

	EVT_COMBOBOX(ID_CBNoteMapper, MFPG_Frame::CBNoteMapper)
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
			wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), wxFD_OPEN, 
			wxDefaultPosition);
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
	config_book->AddPage(config_panel, new_conf, true);
}
void MFPG_Frame::MenuSaveConfig(wxCommandEvent& event) {
		
}
void MFPG_Frame::MenuSaveAsConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::MenuDeleteConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::CBNoteMapper(wxCommandEvent& event) {
	if (notemap_box->GetCurrentSelection() == 0) {
		notemapper = Settings::NOTEMAPPER_BASIC;
		wxMessageBox("BASIC");
	} else if (notemap_box->GetCurrentSelection() == 1) {
		notemapper = Settings::NOTEMAPPER_CSV;
		wxMessageBox("CSV File");
	} else {
		notemapper = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
