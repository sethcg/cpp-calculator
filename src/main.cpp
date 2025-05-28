#include <wx/wx.h>
#include <vector>
#include <colors/colors.h>
#include <calculatorbutton.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class CalculatorFrame : public wxFrame
{
public:
    CalculatorFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

enum
{
    ID_Hello = 1,
    ID_CURRENT_TEXT = 1001
};

bool MyApp::OnInit()
{
    MyApp::SetAppearance(Appearance::Dark);

    CalculatorFrame *frame = new CalculatorFrame("Calculator", wxDefaultPosition, wxSize(270, 360));
    frame->SetIcon(wxIcon("assets\\icon.ico", wxBITMAP_TYPE_ICO));
    frame->Show(true);
    return true;
}

CalculatorFrame::CalculatorFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    const auto TEXT_HORIZONTAL_MARGIN = FromDIP(10);

    auto *textPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    textPanel->SetBackgroundColour(wxColour(45, 45, 45, wxALPHA_OPAQUE));

    auto textContainer = new wxBoxSizer(wxHORIZONTAL);
    auto textInnerContainer = new wxBoxSizer(wxVERTICAL);

    auto *currentTextControl = new wxTextCtrl(textPanel, ID_CURRENT_TEXT, "0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    currentTextControl->SetWindowStyle(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxEXPAND);
    currentTextControl->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    textInnerContainer->Add(currentTextControl, 1, wxEXPAND, 0);
    textContainer->AddSpacer(TEXT_HORIZONTAL_MARGIN);
    textContainer->Add(textInnerContainer, 1, wxEXPAND, 0);
    textContainer->AddSpacer(TEXT_HORIZONTAL_MARGIN);
    textPanel->SetSizer(textContainer);

    const auto BUTTON_GRID_MARGIN = FromDIP(5);
    const auto BUTTON_GRID_ROWS = 6;
    const auto BUTTON_GRID_COLS = 4;
    auto buttonContainer = new wxGridSizer(BUTTON_GRID_ROWS, BUTTON_GRID_COLS, BUTTON_GRID_MARGIN, BUTTON_GRID_MARGIN);

    // TODO: Switch to using wxBitmapButton instead and SVG images for more clear results
    // TODO: Update text display with button clicks
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u0025", GRAY), 1, wxEXPAND, 5);                                                // %, PERCENTAGE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "CE", DARK_GRAY), 1, wxEXPAND, 5);                                               // CE, CLEAR ENTRY
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "C", DARK_GRAY), 1, wxEXPAND, 5);                                                // C, CLEAR (ALL)
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "DEL", DARK_GRAY), 1, wxEXPAND, 5);                                              // DEL, DELETE DIGIT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D"), DARK_GRAY), 1, wxEXPAND, 5); // FRACTION
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2"), DARK_GRAY), 1, wxEXPAND, 5);     // SQUARE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"), DARK_GRAY), 1, wxEXPAND, 5); // SQUARE ROOT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u00F7", DARK_GRAY), 1, wxEXPAND, 5);                                           // DIVIDE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "7", GRAY), 1, wxEXPAND, 5);                                                     // 7
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "8", GRAY), 1, wxEXPAND, 5);                                                     // 8
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "9", GRAY), 1, wxEXPAND, 5);                                                     // 9
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "x", DARK_GRAY), 1, wxEXPAND, 5);                                                // MULTIPLY
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "4", GRAY), 1, wxEXPAND, 5);                                                     // 4
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "5", GRAY), 1, wxEXPAND, 5);                                                     // 5
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "6", GRAY), 1, wxEXPAND, 5);                                                     // 6
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u002D", DARK_GRAY), 1, wxEXPAND, 5);                                           // SUBTRACT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "1", GRAY), 1, wxEXPAND, 5);                                                     // 1
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "2", GRAY), 1, wxEXPAND, 5);                                                     // 2
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "3", GRAY), 1, wxEXPAND, 5);                                                     // 3
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u002D", DARK_GRAY), 1, wxEXPAND, 5);                                           // ADD
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B"), GRAY), 1, wxEXPAND, 5);  // NEGATE (POSITIVE/NEGATIVE)
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "0", GRAY), 1, wxEXPAND, 5);                                                     // 0
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u002E", GRAY), 1, wxEXPAND, 5);                                                // DECIMAL
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, currentTextControl, "\u003D", LIGHT_BLUE, *wxBLACK), 1, wxEXPAND, 5);                                // EQUAL

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &CalculatorFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &CalculatorFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &CalculatorFrame::OnExit, this, wxID_EXIT);

    // ALWAYS FIT THE CONTENT ON THE FRAME/WINDOW WHEN ADJUSTING HEIGHT OR WIDTH
    const auto MARGIN = FromDIP(30);
    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textPanel, 0, wxEXPAND, MARGIN);
    sizer->Add(buttonContainer, 1, wxEXPAND, MARGIN);
    SetSizer(sizer);
    SetMinSize(wxSize(210, 270));

    Center();
}

void CalculatorFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void CalculatorFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void CalculatorFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}