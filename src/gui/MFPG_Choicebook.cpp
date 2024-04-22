#include "MFPG_Choicebook.h"

MFPG_Choicebook::MFPG_Choicebook(wxWindow* window, wxWindowID id) : wxChoicebook(window, id) {};

bool MFPG_Choicebook::AddPage(MFPG_Panel* page, const wxString &text, bool select=false, int imageId=NO_IMAGE) {
	panels.push_back(page);
	return wxChoicebook::AddPage(page, text, select, imageId);
}

MFPG_Panel *MFPG_Choicebook::getCurrentPanel() {
	return panels[GetSelection()];	
}

std::vector<MFPG_Panel*> MFPG_Choicebook::getPanels() {
	return panels;
}

void MFPG_Choicebook::DeletePageAndPanel() {
	size_t page_nr = FindPage(GetCurrentPage());
	int count = 0;
	for (auto p_itr = panels.begin(); p_itr != panels.end(); p_itr++) {
		if (count == page_nr) {
			panels.erase(p_itr);
			DeletePage(page_nr);
			break;
		}
		count++;
	}
}
