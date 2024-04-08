#ifndef MFPG_PANEL_H
#define MFPG_PANEL_H

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

class MFPG_Panel : public wxPanel {
	public:
		MFPG_Panel(wxWindow*);
		
		Settings notemapper = UNDEFINED;
		Settings actionset = UNDEFINED;
		Settings instrument = UNDEFINED;
		Settings solver = UNDEFINED;

		wxStaticBox *notemap_area;
		wxComboBox *notemap_box;
		wxFilePickerCtrl *csv_file;

		wxStaticBox *instrument_area;
		wxComboBox *instrument_box;
		wxComboBox *actionset_box;
		wxFilePickerCtrl *dsl_file;

		wxStaticBox *solver_area;
		wxComboBox *solver_box;
		wxCheckBox *sps_opt_1;
		wxCheckBox *sps_opt_2;

};
#endif
