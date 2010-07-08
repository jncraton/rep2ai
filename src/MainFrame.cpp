/**
 * \file MainFrame.cpp
 * \brief Main Windows Class
 */
 
#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_MENU(ID_EXIT, MainFrame::OnExit)
    EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    CreateGUIControls();
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
    
    // Text Area

    text = new wxTextCtrl(this, ID_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS);
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
