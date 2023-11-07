#pragma once
#include <wx/validate.h>
#include <wx/stattext.h>
#include <wx/textentry.h>

class AbstractValidation : public wxValidator
{
public:
    AbstractValidation(wxStaticText *msgLabel, wxString *val = nullptr)
        : value(val), validationMsgLabel(msgLabel)
    {
        SetupEvents();
    }

    AbstractValidation(const AbstractValidation &validator)
        : wxValidator(validator)
    {
        value = validator.value;
        validationMsgLabel = validator.validationMsgLabel;

        SetupEvents(); // this is why we need copy constructor
    }

    virtual ~AbstractValidation() {}

    virtual wxObject *Clone() const override = 0;

    bool TransferFromWindow() override
    {
        if (value)
        {
            wxTextEntry *const text = GetTextEntry();
            *value = text->GetValue();
        }

        return true;
    }

    bool TransferToWindow() override
    {
        if (value)
        {
            wxTextEntry *const text = GetTextEntry();
            text->SetValue(*value);
        }

        return true;
    }

    virtual bool Validate(wxWindow *parent) override
    {
        const auto &pairValid = CheckValidity(GetTextEntry()->GetValue());
        return pairValid.first;
    }

    void UpdateValidationLabel()
    {
        auto pairValid = CheckValidity(GetTextEntry()->GetValue());

        validationMsgLabel->SetLabel(pairValid.second);
        validationMsgLabel->SetForegroundColour(
            pairValid.first ? wxColor(100, 200, 100) : wxColor(200, 100, 100));

        validationMsgLabel->Refresh(); // needed for Windows to update the color
    }

protected:
    virtual std::pair<bool, wxString> CheckValidity(const wxString &str) const = 0;

    virtual void SetupEvents() { Bind(wxEVT_TEXT, &AbstractValidation::OnText, this); }
    virtual void OnText(wxCommandEvent &e)
    {
        UpdateValidationLabel();
        e.Skip();
    }

    wxTextEntry *GetTextEntry() const { return dynamic_cast<wxTextEntry *>(GetWindow()); }

private:
    wxStaticText *validationMsgLabel;
    wxString *value;
};
