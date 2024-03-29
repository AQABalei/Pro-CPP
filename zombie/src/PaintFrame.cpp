#include "PaintFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/toolbar.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include "PaintDrawPanel.h"
#include "PaintModel.h"

wxBEGIN_EVENT_TABLE(PaintFrame, wxFrame) // NOLINT
	EVT_MENU(wxID_EXIT, PaintFrame::OnExit)
	EVT_MENU(wxID_NEW, PaintFrame::OnNew)
	EVT_MENU(ID_Import, PaintFrame::OnImport)
	EVT_TOOL(ID_Import, PaintFrame::OnImport)
	EVT_MENU(ID_Export, PaintFrame::OnExport)
	EVT_TOOL(ID_Export, PaintFrame::OnExport)
	EVT_MENU(wxID_UNDO, PaintFrame::OnUndo)
	EVT_TOOL(wxID_UNDO, PaintFrame::OnUndo)
	EVT_MENU(wxID_REDO, PaintFrame::OnRedo)
	EVT_TOOL(wxID_REDO, PaintFrame::OnRedo)
	EVT_MENU(ID_Unselect, PaintFrame::OnUnselect)
	EVT_MENU(ID_Delete, PaintFrame::OnDelete)
	EVT_MENU(ID_SetPenColor, PaintFrame::OnSetPenColor)
	EVT_MENU(ID_SetPenWidth, PaintFrame::OnSetPenWidth)
	EVT_MENU(ID_SetBrushColor, PaintFrame::OnSetBrushColor)
	// The different draw modes
	EVT_TOOL(ID_Selector, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawLine, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawEllipse, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawRect, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawPencil, PaintFrame::OnSelectTool)
wxEND_EVENT_TABLE()	

PaintFrame::PaintFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// Initialize image handlers to support BMP, PNG, JPEG
	wxImage::AddHandler(new wxPNGHandler()); // NOLINT
	wxImage::AddHandler(new wxJPEGHandler()); // NOLINT

	SetupMenu(); // NOLINT
	
	SetupToolbar();

	SetupModelAndView();

	wxFrame::Show(true);
	
	wxFrame::SetMinSize(GetSize());
	wxFrame::SetMaxSize(GetSize());
}

void PaintFrame::SetupMenu()
{
	// File menu
	mFileMenu = new wxMenu();
	mFileMenu->Append(wxID_NEW);
	mFileMenu->Append(ID_Export, "Export...",
		"Export current drawing to image file.");
	mFileMenu->AppendSeparator();
	mFileMenu->Append(ID_Import, "Import...",
		"Import image into file.");
	mFileMenu->Append(wxID_EXIT);

	// Edit menu
	mEditMenu = new wxMenu();
	mEditMenu->Append(wxID_UNDO);
	mEditMenu->Append(wxID_REDO);
	mEditMenu->AppendSeparator();
	mEditMenu->Append(ID_Unselect, "Unselect",
		"Unselect the current selection");
	mEditMenu->AppendSeparator();
	mEditMenu->Append(ID_Delete, "Delete\tDel",
		"Delete the current selection");
	
	mEditMenu->Enable(wxID_UNDO, false);
	mEditMenu->Enable(wxID_REDO, false);
	mEditMenu->Enable(ID_Unselect, false);
	mEditMenu->Enable(ID_Delete, false);

	// Colors menu
	mColorMenu = new wxMenu();
	mColorMenu->Append(ID_SetPenColor, "Pen Color...", "Set the pen color.");
	mColorMenu->Append(ID_SetPenWidth, "Pen Width...", "Set the pen width.");
	mColorMenu->AppendSeparator();
	mColorMenu->Append(ID_SetBrushColor, "Brush Color...", "Set brush color");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(mFileMenu, "&File");
	menuBar->Append(mEditMenu, "&Edit");
	menuBar->Append(mColorMenu, "&Colors");
	SetMenuBar(menuBar);
	CreateStatusBar();
}

