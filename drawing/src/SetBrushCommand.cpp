//
//  SetBrushCommand.cpp
//  main
//
//  Created by Zhong Chu on 3/27/18.
//
#include "SetBrushCommand.h"
#include "PaintModel.h"
#include "Shape.h"

SetBrushCommand::SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{
    mOldBrush = mShape->GetBrush();
}

void SetBrushCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mNewBrush = model->GetBrush();
}

void SetBrushCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->SetBrush(mOldBrush);
}

void SetBrushCommand::Redo(std::shared_ptr<PaintModel> model)
{
    mShape->SetBrush(mNewBrush);
}
