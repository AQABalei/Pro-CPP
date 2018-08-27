//
//  DeleteCommand.h
//  pa5
//
//  Created by Zhong Chu on 3/27/18.
//

#ifndef DeleteCommand_h
#define DeleteCommand_h
#include "Command.h"
class DeleteCommand : public Command
{
public:
    DeleteCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    void Finalize(std::shared_ptr<PaintModel> model) override;
    void Undo(std::shared_ptr<PaintModel> model) override;
    void Redo(std::shared_ptr<PaintModel> model) override;
};

#endif /* DeleteCommand_h */
