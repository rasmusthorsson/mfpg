#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"

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
#include "wx/xrc/xmlres.h"
#include <wx/stdpaths.h>

#include "conf_cmake.h"
#include "configs.h"

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

#include "Parser.H"
#include "ParserError.H"

#include <vector>
#include <fstream>

extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

//Seperator depending on OS, might not be needed.
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

MFPG_Frame::MFPG_Frame(bool _use_xrc) : use_xrc(_use_xrc), wxFrame(nullptr, wxID_ANY, "MFPG", 
		wxDefaultPosition, wxSize(WIDTH, HEIGHT), wxDEFAULT_FRAME_STYLE, wxFrameNameStr) {
	//Menus
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

	//Status bar
	CreateStatusBar();
	std::string status("MFPG -- Version: ");
	status += VERSION_MFPG;
	SetStatusText(status);

	//Path to config file
	//wxString configs_dir(wxStandardPaths::Get().GetConfigDir());
	configs_path = wxGetCwd();
	//configs_path.append(sep());
	//configs_path.append("MFPG_Configs");
	configs_path.append(sep());
	configs_path.append(".mfpg_configs.xml");
	
	//Build book and first panel
	config_book = new MFPG_Choicebook(this, ID_CBOOKChange);
	MFPG_Panel *config_panel;
	if (use_xrc) {
		config_panel = new MFPG_Panel();	
		wxXmlResource::Get()->LoadPanel(config_panel, config_book, "MFPG_Panel_XRC");
	} else {
		config_panel = new MFPG_Panel(config_book);	
	}
	config_panel->InitPanel(use_xrc);
	current_panel = config_panel;
	config_book->AddPage(config_panel, "UnnamedConfig", true, -1);
	
	//Build other configs based on configs file
	wxXmlDocument configs_file;
	if (!configs_file.Load(configs_path)) {
		//If configs file does not exist, ask whether a new should be constructed
		wxMessageDialog new_conf_file_q(NULL, "Unable to locate a config file (.mfpg_configs.xml) in the current directory. Would you like to create a new MFPG Config file for saving and loading configurations? The file will be created in the current directory under the name \".mfpg_configs.xml\"", 
			"Create a new MFPG Config file?", wxYES_NO|wxCENTRE|wxICON_QUESTION|wxSTAY_ON_TOP,
			wxDefaultPosition);
		if (new_conf_file_q.ShowModal() == wxID_YES) {
			//Create new file and populate it with basic elements
			std::ofstream new_file;
			new_file.open(configs_path.mb_str());
			new_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			new_file << "<root>\n";
			new_file << "  <configs>\n";
			new_file << "  </configs>\n";
			new_file << "</root>\n";
		} else {
			//Otherwise disable config loading and saving
			menuConfig->Enable(ID_MenuLoadConfig, false);
			menuConfig->Enable(ID_MenuSaveConfig, false);
			menuConfig->Enable(ID_MenuSaveAsConfig, false);
			menuConfig->Enable(ID_MenuDeleteConfig, false);
		}
	} else {
		//If config file exists, ask whether to use it.
		wxMessageDialog load_all_confs(NULL, "Load all saved configs?", "Config Load", 
			wxYES_NO|wxCENTRE|wxICON_QUESTION|wxSTAY_ON_TOP, wxDefaultPosition);
		if (load_all_confs.ShowModal() == wxID_YES) {
			wxXmlNode *c = configs_file.GetRoot()->GetChildren()->GetChildren();
			while (c) {
				LoadConfig(c->GetAttribute(CONFIG_NAME_CONF, wxEmptyString));
				c = c->GetNext();
			}
		} 
	}
}

