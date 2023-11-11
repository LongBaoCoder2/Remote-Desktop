#pragma once

#include <wx/wx.h>
#include <wx/bitmap.h>
#include <wx/timer.h>
#include <wx/dcbuffer.h>

class CaptureFrame : public wxFrame
{
public:
    CaptureFrame(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    const int DELAY_MS = 7;
    bool CAPTURING = false;

    wxPanel* CapturePanel = nullptr;
    wxPanel* ButtonPanel = nullptr;

    wxButton* startCaptureBtn = nullptr;
    wxButton* stopCaptureBtn = nullptr;
    wxButton* saveCaptureBtn = nullptr;

    wxTimer* timer;
    wxScreenDC screenDC;
    wxBitmap screenshot;

    // void OnPaint(wxPaintEvent& event);

    void OnCaptureScreen(wxTimerEvent&);

    void OnStartPress(wxCommandEvent&);
    void OnStopPress(wxCommandEvent&);
    void onSavePress(wxCommandEvent&);
    void takeScreenshot(int imgWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X), int imgHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
};
