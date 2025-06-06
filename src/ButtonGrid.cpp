#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <format>
#include <wx/wx.h>
#include <ctype.h>
#include <colors/Colors.h>
#include <CalculatorButton.h>
#include <ButtonGrid.h>

ButtonGrid::ButtonGrid(wxWindow *parent, wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl) : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(8);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);

    std::vector<CalculatorButton *>
        buttons({
            // AC, CLEAR (ALL)
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleClear(lastTextControl, currentTextControl); }, parent, currentTextControl, BUTTON_STRING_ALL_CLEAR, COLOR_RED),
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
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::MULTIPLY); }, parent, currentTextControl, BUTTON_STRING_MULTIPLY),
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
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::DIVIDE); }, parent, currentTextControl, BUTTON_STRING_DIVIDE),
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
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::SUBTRACT); }, parent, currentTextControl, BUTTON_STRING_SUBTRACT),
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
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::ADD); }, parent, currentTextControl, BUTTON_STRING_ADD),
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
                                 { ButtonGrid::HandleDecimal(currentTextControl, BUTTON_STRING_DECIMAL); }, parent, currentTextControl, BUTTON_STRING_DECIMAL),
            // EQUAL
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleEvaluate(lastTextControl, currentTextControl); }, parent, currentTextControl, BUTTON_STRING_EQUAL, COLOR_ORANGE, *wxBLACK),
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
        // REMOVE THE DEFAULT "0" VALUE OR "Error" MESSAGE
        if (currentValue == "0" || currentValue == "Error")
        {
            currentValue = "";
        }

        const std::string textValue = currentValue.append(buttonValue);
        currentTextControl->SetValue(textValue);
    }
}

void ButtonGrid::HandleDecimal(wxTextCtrl *currentTextControl, std::string buttonValue)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9 || currentValue.find('.') != currentValue.npos)
    {
        // REMOVE THE DEFAULT "0" VALUE OR "Error" MESSAGE
        if (currentValue == "0" || currentValue == "Error")
        {
            currentValue = "";
        }

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

void ButtonGrid::HandleClear(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl)
{
    operationType = OperationType::NONE;
    lastTextControl->SetValue(wxEmptyString);
    currentTextControl->SetValue("0");
}

void ButtonGrid::HandleAction(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType type)
{
    if (lastTextControl->GetValue().length() > 0)
        return;

    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    std::string lastValue = " ";
    switch (type)
    {
    case OperationType::ADD:
        operationType = OperationType::ADD;
        lastValue.insert(0, BUTTON_STRING_ADD);
        break;
    case OperationType::SUBTRACT:
        operationType = OperationType::SUBTRACT;
        lastValue.insert(0, BUTTON_STRING_SUBTRACT);
        break;
    case OperationType::MULTIPLY:
        operationType = OperationType::MULTIPLY;
        lastValue.insert(0, BUTTON_STRING_MULTIPLY);
        break;
    case OperationType::DIVIDE:
        operationType = OperationType::DIVIDE;
        lastValue.insert(0, BUTTON_STRING_DIVIDE);
        break;
    default:
        return;
    }

    lastTextControl->SetValue(currentValue.insert(0, lastValue));
    currentTextControl->SetValue("0");
}

void ButtonGrid::HandleEvaluate(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl)
{
    if (lastTextControl->GetValue().length() <= 0)
        return;

    try
    {
        std::string stringCurrentValue = currentTextControl->GetValue().wxString::ToStdString();

        // REMOVE NON-NUMERIC CHARACTERS FROM STRING Remove non-numeric chars from text
        std::string stringLastValue = lastTextControl->GetValue().wxString::ToStdString();
        std::string temp;
        for (char &character : stringLastValue)
        {
            std::string allowed = "0123456789";
            if (allowed.find(character) != std::string::npos)
            {
                temp.push_back(character);
            }
        }
        stringLastValue = temp;

        double result = 0;
        const double currentValue = std::stod(stringCurrentValue);
        const double lastValue = std::stod(stringLastValue);

        switch (operationType)
        {
        case OperationType::ADD:
            result = lastValue + currentValue;
            break;
        case OperationType::SUBTRACT:
            result = lastValue - currentValue;
            break;
        case OperationType::MULTIPLY:
            result = lastValue * currentValue;
            break;
        case OperationType::DIVIDE:
            result = lastValue / currentValue;
            break;
        default:
            return;
        }

        // RESET THE CONTROLS
        operationType = OperationType::NONE;
        lastTextControl->SetValue(wxEmptyString);

        // ROUND RESULT TO TWO DECIMAL PLACES,
        // OR REMOVE ".00" IF IT ROUNDS TO A PRECISE INTEGER
        std::string stringResult = std::format("{:.2f}", result);
        if (stringResult.length() > 3 && stringResult.substr(stringResult.size() - 3) == ".00")
        {
            currentTextControl->SetValue(stringResult.substr(0, stringResult.size() - 3));
        }
        else
        {
            currentTextControl->SetValue(stringResult);
        }
    }
    catch (int exception)
    {
        (void)exception;
        currentTextControl->SetValue("Error");
    }
}