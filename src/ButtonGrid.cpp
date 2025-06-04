#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <wx/wx.h>
#include <colors/Colors.h>
#include <CalculatorButton.h>
#include <ButtonGrid.h>

ButtonGrid::ButtonGrid(wxWindow *parent, wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType) : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(8);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);

    std::vector<CalculatorButton *>
        buttons({
            // AC, CLEAR (ALL)
            new CalculatorButton([this, operationType, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleClear(lastTextControl, currentTextControl, operationType); }, parent, currentTextControl, BUTTON_STRING_ALL_CLEAR, COLOR_RED),
            // DEL, DELETE DIGIT
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDelete(currentTextControl); }, parent, currentTextControl, BUTTON_STRING_DELETE),
            // %, PERCENTAGE
            new CalculatorButton([]() -> void
                                 {
                                     // TODO: IMPLEMENT
                                 },
                                 parent, currentTextControl, BUTTON_STRING_PERCENT),
            // MULTIPLY
            new CalculatorButton([this, operationType, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, operationType, OperationType::MULTIPLY); }, parent, currentTextControl, BUTTON_STRING_MULTIPLY),
            // 7
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_SEVEN_DIGIT); }, parent, currentTextControl, BUTTON_STRING_SEVEN_DIGIT),
            // 8
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_EIGHT_DIGIT); }, parent, currentTextControl, BUTTON_STRING_EIGHT_DIGIT),
            // 9
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_NINE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_NINE_DIGIT),
            // DIVIDE
            new CalculatorButton([this, operationType, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, operationType, OperationType::DIVIDE); }, parent, currentTextControl, BUTTON_STRING_DIVIDE),
            // 4
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_FOUR_DIGIT); }, parent, currentTextControl, BUTTON_STRING_FOUR_DIGIT),
            // 5
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_FIVE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_FIVE_DIGIT),
            // 6
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_SIX_DIGIT); }, parent, currentTextControl, BUTTON_STRING_SIX_DIGIT),
            // SUBTRACT
            new CalculatorButton([this, operationType, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, operationType, OperationType::SUBTRACT); }, parent, currentTextControl, BUTTON_STRING_SUBTRACT),
            // 1
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_ONE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_ONE_DIGIT),
            // 2
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_TWO_DIGIT); }, parent, currentTextControl, BUTTON_STRING_TWO_DIGIT),
            // 3
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_THREE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_THREE_DIGIT),
            // ADD
            new CalculatorButton([this, operationType, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, operationType, OperationType::ADD); }, parent, currentTextControl, BUTTON_STRING_ADD),
            // NEGATE (POSITIVE/NEGATIVE)
            new CalculatorButton([this, currentTextControl]() -> void
                                 {
                                     // TODO: IMPLEMENT
                                 },
                                 parent, currentTextControl, BUTTON_STRING_NEGATE),
            // 0
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_ZERO_DIGIT); }, parent, currentTextControl, BUTTON_STRING_ZERO_DIGIT),
            // DECIMAL
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_DECIMAL); }, parent, currentTextControl, BUTTON_STRING_DECIMAL),
            // EQUAL
            new CalculatorButton([operationType, lastTextControl, currentTextControl]() -> void
                                 {
                                     // TODO: IMPLEMENT
                                     *operationType = OperationType::NONE;
                                     lastTextControl->SetValue(wxEmptyString);
                                     currentTextControl->SetValue("0");
                                     // const std::string stringValue = currentTextControl->GetValue().wxString::ToStdString();
                                     // const double currentValue = std::stod(stringValue);
                                 },
                                 parent, currentTextControl, BUTTON_STRING_EQUAL, COLOR_ORANGE, *wxBLACK),
        });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonGrid::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}

void ButtonGrid::HandleDigit(wxTextCtrl *currentTextControl, std::string buttonValue)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9)
    {
        // REMOVE THE DEFAULT "0" VALUE
        if (currentValue == "0")
            currentValue = "";

        const std::string textValue = currentValue.append(buttonValue);
        currentTextControl->SetValue(textValue);
    }
}

void ButtonGrid::HandleDelete(wxTextCtrl *currentTextControl)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue == "0")
        return;

    if (currentValue.length() == 1)
    {
        currentTextControl->SetValue("0");
        return;
    }
    else
    {
        currentValue.erase(currentValue.size() - 1);
        currentTextControl->SetValue(currentValue);
    }
}

void ButtonGrid::HandleClear(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType)
{
    *operationType = OperationType::NONE;
    lastTextControl->SetValue(wxEmptyString);
    currentTextControl->SetValue("0");
}

void ButtonGrid::HandleAction(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType, OperationType type)
{
    if (lastTextControl->GetValue().length() > 0)
        return;

    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    std::string lastValue = " ";
    switch (type)
    {
    case OperationType::ADD:
        lastValue.insert(0, BUTTON_STRING_ADD);
        break;
    case OperationType::SUBTRACT:
        lastValue.insert(0, BUTTON_STRING_SUBTRACT);
        break;
    case OperationType::MULTIPLY:
        lastValue.insert(0, BUTTON_STRING_MULTIPLY);
        break;
    case OperationType::DIVIDE:
        lastValue.insert(0, BUTTON_STRING_DIVIDE);
        break;
    default:
        return;
    }

    *operationType = type;
    lastTextControl->SetValue(currentValue.insert(0, lastValue));
    currentTextControl->SetValue("0");
}