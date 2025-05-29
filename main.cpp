#include <wx/wx.h>
#include <vector>
#include <colors/colors.h>
#include <calculatorbutton.h>
#include <buttoncontainer.h>

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

    // INITIALIZE CALCULATOR BUTTONS
    auto buttonContainer = new ButtonContainer(this, currentTextControl);

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