#include "MFPG_Frame.h"
#include "conf_cmake.h"
#include <wx/docview.h>
#include <wx/textctrl.h>
#include <wx/choicebk.h>

MFPG_Frame::MFPG_Frame() : wxFrame(nullptr, wxID_ANY, "MFPG") {
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_Score, "&Select Score","");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar( menuBar );

	CreateStatusBar();
	std::string status("MFPG -- Version: ");
	status += VERSION_MFPG;
	SetStatusText(status);
	
	wxChoicebook *book = new wxChoicebook(this, ID_Config);
	wxPanel *panel = new wxPanel(book);
	new wxButton( panel, ID_Config,
  		_T("Button &1"), wxPoint(50,30), wxSize(100,30) );

}

wxBEGIN_EVENT_TABLE(MFPG_Frame, wxFrame)
	EVT_MENU(wxID_EXIT, MFPG_Frame::OnExit)
	EVT_MENU(wxID_ABOUT, MFPG_Frame::OnAbout)
	EVT_MENU(ID_Score, MFPG_Frame::OnScore)
	EVT_BUTTON(ID_Config, MFPG_Frame::OnConfig)
wxEND_EVENT_TABLE()

void MFPG_Frame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MFPG_Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

void MFPG_Frame::OnScore(wxCommandEvent& event) {
	wxFileDialog *file_dialog = new wxFileDialog(this, _("Choose a musicXML file to open"), 
			wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), wxFD_OPEN, 
			wxDefaultPosition);
	if (file_dialog->ShowModal() == wxID_OK) {
		score = file_dialog->GetPath();
	}
}

void MFPG_Frame::OnConfig(wxCommandEvent& event) {
	
}

