//
//  EllipseShape.cpp
//  main
//
//  Created by Zhong Chu on 3/25/18.
//
#include "EllipseShape.h"


EllipseShape::EllipseShape(const wxPoint& start):Shape(start)
{
    
}

void EllipseShape::Draw(wxDC& dc) const
{
    dc.SetPen(mPenInShape);
    dc.SetBrush(mBrushInShape);
    wxRect rect(mTopLeft + mOffset, mBotRight + mOffset);
    dc.DrawEllipse(rect);
}
