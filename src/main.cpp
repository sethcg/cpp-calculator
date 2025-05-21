#include <wx/wx.h>
#include <vector>

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

    const auto GRAY = wxColour(67, 67, 67, wxALPHA_OPAQUE);          // HEX: #434343
    const auto DARK_GRAY = wxColour(45, 45, 45, wxALPHA_OPAQUE);     // HEX: #2d2d2d
    const auto LIGHT_BLUE = wxColour(135, 206, 235, wxALPHA_OPAQUE); // HEX: #87ceeb

    // TODO: Switch to using wxBitmapButton instead and SVG images for more clear results
    std::vector<std::pair<wxString, wxColour>> buttons = {
        {"\u0025", DARK_GRAY},                                           // %, PERCENTAGE
        {"CE", DARK_GRAY},                                               // CE, CLEAR ENTRY
        {"C", DARK_GRAY},                                                // C, CLEAR (ALL)
        {"DEL", DARK_GRAY},                                              // DEL, DELETE DIGIT
        {wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D"), DARK_GRAY}, // FRACTION
        {wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2"), DARK_GRAY},     // SQUARE
        {wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"), DARK_GRAY}, // SQUARE ROOT
        {"\u00F7", DARK_GRAY},                                           // DIVIDE
        {"7", GRAY},                                                     // 7
        {"8", GRAY},                                                     // 8
        {"9", GRAY},                                                     // 9
        {"x", DARK_GRAY},                                                // MULTIPLY
        {"4", GRAY},                                                     // 4
        {"5", GRAY},                                                     // 5
        {"6", GRAY},                                                     // 6
        {"\u002D", DARK_GRAY},                                           // SUBTRACT
        {"1", GRAY},                                                     // 1
        {"2", GRAY},                                                     // 2
        {"3", GRAY},                                                     // 3
        {"\u002B", DARK_GRAY},                                           // ADD
        {wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B"), GRAY},  // NEGATE (POSITIVE/NEGATIVE)
        {"0", GRAY},                                                     // 0
        {"\u002E", GRAY},                                                // DECIMAL
        {"\u003D", LIGHT_BLUE},                                          // EQUAL
    };

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

    // TODO: Update text display with button clicks
    // TODO: Formalize button creation, color, text color etc. in a custom initialize method
    for (const auto &[label, color] : buttons)
    {
        auto button = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxEXPAND);
        button->SetBackgroundColour(color);
        if (label == "\u003D")
        {
            button->SetForegroundColour(*wxBLACK);
        }
        buttonContainer->Add(button, 1, wxEXPAND, 5);
    }

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