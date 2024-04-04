#ifndef MFPG_FRAME_H
#define MFPG_FRAME_H

#include "wx/wx.h"

class MFPG_Frame : public wxFrame {
	private:
		DECLARE_EVENT_TABLE()
	public:
		void OnScore(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnConfig(wxCommandEvent& event);
		wxString score;
		MFPG_Frame();
};

enum {
	ID_Score = 1,
	ID_Config = 2
};
#endif
