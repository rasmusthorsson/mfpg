#include "MFPG_Gui.h"
#include "MFPG_Frame.h"
#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_aui.h"
#include "wx/xrc/xh_panel.h"

wxIMPLEMENT_APP(MFPG_Gui);
 
bool MFPG_Gui::OnInit() {
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load("../../resources/xrc/resources.xrc");
	MFPG_Frame *frame = new MFPG_Frame();
	frame->Show(true);
	return true;
}
