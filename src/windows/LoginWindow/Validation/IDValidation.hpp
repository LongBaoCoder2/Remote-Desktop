#pragma once

#include "Validation.hpp"
#include <wx/textctrl.h>

class IDValidation : public AbstractValidation
{
public:
    IDValidation(wxStaticText *validationMsg, wxString *val = nullptr, bool isAdmin = true)
        : AbstractValidation(validationMsg, val)
    {
        this->isAdmin = isAdmin;
    }

    IDValidation(const IDValidation &idValidation)
        : AbstractValidation(idValidation)
    {
        this->isAdmin = idValidation.isAdmin;
    }

    virtual wxObject *Clone() const override { return new IDValidation(*this); }

private:
    const size_t MAX_SIZE = 8;
    const size_t MIN_SIZE = 2;

    bool isAdmin;

    std::pair<bool, wxString> CheckValidity(const wxString &str) const override
    {
        auto s = str.ToStdString();

        if (isAdmin)
        {

            if (s.compare("admin") == 0)
            {
                return {true, "ID is valid"};
            }
            else
            {
                return {false, "ID Admin is incorrect"};
            }
        }

        else
        {
            bool hasDigitAndLetter = std::all_of(std::begin(s), std::end(s), [](unsigned char c)
                                                 { return std::isdigit(c) || std::isalpha(c); });
            if (!hasDigitAndLetter)
            {
                return {false, "ID must contain all digit or letter"};
            }
            else if (s.size() < MIN_SIZE || s.size() > MAX_SIZE)
            {
                return {false, wxString::Format("ID length must be betwwen %d and %d.", MIN_SIZE, MAX_SIZE)};
            }

            return {true, "ID is valid"};
        }
    }
};