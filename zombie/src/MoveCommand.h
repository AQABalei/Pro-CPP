//
//  MoveCommand.h
//  pa5
//
//  Created by Zhong Chu on 3/27/18.
//

#ifndef MoveCommand_h
#define MoveCommand_h
#include "Command.h"

class MoveCommand : public Command
{
public:
    MoveCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    void Finalize(std::shared_ptr<PaintModel> model) override;
    void Undo(std::shared_ptr<PaintModel> model) override;
    void Redo(std::shared_ptr<PaintModel> model) override;
    void Update(const wxPoint& newPoint) override;
private:
    wxPoint mOldOffset;
    wxPoint mNewOffset;
    wxPoint mStart;
};
#endif /* MoveCommand_h */
