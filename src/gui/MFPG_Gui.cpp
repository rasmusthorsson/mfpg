#include "MFPG_Gui.h"
#include "MFPG_Frame.h"
#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_panel.h"

wxIMPLEMENT_APP(MFPG_Gui);
 
#ifdef WIN32
	#define XRC_RESOURCE_FILE "../../resources/xrc/resources.xrc"
#else
	#define XRC_RESOURCE_FILE "../resources/xrc/resources.xrc"
#endif

bool MFPG_Gui::OnInit() {
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(XRC_RESOURCE_FILE);
	MFPG_Frame *frame = new MFPG_Frame();
	frame->Show(true);
	return true;
}
