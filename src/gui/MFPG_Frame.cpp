#include "MFPG_Frame.h"
#include <wx/docview.h>
#include <wx/textctrl.h>
#include <wx/choicebk.h>
#include <wx/valtext.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>

#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"

#include "conf_cmake.h"
#include "Log.h"

#include <vector>
#include <fstream>

#include "NoteEnums.h"
#include "NoteMapper.h"
#include "BasicNoteMapper.h"
#include "CSVNoteMapper.h"
#include "ActionSet.h"
#include "LayerList.h"
#include "NoteList.h"
#include "GraphSolver.h"
#include "GreedySolver.h"
#include "Instrument.h"
#include "PhysAttrMap.h"
#include "ExValException.h"
#include "SPSolver.h"
#include "InstrumentBuilder.h"
#include "NoteMapperException.h"
#include "configs.h"

#include "ParserError.H"
#include "Parser.H"

extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

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
	
	wxMenu *menuConfig = new wxMenu;
	menuConfig->Append(ID_MenuNewConfig, "&New Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveConfig, "&Save Config");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuSaveAsConfig, "&Save Config As");
	menuConfig->AppendSeparator();
	menuConfig->Append(ID_MenuDeleteConfig, "&Delete Config");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	menuBar->Append(menuConfig, "&Configs");

	SetMenuBar( menuBar );

	CreateStatusBar();
	std::string status("MFPG -- Version: ");
	status += VERSION_MFPG;
	SetStatusText(status);
	
	config_book = new MFPG_Choicebook(this, ID_CBOOKChange);
	MFPG_Panel *config_panel = new MFPG_Panel(config_book);
	
	current_panel = config_panel;
	config_book->AddPage(config_panel, _T("Config1"), true, 0);
}

wxBEGIN_EVENT_TABLE(MFPG_Frame, wxFrame)
	EVT_MENU(wxID_EXIT, MFPG_Frame::MenuExit)
	EVT_MENU(wxID_ABOUT, MFPG_Frame::MenuAbout)
	EVT_MENU(ID_MenuNewScore, MFPG_Frame::MenuNewScore)
	EVT_MENU(ID_MenuNewConfig, MFPG_Frame::MenuNewConfig)
	EVT_MENU(ID_MenuSaveConfig, MFPG_Frame::MenuSaveConfig)
	EVT_MENU(ID_MenuSaveAsConfig, MFPG_Frame::MenuSaveAsConfig)
	EVT_MENU(ID_MenuDeleteConfig, MFPG_Frame::MenuDeleteConfig)

	EVT_CHOICEBOOK_PAGE_CHANGED(ID_CBOOKChange, MFPG_Frame::CBOOKChange)

	EVT_COMBOBOX(ID_CBNoteMapper, MFPG_Frame::CBNoteMapper)
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
wxEND_EVENT_TABLE()

void MFPG_Frame::MenuExit(wxCommandEvent& event) {
	Close(true);
}

