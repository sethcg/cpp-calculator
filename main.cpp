#include <wx/wx.h>
#include <vector>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

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

    MyFrame *frame = new MyFrame("Calculator", wxDefaultPosition, wxDefaultSize);
    frame->SetIcon(wxIcon("assets\\icon.ico", wxBITMAP_TYPE_ICO));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{

    const auto GRAY = wxColour(67, 67, 67, wxALPHA_OPAQUE);         // HEX: #434343
    const auto DARK_GRAY = wxColour(45, 45, 45, wxALPHA_OPAQUE);    // HEX: #2d2d2d
    const auto LIGHT_BLUE = wxColour(75, 205, 255, wxALPHA_OPAQUE); // HEX: #24b2e5

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

    // TODO: Add the text output box for number display

    const auto GRID_MARGIN = FromDIP(5);
    const auto GRID_ROWS = 6;
    const auto GRID_COLS = 4;
    auto gridSizer = new wxGridSizer(GRID_ROWS, GRID_COLS, GRID_MARGIN, GRID_MARGIN);

    for (const auto &[label, color] : buttons)
    {
        auto button = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxEXPAND);
        gridSizer->Add(button, 1, wxEXPAND, 5);
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

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    // ALWAYS FIT THE CONTENT ON THE FRAME/WINDOW WHEN ADJUSTING HEIGHT OR WIDTH
    const auto MARGIN = FromDIP(30);

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(gridSizer, 1, wxEXPAND, MARGIN);
    SetSizer(sizer);

    Center();
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}