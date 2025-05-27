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
    ID_Hello = 1
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
    // TODO: Resize fontsize when window changes, get bigger/smaller depending on window size
    // TODO: Implement entry history, with "previousText" variable storing last calculation
    const auto TEXT_HORIZONTAL_MARGIN = FromDIP(10);

    auto *textPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    textPanel->SetBackgroundColour(wxColour(45, 45, 45, wxALPHA_OPAQUE));
    auto textContainer = new wxBoxSizer(wxHORIZONTAL);
    auto textInnerContainer = new wxBoxSizer(wxVERTICAL);
    // auto previousText = new wxStaticText(textPanel, wxID_ANY, "+ 7800", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxEXPAND);
    auto currentText = new wxStaticText(textPanel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxEXPAND);

    // SET THE FONT SIZE
    // previousText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    currentText->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // textInnerContainer->Add(previousText, 1, wxEXPAND, 0);
    textInnerContainer->Add(currentText, 1, wxEXPAND, 0);
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
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u0025", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                // %, PERCENTAGE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "CE", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                               // CE, CLEAR ENTRY
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "C", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                                // C, CLEAR (ALL)
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "DEL", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                              // DEL, DELETE DIGIT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D"), wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5); // FRACTION
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2"), wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);     // SQUARE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"), wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5); // SQUARE ROOT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u00F7", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                           // DIVIDE
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "7", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 7
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "8", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 8
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "9", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 9
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "x", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                                // MULTIPLY
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "4", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 4
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "5", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 5
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "6", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 6
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u002D", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                           // SUBTRACT
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "1", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 1
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "2", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 2
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "3", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 3
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u002D", wxDefaultPosition, wxDefaultSize, DARK_GRAY), 1, wxEXPAND, 5);                                           // ADD
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B"), wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);  // NEGATE (POSITIVE/NEGATIVE)
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                     // 0
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u002E", wxDefaultPosition, wxDefaultSize, GRAY), 1, wxEXPAND, 5);                                                // DECIMAL
    buttonContainer->Add(new CalculatorButton(this, wxID_ANY, "\u003D", wxDefaultPosition, wxDefaultSize, LIGHT_BLUE, *wxBLACK), 1, wxEXPAND, 5);                                // EQUAL

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