void MFPG_Frame::MenuAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MFPG_Frame::MenuNewScore(wxCommandEvent& event) {
	wxFileDialog *file_dialog = new wxFileDialog(this, _("Choose a musicXML file to open"), 
			wxEmptyString, wxEmptyString, _("XML files (*.xml)|*.xml"), 
			wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFLP_CHANGE_DIR, wxDefaultPosition);
	if (file_dialog->ShowModal() == wxID_OK) {
		score_path = file_dialog->GetPath();
		for (auto s : config_book->getPanels()) {
			s->file_name->SetLabel(score_path);
			s->file_name->Refresh();
		}
	}
}
void MFPG_Frame::MenuNewConfig(wxCommandEvent& event) {
	wxString new_conf;
	wxTextEntryDialog *input_dialog = new wxTextEntryDialog(this, _("Config Name"), 
			_("New Config"), wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
	input_dialog->SetMaxLength(16);
	wxTextValidator config_names(wxFILTER_INCLUDE_CHAR_LIST);
	config_names.SetCharIncludes(config_chars);
	input_dialog->SetTextValidator(config_names);
	if (input_dialog->ShowModal() == wxID_OK) {
		new_conf = input_dialog->GetValue();
		MFPG_Panel *config_panel = new MFPG_Panel(config_book);
		config_panel->file_name->SetLabel(score_path);
		config_panel->file_name->Refresh();
		config_book->AddPage(config_panel, new_conf, true, 0);
		current_panel = config_panel;
	}
}
void MFPG_Frame::MenuSaveConfig(wxCommandEvent& event) {
		
}
void MFPG_Frame::MenuSaveAsConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::MenuDeleteConfig(wxCommandEvent& event) {
	
}
void MFPG_Frame::CBOOKChange(wxBookCtrlEvent& event) {
	current_panel = config_book->getCurrentPanel();
}
void MFPG_Frame::CBNoteMapper(wxCommandEvent& event) {
	if (current_panel->notemap_box->GetCurrentSelection() == 0) {
		current_panel->csv_file->Disable();
		current_panel->notemapper = Settings::NOTEMAPPER_BASIC;
	} else if (current_panel->notemap_box->GetCurrentSelection() == 1) {
		current_panel->csv_file->Enable();
		current_panel->notemapper = Settings::NOTEMAPPER_CSV;
	} else {
		current_panel->notemapper = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBInstrument(wxCommandEvent& event) {
	if (current_panel->instrument_box->GetCurrentSelection() == 0) {
		if (current_panel->actionset_box->GetCurrentSelection() != 2) {
			current_panel->dsl_file->Disable();
		}
		current_panel->instrument = Settings::INSTRUMENT_VIOLIN;
	} else if (current_panel->instrument_box->GetCurrentSelection() == 1) {
		current_panel->dsl_file->Enable();
		current_panel->instrument = Settings::INSTRUMENT_DSL;
	} else {
		current_panel->instrument = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBActionSet(wxCommandEvent& event) {
	if (current_panel->actionset_box->GetCurrentSelection() == 0) {
		if (current_panel->instrument_box->GetCurrentSelection() != 1) {
			current_panel->dsl_file->Disable();
		}
		current_panel->actionset = Settings::ACTIONSET_T1;
	} else if (current_panel->actionset_box->GetCurrentSelection() == 1) {
		if (current_panel->instrument_box->GetCurrentSelection() != 1) {
			current_panel->dsl_file->Disable();
		}
		current_panel->actionset = Settings::ACTIONSET_T2;
	} else if (current_panel->actionset_box->GetCurrentSelection() == 2) {
		current_panel->dsl_file->Enable();
		current_panel->actionset = Settings::ACTIONSET_DSL;
	} else {
		current_panel->actionset = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CBSolver(wxCommandEvent& event) {
	if (current_panel->solver_box->GetCurrentSelection() == 0) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if ((c->GetName() == "OPT1_TEXT" && current_panel->sps_opt_1->IsChecked()) ||
			     (c->GetName() == "OPT2_TEXT" && current_panel->sps_opt_2->IsChecked())) {
				c->Enable();
			}
		}
		current_panel->sps_opt_1->Enable();
		current_panel->sps_opt_2->Enable();
		current_panel->solver = Settings::SOLVER_SPS;
	} else if (current_panel->solver_box->GetCurrentSelection() == 1) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT" || c->GetName() == "OPT2_TEXT") {
				c->Disable();
			}
		}
		current_panel->sps_opt_1->Disable();
		current_panel->sps_opt_2->Disable();
		current_panel->solver = Settings::SOLVER_GREEDY;
	} else {
		current_panel->solver = Settings::UNDEFINED;
		wxMessageBox("UNDEFINED NOTEMAPPER");
	}
}
void MFPG_Frame::CHBSPSOpt1(wxCommandEvent& event) {
	if (current_panel->sps_opt_1->IsChecked()) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT") {
				c->Enable();
			}
		}
		if (current_panel->sps_opt_2->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_3;
		} else {
			current_panel->solver = Settings::SOLVER_SPS_1;
		}
	} else {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT1_TEXT") {
				c->Disable();
			}
		}
		if (current_panel->sps_opt_2->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_2;
		} else {
			current_panel->solver = Settings::SOLVER_SPS;
		}
	}

}
void MFPG_Frame::CHBSPSOpt2(wxCommandEvent& event) {
	if (current_panel->sps_opt_2->IsChecked()) {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT2_TEXT") {
				c->Enable();
			}
		}
		if (current_panel->sps_opt_1->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_3;
		} else {
			current_panel->solver = Settings::SOLVER_SPS_2;
		}
	} else {
		for (auto c : current_panel->solver_area->GetChildren()) {
			if (c->GetName() == "OPT2_TEXT") {
				c->Disable();
			}
		}
		if (current_panel->sps_opt_1->IsChecked()) {
			current_panel->solver = Settings::SOLVER_SPS_1;
		} else {
			current_panel->solver = Settings::SOLVER_SPS;
		}
	}
}
void MFPG_Frame::CHBOutputToFile(wxCommandEvent& event) {
	if (current_panel->output_to_file->IsChecked()) {
		current_panel->output_file->Enable();
		current_panel->output_to_file_setting = Settings::OUTPUT_TO_FILE;
	} else {
		current_panel->output_file->Disable();
		current_panel->output_to_file_setting = Settings::UNDEFINED;
	}
}
void MFPG_Frame::CBOutput(wxCommandEvent& event) {
	if (current_panel->output_selection_box->GetCurrentSelection() == 0) {
		current_panel->output = Settings::OUTPUT_TO_FILE;	
	} else if (current_panel->output_selection_box->GetCurrentSelection() == 1) {
		current_panel->output = Settings::DIRECT_OUTPUT;	
	}
}
void MFPG_Frame::FPDSL(wxFileDirPickerEvent& event) {
	instrument_dsl_file_path = current_panel->dsl_file->GetPath();
}
void MFPG_Frame::FPCSVNoteMap(wxFileDirPickerEvent& event) {
	notemap_csv_file_path = current_panel->csv_file->GetPath();
}
void MFPG_Frame::FPCSVOutput(wxFileDirPickerEvent& event) {
	output_file_path = current_panel->output_file->GetPath();	
}
void MFPG_Frame::BTGenerate(wxCommandEvent& event) {
	Generate();
}

