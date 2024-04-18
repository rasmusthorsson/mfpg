#include "MFPG_Frame.h"

#include <stdexcept>
#include <wx/docview.h>
#include <wx/textctrl.h>
#include <wx/choicebk.h>
#include <wx/valtext.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/xml/xml.h>
#include <wx/stdpaths.h>

#include "mx/api/DocumentManager.h"

#include "conf_cmake.h"

#include <vector>
#include <fstream>

#include "NoteEnums.h"
#include "NoteMapper.h"
#include "BasicNoteMapper.h"
#include "CSVNoteMapper.h"
#include "LayerList.h"
#include "NoteList.h"
#include "GraphSolver.h"
#include "GreedySolver.h"
#include "SPSolver.h"
#include "Instrument.h"
#include "InstrumentBuilder.h"
#include "NoteMapperException.h"
#include "ExValException.h"
#include "configs.h"

#include "Parser.H"
#include "ParserError.H"

extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

inline char sep()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

#define WIDTH 1280
#define HEIGHT 900

MFPG_Frame::MFPG_Frame() : wxFrame(nullptr, wxID_ANY, "MFPG", wxDefaultPosition, wxSize(WIDTH, HEIGHT),
		wxDEFAULT_FRAME_STYLE, wxFrameNameStr) {
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_MenuNewScore, "&Select Score","");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	menuHelp->Append(ID_MenuGuide, "&Guides");
	
	wxMenu *menuConfig = new wxMenu;
	menuConfig->Append(ID_MenuNewConfig, "&New Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuLoadConfig, "&Load Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveConfig, "&Save Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveAsConfig, "&Save Config As");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuDeleteConfig, "&Delete Saved Config");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	menuBar->Append(menuConfig, "&Configs");

	SetMenuBar( menuBar );

	CreateStatusBar();
	std::string status("MFPG -- Version: ");
	status += VERSION_MFPG;
	SetStatusText(status);

	//wxString configs_dir(wxStandardPaths::Get().GetConfigDir());
	configs_path = wxGetCwd();
	//configs_path.append(sep());
	//configs_path.append("MFPG_Configs");
	configs_path.append(sep());
	configs_path.append(".mfpg_configs.xml");
	wxXmlDocument configs_file;
	if (!configs_file.Load(configs_path)) {
		wxMessageBox("Could not find config file (.mfpg_configs.xml) in current directory.");
	}
	
	config_book = new MFPG_Choicebook(this, ID_CBOOKChange);
	wxMessageDialog load_all_confs(NULL, "Load all saved configs?", "Config Load", 
		wxYES_NO|wxCENTRE|wxICON_QUESTION|wxSTAY_ON_TOP, wxDefaultPosition);
	MFPG_Panel *config_panel = new MFPG_Panel(config_book);	
	current_panel = config_panel;
	config_book->AddPage(config_panel, "UnnamedConfig", true, 0);
	if (load_all_confs.ShowModal() == wxID_YES) {
		wxXmlNode *c = configs_file.GetRoot()->GetChildren()->GetChildren();
		while (c) {
			LoadConfig(c->GetAttribute("name", wxEmptyString));
			c = c->GetNext();
		}
	} 
}

wxBEGIN_EVENT_TABLE(MFPG_Frame, wxFrame)
	EVT_MENU(wxID_EXIT, MFPG_Frame::MenuExit)
	EVT_MENU(wxID_ABOUT, MFPG_Frame::MenuAbout)
	EVT_MENU(ID_MenuGuide, MFPG_Frame::MenuGuide)
	EVT_MENU(ID_MenuNewScore, MFPG_Frame::MenuNewScore)
	EVT_MENU(ID_MenuNewConfig, MFPG_Frame::MenuNewConfig)
	EVT_MENU(ID_MenuLoadConfig, MFPG_Frame::MenuLoadConfig)
	EVT_MENU(ID_MenuSaveConfig, MFPG_Frame::MenuSaveConfig)
	EVT_MENU(ID_MenuSaveAsConfig, MFPG_Frame::MenuSaveAsConfig)
	EVT_MENU(ID_MenuDeleteConfig, MFPG_Frame::MenuDeleteConfig)

	EVT_CHOICEBOOK_PAGE_CHANGED(ID_CBOOKChange, MFPG_Frame::CBOOKChange)
	EVT_NOTEBOOK_PAGE_CHANGED(ID_NBOOKChange, MFPG_Frame::NBOOKChange)

	EVT_COMBOBOX(ID_CBNoteMapper, MFPG_Frame::CBNoteMapper)
	EVT_COMBOBOX(ID_CBInstSettings, MFPG_Frame::CBInstSettings)
	EVT_COMBOBOX(ID_CBInstrument, MFPG_Frame::CBInstrument)
	EVT_COMBOBOX(ID_CBActionSet, MFPG_Frame::CBActionSet)
	EVT_COMBOBOX(ID_CBSolver, MFPG_Frame::CBSolver)
	EVT_COMBOBOX(ID_CBOutput, MFPG_Frame::CBOutput)

	EVT_CHECKBOX(ID_CHBSPSOpt1, MFPG_Frame::CHBSPSOpt1)
	EVT_CHECKBOX(ID_CHBSPSOpt2, MFPG_Frame::CHBSPSOpt2)
	EVT_CHECKBOX(ID_CHBOutputToFile, MFPG_Frame::CHBOutputToFile)

	EVT_FILEPICKER_CHANGED(ID_FPDSL, MFPG_Frame::FPDSL)
	EVT_FILEPICKER_CHANGED(ID_FPCSVNoteMap, MFPG_Frame::FPCSVNoteMap)
	EVT_FILEPICKER_CHANGED(ID_FPCSVOutput, MFPG_Frame::FPCSVOutput)

	EVT_BUTTON(ID_BTGenerate, MFPG_Frame::BTGenerate)
	EVT_BUTTON(ID_BTSavetext, MFPG_Frame::BTSavetext)
	EVT_BUTTON(ID_BTSaveastext, MFPG_Frame::BTSaveastext)
	EVT_BUTTON(ID_BTClearInfo, MFPG_Frame::BTClearInfo)
