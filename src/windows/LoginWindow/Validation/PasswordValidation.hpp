#pragma once

#include "Validation.hpp"
#include <wx/textctrl.h>

class PasswordValidation : public AbstractValidation
{
public:
    PasswordValidation(wxStaticText *validationMsg, wxTextCtrl *sourceCtrl)
        : AbstractValidation(validationMsg), sourceCtrl(sourceCtrl)
    {
    }

    PasswordValidation(const PasswordValidation &pwValidation)
        : AbstractValidation(pwValidation)
    {
        sourceCtrl = pwValidation.sourceCtrl;
    }

    virtual wxObject *Clone() const override { return new PasswordValidation(*this); }

private:
    wxTextCtrl *sourceCtrl;

    std::pair<bool, wxString> CheckValidity(const wxString &str) const override
    {
        auto s = str.ToStdString();

        if (s.compare("admin") == 0)
        {
            return {true, "Password is valid"};
        }
        else
        {
            return {false, "Password Admin is incorrect"};
        }
    }
};