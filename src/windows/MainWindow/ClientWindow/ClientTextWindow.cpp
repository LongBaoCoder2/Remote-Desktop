#include "ClientTextWindow.hpp"
// #include "../CaptureWindow/CaptureFrame.h"

ClientTextWindow::ClientTextWindow(const wxString& title, const wxPoint &pos, const wxSize &size)
: BasicTextFrame(title, pos, size)
{
}

void ClientTextWindow::DisplayMessage(const wxString& message) {
    BasicTextFrame::DisplayMessage("Client message", message);
}