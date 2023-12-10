
#include <algorithm>
#include <chrono>
#include <iterator>

#include "../../../utils/FileNameGenerator/FileNameGenerator.hpp"
#include "../../constant.hpp"
#include "ServerWindow.hpp"
#include <windows.h>


ServerWindow::ServerWindow()
    : wxFrame(nullptr, wxID_ANY, "Server Window", wxDefaultPosition, wxSize(720, 480)), net::IServer<RemoteMessage>()
{
    Start();

    // LogPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1366,
    // 768));
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                              wxDefaultSize,
                              wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

    // Sắp xếp layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(sizer);
    textCtrl->AppendText("Server is running.\n");

    timer = new wxTimer(this, 2);
    this->Bind(wxEVT_TIMER, &ServerWindow::OnCaptureWindow, this,
               timer->GetId());
    // timer->Start(DELAY_MS);

    this->Center();

    // Lấy kích thước toàn bộ màn hình
    screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    m_updateMess = std::thread([this]
        {
            while (true) {
                IServer<RemoteMessage>::Update(-1, true);
            }
        }
    );
}


void ServerWindow::takeScreenshot(int imgWidth, int imgHeight) {
    // Capture Screen
    // wxRect frameRect = CapturePanel->GetRect();
    // frameRect = wxRect(wxGetClientDisplayRect());

    // đây là cái thằng lưu giữ tấm chụp màn hình
    // wxGetDisplaySize() giúp lấy kích cỡ toàn màn hình
    screenshot.Create(wxGetDisplaySize());
    // wxBitmap screenshot(frameRect.GetSize());

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
        /* Getting number of milliseconds as an integer. */
        takeScreenshot(CONFIG_UI::CLIENT_WINDOW_SIZE.GetWidth(), CONFIG_UI::CLIENT_WINDOW_SIZE.GetHeight());

        wxImage image = screenshot.ConvertToImage();
        // Đặt mức chất lượng cho ảnh (giá trị từ 0 đến 100)
        // image.SetOption(wxIMAGE_OPTION_QUALITY, 10);

        wxMemoryOutputStream memStream;
        // image.Rescale(CONFIG_UI::NORMAL_WINDOW.GetWidth(),
        // CONFIG_UI::NORMAL_WINDOW.GetHeight());
        image.SaveFile(memStream, wxBITMAP_TYPE_JPEG);

        // Lấy dữ liệu nén
        size_t dataSize = memStream.GetSize();


        // Đóng gói vào message
        auto msg = std::make_shared<net::message<RemoteMessage>>();
        msg->header.id = RemoteMessage::SERVER_UPDATE;
        msg->header.size = dataSize;

        const unsigned char* dataBuffer = static_cast<const unsigned char*>(memStream.GetOutputStreamBuffer()->GetBufferStart());
        msg->body.assign(dataBuffer, dataBuffer + dataSize);

        MessageAllClients(*msg);
    }
}



bool ServerWindow::OnClientConnect(
    std::shared_ptr<net::session<RemoteMessage>> client) {
    // At this time, we will accept all
    // Remember: We need authentication later

    nCountUser++;
    OnClientValidated(client);
    textCtrl->AppendText(
        wxString::Format(wxT("A client has connected to server!\n")));

    if (nCountUser == 1) {
        if (wxThread::IsMain()) {
            timer->Start(DELAY_MS);
        } else {
            wxTheApp->CallAfter([this]() { timer->Start(DELAY_MS); });
        }

    }
    return true;
}

void ServerWindow::OnClientValidated(
    std::shared_ptr<net::session<RemoteMessage>> client) {
    // Client passed validation check, so send them a message informing
    // them they can continue to communicate
    net::message<RemoteMessage> msg;
    msg.header.id = RemoteMessage::SERVER_ACCEPT;
    client->Send(msg);
}

void ServerWindow::OnClientDisconnect(
    std::shared_ptr<net::session<RemoteMessage>> client) {
    if (client) {
        nCountUser--;

        if (nCountUser == 0) {
            timer->Stop();
        }
    }
}

