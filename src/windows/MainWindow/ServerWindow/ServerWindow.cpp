#include "ServerWindow.hpp"
#include "../../../utils/FileNameGenerator/FileNameGenerator.hpp"
#include <algorithm>
#include <iterator>

ServerWindow::ServerWindow(uint16_t port)
    : wxFrame(nullptr, wxID_ANY, "Server Window", wxDefaultPosition, wxSize(1366, 768)), net::IServer<RemoteMessage>(port), oldscreenshot()
{
    Start();
    oldscreenshot.Create(1366, 768);


    LogPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1366, 768));
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

    // Sắp xếp layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(sizer);
    textCtrl->AppendText("Server is running.\n");
    // text = new wxStaticText(LogPanel, wxID_ANY, "Server is running");

    timer = new wxTimer(this, 2);
    this->Bind(wxEVT_TIMER, &ServerWindow::OnCaptureWindow, this, timer->GetId());
    timer->Start(DELAY_MS);

    // this->SetSizerAndFit(MainSizer);
    this->Center();
}

void ServerWindow::takeScreenshot()
{
    // Capture Screen
    // wxRect frameRect = CapturePanel->GetRect();
    // wxRect frameRect = wxRect(wxGetClientDisplayRect());

    // đây là cái thằng lưu giữ tấm chụp màn hình
    // wxGetDisplaySize() giúp lấy kích cỡ toàn màn hình
    screenshot.Create(wxGetDisplaySize());
    // wxBitmap screenshot(frameRect.GetSize());

    // Lấy kích thước toàn bộ màn hình
    screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    int imgWidth = LogPanel->GetSize().GetWidth();
    int imgHeight = LogPanel->GetSize().GetHeight();

    // Tính toán tỷ lệ scale
    double scaleX = static_cast<double>(imgWidth) / screenWidth;
    double scaleY = static_cast<double>(imgHeight) / screenHeight;

    // biến này đóng vai trò buffer trung gian để thao tác trên screenshot
    wxMemoryDC memDC(screenshot);

    // Thực hiện phép chuyển đổi để vẽ toàn bộ nội dung màn hình
    memDC.SetUserScale(scaleX, scaleY);
    // đẩy dữ liệu từ màn hình vô biến screenshot
    memDC.Blit(0, 0, screenWidth, screenHeight, &screenDC, 0, 0);
    // bỏ screenshot ra khỏi memDC để lát dùng để vẽ lên
    memDC.SelectObject(wxNullBitmap);
}

void ServerWindow::OnCaptureWindow(wxTimerEvent& event)
{
    if (nCountUser)
    {
        takeScreenshot();
        wxImage image = screenshot.ConvertToImage();
        wxImage image2 = oldscreenshot.ConvertToImage();

        if (image.GetSize() == image2.GetSize()) {
            size_t dataSize = image.GetWidth() * image.GetHeight() * 3;
            if (memcmp(image.GetData(), image2.GetData(), dataSize) == 0)
                return;
        }
        wxMemoryOutputStream memStream;
        image.SaveFile(memStream, wxBITMAP_TYPE_JPEG);

        // Lấy dữ liệu nén
        size_t dataSize = memStream.GetSize();
        auto dataBuffer = std::make_shared<std::vector<uint8_t>>(dataSize);

        memStream.CopyTo(&(*dataBuffer)[0], dataSize);

        // Đóng gói vào message
        auto msg = std::make_shared<net::message<RemoteMessage>>();
        msg->header.id = RemoteMessage::SERVER_UPDATE;
        msg->header.size = dataSize;
        msg->body.assign(dataBuffer->begin(), dataBuffer->end());

        textCtrl->AppendText(wxString::Format(wxT("Data sent: %llu bytes.\n"), dataSize));

        // Gửi message đến tất cả clients
        std::thread sendThread([this, msg]() {
            MessageAllClients(*msg);
        });
        sendThread.detach(); 

        oldscreenshot = screenshot;
    }
}


ServerWindow::~ServerWindow()
{
}

bool ServerWindow::OnClientConnect(std::shared_ptr<net::session<RemoteMessage>> client)
{
    // At this time, we will accept all
    // Remember: We need authentication later

    nCountUser++;
    OnClientValidated(client);

    if (nCountUser == 1)
    {
        if (wxThread::IsMain()) {
            timer->Start(DELAY_MS);
        }
        else {
            wxTheApp->CallAfter([this]() {timer->Start(DELAY_MS);});
        }

    }
    return true;
}

void ServerWindow::OnClientValidated(std::shared_ptr<net::session<RemoteMessage>> client)
{
    // Client passed validation check, so send them a message informing
    // them they can continue to communicate
    net::message<RemoteMessage> msg;
    msg.header.id = RemoteMessage::SERVER_ACCEPT;
    client->Send(msg);
}

void ServerWindow::OnClientDisconnect(std::shared_ptr<net::session<RemoteMessage>> client)
{
    if (client)
    {
        nCountUser--;

        if (nCountUser == 0)
        {
            timer->Stop();
        }
    }
}

void ServerWindow::OnMessage(std::shared_ptr<net::session<RemoteMessage>> client, net::message<RemoteMessage>& msg)
{
    // if (!garbageIDs.empty())
    // {
    //     for (auto pid : garbageIDs)
    //     {
    //         net::message<GameMsg> m;
    //         m.header.id = RemoteMessage:REMOTE_CLIENT;
    //         m << pid;
    //         std::cout << "Removing " << pid << "\n";
    //         MessageAllClients(m);
    //     }
    //     garbageIDs.clear();
    // }

    // switch (msg.header.id)
    // {

    // }
}