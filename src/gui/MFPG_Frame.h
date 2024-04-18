#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H

#include "wx/wx.h"
#include "wx/choicebk.h"
#include "wx/filepicker.h"
#include "wx/xml/xml.h"

#include "MFPG_Choicebook.h"

using Distance = int;

class MFPG_Frame : public wxFrame {
	private:
		void Generate();
		const wxString config_chars = ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-");
		DECLARE_EVENT_TABLE()
	public:
		MFPG_Frame();
		void MenuNewScore(wxCommandEvent&);
		void MenuNewConfig(wxCommandEvent&);
		void MenuLoadConfig(wxCommandEvent&);
		void MenuSaveConfig(wxCommandEvent&);
		void MenuSaveAsConfig(wxCommandEvent&);
		void MenuDeleteConfig(wxCommandEvent&);
		void MenuExit(wxCommandEvent&);
		void MenuAbout(wxCommandEvent&);
		void MenuGuide(wxCommandEvent&);
		void CBOOKChange(wxBookCtrlEvent&);
		void NBOOKChange(wxBookCtrlEvent&);
		void CBNoteMapper(wxCommandEvent&);
		void CBInstSettings(wxCommandEvent&);
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
		void BTClearInfo(wxCommandEvent&);

		wxString score_path;
		wxString configs_path;

		MFPG_Choicebook *config_book;
		MFPG_Panel *current_panel;

		void SetNoteMapper(Settings);
		void SetInstSettings(Settings);
		void SetInstrument(Settings);
		void SetActionSet(Settings);
		void SetSolver(Settings);
		void SetOpt(Settings);
		void SetOutputToFile(Settings);
		void SetOutput(Settings);

		void SelectDSLFile(wxString);
		void SelectNoteMapFile(wxString);
		void SelectOutputFile(wxString);

		//New config must be attached to existing document or explicitly deleted
		wxXmlNode *NewConfig(wxString);
		void LoadConfig(wxString);
};

#endif
