#pragma once

#include <wx/wx.h>
#include "../../constant.hpp"

class SettingsFrame : public wxFrame {
public:
    SettingsFrame(const wxString& title = "Remote Desktop options", const wxPoint &pos = wxDefaultPosition, const wxSize &size = CONFIG_UI::SMALL_WINDOW);

    void OnSidebarSelection(wxCommandEvent& event);

    void ShowDetailViewForItem(const wxString& itemText);

private:
    enum class SidebarItem {
        GENERAL,
        ACCOUNT,
        SECURITY,
        REMOTE_CONTROL,
        MEETING,
        AUDIO_CONFERENCING,
        VIDEO,
        CUSTOM_INVITATION,
        ADVANCED
    };
    wxPanel* detailView;
    wxListBox* sidebar;
    wxBoxSizer* sizer;

    void ClearPanelContents(wxWindow* panel);
    void ShowDetailViewForGeneral();
    void ShowDetailViewForAccount();
    void ShowDetailViewForSecurity();
    void ShowDetailViewForRemoteControl();
    void ShowDetailViewForMeeting();
    void ShowDetailViewForAudioConferencing();
    void ShowDetailViewForVideo();
    void ShowDetailViewForCustomInvitation();
    void ShowDetailViewForAdvanced();
};