void ServerWindow::OnMessage(
    std::shared_ptr<net::session<RemoteMessage>> client,
    net::message<RemoteMessage>& msg) {
    switch (msg.header.id) {

    case RemoteMessage::MouseClick: {
        msg >> button >> y >> x;

        fx = x * (65535.0f / (screenWidth - 1));
        fy = y * (65535.0f / (screenHeight - 1));


        //textCtrl->AppendText(wxString::Format(wxT("(%d, %d).\n"), screenWidth, screenHeight));
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = fx;
        Input.mi.dy = fy;
        SendInput(1, &Input, sizeof(INPUT));

        switch (button) {
        case wxMOUSE_BTN_LEFT:
            //textCtrl->AppendText(wxString::Format(wxT("Left Click activate in (%f, %f).\n"), fx, fy));
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        case wxMOUSE_BTN_RIGHT:
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        case wxMOUSE_BTN_MIDDLE:
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        default:
            // Handle other button values if necessary
            break;
        }
        break;
    }

    case RemoteMessage::MouseUnClick: {
        msg >> button >> y >> x;

        fx = x * (65535.0f / (screenWidth - 1));
        fy = y * (65535.0f / (screenHeight - 1));


        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = fx;
        Input.mi.dy = fy;
        SendInput(1, &Input, sizeof(INPUT));

        switch (button) {
        case wxMOUSE_BTN_LEFT:
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        case wxMOUSE_BTN_RIGHT:
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        case wxMOUSE_BTN_MIDDLE:
            ZeroMemory(&Input, sizeof(INPUT));
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            SendInput(1, &Input, sizeof(INPUT));
            break;

        default:
            // Handle other button values if necessary
            break;
        }
        break;
    }

    case RemoteMessage::MouseMove: {
        msg >> y >> x; // Extract coordinates

        fx = x * (65535.0f / (screenWidth - 1));
        fy = y * (65535.0f / (screenHeight - 1));
        // Simulate mouse move
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = fx;
        Input.mi.dy = fy;
        SendInput(1, &Input, sizeof(INPUT));
        break;
    }

    case RemoteMessage::DoubleClick: {
        msg >> button >> y >> x; // Extract coordinates and button


        fx = x * (65535.0f / (screenWidth - 1));
        fy = y * (65535.0f / (screenHeight - 1));
        // Simulate double click
        INPUT Input[2] = {};
        Input[0].type = Input[1].type = INPUT_MOUSE;
        Input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        Input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        SendInput(2, Input, sizeof(INPUT));
        break;
    }

    case RemoteMessage::MouseWheel: {
        msg >> delta >> y >> x; // Extract coordinates and wheel delta

        fx = x * (65535.0f / (screenWidth - 1));
        fy = y * (65535.0f / (screenHeight - 1));
        // Simulate mouse wheel scroll
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        Input.mi.mouseData = delta;
        SendInput(1, &Input, sizeof(INPUT));
        break;
    }


    case RemoteMessage::KeyPress: {
        uint32_t rawKeyCode;
        msg >> rawKeyCode;  // Trích xuất mã phím và trạng thái

        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = static_cast<WORD>(rawKeyCode);  // Mã phím

        SendInput(1, &input, sizeof(INPUT));
        break;
    }

    case RemoteMessage::KeyRelease: {
        uint32_t rawKeyCode;
        msg >> rawKeyCode;  // Trích xuất mã phím và trạng thái

        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = static_cast<WORD>(rawKeyCode);  // Mã phím

        input.ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(1, &input, sizeof(INPUT));
        break;
    }

    }
}


void ServerWindow::OnClose(wxCloseEvent& event) {
    // Xử lý khi cửa sổ được đóng
    // Hoặc hỏi người dùng trước khi đóng cửa sổ
    int answer = wxMessageBox(
        "Are you sure to close this Window?\nClosing the window also ends "
        "current session.",
        "Close Window", wxYES_NO | wxICON_QUESTION, this);

    if (answer == wxYES) {
        net::IServer<RemoteMessage>::Stop();
        event.Skip();  // Đóng cửa sổ
    } else {
        event.Veto();  // Không đóng cửa sổ
    }
}

ServerWindow::~ServerWindow() {
    // textCtrl->Destroy();
    net::IServer<RemoteMessage>::Stop();
}