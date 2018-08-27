//
//  SetPenCommand.cpp
//  main
//
//  Created by Zhong Chu on 3/27/18.
//
#include "SetPenCommand.h"
#include "PaintModel.h"
#include "Shape.h"

SetPenCommand::SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{
    mOldPen = mShape->GetPen();
}

void SetPenCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mNewPen = model->GetPen();
}

void SetPenCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->SetPen(mOldPen);
}

void SetPenCommand::Redo(std::shared_ptr<PaintModel> model)
{
     mShape->SetPen(mNewPen);
}
