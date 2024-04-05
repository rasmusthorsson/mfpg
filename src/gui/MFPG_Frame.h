#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H

#include "wx/wx.h"
#include "wx/choicebk.h"
#include "wx/combobox.h"
#include "Instrument.h"
#include "NoteMapper.h"
#include "BasicNoteMapper.h"
#include "CSVNoteMapper.h"
#include "Gui_Settings.h"

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
		void CBNoteMapper(wxCommandEvent&);
		
		Settings notemapper = UNDEFINED;
		Settings actionset = UNDEFINED;
		Settings instrument = UNDEFINED;
		Settings solver = UNDEFINED;

		wxString score_path;
		wxChoicebook *config_book;
		wxPanel *config_panel;
		wxComboBox *notemap_box;
};

enum {
	ID_MenuNewScore = 101,
	ID_MenuNewConfig = 102,
	ID_MenuSaveConfig = 103,
	ID_MenuSaveAsConfig = 104,
	ID_MenuDeleteConfig = 105,
	ID_CBNoteMapper = 201,
};
#endif
