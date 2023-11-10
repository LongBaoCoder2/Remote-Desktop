#include "ClientWindow.hpp"

ClientWindow::ClientWindow(const std::string &host, uint16_t port)
    : wxFrame(nullptr, wxID_ANY, "Client Window")
{

    if (!ConnectToServer(host, port))
    {
        // LOG
    }

    CapturePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1366, 768));
    CapturePanel->SetBackgroundColour(wxColor(38, 37, 54));

    wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
    MainSizer->Add(CapturePanel, 1, wxEXPAND, 0);

    timer = new wxTimer(this, wxID_ANY);
    this->Bind(wxEVT_TIMER, &ClientWindow::OnUpdateWindow, this);
    timer->Start(DELAY_MS);

    this->SetSizerAndFit(MainSizer);
    this->Center();
}

void ClientWindow::OnUpdateWindow(wxTimerEvent &event)
{

    if (IsConnected())
    {
        while (!Incoming().empty())
        {
            auto msg = Incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case RemoteMessage::SERVER_ACCEPT:
                isWaitingForConnection = false;
                break;
            case RemoteMessage::SERVER_DENY:
                // Disconnect();
                break;
            case RemoteMessage::SERVER_UPDATE:
                // GET IMAGE FROM RAW IMAGE
                break;
            }
        }
    }

    if (isWaitingForConnection)
    {
        ClearPanel();
        return;
    }

    UpdatePanel();
}

void ClientWindow::UpdatePanel()
{
    wxClientDC clientDC(CapturePanel);
    // clientDC.Clear();
    clientDC.DrawBitmap(screenshot, 0, 0, false);
}

void ClientWindow::ClearPanel()
{
    wxClientDC clientDC(CapturePanel);
    clientDC.Clear();
}

ClientWindow::~ClientWindow()
{
    timer->Stop();
    ClearPanel();
}
