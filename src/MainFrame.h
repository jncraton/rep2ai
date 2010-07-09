/**
 * \file MainFrame.h
 * \brief Main window header file
 */

#ifndef __MAINFRAME_h__
#define __MAINFRAME_h__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/frame.h>
#else
    #include <wx/wxprec.h>
#endif

#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/tbarbase.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/sizer.h>
              
#include "AI.h"
#include "Replay.h"
#include "Rep2AI.h"

#undef MainFrame_STYLE
#define MainFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class MainFrame : public wxFrame
{
    public:
        MainFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = MainFrame_STYLE);
        virtual ~MainFrame();

    private:
        // Event handlers
        void OnClose(wxCloseEvent& event);
        void OnExit(wxCommandEvent& event);
        void SelectPlayer(wxCommandEvent& event);
        void OpenReplay(wxCommandEvent& event);
        void RunAI(wxCommandEvent& event);

        DECLARE_EVENT_TABLE();

        // Functions
        void CreateGUIControls();
        
        // wxWidgets gui objects
        wxStatusBar* statusBar;
        wxMenuBar* menuBar;
        wxMenu* fileMenu;
        wxPanel* panel;
        wxBoxSizer* sizer;
        wxBoxSizer* controlsSizer;
        wxComboBox* playerSelection;
        wxStaticText* playerSelectionLabel;
        wxBitmapButton* runButton;
        wxTextCtrl* text;
        
        // rep2ai
        Replay* replay;
        wxString replayFilename;
        
    private:
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_OPEN = 1000,
            ID_RUN,
            ID_RUN_BUTTON,
            ID_EXIT,
            ID_TEXT,
            ID_PLAYERSELECTION,
            ID_STATUSBAR
        };
};

#endif
