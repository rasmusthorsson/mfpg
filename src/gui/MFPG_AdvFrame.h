#ifndef MFPG_ADV_FRAME_H
#define MFPG_ADV_FRAME_H

#include "Gui_Settings.h"

#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>

class MFPG_AdvFrame : public wxFrame {
	public:
		MFPG_AdvFrame(wxWindow*);

		//Output columns
		wxStaticText *out_cols_text;
		wxTextCtrl *add_col_ctrl;
		wxButton *add_col_btn;
		wxButton *rem_col_btn;
		wxButton *clear_col_btn;

		//Solver selection
		wxStaticBox *solver_area;
		wxComboBox *solver_box;
		wxCheckBox *sps_opt_1;
		wxCheckBox *sps_opt_2;
};

#endif
