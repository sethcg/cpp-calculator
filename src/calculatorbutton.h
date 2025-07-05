#pragma once
#include <wx/wx.h>
#include <constants/Colors.h>

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxString &label,
                     const wxColor &backgroundColor = COLOR_GRAY, const wxColor &textColor = *wxWHITE);
};