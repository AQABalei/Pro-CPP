#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif
#include "PaintModel.h"
#include <algorithm>
#include <iostream>
#include <wx/dcmemory.h>

// Draws any shapes in the model to the provided DC (draw context)
void PaintModel::DrawShapes(wxDC& dc, bool showSelection)
{
	// TODO
    if(mBitmap.IsOk())
    {
        dc.DrawBitmap(mBitmap, wxPoint(0, 0));
    }
    for(int i=0; i<mShapes.size(); ++i)
    {
        mShapes[i]->Draw(dc);
    }
    if(mCurrSelected != nullptr)
    {
        mCurrSelected->DrawSelection(dc);
    }
}

// Clear the current paint model and start fresh
void PaintModel::New()
{
	// TODO
    mShapes.clear();
    mCurrActiveCommand = nullptr;
    mCurrSelected = nullptr;
    mPen = *wxBLACK_PEN;
    mBrush = *wxWHITE_BRUSH;
    while(!mUndoStack.empty())
    {
        mUndoStack.pop();
    }
    while(!mRedoStack.empty())
    {
        mRedoStack.pop();
    }
    if(mBitmap.IsOk())
    {
        wxBitmap newBitmap;
        mBitmap = newBitmap;
    }
}

// Add a shape to the paint model
void PaintModel::AddShape(std::shared_ptr<Shape> shape)
{
	mShapes.emplace_back(shape);
}

// Remove a shape from the paint model
void PaintModel::RemoveShape(std::shared_ptr<Shape> shape)
{
	auto iter = std::find(mShapes.begin(), mShapes.end(), shape);
	if (iter != mShapes.end())
	{
        mShapes.erase(iter);
	}
}

bool PaintModel::HasActiveCommand()
{
    return (mCurrActiveCommand != nullptr);
}

void PaintModel::CreateCommand(CommandType cType, wxPoint& startingPoint)
{
    mCurrActiveCommand = CommandFactory::Create(shared_from_this(), cType, startingPoint);
    while(!mRedoStack.empty())
    {
        mRedoStack.pop();
    }
}

void PaintModel::UpdateCommand(wxPoint& point)
{
    mCurrActiveCommand->Update(point);
}

void PaintModel::FinalizeCommand(std::shared_ptr<PaintModel> model)
{
    mCurrActiveCommand->Finalize(model);
    mUndoStack.push(mCurrActiveCommand);
    mCurrActiveCommand = nullptr;
}

bool PaintModel::CanUndo()
{
    return (!mUndoStack.empty());
}

bool PaintModel::CanRedo()
{
    return (!mRedoStack.empty());
}

void PaintModel::Undo(std::shared_ptr<PaintModel> model)
{
    if(CanUndo())
    {
        std::shared_ptr<Command> undoTop = mUndoStack.top();
        undoTop->Undo(model);
        mUndoStack.pop();
        mRedoStack.push(undoTop);
    }
}

void PaintModel::Redo(std::shared_ptr<PaintModel> model)
{
    if(CanRedo())
    {
        std::shared_ptr<Command> redoTop = mRedoStack.top();
        redoTop->Redo(model);
        mRedoStack.pop();
        mUndoStack.push(redoTop);
    }
}

bool PaintModel::FindSelect(wxPoint mousePos)
{
    for(int i=mShapes.size()-1; i>=0; i--)
    {
        if(mShapes[i]->Intersects(mousePos))
        {
            mCurrSelected = mShapes[i];
            return true;
        }
    }
    mCurrSelected = nullptr;
    return false;
}

void PaintModel::Export(std::string filePath, wxSize bitmapSize)
{
    auto it = filePath.find('.');
    std::string format = filePath.substr(it+1);
    wxBitmap bitmap;
    // Create the bitmap of the specified wxSize
    bitmap.Create(bitmapSize);
    // Create a memory DC to draw to the bitmap
    wxMemoryDC dc(bitmap);
    // Clear the background color
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    // Draw all the shapes (make sure not the selection!)
    DrawWithoutSelection(dc);
    // Write the bitmap with the specified file name and wxBitmapType
    wxBitmapType type;
    if(format == "bmp")
    {
        type = wxBITMAP_TYPE_BMP;
    }
    else if(format == "png")
    {
        type = wxBITMAP_TYPE_PNG;
    }
    else
    {
        type = type = wxBITMAP_TYPE_JPEG;
    }
    bitmap.SaveFile(filePath, type);
}

void PaintModel::DrawWithoutSelection(wxDC& dc)
{
    for(int i=0; i<mShapes.size(); ++i)
    {
        mShapes[i]->Draw(dc);
    }
}

void PaintModel::LoadPicture(std::string filePath)
{
    New();
    auto it = filePath.find('.');
    std::string format = filePath.substr(it+1);
    wxBitmapType type;
    if(format == "bmp")
    {
        type = wxBITMAP_TYPE_BMP;
    }
    else if(format == "png")
    {
        type = wxBITMAP_TYPE_PNG;
    }
    else
    {
        type = type = wxBITMAP_TYPE_JPEG;
    }
    //wxString path(filePath.c_str(), wxConvUTF8);
    mBitmap.LoadFile(filePath, type);
    
}
