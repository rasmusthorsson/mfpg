#include "MFPG_Gui.h"
#include "MFPG_Frame.h"

wxIMPLEMENT_APP(MFPG_Gui);
 
bool MFPG_Gui::OnInit() {
	MFPG_Frame *frame = new MFPG_Frame();
	frame->Show(true);
	return true;
}
