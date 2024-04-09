#ifndef MFPG_CHOICEBOOK_H
#define MFPG_CHOICEBOOK_H

#include "wx/wx.h"
#include "wx/choicebk.h"
#include "wx/combobox.h"
#include "wx/statbox.h"
#include "Instrument.h"
#include "NoteMapper.h"
#include "BasicNoteMapper.h"
#include "CSVNoteMapper.h"
#include "Gui_Settings.h"
#include "wx/filepicker.h"
#include "wx/checkbox.h"
#include "MFPG_Panel.h"
#include <vector>

class MFPG_Choicebook : public wxChoicebook {
	private:
		std::vector<MFPG_Panel*> panels;
	public:
		MFPG_Choicebook(wxWindow*, wxWindowID);
		
		bool AddPage(MFPG_Panel*, const wxString&, bool, int);
		MFPG_Panel *getCurrentPanel();
		std::vector<MFPG_Panel*> getPanels() {
			return panels;
		}
};
#endif
