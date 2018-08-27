//
//  PencilShape.h
//  pa5
//
//  Created by Zhong Chu on 3/25/18.
//

#ifndef PencilShape_h
#define PencilShape_h
#include "Shape.h"
#include <vector>

class PencilShape : public Shape
{
public:
    PencilShape(const wxPoint& start);
    void Update(const wxPoint& newPoint) override;
    void Finalize() override;
    void Draw(wxDC& dc) const override;
private:
    std::vector<wxPoint> mPoints;
};


#endif /* PencilShape_h */
