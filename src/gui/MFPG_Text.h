#ifndef MFPG_TEXT_H
#define MFPG_TEXT_H

#include <wx/textctrl.h>

class MFPG_Text : public wxTextCtrl {
	public:
		MFPG_Text(wxWindow*, long, std::string);

		void keyUndo(wxKeyEvent&);
};

#endif
