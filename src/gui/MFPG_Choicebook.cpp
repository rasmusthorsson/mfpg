#include "MFPG_Choicebook.h"

MFPG_Choicebook::MFPG_Choicebook(wxWindow* window, wxWindowID id) : wxChoicebook(window, id) {};

bool MFPG_Choicebook::AddPage(MFPG_Panel* page, const wxString &text, bool select=false, int imageId=NO_IMAGE) {
	panels.push_back(page);
	return wxChoicebook::AddPage(page, text, select, imageId);
}

MFPG_Panel *MFPG_Choicebook::getCurrentPanel() {
	return panels[GetSelection()];	
}

void MFPG_Choicebook::removePanel(const wxString name) {
	int page = 0;
	for (auto p = panels.begin(); p != panels.end(); p++) {
		if ((*p)->GetName() == name) {
			DeletePage(page);
			panels.erase(p);
			return;
		}
		page++;
	}
}