//Construct the event table.
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
	//For the static structures
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
	EVT_BUTTON(ID_BTRemoveConfig, MFPG_Frame::BTRemoveConfig)
	//For XRC file
	EVT_NOTEBOOK_PAGE_CHANGED(XRCID("ID_NBOOKChange"), MFPG_Frame::NBOOKChange)

	EVT_COMBOBOX(XRCID("ID_CBNoteMapper"), MFPG_Frame::CBNoteMapper)
	EVT_COMBOBOX(XRCID("ID_CBInstSettings"), MFPG_Frame::CBInstSettings)
	EVT_COMBOBOX(XRCID("ID_CBInstrument"), MFPG_Frame::CBInstrument)
	EVT_COMBOBOX(XRCID("ID_CBActionSet"), MFPG_Frame::CBActionSet)
	EVT_COMBOBOX(XRCID("ID_CBSolver"), MFPG_Frame::CBSolver)
	EVT_COMBOBOX(XRCID("ID_CBOutput"), MFPG_Frame::CBOutput)

	EVT_CHECKBOX(XRCID("ID_CHBSPSOpt1"), MFPG_Frame::CHBSPSOpt1)
	EVT_CHECKBOX(XRCID("ID_CHBSPSOpt2"), MFPG_Frame::CHBSPSOpt2)
	EVT_CHECKBOX(XRCID("ID_CHBOutputToFile"), MFPG_Frame::CHBOutputToFile)

	EVT_FILEPICKER_CHANGED(XRCID("ID_FPDSL"), MFPG_Frame::FPDSL)
	EVT_FILEPICKER_CHANGED(XRCID("ID_FPCSVNoteMap"), MFPG_Frame::FPCSVNoteMap)
	EVT_FILEPICKER_CHANGED(XRCID("ID_FPCSVOutput"), MFPG_Frame::FPCSVOutput)

	EVT_BUTTON(XRCID("ID_BTGenerate"), MFPG_Frame::BTGenerate)
	EVT_BUTTON(XRCID("ID_BTSavetext"), MFPG_Frame::BTSavetext)
	EVT_BUTTON(XRCID("ID_BTSaveastext"), MFPG_Frame::BTSaveastext)
	EVT_BUTTON(XRCID("ID_BTClearInfo"), MFPG_Frame::BTClearInfo)
	EVT_BUTTON(XRCID("ID_BTRemoveConfig"), MFPG_Frame::BTRemoveConfig)
wxEND_EVENT_TABLE()

void MFPG_Frame::MenuExit(wxCommandEvent& event) {
	Close(true);
}

