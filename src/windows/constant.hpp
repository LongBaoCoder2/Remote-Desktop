#pragma once

#include <wx/gdicmn.h>
#include <wx/colour.h>
#include <string>

namespace CONFIG_UI
{
    // Size of window | frame
    const wxSize VERY_SMALL_WINDOW = wxSize(1920 / 4, 1080 / 2);
    const wxSize NORMAL_WINDOW = wxSize(1600, 900);
    const wxSize SMALL_WINDOW = wxSize(960, 540);
    const wxSize MEDIUM_WINDOW = wxSize(1280, 720);

    // Size of control
    const wxSize NAVIGATION_SIZE = wxSize(256, 900);
    const wxSize PRIMARY_BUTTON_SIZE = wxSize(220, 42);

    // Configuration of color
    const wxColour PRIMARY_LIGHT_COLOR = wxColour(237, 238, 241);
    const wxColour SECONDARY_LIGHT_COLOR = wxColour(255, 255, 255);


    const wxColour PRIMARY_DARK_COLOR = wxColour(15, 23, 36);
}

namespace CONFIG_APP
{
    const wxString NAME_APP = "Remote Desktop";

    const std::string USER_ICON_PATH = "assets/user_icon.png";
};