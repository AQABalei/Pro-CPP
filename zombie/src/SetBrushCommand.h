//
//  SetBrushCommand.h
//  pa5
//
//  Created by Zhong Chu on 3/27/18.
//

#ifndef SetBrushCommand_h
#define SetBrushCommand_h
#include "Command.h"

class SetBrushCommand : public Command
{
public:
    SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    void Finalize(std::shared_ptr<PaintModel> model) override;
    void Undo(std::shared_ptr<PaintModel> model) override;
    void Redo(std::shared_ptr<PaintModel> model) override;
private:
    wxBrush mOldBrush;
    wxBrush mNewBrush;
};

#endif /* SetBrushCommand_h */
