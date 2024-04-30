#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H
#include "MFPG_Choicebook.h"

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "wx/xml/xml.h"

//Definitions of XML attribute names
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
		//Must declare event table
		DECLARE_EVENT_TABLE()
		//If XRC file is used or if static structure definitions are used
		bool use_xrc;
	public:
		MFPG_Frame(bool);

		//Interactive structures in the GUI
		//Menu
		void MenuNewScore(wxCommandEvent&);
		void MenuNewConfig(wxCommandEvent&);
		void MenuLoadConfig(wxCommandEvent&);
		void MenuSaveConfig(wxCommandEvent&);
		void MenuSaveAsConfig(wxCommandEvent&);
		void MenuDeleteConfig(wxCommandEvent&);
		void MenuExit(wxCommandEvent&);
		void MenuAbout(wxCommandEvent&);
		void MenuGuide(wxCommandEvent&);
		//Books
		void CBOOKChange(wxBookCtrlEvent&);
		void NBOOKChange(wxBookCtrlEvent&);
		//Choiceboxes
		void CBNoteMapper(wxCommandEvent&);
		void CBInstSettings(wxCommandEvent&);
		void CBInstrument(wxCommandEvent&);
		void CBActionSet(wxCommandEvent&);
		void CBSolver(wxCommandEvent&);
		void CBOutput(wxCommandEvent&);
		//Checkboxes
		void CHBSPSOpt1(wxCommandEvent&);
		void CHBSPSOpt2(wxCommandEvent&);
		void CHBOutputToFile(wxCommandEvent&);
		//Filepickers
		void FPDSL(wxFileDirPickerEvent&);
		void FPCSVNoteMap(wxFileDirPickerEvent&);
		void FPCSVOutput(wxFileDirPickerEvent&);
		//Buttons
		void BTRemoveConfig(wxCommandEvent&);
		void BTGenerate(wxCommandEvent&);
		void BTSavetext(wxCommandEvent&);
		void BTSaveastext(wxCommandEvent&);
		void BTClearInfo(wxCommandEvent&);

		//Programwide paths
		wxString score_path;
		wxString configs_path;

		//Frame book
		MFPG_Choicebook *config_book;
		//Keeping track of which panel is currently active
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
