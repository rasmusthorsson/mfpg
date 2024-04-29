#include "MFPG_Gui.h"
#include "MFPG_Frame.h"

#include "wx/xrc/xmlres.h"

#include "fstream"

wxIMPLEMENT_APP(MFPG_Gui);

bool MFPG_Gui::OnInit() {
	//Possible locations
	std::vector<std::string> xrc_locations({
			"../../resources/xrc/resources.xrc",
			"../resources/xrc/resources.xrc",
			"resources.xrc"
			});
	std::ifstream xrc_stream;
	MFPG_Frame *frame;
	for (auto s : xrc_locations) {
		xrc_stream.open(s); //Check to see if file exists
		if (xrc_stream.is_open()) {
			xrc_stream.close();
			wxXmlResource::Get()->InitAllHandlers();
			wxXmlResource::Get()->Load(s);
			frame = new MFPG_Frame(true);
			frame->Show(true);
			return true;
		}
	}
	wxMessageBox("Could not find any XRC file, defaulting to basic layout...");
	frame = new MFPG_Frame(false);
	frame->Show(true);
	return true;
}
