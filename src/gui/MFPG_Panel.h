#ifndef MFPG_PANEL_H
#define MFPG_PANEL_H

#include "wx/choicebk.h"
#include "wx/combobox.h"
#include "wx/statbox.h"
#include "wx/stattext.h"
#include "wx/filepicker.h"
#include "wx/checkbox.h"
#include "wx/panel.h"
#include "wx/msgdlg.h"

#include "Gui_Settings.h"

class MFPG_Panel : public wxPanel {
	public:
		MFPG_Panel(wxWindow*);

		//Settings for when the program is run, set during GUI selection
		Settings ST_INSTRUMENT_SETTING = UNDEFINED;
		Settings ST_NOTEMAPPER = UNDEFINED;
		Settings ST_ACTIONSET = UNDEFINED;
		Settings ST_INSTRUMENT = UNDEFINED;
		Settings ST_SOLVER = UNDEFINED;
		Settings ST_OPT = UNDEFINED;
		Settings ST_OUTPUTTYPE = UNDEFINED;
		Settings ST_OUTPUTTOFILE = UNDEFINED;

		//Relevant filepaths
		wxString FilePath_Notemap;
		wxString FilePath_DSL;
		wxString FilePath_Output;
	
		//Notemap settings
		wxStaticBox *notemap_area;
		wxComboBox *notemap_box;
		wxFilePickerCtrl *notemap_filepicker;

		//Instrument settings
		wxStaticBox *instrument_area;
		wxComboBox *instrument_settings_box;
		wxComboBox *instrument_box;
		wxComboBox *actionset_box;
		wxFilePickerCtrl *dsl_filepicker;

		//Solver settings
		wxStaticBox *solver_area;
		wxComboBox *solver_box;
		wxCheckBox *sps_opt_1;
		wxCheckBox *sps_opt_2;

		//Open files
		wxStaticBox *files_area;
		wxNotebook *files_book;
		wxButton *save_file_button;
		wxButton *save_as_file_button;
		wxTextCtrl *dsl_text;
		wxTextCtrl *notemapper_text;
		wxTextCtrl *output_text;

		//Output settings
		wxStaticBox *output_settings_area;
		wxComboBox *output_selection_box;
		wxCheckBox *output_to_file;
		wxFilePickerCtrl *output_file;//TODO fix

		//Generation button
		wxStaticBox *generation_area;
		wxStaticText *score_selected_text;
		wxButton *generate_button;

		//Output information
		wxStaticBox *information_area;
		wxTextCtrl *information_text;
		wxButton *clear_info_button;
};


#endif