wxEND_EVENT_TABLE()

void MFPG_Frame::MenuExit(wxCommandEvent& event) {
	Close(true);
}

void MFPG_Frame::MenuGuide(wxCommandEvent& event) {
	wxMessageBox("NOT IMPLEMENTED");
}
void MFPG_Frame::MenuAbout(wxCommandEvent& event) {
	wxMessageBox("A tool for generating fingering position for scores played on bowed string instruments  by using customizable configurations which allow users to generate their preferred fingerings.", 
			"About MFPG", wxOK|wxICON_INFORMATION);
}
void MFPG_Frame::MenuNewScore(wxCommandEvent& event) {
	wxFileDialog *file_dialog = new wxFileDialog(this, _("Choose a musicXML file to open"), 
		wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), 
		wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFLP_CHANGE_DIR, wxDefaultPosition);
	if (file_dialog->ShowModal() == wxID_OK) {
		score_path = file_dialog->GetPath();
		for (auto s : config_book->getPanels()) {
			s->score_selected_text->SetLabel(score_path);
			s->score_selected_text->Refresh();
		}
	}
}
void MFPG_Frame::MenuNewConfig(wxCommandEvent& event) {
	wxString new_conf;
	wxTextEntryDialog *input_dialog = new wxTextEntryDialog(this, _("Config Name"), _("New Config"), 
		wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
	input_dialog->SetMaxLength(16);
	wxTextValidator config_names(wxFILTER_INCLUDE_CHAR_LIST);
	config_names.SetCharIncludes(config_chars);
	input_dialog->SetTextValidator(config_names);

	if (input_dialog->ShowModal() == wxID_OK) {
		new_conf = input_dialog->GetValue();
		MFPG_Panel *config_panel = new MFPG_Panel(config_book);
		config_panel->score_selected_text->SetLabel(score_path);
		config_panel->score_selected_text->Refresh();
		config_book->AddPage(config_panel, new_conf, true, 0);
		current_panel = config_panel;
	}
}
void MFPG_Frame::MenuLoadConfig(wxCommandEvent& event) {
	wxXmlDocument conf;
	conf.Load(configs_path);
	std::vector<wxString> config_names;
	wxXmlNode *config = conf.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		config_names.push_back(config->GetAttribute("name", wxEmptyString));
		config = config->GetNext();
	}
	wxSingleChoiceDialog dialog(NULL, "Select Config to load.", "Load Config", config_names.size(),
		&config_names[0], NULL, wxCHOICEDLG_STYLE, wxDefaultPosition);
	wxXmlNode *loaded_config = conf.GetRoot()->GetChildren()->GetChildren();
	if (dialog.ShowModal() == wxID_OK) {
		while (loaded_config) {
			if (loaded_config->GetAttribute("name", wxEmptyString) == 
									dialog.GetStringSelection()) {
				LoadConfig(dialog.GetStringSelection());
				return;
			} else {
				loaded_config = loaded_config->GetNext();
			}
		}
		wxMessageBox("Selected config was not present in the config file.");
	} else {
		return;
	}
}
void MFPG_Frame::LoadConfig(wxString name) {
	wxXmlDocument configs_file;
	configs_file.Load(configs_path);
	wxXmlNode *node = configs_file.GetRoot()->GetChildren()->GetChildren();
	MFPG_Panel *config_panel = new MFPG_Panel(config_book);	
	current_panel = config_panel;
	config_book->AddPage(config_panel, name, true, 0);
	while (node) {
		if (name == node->GetAttribute("name", wxEmptyString)) {
			break;
		} else {
			node = node->GetNext();
		}
	}
	if (!node) {
		wxMessageBox("Could not find a Config by that name");
		return;
	}
	node = node->GetChildren();
	SetInstSettings(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	if (!(node->GetNodeContent() == "NONE")) {
		SelectDSLFile(std::string(node->GetNodeContent()));
	}
	node = node->GetNext();
	SetInstrument(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	SetActionSet(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	SetNoteMapper(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	if (!(node->GetNodeContent() == "NONE")) {
		SelectNoteMapFile(std::string(node->GetNodeContent()));
	}
	node = node->GetNext();
	SetSolver(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	SetOpt(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	SetOutput(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	SetOutputToFile(S_(std::string(node->GetNodeContent())));
	node = node->GetNext();
	if (!(node->GetNodeContent() == "NONE")) {
		SelectOutputFile(std::string(node->GetNodeContent()));
	}
}
void MFPG_Frame::MenuSaveConfig(wxCommandEvent& event) {
	wxString conf_name = config_book->GetPageText(config_book->GetSelection());
	wxXmlDocument config_file;
	config_file.Load(configs_path);
	wxXmlNode *config = config_file.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		wxString c = config->GetAttribute("name", wxEmptyString);
		if (c == conf_name) {	
			break;	
		} else {
			config = config->GetNext();
		}
	}
	if (!config) {
		config = NewConfig(conf_name);
	}
	wxXmlNode *option = config->GetChildren();
	option->GetChildren()->SetContent(_S(current_panel->ST_INSTRUMENT_SETTING));
	option = option->GetNext();
	if (!current_panel->FilePath_DSL) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_DSL);
	}
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_INSTRUMENT));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_ACTIONSET));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_NOTEMAPPER));
	option = option->GetNext();
	if (!current_panel->FilePath_Notemap) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_Notemap);
	}
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_SOLVER));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OPT));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OUTPUTTYPE));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OUTPUTTOFILE));
	option = option->GetNext();
	if (!current_panel->FilePath_Output) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_Output);
	}
	config_file.GetRoot()->GetChildren()->AddChild(config);
	config_file.Save(configs_path);
	delete(config);
}
void MFPG_Frame::MenuSaveAsConfig(wxCommandEvent& event) {
	wxString conf_name = config_book->GetPageText(config_book->GetSelection());
	wxXmlDocument config_file;
	config_file.Load(configs_path);
	wxXmlNode *config = config_file.GetRoot()->GetChildren()->GetChildren();
	wxTextEntryDialog select_name(NULL, "Input Config name to save as", "Save Config as", conf_name, 
		wxTextEntryDialogStyle, wxDefaultPosition);
	if (select_name.ShowModal() == wxID_OK) {
		conf_name = select_name.GetValue();
	} else {
		return;
	}
	while (config) {
		wxString c = config->GetAttribute("name", wxEmptyString);
		if (c == conf_name) {	
			break;	
		} else {
			config = config->GetNext();
		}
	}
	wxMessageDialog save_as_dialog(NULL, "Config already exists, overwrite existing config?",
		"Overwrite Config?", wxSTAY_ON_TOP|wxYES_NO|wxICON_QUESTION, wxDefaultPosition);
	if (config) {
		if (save_as_dialog.ShowModal() == wxID_YES) {	

		} else {
			return;
		}
	} else {
		config = NewConfig(conf_name);
		config_file.GetRoot()->GetChildren()->AddChild(config);
		config_file.Save(configs_path);
	}
	wxXmlNode *option = config->GetChildren();
	option->GetChildren()->SetContent(_S(current_panel->ST_INSTRUMENT_SETTING));
	option = option->GetNext();
	if (!current_panel->FilePath_DSL) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_DSL);
	}
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_INSTRUMENT));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_ACTIONSET));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_NOTEMAPPER));
	option = option->GetNext();
	if (!current_panel->FilePath_Notemap) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_Notemap);
	}
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_SOLVER));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OPT));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OUTPUTTYPE));
	option = option->GetNext();
	option->GetChildren()->SetContent(_S(current_panel->ST_OUTPUTTOFILE));
	option = option->GetNext();
	if (!current_panel->FilePath_Output) {
		option->GetChildren()->SetContent("NONE");
	} else {
		option->GetChildren()->SetContent(current_panel->FilePath_Output);
	}
	config_file.Save(configs_path);
	delete(config);
}
wxXmlNode *MFPG_Frame::NewConfig(wxString conf_name) {
	wxXmlAttribute *c = new wxXmlAttribute("name", conf_name);
	wxXmlNode *config = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "config", wxEmptyString,
		c, NULL, -1);
	
	wxXmlNode *i_s = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "instrument_settings", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *i_s_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"USE_PRESETS", NULL, NULL, -1);
	i_s->AddChild(i_s_c);
	config->AddChild(i_s);
	
	wxXmlNode *d_f = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "dsl_file", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *d_f_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"NONE", NULL, NULL, -1);
	d_f->AddChild(d_f_c);
	config->AddChild(d_f);

	wxXmlNode *i = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "instrument", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *i_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"INSTRUMENT_VIOLIN", NULL, NULL, -1);
	i->AddChild(i_c);
	config->AddChild(i);
	
	wxXmlNode *a_s = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "actionset", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *a_s_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"ACTIONSET_T1", NULL, NULL, -1);
	a_s->AddChild(a_s_c);
	config->AddChild(a_s);
	
	wxXmlNode *n_s = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "notemapper_settings", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *n_s_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"NOTEMAPPER_BASIC", NULL, NULL, -1);
	n_s->AddChild(n_s_c);
	config->AddChild(n_s);
	
	wxXmlNode *n_f = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "notemapper_file", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *n_f_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"NONE", NULL, NULL, -1);
	n_f->AddChild(n_f_c);
	config->AddChild(n_f);
	
	wxXmlNode *s_s = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "solver_settings", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *s_s_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"SOLVER_SPS", NULL, NULL, -1);
	s_s->AddChild(s_s_c);
	config->AddChild(s_s);
	
	wxXmlNode *s_o = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "solver_opt", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *s_o_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"OPT_3", NULL, NULL, -1);
	s_o->AddChild(s_o_c);
	config->AddChild(s_o);
	
	wxXmlNode *o_s = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "output_settings", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *o_s_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"CSV_OUTPUT", NULL, NULL, -1);
	o_s->AddChild(o_s_c);
	config->AddChild(o_s);

	wxXmlNode *o_t = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "output_to_file", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *o_t_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"OUTPUT_TO_FILE", NULL, NULL, -1);
	o_t->AddChild(o_t_c);
	config->AddChild(o_t);

	wxXmlNode *o_f = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "output_file", 
		wxEmptyString, NULL, NULL, -1);
	wxXmlNode *o_f_c = new wxXmlNode(NULL, wxXML_TEXT_NODE, wxEmptyString, 
		"NONE", NULL, NULL, -1);
	o_f->AddChild(o_f_c);
	config->AddChild(o_f);

	return config;
}
void MFPG_Frame::MenuDeleteConfig(wxCommandEvent& event) {
	wxXmlDocument conf;
	conf.Load(configs_path);
	std::vector<wxString> config_names;
	wxXmlNode *config = conf.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		config_names.push_back(config->GetAttribute("name", wxEmptyString));
		config = config->GetNext();
	}
	wxSingleChoiceDialog dialog(NULL, "Select saved Config to delete.", "Delete Saved Config", config_names.size(),
		&config_names[0], NULL, wxCHOICEDLG_STYLE, wxDefaultPosition);
	if (dialog.ShowModal() == wxID_OK) {
		wxXmlNode *removed_node = conf.GetRoot()->GetChildren()->GetChildren();
		while (removed_node) {
			if (removed_node->GetAttribute("name", wxEmptyString) == 
									dialog.GetStringSelection()) {
				conf.GetRoot()->GetChildren()->RemoveChild(removed_node);
				conf.Save(configs_path);
				return;
			} else {
				removed_node = removed_node->GetNext();
			}
		}
		wxMessageBox("Selected config was not present in the config file.");
	} else {
		return;
	}
}
void MFPG_Frame::CBOOKChange(wxBookCtrlEvent& event) {
	current_panel = config_book->getCurrentPanel();
}
void MFPG_Frame::NBOOKChange(wxBookCtrlEvent& event) {
	if (current_panel->files_book->GetCurrentPage()->GetName() == "OUTPUT_TEXT") {
		current_panel->save_file_button->Enable();
	} else if (current_panel->files_book->GetCurrentPage()->GetName() == "NOTEMAPPER_TEXT") {
		current_panel->save_file_button->Enable();
	} else if (current_panel->files_book->GetCurrentPage()->GetName() == "DSL_TEXT") {
		current_panel->save_file_button->Enable();
	} 
}	
void MFPG_Frame::CBNoteMapper(wxCommandEvent& event) {
	switch (current_panel->notemap_box->GetCurrentSelection()) {
		case 0:
			SetNoteMapper(NOTEMAPPER_BASIC);
			break;
		case 1:
			SetNoteMapper(NOTEMAPPER_CSV);
			break;
		default:
			SetNoteMapper(UNDEFINED);
			wxMessageBox("UNDEFINED NOTEMAPPER");
			break;
	}
}
void MFPG_Frame::SetNoteMapper(Settings s) {
	switch (s) {
		case NOTEMAPPER_BASIC:
			current_panel->notemap_filepicker->Disable();
			current_panel->notemapper_text->Disable();
			current_panel->ST_NOTEMAPPER = NOTEMAPPER_BASIC;
			current_panel->notemap_box->SetSelection(0);
			break;
		case NOTEMAPPER_CSV:
			current_panel->notemap_filepicker->Enable();
			current_panel->notemapper_text->Enable();
			current_panel->ST_NOTEMAPPER = NOTEMAPPER_CSV;
			current_panel->notemap_box->SetSelection(1);
			break;
		default:
			current_panel->ST_NOTEMAPPER = UNDEFINED;
			current_panel->notemap_box->SetSelection(-1);
			break;
	}
}