void PaintFrame::SetupToolbar()
{
	// Create the toolbar
	mToolbar = CreateToolBar();
	mToolbar->AddTool(wxID_NEW, "New",
		wxBitmap("Icons/New.png", wxBITMAP_TYPE_PNG),
		"New");
	mToolbar->AddTool(ID_Export, "Export",
		wxBitmap("Icons/Save.png", wxBITMAP_TYPE_PNG),
		"Export");
	mToolbar->AddTool(ID_Import, "Import",
		wxBitmap("Icons/Import.png", wxBITMAP_TYPE_PNG),
		"Import");
	mToolbar->AddSeparator();

	mToolbar->AddTool(wxID_UNDO, "Undo",
		wxBitmap("Icons/Undo.png", wxBITMAP_TYPE_PNG),
		"Undo");
	mToolbar->AddTool(wxID_REDO, "Redo",
		wxBitmap("Icons/Redo.png", wxBITMAP_TYPE_PNG),
		"Redo");
	mToolbar->AddSeparator();

	mToolbar->AddTool(ID_Selector, "Selector",
		wxBitmap("Icons/Cursor.png", wxBITMAP_TYPE_PNG),
		"Selector", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawLine, "Draw Line",
		wxBitmap("Icons/Line.png", wxBITMAP_TYPE_PNG),
		"Draw Line", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawEllipse, "Draw Ellipse",
		wxBitmap("Icons/Ellipse.png", wxBITMAP_TYPE_PNG),
		"Draw Ellipse", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawRect, "Draw Rectangle",
		wxBitmap("Icons/Rectangle.png", wxBITMAP_TYPE_PNG),
		"Draw Rectangle", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawPencil, "Pencil",
		wxBitmap("Icons/Pencil.png", wxBITMAP_TYPE_PNG),
		"Pencil", wxITEM_CHECK);

	mToolbar->Realize();

	ToggleTool(ID_Selector);

	// Both undo and redo are disabled initially
	mToolbar->EnableTool(wxID_UNDO, false);
	mToolbar->EnableTool(wxID_REDO, false);
}

void PaintFrame::SetupModelAndView()
{
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new PaintDrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);

	// Programatically bind the mouse events on the draw panel to us
	mPanel->Bind(wxEVT_LEFT_DOWN, &PaintFrame::OnMouseButton, this);
	mPanel->Bind(wxEVT_LEFT_UP, &PaintFrame::OnMouseButton, this);
	mPanel->Bind(wxEVT_MOTION, &PaintFrame::OnMouseMove, this);

	// Create the model
	mModel = std::make_shared<PaintModel>();
	mPanel->SetModel(mModel);
	SetSizer(sizer);

	SetAutoLayout(true);
}

void PaintFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void PaintFrame::OnNew(wxCommandEvent& event)
{
	mModel->New();
	mPanel->PaintNow();
    mToolbar->EnableTool(wxID_UNDO, false);
    mEditMenu->Enable(wxID_UNDO, false);
    mToolbar->EnableTool(wxID_REDO, false);
    mEditMenu->Enable(wxID_REDO, false);
}

