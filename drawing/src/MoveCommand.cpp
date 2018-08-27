//
//  MoveCommand.cpp
//  main
//
//  Created by Zhong Chu on 3/27/18.
//
#include "PaintModel.h"
#include "MoveCommand.h"
#include "Shape.h"

MoveCommand::MoveCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{
    mOldOffset = mShape->GetOffset();
    mStart = start;
}
void MoveCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mShape->Finalize();
    mNewOffset = mShape->GetOffset();
}

void MoveCommand::Update(const wxPoint& newPoint)
{
    //Command::Update(newPoint);
    mNewOffset = mOldOffset + newPoint - mStart;
    mShape->SetOffset(mNewOffset);
}

void MoveCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->SetOffset(mOldOffset);
}

void MoveCommand::Redo(std::shared_ptr<PaintModel> model)
{
    mShape->SetOffset(mNewOffset);
}
