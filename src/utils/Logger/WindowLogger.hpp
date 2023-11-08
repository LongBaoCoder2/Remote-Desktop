#pragma once
#include <wx/log.h>
#include <wx/ffile.h>

class wxLogGuiMod : public wxLogGui
{
protected:
    virtual void DoLogRecord(wxLogLevel level,
                             const wxString &msg,
                             const wxLogRecordInfo &info);
};
void wxLogGuiMod::DoLogRecord(wxLogLevel level,
                              const wxString &msg,
                              const wxLogRecordInfo &info)
{
    if (level == wxLOG_Info)
        return;
    else
        wxLogGui::DoLogRecord(level, msg, info);
}

class Logger
{
private:
    wxLog *logger;

public:
    ~Logger()
    {

        delete logger;
    }

    Logger(wxWindow *parents)
    {
        wxLog::SetLogLevel(wxLOG_Max);
        wxLog::SetVerbose();
        // create logfile
        wxFFile *test = new wxFFile("application.log", "a");
        wxLog *temp = new wxLogStderr(test->fp());
        wxLog::SetActiveTarget(temp);
        // create loggui and chain it
        wxLog::SetActiveTarget(new wxLogChain(new wxLogGuiMod()));
        // create logwindow
        logger = new wxLogWindow(parents, wxS("Log messages"), true, false); // true to make visible at start
                                                                             // no need to setactivetarget or wxlogchain on wxLogWindow
    }
};

/*
example:
#ifdef DEV
    std::unique_ptr<Logger> logger;
#endif

#ifdef DEV
    logger = std::make_unique<Logger>(this);
#endif

// test functions
#ifdef DEV
    wxLogMessage("Message"); // produces messagebox and  logs to file/window
    wxLogError("Error");     // produces error message and logs to file/window
    wxLogStatus("Status");   // creates message on app status bar and logs to file/window
    wxLogVerbose("Verbose"); // does not create message (due to wxLogGuiMod) and logs to file/window
#endif

*/