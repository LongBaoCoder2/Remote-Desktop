#include "ClientWindow.hpp"

ClientWindow::ClientWindow(const std::string& host, uint16_t port)
    : wxFrame(nullptr, wxID_ANY, "Client Window"), net::IClient<RemoteMessage>()
{

    if (!ConnectToServer(host, port))
    {
        // LOG
        wxMessageBox(wxT("Failed to connect to Server."), wxT("Error"), wxICON_ERROR | wxOK);
    }
    // wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);

    CapturePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1280, 960));
    CapturePanel->SetBackgroundColour(wxColor(38, 37, 54));

    // Tạo một wxTextCtrl để hiển thị văn bản
    // textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    // textCtrl->SetBackgroundColour(wxColor(255, 255, 255));


    // Tạo một wxBoxSizer với hướng ngang
    wxBoxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Thêm CapturePanel vào MainSizer với tỷ lệ 1
    MainSizer->Add(CapturePanel, 1, wxEXPAND, 0);

    // Thêm textCtrl vào MainSizer với tỷ lệ 1
    // MainSizer->Add(textCtrl, 1, wxEXPAND, 0);

    timer = new wxTimer(this, 1);
    this->Bind(wxEVT_TIMER, &ClientWindow::OnUpdateWindow, this, timer->GetId());
    timer->Start(DELAY_MS);

    this->SetSizerAndFit(MainSizer);
    this->Center();
}

void ClientWindow::OnUpdateWindow(wxTimerEvent& event)
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
                wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                break;
            case RemoteMessage::SERVER_DENY:
                // Disconnect();
                wxMessageBox(wxT("Disconnected from the server."), wxT("Disconnected"), wxICON_INFORMATION | wxOK);
                break;

            case RemoteMessage::SERVER_UPDATE:
                isWaitingForConnection = false;

                OnReceiveImage(msg);

                // Tạo một memory stream từ dữ liệu nhận được
                // wxMemoryInputStream memStream(msg.body.data(), msg.body.size());
                // wxMessageBox(wxString::Format(wxT("Data received: %llu bytes.\n"), msg.body.size()), wxT("Message"), wxICON_INFORMATION | wxOK);

                // // Tải hình ảnh từ memory stream
                // wxImage image;
                // image.LoadFile(memStream, wxBITMAP_TYPE_PNG);
                // wxMessageBox(wxT("Image convert successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);

                // // Chuyển đổi wxImage thành wxBitmap để hiển thị
                // if (image.IsOk())
                // {
                //     screenshot = wxBitmap(image);
                //     wxMessageBox(wxT("Image sent successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                // }
                // else
                // {
                //     wxMessageBox(wxT("Failed to load the image."), wxT("Error"), wxICON_ERROR | wxOK);
                // }

                break;
            }
        }
    }

    // textCtrl->AppendText("Chua thay connection!\n");

    if (isWaitingForConnection)
    {
        // ClearPanel();
        return;
    }

    UpdatePanel();
}

void ClientWindow::UpdatePanel()
{
    // clientDC.Clear();
    if (screenshot.IsOk()) {
        wxClientDC clientDC(CapturePanel);
        clientDC.DrawBitmap(screenshot, 0, 0, false);
    }
}

void ClientWindow::ClearPanel()
{
    wxClientDC clientDC(CapturePanel);
    clientDC.Clear();
}

void ClientWindow::OnReceiveImage(net::message<RemoteMessage>& msg)
{
    unsigned char* bitmapData = reinterpret_cast<unsigned char*>(msg.body.data());

    wxImage image(1280, 960, bitmapData, true);
    screenshot = wxBitmap(image);
}


ClientWindow::~ClientWindow()
{
    timer->Stop();
    ClearPanel();
}
