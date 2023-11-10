#include "ServerWindow.hpp"
#include "../../../utils/FileNameGenerator/FileNameGenerator.hpp"
#include <algorithm>
#include <iterator>

ServerWindow::ServerWindow(uint16_t port)
    : wxFrame(nullptr, wxID_ANY, "Server Window", wxDefaultPosition, wxSize(1366, 768)), net::IServer<RemoteMessage>(port)
{
    Start();

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

void ServerWindow::OnCaptureWindow(wxTimerEvent &event)
{
    if (nCountUser)
    {
        takeScreenshot();
        wxImage image = screenshot.ConvertToImage();

        image = image.Rescale(1280, 960, wxIMAGE_QUALITY_HIGH);

        // Nén hình ảnh thành PNG
        wxMemoryOutputStream memStream;
        image.SaveFile(memStream, wxBITMAP_TYPE_PNG);

        // Lấy dữ liệu nén
        // wxStreamBuffer* memBuffer = memStream.GetOutputStreamBuffer();
        // size_t dataSize = memBuffer->GetDataLeft();
        // size_t dataSize = memStream.GetSize();
        size_t dataSize = 20;
        auto *dataBuffer = new uint8_t[dataSize + 10];
        for (int i = 0; i < 20; ++i) {
            dataBuffer[i] = 1;
        }
        // memStream.CopyTo(dataBuffer, dataSize);

        // wxMemoryInputStream mem1Stream(dataBuffer, dataSize);
        // image.LoadFile(mem1Stream, wxBITMAP_TYPE_PNG);
        // image.SaveFile("abc.png", wxBITMAP_TYPE_PNG);

        // Đóng gói vào message
        net::message<RemoteMessage> msg;
        msg.header.id = RemoteMessage::SERVER_UPDATE;
        msg.header.size = dataSize;
        std::copy(dataBuffer, dataBuffer + dataSize, std::back_inserter(msg.body));
        // msg.body.assign(dataBuffer, dataBuffer + dataSize);

        textCtrl->AppendText(wxString::Format(wxT("Data sent: %llu bytes.\n"), dataSize));

        // Gửi message đến tất cả clients
        MessageAllClients(msg);

        // Dọn dẹp bộ nhớ
        delete[] dataBuffer;
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
        timer->Start(DELAY_MS);
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

void ServerWindow::OnMessage(std::shared_ptr<net::session<RemoteMessage>> client, net::message<RemoteMessage> &msg)
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