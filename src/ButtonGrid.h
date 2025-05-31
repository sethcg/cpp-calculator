#pragma once
#include <wx/wx.h>

inline const int BUTTON_CONTAINER_ROWS = 5;
inline const int BUTTON_CONTAINER_COLS = 4;

class ButtonGrid : public wxGridSizer
{
public:
    ButtonGrid(wxWindow *parent, wxTextCtrl *textControl);

private:
    void CreateButton(wxGridSizer *container, CalculatorButton *button);
};