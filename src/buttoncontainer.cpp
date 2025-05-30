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
    std::vector<CalculatorButton *>
        buttons({
            // %, PERCENTAGE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u0025"); }, parent, textControl, wxID_ANY, "\u0025", DARK_GRAY, *wxWHITE),
            // CE, CLEAR ENTRY
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("CE"); }, parent, textControl, wxID_ANY, "CE", DARK_GRAY, *wxWHITE),
            // C, CLEAR (ALL)
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("C"); }, parent, textControl, wxID_ANY, "C", DARK_GRAY, *wxWHITE),
            // DEL, DELETE DIGIT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("DEL"); }, parent, textControl, wxID_ANY, "DEL", DARK_GRAY, *wxWHITE),
            // FRACTION
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D")); }, parent, textControl, wxID_ANY, wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D"), DARK_GRAY, *wxWHITE),
            // SQUARE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2")); }, parent, textControl, wxID_ANY, wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2"), DARK_GRAY, *wxWHITE),
            // SQUARE ROOT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D")); }, parent, textControl, wxID_ANY, wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"), DARK_GRAY, *wxWHITE),
            // DIVIDE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u00F7"); }, parent, textControl, wxID_ANY, "\u00F7", DARK_GRAY, *wxWHITE),
            // 7
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("7"); }, parent, textControl, wxID_ANY, "7", GRAY, *wxWHITE),
            // 8
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("8"); }, parent, textControl, wxID_ANY, "8", GRAY, *wxWHITE),
            // 9
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("9"); }, parent, textControl, wxID_ANY, "9", GRAY, *wxWHITE),
            // MULTIPLY
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("x"); }, parent, textControl, wxID_ANY, "x", DARK_GRAY, *wxWHITE),
            // 4
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("4"); }, parent, textControl, wxID_ANY, "4", GRAY, *wxWHITE),
            // 5
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("5"); }, parent, textControl, wxID_ANY, "5", GRAY, *wxWHITE),
            // 6
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("6"); }, parent, textControl, wxID_ANY, "6", GRAY, *wxWHITE),
            // SUBTRACT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u002D"); }, parent, textControl, wxID_ANY, "\u002D", DARK_GRAY, *wxWHITE),
            // 1
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("1"); }, parent, textControl, wxID_ANY, "1", GRAY, *wxWHITE),
            // 2
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("2"); }, parent, textControl, wxID_ANY, "2", GRAY, *wxWHITE),
            // 3
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("3"); }, parent, textControl, wxID_ANY, "3", GRAY, *wxWHITE),
            // ADD
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u00B1"); }, parent, textControl, wxID_ANY, "\u00B1", DARK_GRAY, *wxWHITE),
            // NEGATE (POSITIVE/NEGATIVE)
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B")); }, parent, textControl, wxID_ANY, wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B"), GRAY, *wxWHITE),
            // 0
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("0"); }, parent, textControl, wxID_ANY, "0", GRAY, *wxWHITE),
            // DECIMAL
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u002E"); }, parent, textControl, wxID_ANY, "\u002E", GRAY, *wxWHITE),
            // EQUAL
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue("\u003D"); }, parent, textControl, wxID_ANY, "\u003D", LIGHT_BLUE, *wxBLACK),
        });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonContainer::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}