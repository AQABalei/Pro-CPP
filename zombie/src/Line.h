//
//  Line.h
//  pa5
//
//  Created by Zhong Chu on 3/25/18.
//

#ifndef Line_h
#define Line_h
#include "Shape.h"

class Line : public Shape
{
public:
    Line(const wxPoint& start);
    void Draw(wxDC& dc) const override;
};

#endif /* Line_h */
