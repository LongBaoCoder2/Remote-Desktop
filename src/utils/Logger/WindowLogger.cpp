#include "WindowLogger.hpp"

void wxLogGuiModHandler::DoLogRecord(wxLogLevel level,
                                     const wxString &msg,
                                     const wxLogRecordInfo &info)
{
    if (level == wxLOG_Info)
        return;
    else
        wxLogGui::DoLogRecord(level, msg, info);
}

Logger::Logger(wxWindow *parents)
{
    // wxLog::SetLogLevel(wxLOG_Max);
    // wxLog::SetVerbose();
    // // create logfile
    // wxFFile *test = new wxFFile("application.log", "a");
    // wxLog *temp = new wxLogStderr(test->fp());
    // wxLog::SetActiveTarget(temp);
    // create loggui and chain it
    wxLog::SetActiveTarget(new wxLogChain(new wxLogGuiModHandler()));
    // create logwindow
    logger = new wxLogWindow(parents, wxS("Log messages"), true, false); // true to make visible at start
                                                                         // no need to setactivetarget or wxlogchain on wxLogWindow
}

Logger::~Logger()
{
    delete logger;
}