void MFPG_Frame::CBInstSettings(wxCommandEvent& event) {
	switch (current_panel->instrument_settings_box->GetCurrentSelection()) {
		case 0:
			SetInstSettings(USE_PRESETS);
			break;
		case 1:
			SetInstSettings(USE_DSL);
			break;
		default:
			SetInstSettings(UNDEFINED);
			wxMessageBox("UNDEFINED INSTRUMENT SETTING");
			break;
	}
}
void MFPG_Frame::SetInstSettings(Settings s) {
	switch (s) {
		case USE_PRESETS:
			current_panel->ST_INSTRUMENT_SETTING = USE_PRESETS;
			current_panel->instrument_settings_box->SetSelection(0);
			current_panel->instrument_box->Enable();
			current_panel->actionset_box->Enable();
			current_panel->dsl_filepicker->Disable();
			break;
		case USE_DSL:
			current_panel->instrument_settings_box->SetSelection(1);
			current_panel->ST_INSTRUMENT_SETTING = USE_DSL;
			current_panel->instrument_box->Disable();
			current_panel->actionset_box->Disable();
			current_panel->dsl_filepicker->Enable();
			break;
		default:
			current_panel->instrument_settings_box->SetSelection(-1);
			current_panel->ST_INSTRUMENT_SETTING = UNDEFINED;
			break;
	}
} 
void MFPG_Frame::CBInstrument(wxCommandEvent& event) {
	switch (current_panel->instrument_box->GetCurrentSelection()) {
		case 0:
			SetInstrument(INSTRUMENT_VIOLIN);
		default:
			SetInstrument(UNDEFINED);
			wxMessageBox("UNDEFINED INSTRUMENT");
	}
}
void MFPG_Frame::SetInstrument(Settings s) {
	switch (s) {
		case INSTRUMENT_VIOLIN:
			current_panel->instrument_box->SetSelection(0);
			current_panel->ST_INSTRUMENT = INSTRUMENT_VIOLIN;
			break;
		default:
			current_panel->instrument_box->SetSelection(-1);
			current_panel->ST_INSTRUMENT = UNDEFINED;
			break;
	}
}
void MFPG_Frame::CBActionSet(wxCommandEvent& event) {
	switch (current_panel->actionset_box->GetCurrentSelection()) {
		case 0:
			SetActionSet(ACTIONSET_T1);
			break;
		case 1:
			SetActionSet(ACTIONSET_T2);
			break;
		default:
			SetActionSet(UNDEFINED);
			wxMessageBox("UNDEFINED NOTEMAPPER");
			break;
	}
}
void MFPG_Frame::SetActionSet(Settings s) {
	switch (s) {
		case ACTIONSET_T1:	
			current_panel->actionset_box->SetSelection(0);
			current_panel->ST_ACTIONSET = ACTIONSET_T1;
			break;
		case ACTIONSET_T2:	
			current_panel->actionset_box->SetSelection(1);
			current_panel->ST_ACTIONSET = ACTIONSET_T2;
			break;
		case UNDEFINED:	
			current_panel->actionset_box->SetSelection(-1);
			current_panel->ST_ACTIONSET = UNDEFINED;
			break;
	}
}
void MFPG_Frame::CBSolver(wxCommandEvent& event) {
	switch (current_panel->solver_box->GetCurrentSelection()) {
		case 0:
			SetSolver(SOLVER_SPS);
			break;
		case 1:
			SetSolver(SOLVER_GREEDY);
			break;
		default:
			SetSolver(UNDEFINED);
			wxMessageBox("UNDEFINED NOTEMAPPER");
			break;
	}
}
void MFPG_Frame::SetSolver(Settings s) {
	switch (s) {
		case SOLVER_SPS:
			for (auto c : current_panel->solver_area->GetChildren()) {
				if ((c->GetName() == "OPT1_TEXT" && 
						current_panel->sps_opt_1->IsChecked()) || 
				   (c->GetName() == "OPT2_TEXT" && 
				    		current_panel->sps_opt_2->IsChecked())) {
					c->Enable();
				}
			}
			current_panel->sps_opt_1->Enable();
			current_panel->sps_opt_2->Enable();
			current_panel->solver_box->SetSelection(0);
			current_panel->ST_SOLVER = SOLVER_SPS;
			break;
		case SOLVER_GREEDY:
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT1_TEXT" || c->GetName() == "OPT2_TEXT") {
					c->Disable();
				}
			}
			current_panel->sps_opt_1->Disable();
			current_panel->sps_opt_2->Disable();
			current_panel->solver_box->SetSelection(1);
			current_panel->ST_SOLVER = SOLVER_GREEDY;
			break;
		default:
			current_panel->solver_box->SetSelection(-1);
			current_panel->ST_SOLVER = UNDEFINED;
			break;
	}
}
void MFPG_Frame::CHBSPSOpt1(wxCommandEvent& event) {
	if (current_panel->sps_opt_1->IsChecked()) {
		if (current_panel->sps_opt_2->IsChecked()) {
			SetOpt(OPT_3);
		} else {
			SetOpt(OPT_1);
		}
	} else {
		if (current_panel->sps_opt_2->IsChecked()) {
			SetOpt(OPT_2);
		} else {
			SetOpt(OPT_0);
		}
	}
}
void MFPG_Frame::CHBSPSOpt2(wxCommandEvent& event) {
	if (current_panel->sps_opt_2->IsChecked()) {
		if (current_panel->sps_opt_1->IsChecked()) {
			SetOpt(OPT_3);
		} else {
			SetOpt(OPT_2);
		}
	} else {
		if (current_panel->sps_opt_1->IsChecked()) {
			SetOpt(OPT_1);
		} else {
			SetOpt(OPT_0);
		}
	}
}
void MFPG_Frame::SetOpt(Settings s) {
	switch (s) {
		case OPT_0:
			current_panel->sps_opt_1->SetValue(false);
			current_panel->sps_opt_2->SetValue(false);
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT1_TEXT") {
					c->Disable();
				}
			}
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT2_TEXT") {
					c->Disable();
				}
			}
			current_panel->ST_OPT = OPT_0;
			break;
		case OPT_1:
			current_panel->sps_opt_1->SetValue(true);
			current_panel->sps_opt_2->SetValue(false);
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT1_TEXT") {
					c->Enable();
				}
			}
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT2_TEXT") {
					c->Disable();
				}
			}
			current_panel->ST_OPT = OPT_1;
			break;
		case OPT_2:
			current_panel->sps_opt_1->SetValue(false);
			current_panel->sps_opt_2->SetValue(true);
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT1_TEXT") {
					c->Disable();
				}
			}
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT2_TEXT") {
					c->Enable();
				}
			}
			current_panel->ST_OPT = OPT_2;
			break;
		case OPT_3:
			current_panel->sps_opt_1->SetValue(true);
			current_panel->sps_opt_2->SetValue(true);
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT1_TEXT") {
					c->Enable();
				}
			}
			for (auto c : current_panel->solver_area->GetChildren()) {
				if (c->GetName() == "OPT2_TEXT") {
					c->Enable();
				}
			}
			current_panel->ST_OPT = OPT_3;
			break;
		default:
			current_panel->sps_opt_1->SetValue(false);
			current_panel->sps_opt_2->SetValue(false);
			current_panel->ST_OPT = UNDEFINED;
			break;
	}
}
void MFPG_Frame::CHBOutputToFile(wxCommandEvent& event) {
	if (current_panel->output_to_file->IsChecked()) {
		SetOutputToFile(OUTPUT_TO_FILE);
	} else {
		SetOutputToFile(UNDEFINED);
	}
}
void MFPG_Frame::SetOutputToFile(Settings s) {
	switch (s) {
		case OUTPUT_TO_FILE:
			current_panel->output_file->Enable();
			current_panel->output_text->Enable();
			current_panel->output_to_file->SetValue(true);
			current_panel->ST_OUTPUTTOFILE = OUTPUT_TO_FILE;
			break;
		default:
			current_panel->output_file->Disable();
			current_panel->output_text->Disable();
			current_panel->output_to_file->SetValue(false);
			current_panel->ST_OUTPUTTOFILE = UNDEFINED;
			break;
	}
}
void MFPG_Frame::CBOutput(wxCommandEvent& event) {
	switch (current_panel->output_selection_box->GetCurrentSelection()) {
		case 0:
			SetOutput(CSV_OUTPUT);
			break;
		case 1:
			SetOutput(DIRECT_OUTPUT);
			break;
		default:
			SetOutput(UNDEFINED);
			wxMessageBox("OUTPUT TYPE UNDEFINED");
			break;
	}
}
void MFPG_Frame::SetOutput(Settings s) {
	switch (s) {
		case CSV_OUTPUT:
			current_panel->output_selection_box->SetSelection(0);
			current_panel->ST_OUTPUTTYPE = CSV_OUTPUT;	
			break;
		case DIRECT_OUTPUT:
			current_panel->output_selection_box->SetSelection(1);
			current_panel->ST_OUTPUTTYPE = DIRECT_OUTPUT;	
			break;
		default:
			current_panel->output_selection_box->SetSelection(-1);
			current_panel->ST_OUTPUTTYPE = UNDEFINED;	
			break;
	}
}
void MFPG_Frame::FPDSL(wxFileDirPickerEvent& event) {
	SelectDSLFile(current_panel->dsl_filepicker->GetPath());
}
void MFPG_Frame::SelectDSLFile(wxString path) {
	current_panel->FilePath_DSL = path;
	current_panel->dsl_filepicker->SetPath(current_panel->FilePath_DSL);
	current_panel->dsl_text->Enable();
	current_panel->dsl_text->LoadFile(current_panel->FilePath_DSL);
}
void MFPG_Frame::FPCSVNoteMap(wxFileDirPickerEvent& event) {
	SelectNoteMapFile(current_panel->notemap_filepicker->GetPath());
}
void MFPG_Frame::SelectNoteMapFile(wxString path) {
	current_panel->FilePath_Notemap = path;
	current_panel->notemap_filepicker->SetPath(current_panel->FilePath_Notemap);
	current_panel->notemapper_text->Enable();
	current_panel->notemapper_text->LoadFile(current_panel->FilePath_Notemap);
}
void MFPG_Frame::FPCSVOutput(wxFileDirPickerEvent& event) {
	SelectOutputFile(current_panel->output_file->GetPath());
}
void MFPG_Frame::SelectOutputFile(wxString path) {
	current_panel->FilePath_Output = path;
	current_panel->output_file->SetPath(current_panel->FilePath_Output);
	current_panel->output_text->Enable();
	current_panel->output_text->LoadFile(current_panel->FilePath_Output);
}
void MFPG_Frame::BTSaveastext(wxCommandEvent& event) {
	wxFileDialog save_as_dialog(NULL, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, 
			wxFileSelectorDefaultWildcardStr, wxFD_SAVE|wxFD_OVERWRITE_PROMPT, 
			wxDefaultPosition, wxDefaultSize, wxFileDialogNameStr);
	switch (current_panel->files_book->GetSelection()) {
		case 0:
			if (!current_panel->output_text->IsEnabled()) {
				wxMessageBox("Nothing to save in output");
				return;
			}
			break;
		case 1:
			if (!current_panel->notemapper_text->IsEnabled()) {
				wxMessageBox("Nothing to save in notemapper CSV File");
				return;
			}
			break;
		case 2:
			if (!current_panel->dsl_text->IsEnabled()) {
				wxMessageBox("Nothing to save in DSL File");
				return;
			}
			break;
		default:
			break;
	}
	if (save_as_dialog.ShowModal() == wxID_OK) {
		current_panel->output_text->SaveFile(save_as_dialog.GetPath());
	}
}

