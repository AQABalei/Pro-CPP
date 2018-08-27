//
//  Line.cpp
//  main
//
//  Created by Zhong Chu on 3/25/18.
//
#include "Line.h"


Line::Line(const wxPoint& start):Shape(start)
{
    
}

void Line::Draw(wxDC& dc) const
{
    dc.SetPen(mPenInShape);
    dc.SetBrush(mBrushInShape);
    dc.DrawLine(mStartPoint + mOffset, mEndPoint + mOffset);
}
