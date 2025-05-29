#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <wx/wx.h>
#include <colors/colors.h>
#include <calculatorbutton.h>
#include <buttoncontainer.h>

ButtonContainer::ButtonContainer(wxWindow *parent, wxTextCtrl *textControl) : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(5);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);

    std::vector<CalculatorButton *> buttons({
        new CalculatorButton(parent, wxID_ANY, textControl, "\u0025", DARK_GRAY),                                           // %, PERCENTAGE
        new CalculatorButton(parent, wxID_ANY, textControl, "CE", DARK_GRAY),                                               // CE, CLEAR ENTRY
        new CalculatorButton(parent, wxID_ANY, textControl, "C", DARK_GRAY),                                                // C, CLEAR (ALL)
        new CalculatorButton(parent, wxID_ANY, textControl, "DEL", DARK_GRAY),                                              // DEL, DELETE DIGIT
        new CalculatorButton(parent, wxID_ANY, textControl, wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D"), DARK_GRAY), // FRACTION
        new CalculatorButton(parent, wxID_ANY, textControl, wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2"), DARK_GRAY),     // SQUARE
        new CalculatorButton(parent, wxID_ANY, textControl, wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"), DARK_GRAY), // SQUARE ROOT
        new CalculatorButton(parent, wxID_ANY, textControl, "\u00F7", DARK_GRAY),                                           // DIVIDE
        new CalculatorButton(parent, wxID_ANY, textControl, "7", GRAY),                                                     // 7
        new CalculatorButton(parent, wxID_ANY, textControl, "8", GRAY),                                                     // 8
        new CalculatorButton(parent, wxID_ANY, textControl, "9", GRAY),                                                     // 9
        new CalculatorButton(parent, wxID_ANY, textControl, "x", DARK_GRAY),                                                // MULTIPLY
        new CalculatorButton(parent, wxID_ANY, textControl, "4", GRAY),                                                     // 4
        new CalculatorButton(parent, wxID_ANY, textControl, "5", GRAY),                                                     // 5
        new CalculatorButton(parent, wxID_ANY, textControl, "6", GRAY),                                                     // 6
        new CalculatorButton(parent, wxID_ANY, textControl, "\u002D", DARK_GRAY),                                           // SUBTRACT
        new CalculatorButton(parent, wxID_ANY, textControl, "1", GRAY),                                                     // 1
        new CalculatorButton(parent, wxID_ANY, textControl, "2", GRAY),                                                     // 2
        new CalculatorButton(parent, wxID_ANY, textControl, "3", GRAY),                                                     // 3
        new CalculatorButton(parent, wxID_ANY, textControl, "\u002D", DARK_GRAY),                                           // ADD
        new CalculatorButton(parent, wxID_ANY, textControl, wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B"), GRAY),  // NEGATE (POSITIVE/NEGATIVE)
        new CalculatorButton(parent, wxID_ANY, textControl, "0", GRAY),                                                     // 0
        new CalculatorButton(parent, wxID_ANY, textControl, "\u002E", GRAY),                                                // DECIMAL
        new CalculatorButton(parent, wxID_ANY, textControl, "\u003D", LIGHT_BLUE, *wxBLACK),                                // EQUAL
    });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonContainer::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}