void MFPG_Frame::MenuGuide(wxCommandEvent& event) {
	//TODO Create a guide on github pages and link to it from here
	wxMessageBox("NOT IMPLEMENTED");
}
void MFPG_Frame::MenuAbout(wxCommandEvent& event) {
	wxMessageBox("A tool for generating fingering position for scores played on bowed string instruments  by using customizable configurations which allow users to generate their preferred fingerings.", 
			"About MFPG", wxOK|wxICON_INFORMATION);
}
void MFPG_Frame::MenuNewScore(wxCommandEvent& event) {
	wxFileDialog *score_select_dialog = new wxFileDialog(this, _("Choose a musicXML file to open"), 
		wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), 
		wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	if (score_select_dialog->ShowModal() == wxID_OK) {
		score_path = score_select_dialog->GetPath();
		for (auto panel : config_book->getPanels()) {
			panel->score_selected_text->SetLabel(score_path);
			panel->score_selected_text->Refresh();
		}
	}
}
void MFPG_Frame::MenuNewConfig(wxCommandEvent& event) {
	wxString new_conf;
	wxTextEntryDialog *conf_name_dialog = new wxTextEntryDialog(this, _("Config Name"),
		_("New Config"), wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
	conf_name_dialog->SetMaxLength(16);
	wxTextValidator config_names(wxFILTER_INCLUDE_CHAR_LIST);
	config_names.SetCharIncludes(config_chars);
	conf_name_dialog->SetTextValidator(config_names);

	if (conf_name_dialog->ShowModal() == wxID_OK) {
		new_conf = conf_name_dialog->GetValue();
		MFPG_Panel *config_panel = new MFPG_Panel(config_book);
		config_panel->score_selected_text->SetLabel(score_path);
		config_panel->score_selected_text->Refresh();
		config_book->AddPage(config_panel, new_conf, true, 0);
		current_panel = config_panel;
	}
}
void MFPG_Frame::MenuLoadConfig(wxCommandEvent& event) {
	wxXmlDocument conf_doc;
	conf_doc.Load(configs_path);
	std::vector<wxString> config_names;
	wxXmlNode *config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		config_names.push_back(config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString));
		config = config->GetNext();
	}
	void** c = NULL; //Avoid constructor ambiguity in lower wx versions
	wxSingleChoiceDialog load_conf_dialog(NULL, "Select Config to load.", "Load Config", 
		config_names.size(), &config_names[0], c, wxCHOICEDLG_STYLE, wxDefaultPosition);
	wxXmlNode *loaded_config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	if (load_conf_dialog.ShowModal() == wxID_OK) {
		while (loaded_config) {
			if (loaded_config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString) == 
								load_conf_dialog.GetStringSelection()) {
				LoadConfig(load_conf_dialog.GetStringSelection());
				return;
			} else {
				loaded_config = loaded_config->GetNext();
			}
		}
		wxMessageBox("Selected config was not present in the config file.");
	}
}
void MFPG_Frame::LoadConfig(wxString name) {
	wxXmlDocument conf_doc;
	conf_doc.Load(configs_path);
	wxXmlNode *config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	MFPG_Panel *new_config_panel;
	if (use_xrc) {
		new_config_panel = new MFPG_Panel();	
		wxXmlResource::Get()->LoadPanel(new_config_panel, config_book, "MFPG_Panel_XRC");
	} else {
		new_config_panel = new MFPG_Panel(config_book);	
	}
	new_config_panel->InitPanel(use_xrc);
	current_panel = new_config_panel;
	config_book->AddPage(new_config_panel, name, true, 0);

	while (config) {
		if (name == config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString)) {
			break;
		} else {
			config = config->GetNext();
		}
	}
	if (!config) {
		wxMessageBox("Could not find a Config by that name");
		return;
	}

	SetInstSettings(S_(std::string(config->GetAttribute(INSTRUMENT_SETTINGS_CONF, wxEmptyString))));
	
	SetInstrument(S_(std::string(config->GetAttribute(INSTRUMENT_CONF, wxEmptyString))));
	
	SetActionSet(S_(std::string(config->GetAttribute(ACTIONSET_CONF, wxEmptyString))));
	
	SetNoteMapper(S_(std::string(config->GetAttribute(NOTEMAPPER_SETTINGS_CONF, wxEmptyString))));
	
	SetSolver(S_(std::string(config->GetAttribute(SOLVER_SETTINGS_CONF, wxEmptyString))));
	
	SetOpt(S_(std::string(config->GetAttribute(SOLVER_OPT_CONF, wxEmptyString))));
	
	SetOutput(S_(std::string(config->GetAttribute(OUTPUT_SETTINGS_CONF, wxEmptyString))));
	
	SetOutputToFile(S_(std::string(config->GetAttribute(OUTPUT_TO_FILE_CONF, wxEmptyString))));

	if (config->GetAttribute(DSL_FILE_CONF, wxEmptyString) == "NONE") {
		SelectDSLFile("");	
	} else {
		SelectDSLFile(std::string(config->GetAttribute(DSL_FILE_CONF, wxEmptyString)));
	}
	if (config->GetAttribute(NOTEMAPPER_FILE_CONF, wxEmptyString) == "NONE") {
		SelectNoteMapFile("");	
	} else {
		SelectNoteMapFile(std::string(config->GetAttribute(NOTEMAPPER_FILE_CONF, wxEmptyString)));
	}
	if (config->GetAttribute(OUTPUT_FILE_CONF, wxEmptyString) == "NONE") {
		SelectOutputFile("");	
	} else {
		SelectOutputFile(std::string(config->GetAttribute(OUTPUT_FILE_CONF, wxEmptyString)));
	}
}
void MFPG_Frame::MenuSaveConfig(wxCommandEvent& event) {
	wxString conf_name = config_book->GetPageText(config_book->GetSelection());
	wxXmlDocument conf_doc;
	conf_doc.Load(configs_path);
	wxXmlNode *config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		wxString c = config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString);
		if (c == conf_name) {	
			break;	
		} else {
			config = config->GetNext();
		}
	}
	if (!config) {
		config = NewConfig(conf_name);
	}
	std::string dsl_file = "NONE";
	if (!current_panel->FilePath_DSL) {
	} else {
		dsl_file = current_panel->FilePath_DSL;
	}
	std::string notemapper_file = "NONE";
	if (!current_panel->FilePath_Notemap) {
	} else {
		notemapper_file = current_panel->FilePath_Notemap;
	}
	std::string output_file = "NONE";
	if (!current_panel->FilePath_Output) {
	} else {
		output_file = current_panel->FilePath_Output;
	}
	std::vector<std::pair<std::string, std::string>> config_attrs({
			{INSTRUMENT_SETTINGS_CONF, _S(current_panel->ST_INSTRUMENT_SETTING)},
			{DSL_FILE_CONF, dsl_file},
			{INSTRUMENT_CONF, _S(current_panel->ST_INSTRUMENT)},
			{ACTIONSET_CONF, _S(current_panel->ST_ACTIONSET)},
			{NOTEMAPPER_SETTINGS_CONF, _S(current_panel->ST_NOTEMAPPER)},
			{NOTEMAPPER_FILE_CONF, notemapper_file},
			{SOLVER_SETTINGS_CONF, _S(current_panel->ST_SOLVER)},
			{SOLVER_OPT_CONF, _S(current_panel->ST_OPT)},
			{OUTPUT_SETTINGS_CONF, _S(current_panel->ST_OUTPUTTYPE)},
			{OUTPUT_TO_FILE_CONF, _S(current_panel->ST_OUTPUTTOFILE)},
			{OUTPUT_FILE_CONF, output_file}
			});
	wxXmlAttribute *attr = config->GetAttributes();
	while (attr) {
		for (int i = 0; i < config_attrs.size(); i++) {
			if (attr->GetName() == config_attrs[i].first) {
				attr->SetValue(config_attrs[i].second);	
				break;
			}
		}
		attr = attr->GetNext();
	}
	conf_doc.Save(configs_path);
}
void MFPG_Frame::MenuSaveAsConfig(wxCommandEvent& event) {
	wxString conf_name;
	wxXmlDocument conf_doc;
	conf_doc.Load(configs_path);
	wxXmlNode *config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	wxTextEntryDialog select_name(NULL, "Input Config name to save as", "Save Config as", 
		wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
	if (select_name.ShowModal() == wxID_OK) {
		conf_name = select_name.GetValue();
	} else {
		return;
	}
	while (config) {
		wxString c = config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString);
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
		conf_doc.GetRoot()->GetChildren()->AddChild(config);
		conf_doc.Save(configs_path);
	}
	std::string dsl_file = "NONE";
	if (!current_panel->FilePath_DSL) {
	} else {
		dsl_file = current_panel->FilePath_DSL;
	}
	std::string notemapper_file = "NONE";
	if (!current_panel->FilePath_Notemap) {
	} else {
		notemapper_file = current_panel->FilePath_Notemap;
	}
	std::string output_file = "NONE";
	if (!current_panel->FilePath_Output) {
	} else {
		output_file = current_panel->FilePath_Output;
	}
	std::vector<std::pair<std::string, std::string>> config_attrs({
			{INSTRUMENT_SETTINGS_CONF, _S(current_panel->ST_INSTRUMENT_SETTING)},
			{DSL_FILE_CONF, dsl_file},
			{INSTRUMENT_CONF, _S(current_panel->ST_INSTRUMENT)},
			{ACTIONSET_CONF, _S(current_panel->ST_ACTIONSET)},
			{NOTEMAPPER_SETTINGS_CONF, _S(current_panel->ST_NOTEMAPPER)},
			{NOTEMAPPER_FILE_CONF, notemapper_file},
			{SOLVER_SETTINGS_CONF, _S(current_panel->ST_SOLVER)},
			{SOLVER_OPT_CONF, _S(current_panel->ST_OPT)},
			{OUTPUT_SETTINGS_CONF, _S(current_panel->ST_OUTPUTTYPE)},
			{OUTPUT_TO_FILE_CONF, _S(current_panel->ST_OUTPUTTOFILE)},
			{OUTPUT_FILE_CONF, output_file}
			});
	wxXmlAttribute *attr = config->GetAttributes();
	while (attr) {
		for (int i = 0; i < config_attrs.size(); i++) {
			if (attr->GetName() == config_attrs[i].first) {
				attr->SetValue(config_attrs[i].second);	
				break;
			}
		}
		attr = attr->GetNext();
	}
	conf_doc.Save(configs_path);
}
wxXmlNode *MFPG_Frame::NewConfig(wxString conf_name) {
	wxXmlAttribute *c = new wxXmlAttribute("name", conf_name);
	wxXmlNode *config = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "config", wxEmptyString, c, NULL, -1);
	
	std::vector<std::pair<std::string, std::string>> config_settings({
			{INSTRUMENT_SETTINGS_CONF, "USE_PRESETS"},
			{DSL_FILE_CONF, "NONE"},
			{INSTRUMENT_CONF, "INSTRUMENT_VIOLIN"},
			{ACTIONSET_CONF, "ACTIONSET_T1"},
			{NOTEMAPPER_SETTINGS_CONF, "NOTEMAPPER_BASIC"},
			{NOTEMAPPER_FILE_CONF, "NONE"},
			{SOLVER_SETTINGS_CONF, "SOLVER_SPS"},
			{SOLVER_OPT_CONF, "OPT_3"},
			{OUTPUT_SETTINGS_CONF, "CSV_OUTPUT"},
			{OUTPUT_TO_FILE_CONF, "OUTPUT_TO_FILE"},
			{OUTPUT_FILE_CONF, "NONE"}
			});

	for (auto p : config_settings) {
		wxXmlAttribute *settings_attr = new wxXmlAttribute(p.first, p.second);
		config->AddAttribute(settings_attr);
	}
	return config;
}
void MFPG_Frame::MenuDeleteConfig(wxCommandEvent& event) {
	wxXmlDocument conf_doc;
	conf_doc.Load(configs_path);
	std::vector<wxString> config_names;
	wxXmlNode *config = conf_doc.GetRoot()->GetChildren()->GetChildren();
	while (config) {
		config_names.push_back(config->GetAttribute(CONFIG_NAME_CONF, wxEmptyString));
		config = config->GetNext();
	}
	void** c = NULL;
	wxSingleChoiceDialog dialog(NULL, "Select saved Config to delete.", "Delete Saved Config", 
		config_names.size(), &config_names[0], c, wxCHOICEDLG_STYLE, wxDefaultPosition);
	if (dialog.ShowModal() == wxID_OK) {
		wxXmlNode *removed_node = conf.GetRoot()->GetChildren()->GetChildren();
		while (removed_node) {
			if (removed_node->GetAttribute(CONFIG_NAME_CONF, wxEmptyString) == 
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
	if (current_panel == NULL) {
		return;
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
			current_panel->notemapper_text->Disable();
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
			current_panel->dsl_text->Disable();
			break;
		case USE_DSL:
			current_panel->instrument_settings_box->SetSelection(1);
			current_panel->ST_INSTRUMENT_SETTING = USE_DSL;
			current_panel->instrument_box->Disable();
			current_panel->actionset_box->Disable();
			current_panel->dsl_filepicker->Enable();
			current_panel->dsl_text->Enable();
			break;
		default:
			current_panel->instrument_settings_box->SetSelection(-1);
			current_panel->ST_INSTRUMENT_SETTING = UNDEFINED;
			current_panel->dsl_text->Disable();
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
			//Enable help-text underneath checkboxes
			for (auto text : current_panel->solver_area->GetChildren()) {
				if ((text->GetName() == "OPT1_TEXT" && 
				     current_panel->sps_opt_1->IsChecked()) || 
				     (text->GetName() == "OPT2_TEXT" && 
				      current_panel->sps_opt_2->IsChecked())) {
					text->Enable();
				}
			}
			current_panel->sps_opt_1->Enable();
			current_panel->sps_opt_2->Enable();
			current_panel->solver_box->SetSelection(0);
			current_panel->ST_SOLVER = SOLVER_SPS;
			break;
		case SOLVER_GREEDY:
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT1_TEXT" || text->GetName() == "OPT2_TEXT") {
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
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT1_TEXT") {
					text->Disable();
				}
			}
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT2_TEXT") {
					text->Disable();
				}
			}
			current_panel->ST_OPT = OPT_0;
			break;
		case OPT_1:
			current_panel->sps_opt_1->SetValue(true);
			current_panel->sps_opt_2->SetValue(false);
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT1_TEXT") {
					text->Enable();
				}
			}
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT2_TEXT") {
					text->Disable();
				}
			}
			current_panel->ST_OPT = OPT_1;
			break;
		case OPT_2:
			current_panel->sps_opt_1->SetValue(false);
			current_panel->sps_opt_2->SetValue(true);
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT1_TEXT") {
					text->Disable();
				}
			}
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT2_TEXT") {
					text->Enable();
				}
			}
			current_panel->ST_OPT = OPT_2;
			break;
		case OPT_3:
			current_panel->sps_opt_1->SetValue(true);
			current_panel->sps_opt_2->SetValue(true);
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT1_TEXT") {
					text->Enable();
				}
			}
			for (auto text : current_panel->solver_area->GetChildren()) {
				if (text->GetName() == "OPT2_TEXT") {
					text->Enable();
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
			current_panel->output_filepicker->Enable();
			current_panel->output_text->Enable();
			current_panel->output_to_file->SetValue(true);
			current_panel->ST_OUTPUTTOFILE = OUTPUT_TO_FILE;
			break;
		default:
			current_panel->output_filepicker->Disable();
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
	if (!path) {
	} else {
		current_panel->dsl_filepicker->SetPath(current_panel->FilePath_DSL);
		current_panel->dsl_text->LoadFile(current_panel->FilePath_DSL);
	}
}

void MFPG_Frame::FPCSVNoteMap(wxFileDirPickerEvent& event) {
	SelectNoteMapFile(current_panel->notemap_filepicker->GetPath());
}
void MFPG_Frame::SelectNoteMapFile(wxString path) {
	current_panel->FilePath_Notemap = path;
	if (!path) {
	} else {
		current_panel->notemap_filepicker->SetPath(current_panel->FilePath_Notemap);
		current_panel->notemapper_text->LoadFile(current_panel->FilePath_Notemap);
	}
}

void MFPG_Frame::FPCSVOutput(wxFileDirPickerEvent& event) {
	SelectOutputFile(current_panel->output_filepicker->GetPath());
}
void MFPG_Frame::SelectOutputFile(wxString path) {
	current_panel->FilePath_Output = path;
	if (!path) {
	} else {
		current_panel->output_filepicker->SetPath(current_panel->FilePath_Output);
		current_panel->output_text->LoadFile(current_panel->FilePath_Output);
	}
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
						current_panel->output_text->SaveFile(
							current_panel->FilePath_Output);
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
						current_panel->notemapper_text->SaveFile(
							current_panel->notemap_filepicker->GetPath());
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
						current_panel->dsl_text->SaveFile(
							current_panel->dsl_filepicker->GetPath());
					}
				}
			}
			break;
		default:
			break;
	}
}

