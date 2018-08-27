//
//  SetPenCommand.h
//  pa5
//
//  Created by Zhong Chu on 3/27/18.
//

#ifndef SetPenCommand_h
#define SetPenCommand_h
#include "Command.h"

class SetPenCommand : public Command
{
public:
    //DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    void Finalize(std::shared_ptr<PaintModel> model) override;
    void Undo(std::shared_ptr<PaintModel> model) override;
    void Redo(std::shared_ptr<PaintModel> model) override;
private:
    wxPen mOldPen;
    wxPen mNewPen;
};

#endif /* SetPenCommand_h */
