//
//  DrawCommand.h
//  pa5
//
//  Created by Zhong Chu on 3/17/18.
//

#ifndef DrawCommand_h
#define DrawCommand_h
#include "Shape.h"
#include "Command.h"

class DrawCommand : public Command
{
public:
    DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    void Finalize(std::shared_ptr<PaintModel> model) override;
    void Undo(std::shared_ptr<PaintModel> model) override;
    void Redo(std::shared_ptr<PaintModel> model) override;
    void Update(const wxPoint& newPoint) override;
};
#endif /* DrawCommand_h */
