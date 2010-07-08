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


#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/progdlg.h>
#include <wx/dcbuffer.h>
                           
#undef MainFrame_STYLE
#define MainFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class MainFrame : public wxFrame
{
    public:
        MainFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = MainFrame_STYLE);
        virtual ~MainFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();
        void OnClose(wxCloseEvent& event);

        // Functions
        void CreateGUIControls();
        
        // wxWidgets gui objects
        wxStatusBar* statusBar;
        wxMenuBar* menuBar;
        
    private:
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_TEXT = 1000,
            ID_STATUSBAR
        };
};

#endif
