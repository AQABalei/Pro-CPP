#pragma once
#include <wx/dc.h>

// Abstract base class for all Shapes
class Shape
{
public:
	Shape(const wxPoint& start);
	// Tests whether the provided point intersects
	// with this shape
	bool Intersects(const wxPoint& point) const;
	// Update shape with new provided point
	virtual void Update(const wxPoint& newPoint);
	// Finalize the shape -- when the user has finished drawing the shape
	virtual void Finalize();
	// Returns the top left/bottom right points of the shape
	void GetBounds(wxPoint& topLeft, wxPoint& botRight) const;
	// Draw the shape
	virtual void Draw(wxDC& dc) const = 0;
    //Select Shape
    void DrawSelection(wxDC& dc);
    wxPen GetPen()
    {
        return mPenInShape;
    }
    void SetPen(wxPen pen)
    {
        mPenInShape = pen;
    }
    wxBrush GetBrush()
    {
        return mBrushInShape;
    }
    void SetBrush(wxBrush brush)
    {
        mBrushInShape = brush;
    }
    wxPoint GetTopLeft()
    {
        return mTopLeft;
    }
    wxPoint GetBotRight()
    {
        return mBotRight;
    }
    wxPoint GetOffset()
    {
        return mOffset;
    }
    void SetOffset(wxPoint offset)
    {
        mOffset = offset;
    }
protected:
	// Starting point of shape
	wxPoint mStartPoint;
	// Ending point of shape
	wxPoint mEndPoint;
	// Top left point of shape
	wxPoint mTopLeft;
	// Bottom right point of shape
	wxPoint mBotRight;
    
    wxPen mPenInShape;
    wxBrush mBrushInShape;
    wxPoint mOffset;
};
