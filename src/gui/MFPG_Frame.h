#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H

#include "wx/wx.h"
#include "wx/choicebk.h"
#include "wx/filepicker.h"
#include "wx/xml/xml.h"

#include "MFPG_Choicebook.h"

#define INSTRUMENT_SETTINGS_CONF "instrument_settings"
#define DSL_FILE_CONF "dsl_file"
#define INSTRUMENT_CONF "instrument"
#define ACTIONSET_CONF "actionset"
#define NOTEMAPPER_SETTINGS_CONF "notemapper_settings"
#define NOTEMAPPER_FILE_CONF "notemapper_file"
#define SOLVER_SETTINGS_CONF "solver_settings"
#define SOLVER_OPT_CONF "solver_opt"
#define OUTPUT_SETTINGS_CONF "output_settings"
#define OUTPUT_TO_FILE_CONF "output_to_file"
#define OUTPUT_FILE_CONF "output_file"
#define CONFIG_NAME_CONF "name"

using Distance = int;

class MFPG_Frame : public wxFrame {
	private:
		//Main generation of output
		void Generate();
		//Allowed characters for config names
		const wxString config_chars = ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-");
		DECLARE_EVENT_TABLE()
	public:
		MFPG_Frame();

		//Interactive objects in the GUI
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
		void BTRemoveConfig(wxCommandEvent&);
		void BTGenerate(wxCommandEvent&);
		void BTSavetext(wxCommandEvent&);
		void BTSaveastext(wxCommandEvent&);
		void BTClearInfo(wxCommandEvent&);

		wxString score_path;
		wxString configs_path;

		MFPG_Choicebook *config_book;
		MFPG_Panel *current_panel;

		//Functions to allow setting the settings while also activating the correct buttons
		//in the gui from inside the code.
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
