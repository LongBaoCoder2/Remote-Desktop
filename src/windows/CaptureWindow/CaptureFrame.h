#include <wx/wx.h>
#include <wx/bitmap.h>
#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include "../BasicTextWindow/BasicTextFrame.hpp"


class CaptureFrame : public wxFrame
{
public:
    CaptureFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:

    // class MyBufferedPanel : public wxPanel
    // {
    // public:
    //     MyBufferedPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
        


    // private:
    //     void OnPaint(wxPaintEvent& event);
    // };
    const int DELAY_MS = 0;
    bool CAPTURING = false;

    wxPanel *CapturePanel = nullptr;
    wxPanel *ButtonPanel = nullptr;
    BasicTextFrame* CaptureFrameLogger = nullptr;


    wxButton *startCaptureBtn = nullptr;
    wxButton *stopCaptureBtn = nullptr;
    wxButton *saveCaptureBtn = nullptr;

    wxTimer *timer;
    wxTimer* secondTimer;
    
    wxScreenDC screenDC;
    wxMemoryDC memDC;
    wxBitmap screenshot;
    wxClientDC* clientDC;

    // wxPaintDC* paintDC;
    // wxBufferedDC* bufferedDC;


    int imagesDisplayedThisSecond = 0;

    // void OnPaint(wxPaintEvent& event);

    void OnCaptureScreen(wxTimerEvent &);
    // void OnPaint(wxPaintEvent &event);
    void OnSecondTimer(wxTimerEvent& event);

    void OnStartPress(wxCommandEvent &);
    void OnStopPress(wxCommandEvent &);
    void onSavePress(wxCommandEvent &);
    void takeScreenshot(int imgWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X), int imgHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
};
