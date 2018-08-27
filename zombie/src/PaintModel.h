#pragma once
#include <memory>
#include <vector>
#include <stack>
#include "Shape.h"
#include "Command.h"
#include <wx/bitmap.h>

class PaintModel : public std::enable_shared_from_this<PaintModel>
{
public:
	// Draws any shapes in the model to the provided DC (draw context)
	void DrawShapes(wxDC& dc, bool showSelection = true);

	// Clear the current paint model and start fresh
	void New();

	// Add a shape to the paint model
	void AddShape(std::shared_ptr<Shape> shape);
	// Remove a shape from the paint model
	void RemoveShape(std::shared_ptr<Shape> shape);
    
    bool HasActiveCommand();
    void CreateCommand(CommandType cType, wxPoint& startingPoint);
    void UpdateCommand(wxPoint& point);
    void FinalizeCommand(std::shared_ptr<PaintModel> model);
    void Undo(std::shared_ptr<PaintModel> model);
    void Redo(std::shared_ptr<PaintModel> model);
    bool CanUndo();
    bool CanRedo();
    bool FindSelect(wxPoint mousePos);
    void Export(std::string filePath, wxSize bitmapSize);
    void DrawWithoutSelection(wxDC& dc);
    void LoadPicture(std::string filePath);
    wxPen GetPen()
    {
        return mPen;
    }
    wxBrush GetBrush()
    {
        return mBrush;
    }
    wxColour GetPenColour()
    {
        return mPen.GetColour();
    }
    void SetPenColour(wxColour &col)
    {
        mPen.SetColour(col);
    }
    int GetPenWidth()
    {
        return mPen.GetWidth();
    }
    void SetPenWidth(int width)
    {
        mPen.SetWidth(width);
    }
    wxColour GetBrushColour()
    {
        return mBrush.GetColour();
    }
    void SetBrushColour(wxColour &col)
    {
        mBrush.SetColour(col);
    }
    std::shared_ptr<Shape> GetCurrSelected()
    {
        return mCurrSelected;
    }
    void SetCurrSelected(std::shared_ptr<Shape> currSelected)
    {
        mCurrSelected = currSelected;
    }
private:
	// Vector of all the shapes in the model
	std::vector<std::shared_ptr<Shape>> mShapes;
    std::shared_ptr<Command> mCurrActiveCommand;
    std::stack<std::shared_ptr<Command> > mUndoStack;
    std::stack<std::shared_ptr<Command> > mRedoStack;
    std::shared_ptr<Shape> mCurrSelected;
    wxPen mPen = *wxBLACK_PEN;
    wxBrush mBrush = *wxWHITE_BRUSH;
    wxBitmap mBitmap;
};
