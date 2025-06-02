#pragma once
#include <wx/wx.h>

inline const int BUTTON_CONTAINER_ROWS = 5;
inline const int BUTTON_CONTAINER_COLS = 4;

const enum OperationType {
    NONE,
    MULTIPLY,
    DIVIDE,
    SUBTRACT,
    ADD
};

class ButtonGrid : public wxGridSizer
{
public:
    ButtonGrid(wxWindow *parent, wxTextCtrl *textControl, OperationType *operationType);

private:
    void CreateButton(wxGridSizer *container, CalculatorButton *button);

    void AppendDigit(wxTextCtrl *textControl, std::string buttonValue);
    void DeleteDigit(wxTextCtrl *textControl);
};