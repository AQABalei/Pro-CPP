//
//  PencilShape.cpp
//  main
//
//  Created by Zhong Chu on 3/25/18.
//
#include "PencilShape.h"


PencilShape::PencilShape(const wxPoint& start):Shape(start)
{
    mPoints.push_back(mStartPoint);
}

void PencilShape::Update(const wxPoint& newPoint)
{
    Shape::Update(newPoint);
    mPoints.push_back(newPoint);
}

void PencilShape::Finalize()
{
    int topLeftX = mPoints[0].x;
    int botRightX = mPoints[0].x;
    int topLeftY = mPoints[0].y;
    int botRightY = mPoints[0].y;
    for(int i=0; i<mPoints.size(); ++i)
    {
        if(mPoints[i].x < topLeftX)
        {
            topLeftX = mPoints[i].x;
        }
        if(mPoints[i].x > botRightX)
        {
            botRightX = mPoints[i].x;
        }
        if(mPoints[i].y < topLeftY)
        {
            topLeftY = mPoints[i].y;
        }
        if(mPoints[i].y > botRightY)
        {
            botRightY = mPoints[i].y;
        }
    }
    mTopLeft = wxPoint(topLeftX, topLeftY);
    mBotRight = wxPoint(botRightX, botRightY);
}

void PencilShape::Draw(wxDC& dc) const
{
    dc.SetPen(mPenInShape);
    dc.SetBrush(mBrushInShape);
    if(mPoints.size() == 1)
    {
        dc.DrawPoint(mPoints[0].x, mPoints[0].y);
    }
    else
    {
        wxPoint points[mPoints.size()];
        for(int i=0; i<mPoints.size(); ++i)
        {
            points[i] = mPoints[i];
        }
        dc.DrawLines(mPoints.size(), points, mOffset.x, mOffset.y);
    }
}
