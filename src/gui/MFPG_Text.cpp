#include "MFPG_Text.h"
#include "wx/msgdlg.h"

#define T_WIDTH 500
#define T_HEIGHT 520

#define T_X 10
#define T_Y 10

MFPG_Text::MFPG_Text(wxWindow* window, long style, std::string name) : wxTextCtrl(window, wxID_ANY, 
		"", wxPoint(T_X, T_Y), wxSize(T_WIDTH, T_HEIGHT), style, wxDefaultValidator, name) {
}
