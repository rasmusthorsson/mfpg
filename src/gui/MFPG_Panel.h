#ifndef MFPG_PANEL_H
#define MFPG_PANEL_H

#include "Gui_Settings.h"

#include "wx/choicebk.h"
#include "wx/combobox.h"
#include "wx/statbox.h"
#include "wx/stattext.h"
#include "wx/filepicker.h"
#include "wx/checkbox.h"
#include "wx/panel.h"
#include "wx/msgdlg.h"

#define STATIC_BOX wxStaticBox

class MFPG_Panel : public wxPanel {
	public:
		MFPG_Panel(wxWindow*);
		MFPG_Panel();

		//Inits the components of the panel, boolean for whether to use an XRC file or static
		//structures.
		void InitPanel(bool);

		//Settings for when the program is run, set during GUI selection
		Settings ST_INSTRUMENT_SETTING = UNDEFINED;
		Settings ST_NOTEMAPPER = UNDEFINED;
		Settings ST_ACTIONSET = UNDEFINED;
		Settings ST_INSTRUMENT = UNDEFINED;
		Settings ST_OUTPUTTYPE = UNDEFINED;
		Settings ST_OUTPUTTOFILE = UNDEFINED;
		Settings ST_SOLVER = UNDEFINED;
		Settings ST_OPT = UNDEFINED;

		//Relevant filepaths
		wxString FilePath_Notemap;
		wxString FilePath_DSL;
		wxString FilePath_Output;
		wxString score_path;
		
		//Other
		wxStaticText *score_selected_text;
		wxButton *remove_config_button;
	
		//Notemap settings
		STATIC_BOX *notemap_area;
		wxComboBox *notemap_box;
		wxFilePickerCtrl *notemap_filepicker;

		//Instrument settings
		STATIC_BOX *instrument_area;
		wxTextCtrl *instrument_text;
		wxComboBox *instrument_settings_box;
		wxComboBox *instrument_box;
		wxComboBox *actionset_box;
		wxFilePickerCtrl *dsl_filepicker;

		//Open files
		STATIC_BOX *files_area;
		wxNotebook *files_book;
		wxButton *save_file_button;
		wxButton *save_as_file_button;
		wxTextCtrl *dsl_text;
		wxTextCtrl *notemapper_text;
		wxTextCtrl *output_text;

		//Output settings
		STATIC_BOX *output_settings_area;
		wxComboBox *output_selection_box;
		wxCheckBox *output_to_file;
		wxFilePickerCtrl *output_filepicker;

		//Generation button
		STATIC_BOX *generation_area;
		wxButton *generate_button;

		//Output information
		STATIC_BOX *information_area;
		wxTextCtrl *information_text;
		wxButton *clear_info_button;
};
#endif
