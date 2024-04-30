#ifndef MFPG_CHOICEBOOK_H
#define MFPG_CHOICEBOOK_H
#include "MFPG_Panel.h"

#include "wx/wx.h"
#include "wx/choicebk.h"

#include <vector>

class MFPG_Choicebook : public wxChoicebook {
	private:
		//Contains all active panels in the book, one per page.
		std::vector<MFPG_Panel*> panels;
	public:
		MFPG_Choicebook(wxWindow*, wxWindowID);
		
		//Add page 'override' to allow panel addition alongside page addition.
		bool AddPage(MFPG_Panel*, const wxString&, bool, int);

		//Gets panel of current page.
		MFPG_Panel *getCurrentPanel();

		//Gets all panels.
		std::vector<MFPG_Panel*> getPanels();

		//Delete both page and associated panel.
		void DeletePageAndPanel();
};
#endif
