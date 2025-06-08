#pragma once
#include <wx/wx.h>
#include <colors/Colors.h>

const inline std::string BUTTON_STRING_ZERO_DIGIT = "\u0030";         // STRING VALUE: "0"
const inline std::string BUTTON_STRING_ONE_DIGIT = "\u0031";          // STRING VALUE: "1"
const inline std::string BUTTON_STRING_TWO_DIGIT = "\u0032";          // STRING VALUE: "2"
const inline std::string BUTTON_STRING_THREE_DIGIT = "\u0033";        // STRING VALUE: "3"
const inline std::string BUTTON_STRING_FOUR_DIGIT = "\u0034";         // STRING VALUE: "4"
const inline std::string BUTTON_STRING_FIVE_DIGIT = "\u0035";         // STRING VALUE: "5"
const inline std::string BUTTON_STRING_SIX_DIGIT = "\u0036";          // STRING VALUE: "6"
const inline std::string BUTTON_STRING_SEVEN_DIGIT = "\u0037";        // STRING VALUE: "7"
const inline std::string BUTTON_STRING_EIGHT_DIGIT = "\u0038";        // STRING VALUE: "8"
const inline std::string BUTTON_STRING_NINE_DIGIT = "\u0039";         // STRING VALUE: "9"
const inline std::string BUTTON_STRING_ALL_CLEAR = "\u0041\u0043";    // STRING VALUE: "AC"
const inline std::string BUTTON_STRING_DELETE = "\u0044\u0045\u004C"; // STRING VALUE: "DEL"

const inline std::string BUTTON_STRING_PERCENT = "\u0025";  // STRING VALUE: "%"
const inline std::string BUTTON_STRING_DECIMAL = "\u002E";  // STRING VALUE: "."
const inline std::string BUTTON_STRING_MULTIPLY = "\u00D7"; // STRING VALUE: "x"
const inline std::string BUTTON_STRING_DIVIDE = "\u00F7";   // STRING VALUE: "÷"
const inline std::string BUTTON_STRING_ADD = "\u002B";      // STRING VALUE: "+"
const inline std::string BUTTON_STRING_SUBTRACT = "\u002D"; // STRING VALUE: "-"
const inline std::string BUTTON_STRING_EQUAL = "\u003D";    // STRING VALUE: "="
const inline std::string BUTTON_STRING_NEGATE = "\u00B1";   // STRING VALUE: "±"

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxString &label, const wxColor &backgroundColor = COLOR_GRAY, const wxColor &textColor = *wxWHITE);
};