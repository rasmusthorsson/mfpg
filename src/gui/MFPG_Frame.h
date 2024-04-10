#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H

#include "wx/wx.h"
#include "wx/choicebk.h"
#include "wx/filepicker.h"

#include "MFPG_Panel.h"
#include "MFPG_Choicebook.h"

using Distance = int;

class MFPG_Frame : public wxFrame {
	private:
		const wxString config_chars = ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-");
		DECLARE_EVENT_TABLE()
	public:
		MFPG_Frame();
		void MenuNewScore(wxCommandEvent&);
		void MenuNewConfig(wxCommandEvent&);
		void MenuSaveConfig(wxCommandEvent&);
		void MenuSaveAsConfig(wxCommandEvent&);
		void MenuDeleteConfig(wxCommandEvent&);
		void MenuExit(wxCommandEvent&);
		void MenuAbout(wxCommandEvent&);
		void MenuGuide(wxCommandEvent&);
		void CBOOKChange(wxBookCtrlEvent&);
		void NBOOKChange(wxBookCtrlEvent&);
		void CBNoteMapper(wxCommandEvent&);
		void CBInstrument(wxCommandEvent&);
		void CBActionSet(wxCommandEvent&);
		void CBSolver(wxCommandEvent&);
		void CHBSPSOpt1(wxCommandEvent&);
		void CHBSPSOpt2(wxCommandEvent&);
		void CHBOutputToFile(wxCommandEvent&);
		void CBOutput(wxCommandEvent&);
		void FPDSL(wxFileDirPickerEvent&);
		void FPCSVNoteMap(wxFileDirPickerEvent&);
		void FPCSVOutput(wxFileDirPickerEvent&);
		void BTGenerate(wxCommandEvent&);
		void BTSavetext(wxCommandEvent&);
		void BTSaveastext(wxCommandEvent&);
		
		void Generate();

		wxString score_path;

		MFPG_Choicebook *config_book;
		MFPG_Panel *current_panel;
};

#endif
