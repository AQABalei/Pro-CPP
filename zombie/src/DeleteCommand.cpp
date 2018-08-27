//
//  DeleteCommand.cpp
//  main
//
//  Created by Zhong Chu on 3/27/18.
//
#include "DeleteCommand.h"
#include "PaintModel.h"
#include "Shape.h"

DeleteCommand::DeleteCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{
    
}

void DeleteCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mShape);
    model->SetCurrSelected(nullptr);
//    mShape = nullptr;
}

void DeleteCommand::Undo(std::shared_ptr<PaintModel> model)
{
    model->AddShape(mShape);
}

void DeleteCommand::Redo(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mShape);
}
