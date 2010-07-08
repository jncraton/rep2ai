/**
 * \file App.cpp
 * \brief Main Application Code
 */

#include "App.h"
#include "MainFrame.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
    /**
    *   Creates the main frame and shows it
    */
    MainFrame* frame = new MainFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int App::OnExit()
{
    /**
    *   Closes the application
    */
    return 0;
}