void MFPG_Frame::Generate() {
	std::string score_path_;
	score_path_ = score_path;
	
	using namespace mx::api;
	auto& mgr = DocumentManager::getInstance();	
	const auto documentID = mgr.createFromFile(score_path_);

	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	const NoteList note_list(score);

	std::shared_ptr<Instrument<int>> violin_i;
	InstrumentBuilder instrument_builder;
	FILE *dsl_file;
	dsl_file = fopen(instrument_dsl_file_path.c_str(), "r");
	
	Input *parse_tree = NULL;
	parse_tree = pInput(dsl_file);
	fclose(dsl_file);

	instrument_builder.visitInput(parse_tree);
	violin_i = instrument_builder.i_inst;

	TUPLESIZE = instrument_builder.attrs.size();
	ATTRIBUTES = instrument_builder.attrs;
	ATTRIBUTE_TYPES = instrument_builder.attrtypes;
	
	std::string map_csv_path;
	map_csv_path = notemap_csv_file_path;

	std::shared_ptr<NoteMapper> note_mapper(new CSVNoteMapper(map_csv_path, violin_i->getIStrings()));

	LayerList<int> list(note_list, note_mapper);

	list.buildTransitions(violin_i->getActionSet());

	std::shared_ptr<GraphSolver<int>> solver;
	solver = std::shared_ptr<GraphSolver<int>>(new SPSolver<int>(3));

	solver->solve(list);
	
	std::string csv_out_path;
	csv_out_path = output_file_path;
	std::ofstream out; 
	out.open(csv_out_path, std::ofstream::binary);

	configs::writeOutput(out, solver, true);
	current_panel->output_text->Clear();
	//TODO continue here
	if (current_panel->output_text->LoadFile(output_file_path)) {
		wxMessageBox(_("SUCCESS!"));
	} else {
		wxMessageBox(_("FAILURE!"));
	}
}