void MFPG_Frame::BTSavetext(wxCommandEvent& event) {
	wxMessageDialog save_file_dialog(NULL, "Save File?", "Save Confirmation", 
			wxYES_NO|wxCENTRE|wxICON_QUESTION|wxSTAY_ON_TOP, wxPoint(150, 150));
	switch (current_panel->files_book->GetSelection()) {
		case 0:
			if (!current_panel->FilePath_Output) {
				wxMessageBox("No Output file selected.");
			} else {
				if (current_panel->output_text->IsModified()) {
					if (save_file_dialog.ShowModal() == wxID_YES) {
						current_panel->output_text->SaveFile(current_panel->FilePath_Output);
					}
				}
			}
			break;
		case 1:
			if (!current_panel->FilePath_Notemap) {
				wxMessageBox("No Notemap CSV file selected.");
			} else {
				if (current_panel->notemapper_text->IsModified()) {
					if (save_file_dialog.ShowModal() == wxID_YES) {
						current_panel->notemapper_text->SaveFile(current_panel->notemap_filepicker->GetPath());
					}
				}
			}
			break;
		case 2:
			if (!current_panel->FilePath_DSL) {
				wxMessageBox("No DSL file selected.");
			} else {
				if (current_panel->dsl_text->IsModified()) {
					if (save_file_dialog.ShowModal() == wxID_YES) {
						current_panel->dsl_text->SaveFile(current_panel->dsl_filepicker->GetPath());
					}
				}
			}
			break;
		default:
			break;
	}
}
void MFPG_Frame::BTClearInfo(wxCommandEvent& event) {
	current_panel->information_text->Clear();
}
void MFPG_Frame::BTGenerate(wxCommandEvent& event) {
	Generate();
}

