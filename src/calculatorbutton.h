#pragma once
#include <wx/wx.h>

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxWindowID &id, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor);
};