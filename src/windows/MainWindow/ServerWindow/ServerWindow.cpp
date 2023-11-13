#include "ServerWindow.hpp"
#include "../../../utils/FileNameGenerator/FileNameGenerator.hpp"
#include "../../constant.hpp"
#include <algorithm>
#include <iterator>
#include <chrono>

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

    // Ở đâu đó trong constructor hoặc khởi tạo timer
    secondTimer = new wxTimer(this, 3);
    this->Bind(wxEVT_TIMER, &ServerWindow::OnSecondTimer, this, secondTimer->GetId());
    secondTimer->Start(1000);  // Đặt timer chạy mỗi giây (1000ms)

    QueueTimer = new wxTimer(this, 5);
    this->Bind(wxEVT_TIMER, &ServerWindow::OnUpdateWindow, this, QueueTimer->GetId());
    QueueTimer->Start(DELAY_MS);
    // this->SetSizerAndFit(MainSizer);
    this->Center();
}

void ServerWindow::OnUpdateWindow(wxTimerEvent& event) {
    IServer<RemoteMessage>::Update(-1, true);
}

void ServerWindow::takeScreenshot(int imgWidth, int imgHeight)
{
    // Capture Screen
    // wxRect frameRect = CapturePanel->GetRect();
    // frameRect = wxRect(wxGetClientDisplayRect());

    // đây là cái thằng lưu giữ tấm chụp màn hình
    // wxGetDisplaySize() giúp lấy kích cỡ toàn màn hình
    screenshot.Create(wxGetDisplaySize());
    // wxBitmap screenshot(frameRect.GetSize());

    // Lấy kích thước toàn bộ màn hình
    screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    // int imgWidth = LogPanel->GetSize().GetWidth();
    // int imgHeight = LogPanel->GetSize().GetHeight();

    // Tính toán tỷ lệ scale
    double scaleX = static_cast<double>(imgWidth) / screenWidth;
    double scaleY = static_cast<double>(imgHeight) / screenHeight;

    // biến này đóng vai trò buffer trung gian để thao tác trên screenshot
    // memDC(screenshot);
    memDC.SelectObject(screenshot);

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

        // using std::chrono::high_resolution_clock;
        // using std::chrono::duration_cast;
        // using std::chrono::duration;
        // using std::chrono::milliseconds;


        /* Getting number of milliseconds as an integer. */

        auto t1 = std::chrono::high_resolution_clock::now();
        takeScreenshot(CONFIG_UI::NORMAL_WINDOW.GetWidth(), CONFIG_UI::NORMAL_WINDOW.GetHeight());
        // takeScreenshot(160, 90);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int_12    = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        // textCtrl->AppendText(wxString::Format(wxT("Take screenshot takes: %lld ms.\n"), ms_int_12.count()));

        // takeScreenshot();
        wxImage image = screenshot.ConvertToImage();
        auto t3 = std::chrono::high_resolution_clock::now();
        auto ms_int_23    = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
        // textCtrl->AppendText(wxString::Format(wxT("Convert image takes: %lld ms.\n"), ms_int_23.count()));

        // wxImage image2 = oldscreenshot.ConvertToImage();

        // Đặt mức chất lượng cho ảnh (giá trị từ 0 đến 100)
        // image.SetOption(wxIMAGE_OPTION_QUALITY, 10);

        // if (image.GetSize() == image2.GetSize()) {
        //     size_t dataSize = image.GetWidth() * image.GetHeight() * 3;
        //     if (memcmp(image.GetData(), image2.GetData(), dataSize) == 0)
        //         return;
        // }
        wxMemoryOutputStream memStream;
        // image.Rescale(CONFIG_UI::NORMAL_WINDOW.GetWidth(), CONFIG_UI::NORMAL_WINDOW.GetHeight());
        image.SaveFile(memStream, wxBITMAP_TYPE_JPEG);
        auto t4 = std::chrono::high_resolution_clock::now();
        auto ms_int_34    = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
        // textCtrl->AppendText(wxString::Format(wxT("Save file takes: %lld ms.\n"), ms_int_34.count()));

        // Lấy dữ liệu nén
        size_t dataSize = memStream.GetSize();
        // auto dataBuffer = std::make_shared<std::vector<uint8_t>>(dataSize);

        // memStream.CopyTo(&(*dataBuffer)[0], dataSize);

        // Đóng gói vào message
        auto msg = std::make_shared<net::message<RemoteMessage>>();
        msg->header.id = RemoteMessage::SERVER_UPDATE;
        msg->header.size = dataSize;
        // msg->body.assign(dataBuffer->begin(), dataBuffer->end());
        // msg->body.assign(image.GetData(), image.GetData() + dataSize);
        const char *dataBuffer = static_cast<const char *>(memStream.GetOutputStreamBuffer()->GetBufferStart());
        msg->body.assign(dataBuffer, dataBuffer + dataSize);

        auto t5 = std::chrono::high_resolution_clock::now();
        auto ms_int_45    = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4);
        // textCtrl->AppendText(wxString::Format(wxT("Assign data to msg takes: %lld ms.\n"), ms_int_45.count()));

        MessageAllClients(*msg);
        auto t6 = std::chrono::high_resolution_clock::now();
        auto ms_int_56    = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5);
        // textCtrl->AppendText(wxString::Format(wxT("Send message takes: %lld ms.\n"), ms_int_56.count()));

        auto ms_int_61   = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t1);
        // textCtrl->AppendText(wxString::Format(wxT("All server operations take: %lld ms.\n"), ms_int_61.count()));
        // textCtrl->AppendText(wxString::Format(wxT("Data sent: %llu bytes.\n\n\n"), dataSize));

        // Gửi message đến tất cả clients
        // std::thread sendThread([this, msg]() {
        // });
        // sendThread.detach(); 

        // oldscreenshot = screenshot;
        

        // Tăng biến đếm
        ++imagesSentThisSecond;
    }
}

// void ServerWindow::CaptureAndSend() {
//     const int numThreads = 1;
//         std::vector<std::thread> threads;

//         for (int i = 0; i < numThreads; ++i) {
//             threads.emplace_back(&ServerWindow::CaptureAndSend, this);
//         }

//         // Đợi cho tất cả các thread kết thúc
//         for (auto& thread : threads) {
//             thread.join();
//         }

//         // Tính toán và hiển thị thông tin thống kê nếu cần
//         // ...
// }

// Khi timer đếm giây chạy
void ServerWindow::OnSecondTimer(wxTimerEvent& event)
{
    // In thông tin thống kê và đặt biến đếm về 0
    // textCtrl->AppendText(wxString::Format(wxT("Images sent this second: %d\n"), imagesSentThisSecond));
    imagesSentThisSecond = 0;
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

    textCtrl->AppendText(wxString::Format(wxT("Some shit msg is received")));
    switch (msg.header.id) {

        case RemoteMessage::MouseClick: {
            int x, y;
            int32_t button;
            msg >> x >> y >> button;
            // Giả lập click chuột
            
            textCtrl->AppendText(wxString::Format(wxT("Some Click activate in (%d, %d).\n"), x, y));
            if(button == 1)
                textCtrl->AppendText(wxString::Format(wxT("Left Click activate in (%d, %d).\n"), x, y));
            else if(button == 2) 
                textCtrl->AppendText(wxString::Format(wxT("Right Click activate in (%d, %d).\n"), x, y));
            break;
        }
        case RemoteMessage::KeyPress: {
            int32_t key;
            bool is_down;
            msg >> key >> is_down;
            // Giả lập nhấn phím
            break;
        }
    }
}

