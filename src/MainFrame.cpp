/**
 * \file MainFrame.cpp
 * \brief Main Windows Class
 */
 
#include "MainFrame.h"

#include "icons.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_MENU(ID_EXIT, MainFrame::OnExit)
    EVT_MENU(ID_OPEN, MainFrame::OpenReplay)
    EVT_CLOSE(MainFrame::OnClose)
    EVT_COMBOBOX(ID_PLAYERSELECTION, MainFrame::SelectPlayer)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    CreateGUIControls();
    replayFilename = "";
}

MainFrame::~MainFrame() {
    /** 
    *   Destructor for the Main form.
    */
}

void MainFrame::CreateGUIControls() {
    /**
    *   Creates all of the GUI controls on the main form.
    */
    
    // Set window properties and title bar
    SetTitle(wxT("rep2ai"));
    SetIcon(wxNullIcon);
    
    // Menu Bar
    menuBar = new wxMenuBar();

    fileMenu = new wxMenu();
    fileMenu->Append(ID_OPEN, _T("&Open"));
    fileMenu->Append(ID_EXIT, _T("&Quit"));
    menuBar->Append(fileMenu, _T("&File"));
 
    SetMenuBar(menuBar);
    
    // Main Panel
    sizer = new wxBoxSizer(wxVERTICAL);
    panel = new wxPanel(this);
    panel->SetSizer(sizer);

    // Controls
    controlsSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(controlsSizer,0);

    // Player Selection
    playerSelectionLabel = new wxStaticText(panel, -1, wxT("Player:"));
    playerSelection = new wxComboBox(panel, ID_PLAYERSELECTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL,wxCB_READONLY|wxCB_SORT);
    playerSelection->Append(wxT("Open a Replay first"));
    
    controlsSizer->Add(playerSelectionLabel);
    controlsSizer->Add(playerSelection);
    
    // Run Button
    
    runButton = new wxBitmapButton(panel, ID_RUN_BUTTON, wxBitmap(controller_xpm));
    controlsSizer->Add(runButton);
    
    // Text Area

    text = new wxTextCtrl(panel, ID_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxTE_READONLY|wxTE_MULTILINE);
    sizer->Add(text,1,wxEXPAND|wxALL);
}              

void MainFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    exit(0);
}

void MainFrame::OnExit( wxCommandEvent& event ) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    exit(0);
}

void MainFrame::OpenReplay( wxCommandEvent& event ) {
    /**
    *   Event handler opening a replay
    */
    wxFileDialog file_dialog(this, wxT("Select a replay to open"), wxT(""), wxT(""), wxT("*.rep"), wxOPEN);
    file_dialog.ShowModal();
    
    replayFilename = file_dialog.GetPath();
    
    *text << "Opening replay " << replayFilename << "...\n";
    
    replay = new Replay((char*)replayFilename.c_str());
    
    *text << "Parsing Player List...\n";

    playerSelection->Clear();
    for(int i = 0; i < 8; i++) {
        if (replay->playerID[i] > -1 ) {
            playerSelection->Append(wxString(replay->playerName[i]));
        }
    }
}

void MainFrame::SelectPlayer( wxCommandEvent& event ) {
    /**
    *   Event handler for selecting a player
    */
	wxString player(playerSelection->GetString(playerSelection->GetCurrentSelection()));
    
	if(replayFilename == "") return;
	
    Rep2AI rep2ai(replay);
	                          
    *text << "Creating AI script for " << player << "...\n";

	rep2ai.findPlayer((char*)player.c_str());

    *text << "Writing aiscript.bin...\n";
	rep2ai.makeAI();
	
    *text << "Build Order:\n" << rep2ai.getBuildOrderAsText();
}

void MainFrame::RunAI( wxCommandEvent& event ) {
    /**
    *   Event handler for running the AI
    */
    Rep2AI rep2ai(replay);
	rep2ai.runAI();
}