void MFPG_Frame::BTRemoveConfig(wxCommandEvent& event) {
	wxMessageDialog q(NULL, "Remove Config?", "Remove Config from menu?", wxYES_NO|wxICON_QUESTION,
		wxDefaultPosition);
	if (q.ShowModal() == wxID_YES) {
		config_book->DeletePageAndPanel();
		config_book->Refresh();
	}
}

void MFPG_Frame::BTClearInfo(wxCommandEvent& event) {
	current_panel->information_text->Clear();
}

void MFPG_Frame::BTGenerate(wxCommandEvent& event) {
	Generate();
}

//Generate the solution with the specified settings.
void MFPG_Frame::Generate() {
	//Redirect std::cout to write to information window
	wxStreamToTextRedirector redirect(current_panel->information_text);
	std::string score_path_; 
	score_path_ = score_path; //wxString to string
	if (!score_path) {
		wxMessageBox("No Score file selected");
		return;
	}
	
	//Read file into mx structures
	using namespace mx::api;
	auto& mgr = DocumentManager::getInstance();	
	const auto documentID = mgr.createFromFile(score_path_);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	const NoteList note_list(score);
	
	InstrumentBuilder instrument_builder;

	//Patchwork fix for multiple output types
	std::shared_ptr<Instrument<int>> violin_i;
	std::shared_ptr<Instrument<double>> violin_d;

	char output_type = 'i';
	
	if (current_panel->ST_INSTRUMENT_SETTING == USE_DSL) {
		FILE *dsl_file;	
		dsl_file = fopen((current_panel->FilePath_DSL).c_str(), "r");
		if (dsl_file == nullptr) {
			wxMessageBox("Could not open DSL file.");
			return;
		}
		Input *parse_tree = NULL;
		try {
			parse_tree = pInput(dsl_file);
		} catch (parse_error &e) {
			fclose(dsl_file);
			delete(parse_tree);
			std::string e_msg = "DSL Parse error on line: ";
			e_msg += std::to_string(e.getLine());
			std::cout << e_msg << "\n";
			wxMessageBox(e_msg);
			return;
		}
		fclose(dsl_file);

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
		delete(parse_tree);
	} else if (current_panel->ST_INSTRUMENT_SETTING == USE_PRESETS) {
		TUPLESIZE = 3;
		ATTRIBUTES = {"STRING", "FINGER", "HAND_POS"};
		ATTRIBUTE_TYPES = "iii";

		std::shared_ptr<ActionSet<int>> as_i;

		switch (current_panel->ST_ACTIONSET) {
			case ACTIONSET_T1:
				as_i = configs::test_configuration_1();
				break;
			case ACTIONSET_T2:
				as_i = configs::test_configuration_2();
				break;
			case UNDEFINED:
				wxMessageBox("Could not find ActionSet, Aborting...");
				return;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
		switch (current_panel->ST_INSTRUMENT) {
			case INSTRUMENT_VIOLIN:
				violin_i = std::shared_ptr<Instrument<int>>(new Instrument<int>(as_i));
				violin_i->makeIString(1, Note::G_3, Note::Gs_5);
				violin_i->makeIString(2, Note::D_4, Note::Ds_6);
				violin_i->makeIString(3, Note::A_4, Note::As_6);
				violin_i->makeIString(4, Note::E_5, Note::F_7);
				break;
			case UNDEFINED:
				wxMessageBox("Could not find Instrument, Aborting...");
				return;
			default:
				wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
				return;
		}
	} else {
		wxMessageBox("No instrument settings selected");
		return;
	}
	std::shared_ptr<NoteMapper> note_mapper;
	try {
		std::string map_csv_path;
		switch (current_panel->ST_NOTEMAPPER) {
			case NOTEMAPPER_BASIC:
				if (output_type == 'i') {
					note_mapper = std::shared_ptr<NoteMapper>(new BasicNoteMapper(
										violin_i->getIStrings()));
				} else if (output_type == 'd') {
					note_mapper = std::shared_ptr<NoteMapper>(new BasicNoteMapper(
										violin_d->getIStrings()));
				}
				break;
			case NOTEMAPPER_CSV:
				map_csv_path = current_panel->FilePath_Notemap;
				if (output_type == 'i') {
					note_mapper = std::shared_ptr<NoteMapper>(new CSVNoteMapper(
								map_csv_path, violin_i->getIStrings()));
				} else if (output_type == 'd') {
					note_mapper = std::shared_ptr<NoteMapper>(new CSVNoteMapper(
								map_csv_path, violin_d->getIStrings()));
				}
				break;
			case UNDEFINED:
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
			list_i = std::shared_ptr<LayerList<int>>(
							new LayerList<int>(note_list, note_mapper));
			list_i->buildTransitions(violin_i->getActionSet());
		} else if (output_type == 'd') {
			list_d = std::shared_ptr<LayerList<double>>(
							new LayerList<double>(note_list, note_mapper));
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
		case SOLVER_GREEDY:
			solver_i = std::shared_ptr<GraphSolver<int>>(new GreedySolver());
			if (output_type == 'd') {
				wxMessageBox("Greedy Solver is not implemented for double outputs.");
				return;
			}
			break;
		case SOLVER_SPS:
			switch (current_panel->ST_OPT) {
				case OPT_0:
					solver_i = std::shared_ptr<GraphSolver<int>>(
										new SPSolver<int>(0));
					solver_d = std::shared_ptr<GraphSolver<double>>(
										new SPSolver<double>(0));
					break;
				case OPT_1:
					solver_i = std::shared_ptr<GraphSolver<int>>(
										new SPSolver<int>(1));
					solver_d = std::shared_ptr<GraphSolver<double>>(
										new SPSolver<double>(1));
					break;
				case OPT_2:
					solver_i = std::shared_ptr<GraphSolver<int>>(
										new SPSolver<int>(2));
					solver_d = std::shared_ptr<GraphSolver<double>>(
										new SPSolver<double>(2));
					break;
				case OPT_3:
					solver_i = std::shared_ptr<GraphSolver<int>>(
										new SPSolver<int>(3));
					solver_d = std::shared_ptr<GraphSolver<double>>(
										new SPSolver<double>(3));
					break;
				case UNDEFINED:
					solver_i = std::shared_ptr<GraphSolver<int>>(
										new SPSolver<int>(0));
					solver_d = std::shared_ptr<GraphSolver<double>>(
										new SPSolver<double>(0));
					break;
				default:
					wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
					return;
			}
			break;
		case UNDEFINED:
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
	bool use_csv = false;
	switch (current_panel->ST_OUTPUTTYPE) {
		case CSV_OUTPUT:
			use_csv = true;
			break;
		case DIRECT_OUTPUT:
			use_csv = false;
			break;
		case UNDEFINED:
			use_csv = false;
			break;
		default:
			wxMessageBox("IMPOSSIBLE PROGRAM FLOW");
			return;
	}
	current_panel->output_text->Clear();
	if (current_panel->ST_OUTPUTTOFILE) {
		std::string out_path;
		std::ofstream out; 
		if (!current_panel->FilePath_Output) {
			wxMessageBox("No Output file selected");
			return;
		}
		out_path = current_panel->FilePath_Output;
		out.open(out_path, std::ofstream::binary);
		if (output_type == 'i') {
			configs::writeOutput(out, solver_i, use_csv);
		} else if (output_type == 'd') {
			configs::writeOutput(out, solver_d, use_csv);
		}
		out.close();
		current_panel->output_text->LoadFile(current_panel->FilePath_Output);
	} else {
		std::ostream *to_out = new std::ostream{nullptr};
		wxStreamToTextRedirector out_redirect(current_panel->output_text, to_out);
		if (output_type == 'i') {
			configs::writeOutput(*to_out, solver_i, use_csv);
		} else if (output_type == 'd') {
			configs::writeOutput(*to_out, solver_d, use_csv);
		}
	}
}
