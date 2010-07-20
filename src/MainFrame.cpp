/**
 * \file MainFrame.cpp
 * \brief Main Windows Class
 */
 
#include "MainFrame.h"

#include "icons.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_MENU(ID_EXIT, MainFrame::OnExit)
    EVT_MENU(ID_OPEN, MainFrame::OpenReplay)
    EVT_MENU(ID_RUN, MainFrame::RunAI)
    EVT_MENU(ID_SAVE_AISCRIPT, MainFrame::SaveToAiscript)
    EVT_MENU(ID_WEBSITE, MainFrame::Website)
    EVT_MENU(ID_ABOUT, MainFrame::About)
    EVT_BUTTON(ID_RUN_BUTTON, MainFrame::RunAI)
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
    playerSelected = false;
    replayOpen = false;
    
    replay = NULL;
    rep2ai = NULL;
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
    SetTitle(wxT(NAME));
    SetIcon(wxNullIcon);
    
    // Menu Bar
    menuBar = new wxMenuBar();

    fileMenu = new wxMenu();
    fileMenu->Append(ID_OPEN, _T("&Open"));
    fileMenu->Append(ID_RUN, _T("&Run"));
    fileMenu->Append(ID_SAVE_AISCRIPT, _T("&Save to aiscript.bin"));
    fileMenu->Append(ID_EXIT, _T("&Quit"));
    menuBar->Append(fileMenu, _T("&File"));

    helpMenu = new wxMenu();
    helpMenu->Append(ID_WEBSITE, _T("&Website"));
    helpMenu->Append(ID_ABOUT, _T("&About"));
    menuBar->Append(helpMenu, _T("&Help"));
    
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
    
    if ( replay != NULL ) free(replay);
    
    replay = new Replay((char*)replayFilename.c_str());
    
    *text << "Parsing Player List...\n";

    playerSelection->Clear();
    for(int i = 0; i < 8; i++) {
        if (replay->playerID[i] > -1 ) {
            playerSelection->Append(wxString(replay->playerName[i]));
        }
    }
    
    replayOpen = true;
    playerSelected = false;
}

void MainFrame::SaveToAiscript( wxCommandEvent& event ) {
    /**
    *   Event handler to save a replay to aiscript.bin
    */
    if ( replayOpen && playerSelected ) {
        wxFileDialog file_dialog(this, wxT("Select location to save to"), wxT(""), wxT("aiscript.bin"), wxT("*.bin"), wxSAVE);
        file_dialog.ShowModal();
        
        wxString filename = file_dialog.GetPath();

        *text << "Saving AI as " << filename << "...\n";
        
        rep2ai->saveToAiscript((char*)filename.c_str());
    }
}

void MainFrame::SelectPlayer( wxCommandEvent& event ) {
    /**
    *   Event handler for selecting a player
    */
	wxString player(playerSelection->GetString(playerSelection->GetCurrentSelection()));
    
	if(replayFilename == "") return;
	
	if ( rep2ai != NULL ) free(rep2ai);
	
    rep2ai = new Rep2AI(replay);
	                          
    *text << "Creating AI script for " << player << "...\n";

	rep2ai->findPlayer((char*)player.c_str());

    *text << "Writing aiscript.bin...\n";
	rep2ai->makeAI();
	
    *text << "Build Order:\n" << rep2ai->getBuildOrderAsText();
    
    playerSelected = true;
}

void MainFrame::RunAI( wxCommandEvent& event ) {
    /**
    *   Event handler for running the AI
    */
    if ( replayOpen && playerSelected ) {
        rep2ai->runAI();
    }
}

void MainFrame::About( wxCommandEvent& event ) {
    /**
     * Event handler for the about box
     */
     
     wxDialog about(this, -1, wxString("About"));
     wxBoxSizer about_sizer(wxVERTICAL);
     wxHtmlWindow about_html(&about);
     
     about.SetSizer(&about_sizer);
    
     about_html.SetPage(
         wxString("<h1>")+wxString(NAME)+wxString("</h1>")+
         wxString("<p>By: ")+wxString(AUTHOR)+wxString("</p>")+
         wxString("<p>")+wxString(WEBSITE)+wxString("</p>")
         );
     
     about_sizer.Add(&about_html,1,wxEXPAND);

     about.ShowModal();
}

void MainFrame::Website( wxCommandEvent& event ) {
    /**
     * Event handler for website
     */
     wxLaunchDefaultBrowser(WEBSITE);
}
