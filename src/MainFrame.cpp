/**
 * \file MainFrame.cpp
 * \brief Main Windows Class
 */
 
#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
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
    
}

void MainFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    exit(0);
}