void MFPG_Frame::Generate() {
	wxStreamToTextRedirector redirect(current_panel->information_text);
	std::string score_path_;
	score_path_ = score_path;
	if (!score_path) {
		wxMessageBox("No Score file selected");
		return;
	}
	
	using namespace mx::api;
	auto& mgr = DocumentManager::getInstance();	
	const auto documentID = mgr.createFromFile(score_path_);

	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	const NoteList note_list(score);
	
	InstrumentBuilder instrument_builder;

	std::shared_ptr<Instrument<int>> violin_i;
	std::shared_ptr<Instrument<double>> violin_d;

	char output_type = 'i';
	
	if (current_panel->ST_INSTRUMENT_SETTING == Settings::USE_DSL) {
		FILE *dsl_filepicker;	
		dsl_filepicker = fopen((current_panel->FilePath_DSL).c_str(), "r");
		Input *parse_tree = NULL;
		try {
			parse_tree = pInput(dsl_filepicker);
		} catch (parse_error &e) {
			std::string e_msg = "DSL Parse error on line: ";
			e_msg += std::to_string(e.getLine());
			std::cout << e_msg << "\n";
			wxMessageBox(e_msg);
			return;
		}
		fclose(dsl_filepicker);

		instrument_builder.visitInput(parse_tree);
		
		output_type = instrument_builder.output;

		TUPLESIZE = instrument_builder.attrs.size();
		ATTRIBUTES = instrument_builder.attrs;
		ATTRIBUTE_TYPES = instrument_builder.attrtypes;

		if (output_type == 'i') {
			violin_i = instrument_builder.i_inst;
		} else if (output_type == 'd') {
			violin_d = instrument_builder.d_inst;
		}
	} else {
		TUPLESIZE = 3;
		ATTRIBUTES = {"STRING", "FINGER", "HAND_POS"};
		ATTRIBUTE_TYPES = "iii";

		std::shared_ptr<ActionSet<int>> as_i;

		switch (current_panel->ST_ACTIONSET) {
			case Settings::ACTIONSET_T1:
				as_i = configs::test_configuration_1();
				break;
			case Settings::ACTIONSET_T2:
				as_i = configs::test_configuration_2();
				break;
			case Settings::UNDEFINED:
				wxMessageBox("Could not find ActionSet, Aborting...");
				return;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
		switch (current_panel->ST_INSTRUMENT) {
			case Settings::INSTRUMENT_VIOLIN:
				violin_i = std::shared_ptr<Instrument<int>>(new Instrument<int>(as_i));
				violin_i->makeIString(1, Note::G_3, Note::Gs_5);
				violin_i->makeIString(2, Note::D_4, Note::Ds_6);
				violin_i->makeIString(3, Note::A_4, Note::As_6);
				violin_i->makeIString(4, Note::E_5, Note::F_7);
				break;
			case Settings::UNDEFINED:
				wxMessageBox("Could not find Instrument, Aborting...");
				return;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
	}
	std::shared_ptr<NoteMapper> note_mapper;
	try {
		std::string map_csv_path;
		switch (current_panel->ST_NOTEMAPPER) {
			case Settings::NOTEMAPPER_BASIC:
				if (output_type == 'i') {
					note_mapper = std::shared_ptr<NoteMapper>(new BasicNoteMapper(violin_i->getIStrings()));
				} else if (output_type == 'd') {
					note_mapper = std::shared_ptr<NoteMapper>(new BasicNoteMapper(violin_d->getIStrings()));
				}
				break;
			case Settings::NOTEMAPPER_CSV:
				map_csv_path = current_panel->FilePath_Notemap;
				if (output_type == 'i') {
					note_mapper = std::shared_ptr<NoteMapper>(new CSVNoteMapper(map_csv_path, violin_i->getIStrings()));
				} else if (output_type == 'd') {
					note_mapper = std::shared_ptr<NoteMapper>(new CSVNoteMapper(map_csv_path, violin_d->getIStrings()));
				}
				break;
			case Settings::UNDEFINED:
				wxMessageBox("No Notemapper was defined, Aborting...");
				return;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
	} catch (NoteMapperException &e) {
		std::cout << e.what() << "\n";
		wxMessageBox(e.what());
		return;
	}
	std::shared_ptr<LayerList<int>> list_i;
	std::shared_ptr<LayerList<double>> list_d;
	try {
		if (output_type == 'i') {
			list_i = std::shared_ptr<LayerList<int>>(new LayerList<int>(note_list, note_mapper));
			list_i->buildTransitions(violin_i->getActionSet());
		} else if (output_type == 'd') {
			list_d = std::shared_ptr<LayerList<double>>(new LayerList<double>(note_list, note_mapper));
			list_d->buildTransitions(violin_d->getActionSet());
		}
	} catch (NodeException &e) {
		std::string e_msg = e.what() + "Failed note: " + e.failedNote().to_string() + 
			" Failed node: " + e.failedNode().to_string();
		std::cout << e_msg << "\n";
		wxMessageBox(e_msg);
		return;
	} catch (LinkException<int> &e) {
		std::cout << e.what() << "\n";
		wxMessageBox(e.what());
		return;
	} catch (LinkException<double> &e) {
		std::cout << e.what() << "\n";
		wxMessageBox(e.what());
		return;
	} catch (ExValException &e) {
		std::string affected_tuples = "[";
		int count = 1;
		for (auto t : e.getExVal()) {
			affected_tuples += "Tuple " + std::to_string(count) + ": " + t.to_string();
			if (count < e.getExVal().size()) {
				affected_tuples += ", ";
			} else {
				affected_tuples += "]";
			}
			count++;
		}
		std::string e_msg = e.what() + "\nAffected Tuples: " + affected_tuples;
		std::cout << e_msg << "\n";
		wxMessageBox(e_msg);
		return;
	}

	std::shared_ptr<GraphSolver<int>> solver_i;
	std::shared_ptr<GraphSolver<double>> solver_d;
	switch (current_panel->ST_SOLVER) {
		case Settings::SOLVER_GREEDY:
			solver_i = std::shared_ptr<GraphSolver<int>>(new GreedySolver());
			if (output_type == 'd') {
				wxMessageBox("Greedy Solver is not implemented for double outputs.");
				return;
			}
			break;
		case Settings::SOLVER_SPS:
			switch (current_panel->ST_OPT) {
				case Settings::OPT_0:
					solver_i = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(0));
					solver_d = std::shared_ptr<GraphSolver<double>>(new SPSolver<double>(0));
					break;
				case Settings::OPT_1:
					solver_i = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(1));
					solver_d = std::shared_ptr<GraphSolver<double>>(new SPSolver<double>(1));
					break;
				case Settings::OPT_2:
					solver_i = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(2));
					solver_d = std::shared_ptr<GraphSolver<double>>(new SPSolver<double>(2));
					break;
				case Settings::OPT_3:
					solver_i = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(3));
					solver_d = std::shared_ptr<GraphSolver<double>>(new SPSolver<double>(3));
					break;
				case Settings::UNDEFINED:
					solver_i = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(0));
					solver_d = std::shared_ptr<GraphSolver<double>>(new SPSolver<double>(0));
					break;
				default:
					wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
					return;
			}
			break;
		case Settings::UNDEFINED:
			wxMessageBox("Could not find solver, Aborting...");
			return;
		default:
			wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
			return;
	}

	try {
		if (output_type == 'i') {
			solver_i->solve(*list_i);
		} else if (output_type == 'd') {
			solver_d->solve(*list_d);
		}
	} catch (SolverException &e) {
		std::string e_msg = e.what() + "\nFailed to find layer path: " + 
			configs::to_string(e.getLayer()) + " -> " + configs::to_string(e.getLayer() + 1);
		std::cout << e_msg << "\n";
		wxMessageBox(e_msg);
		return;
	} catch (std::out_of_range &e) {
		std::string e_msg = std::string(e.what());
		std::cout << e_msg << "\n";
		wxMessageBox(e_msg);
		return;
	}
	if (current_panel->ST_OUTPUTTOFILE) {
		std::string csv_out_path;
		std::ofstream out; 
		if (!current_panel->FilePath_Output) {
			wxMessageBox("No Output file selected");
			return;
		}
		csv_out_path = current_panel->FilePath_Output;
		out.open(csv_out_path, std::ofstream::binary);
		bool use_csv = false;
		switch (current_panel->ST_OUTPUTTYPE) {
			case Settings::CSV_OUTPUT:
				use_csv = true;
				break;
			case Settings::DIRECT_OUTPUT:
				use_csv = false;
				break;
			case Settings::UNDEFINED:
				use_csv = false;
				break;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
		if (output_type == 'i') {
			configs::writeOutput(out, solver_i, use_csv);
		} else if (output_type == 'd') {
			configs::writeOutput(out, solver_d, use_csv);
			return;
		}
		out.close();
	} else {
		wxMessageBox("Currently output must be written to a file.");
		return;
	}
	current_panel->output_text->LoadFile(current_panel->FilePath_Output);
}
