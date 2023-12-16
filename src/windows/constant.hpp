#pragma once


#include <wx/wx.h>
#include <wx/gdicmn.h>
#include <wx/colour.h>
#include <string>

namespace CONFIG_UI
{
    const int screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    const int screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
    // Size of window | frame
    const wxSize VERY_SMALL_WINDOW = wxSize(screenWidth / 4, screenHeight / 2);
    const wxSize NORMAL_WINDOW = wxSize(screenWidth / 5 * 4, screenHeight / 5 * 4);
    const wxSize SMALL_WINDOW = wxSize(screenWidth / 5 * 2, screenHeight / 5 * 2);
    const wxSize MEDIUM_WINDOW = wxSize(screenWidth / 5 * 3, screenHeight / 5 * 3);

    const wxSize CLIENT_WINDOW_SIZE = wxSize(1280, 720);

    // Size of control
    const wxSize NAVIGATION_SIZE = wxSize(screenWidth / 6.5, screenHeight / 5 * 4);
    const wxSize PRIMARY_BUTTON_SIZE = wxSize(screenWidth / 8.75, 40);

    // Configuration of color
    const wxColour PRIMARY_LIGHT_COLOR = wxColour(237, 238, 241);
    const wxColour SECONDARY_LIGHT_COLOR = wxColour(255, 255, 255);

    // Configuration of User Panel Size
    const wxSize PRIMARY_USER_PANEL_SIZE = wxSize(screenWidth / 33, screenWidth / 33);
    const wxSize SECONDARY_USER_PANEL_SIZE = wxSize(40, 40);

    // Configuration of Font size
    const int PRIMARY_FONT_SIZE = 18;
    const int SECONDARY_FONT_SIZE = 10;

    const wxColour PRIMARY_DARK_COLOR = wxColour(15, 23, 36);
}

namespace CONFIG_APP
{
    const wxString NAME_APP = "Remote Desktop";

    const std::string USER_ICON_PATH = "assets/user_icon.png";
    const int ID_TOOL_DISCONNECT = 1001;
    const int ID_TOOL_CAPTURE = 1002;
    const int ID_TOOL_KEYLOG = 1003;
    const int ID_TOOL_HOOK = 1004;
    const int ID_TOOL_UNHOOK = 1005;

    const uint16_t IMAGE_PORT = 8282;
    const uint16_t EVENT_PORT = 8285;
    const uint16_t PORT = 8288;
};