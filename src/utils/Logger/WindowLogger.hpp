#pragma once
#include <wx/log.h>
#include <wx/ffile.h>

class wxLogGuiModHandler : public wxLogGui
{
protected:
    virtual void DoLogRecord(wxLogLevel level,
                             const wxString &msg,
                             const wxLogRecordInfo &info);
};
class Logger
{
private:
    wxLog *logger;

public:
    ~Logger();

    Logger(wxWindow *parents);
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