void PaintFrame::OnExport(wxCommandEvent& event)
{
	// TODO
    //wxString str;
    wxString format = "BMP files (*.bmp)|*.bmp|PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg";
    wxFileDialog saveDialog(this, "Export", "", "", format, wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    //dialog.SetWildcard(format);
    if (saveDialog.ShowModal() == wxID_OK)
    {
        wxSize mySize = mPanel->GetSize();
        std::string filePath = std::string(saveDialog.GetPath().mb_str());
        mModel->Export(filePath, mySize);
    }
}

void PaintFrame::OnImport(wxCommandEvent& event)
{
	// TODO
    wxString format = "BMP files (*.bmp)|*.bmp|PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg";
    wxFileDialog openFileDialog(this, "Import", "", "", format, wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_OK)
    {
        std::string filePath = std::string(openFileDialog.GetPath().mb_str());
        mModel->LoadPicture(filePath);
        mPanel->PaintNow();
    }
}

void PaintFrame::OnUndo(wxCommandEvent& event)
{
	// TODO
    mModel->Undo(mModel);
    mPanel->PaintNow();
    if(mModel->CanUndo())
    {
        mToolbar->EnableTool(wxID_UNDO, true);
        mEditMenu->Enable(wxID_UNDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_UNDO, false);
        mEditMenu->Enable(wxID_UNDO, false);
    }
    if(mModel->CanRedo())
    {
        mToolbar->EnableTool(wxID_REDO, true);
        mEditMenu->Enable(wxID_REDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_REDO, false);
        mEditMenu->Enable(wxID_REDO, false);
    }
}

void PaintFrame::OnRedo(wxCommandEvent& event)
{
	// TODO
    mModel->Redo(mModel);
    mPanel->PaintNow();
    if(mModel->CanUndo())
    {
        mToolbar->EnableTool(wxID_UNDO, true);
        mEditMenu->Enable(wxID_UNDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_UNDO, false);
        mEditMenu->Enable(wxID_UNDO, false);
    }
    if(mModel->CanRedo())
    {
        mToolbar->EnableTool(wxID_REDO, true);
        mEditMenu->Enable(wxID_REDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_REDO, false);
        mEditMenu->Enable(wxID_REDO, false);
    }
}

void PaintFrame::OnUnselect(wxCommandEvent& event)
{
	// TODO
    mModel->SetCurrSelected(nullptr);
    mPanel->PaintNow();
    mEditMenu->Enable(ID_Unselect, false);
    mEditMenu->Enable(ID_Delete, false);
}

void PaintFrame::OnDelete(wxCommandEvent& event)
{
	// TODO
    wxPoint one, two;
    mModel->GetCurrSelected()->GetBounds(one, two);
    mModel->CreateCommand(CM_Delete, one);
    mModel->FinalizeCommand(mModel);
    mPanel->PaintNow();
    mEditMenu->Enable(ID_Delete, false);
}

void PaintFrame::OnSetPenColor(wxCommandEvent& event)
{
	// TODO
    wxColourData data;
    data.SetColour(mModel->GetPenColour());
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        // Use dialog.GetColourData() to get the color picked
        // and do s
        mModel->SetPenColour(dialog.GetColourData().GetColour());
    }
    if(mModel->GetCurrSelected())
    {
        wxPoint one, two;
        mModel->GetCurrSelected()->GetBounds(one, two);
        mModel->CreateCommand(CM_SetPen, one);
        mModel->FinalizeCommand(mModel);
        mPanel->PaintNow();
    }
}

void PaintFrame::OnSetPenWidth(wxCommandEvent& event)
{
	// TODO
    wxString defaultWidth = "Current width: ";
    defaultWidth << mModel->GetPenWidth();
    wxString str;
    wxTextEntryDialog dialog(this, defaultWidth, str);
    dialog.SetTextValidator(wxFILTER_NUMERIC);
    dialog.SetMaxLength(2);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString input = dialog.GetValue();
        int width = wxAtoi(input);
        if(width >= 1 && width <= 10)
        {
            mModel->SetPenWidth(width);
        }
    }
    if(mModel->GetCurrSelected())
    {
        wxPoint one, two;
        mModel->GetCurrSelected()->GetBounds(one, two);
        mModel->CreateCommand(CM_SetPen, one);
        mModel->FinalizeCommand(mModel);
        mPanel->PaintNow();
    }
}

void PaintFrame::OnSetBrushColor(wxCommandEvent& event)
{
	// TODO
    wxColourData data;
    data.SetColour(mModel->GetBrushColour());
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        // Use dialog.GetColourData() to get the color picked
        // and do s
        mModel->SetBrushColour(dialog.GetColourData().GetColour());
    }
    if(mModel->GetCurrSelected())
    {
        wxPoint one, two;
        mModel->GetCurrSelected()->GetBounds(one, two);
        mModel->CreateCommand(CM_SetBrush, one);
        mModel->FinalizeCommand(mModel);
        mPanel->PaintNow();
    }
}

