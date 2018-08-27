//
//  RectShape.cpp
//  main
//
//  Created by Zhong Chu on 3/25/18.
//
#include "RectShape.h"


RectShape::RectShape(const wxPoint& start):Shape(start)
{
    
}

void RectShape::Draw(wxDC& dc) const
{
    dc.SetPen(mPenInShape);
    dc.SetBrush(mBrushInShape);
    wxRect rect(mTopLeft + mOffset, mBotRight + mOffset);
    dc.DrawRectangle(rect);
}
