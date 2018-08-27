//
//  RectShape.h
//  pa5
//
//  Created by Zhong Chu on 3/25/18.
//

#ifndef RectShape_h
#define RectShape_h
#include "Shape.h"

class RectShape : public Shape
{
public:
    RectShape(const wxPoint& start);
    void Draw(wxDC& dc) const override;
};

#endif /* RectShape_h */