void PaintFrame::OnMouseButton(wxMouseEvent& event)
{
	if (event.LeftDown())
	{
		// TODO: This is when the left mouse button is pressed
        wxPoint mousePos = event.GetPosition();
        if(mModel->GetCurrSelected() != nullptr)
        {
            if(mousePos.x >= mModel->GetCurrSelected()->GetTopLeft().x && mousePos.x <= mModel->GetCurrSelected()->GetBotRight().x && mousePos.y >= mModel->GetCurrSelected()->GetTopLeft().y && mousePos.y <= mModel->GetCurrSelected()->GetBotRight().y)
            {
                mPanel->SetCursor(CU_Move);
            }
            else
            {
                mPanel->SetCursor(CU_Default);
            }
        }
        if(mCurrentTool == ID_DrawRect)
        {
            //CommandType currCommnad = CM_DrawRect;
            mModel->CreateCommand(CM_DrawRect, mousePos);
            mPanel->PaintNow();
        }
        else if(mCurrentTool == ID_DrawEllipse)
        {
            mModel->CreateCommand(CM_DrawEllipse, mousePos);
            mPanel->PaintNow();
        }
        else if(mCurrentTool == ID_DrawLine)
        {
            mModel->CreateCommand(CM_DrawLine, mousePos);
            mPanel->PaintNow();
        }
        else if(mCurrentTool == ID_DrawPencil)
        {
            mModel->CreateCommand(CM_DrawPencil, mousePos);
            mPanel->PaintNow();
        }
        else if(mCurrentTool == ID_Selector)
        {
            if(mModel->FindSelect(mousePos))
            {
                mEditMenu->Enable(ID_Unselect, true);
                mEditMenu->Enable(ID_Delete, true);
                mModel->CreateCommand(CM_Move, mousePos);
                mPanel->PaintNow();
            }
            else
            {
                mEditMenu->Enable(ID_Unselect, false);
                mEditMenu->Enable(ID_Delete, false);
            }
            mPanel->PaintNow();
        }
	}
	else if (event.LeftUp())
	{
        // TODO: This is when the left mouse button is released
        if(mModel->HasActiveCommand())
        {
            wxPoint mousePos = event.GetPosition();
            mModel->UpdateCommand(mousePos);
            mModel->FinalizeCommand(mModel);
            mPanel->PaintNow();
        }
	}
    if(mModel->CanUndo())
    {
        mToolbar->EnableTool(wxID_UNDO, true);
        mEditMenu->Enable(wxID_UNDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_UNDO, false);
        mEditMenu->Enable(wxID_UNDO, false);
    }
    if(mModel->CanRedo())
    {
        mToolbar->EnableTool(wxID_REDO, true);
        mEditMenu->Enable(wxID_REDO, true);
    }
    else
    {
        mToolbar->EnableTool(wxID_REDO, false);
        mEditMenu->Enable(wxID_REDO, false);
    }
}

void PaintFrame::OnMouseMove(wxMouseEvent& event)
{
	// TODO: This is when the mouse is moved inside the drawable area
    wxPoint mousePos = event.GetPosition();
    if(mModel->HasActiveCommand())
    {
        mModel->UpdateCommand(mousePos);
        mPanel->PaintNow();
    }
}

void PaintFrame::ToggleTool(EventID toolID)
{
	// Deselect everything
	for (int i = ID_Selector; i <= ID_DrawPencil; i++)
	{
		mToolbar->ToggleTool(i, false);
	}

	// Select the new tool
	mToolbar->ToggleTool(toolID, true);

	mCurrentTool = toolID;
}

void PaintFrame::SetCursorType(CursorType type)
{
	wxCursor* cursor = mCursors.GetCursor(type);
	if (cursor != nullptr)
	{
		mPanel->SetCursor(*cursor);
	}
}

void PaintFrame::OnSelectTool(wxCommandEvent& event)
{
	EventID id = static_cast<EventID>(event.GetId());
	ToggleTool(id);

	// Select appropriate cursor
	switch (id)
	{
	case ID_DrawLine:
	case ID_DrawEllipse:
	case ID_DrawRect:
		SetCursorType(CU_Cross);
		break;
	case ID_DrawPencil:
		SetCursorType(CU_Pencil);
		break;
	default:
		SetCursorType(CU_Default);
		break;
	}
}
