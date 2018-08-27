#include "Shape.h"
#include <algorithm>

Shape::Shape(const wxPoint& start)
	:mStartPoint(start)
	,mEndPoint(start)
	,mTopLeft(start)
	,mBotRight(start)
{
    wxPoint zero(0, 0);
    mOffset = zero;
}

// Tests whether the provided point intersects
// with this shape
bool Shape::Intersects(const wxPoint& point) const
{
	bool retVal = false;
	wxPoint topleft;
	wxPoint botright;
	GetBounds(topleft, botright);
	if (point.x >= topleft.x && point.x <= botright.x &&
		point.y >= topleft.y && point.y <= botright.y)
	{
		retVal = true;
	}
	return retVal;
}

// Update shape with new provided point
void Shape::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;

	// For most shapes, we only have two points - start and end
	// So we can figure out the top left/bottom right bounds
	// based on this.
	mTopLeft.x = std::min(mStartPoint.x, mEndPoint.x);
	mTopLeft.y = std::min(mStartPoint.y, mEndPoint.y);
	mBotRight.x = std::max(mStartPoint.x, mEndPoint.x);
	mBotRight.y = std::max(mStartPoint.y, mEndPoint.y);
}

void Shape::Finalize()
{
	// Default finalize doesn't do anything
}

void Shape::GetBounds(wxPoint& topLeft, wxPoint& botRight) const
{
	topLeft = mTopLeft + mOffset;
	botRight = mBotRight + mOffset;
}

void Shape::DrawSelection(wxDC& dc)
{
    dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    
    wxPoint largerTopLeft(0,0);
    largerTopLeft.x = mTopLeft.x - 5 + mOffset.x;
    largerTopLeft.y = mTopLeft.y - 5 + mOffset.y;
    wxPoint largerBotRight;
    largerBotRight.x = mBotRight.x + 5 + mOffset.x;
    largerBotRight.y = mBotRight.y + 5 + mOffset.y;
    
    wxRect rect(largerTopLeft, largerBotRight);
    dc.DrawRectangle(rect);
}
