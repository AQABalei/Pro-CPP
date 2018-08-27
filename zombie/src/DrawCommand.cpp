//
//  DrawCommand.cpp
//  main
//
//  Created by Zhong Chu on 3/17/18.
//
#include "DrawCommand.h"
#include "PaintModel.h"

DrawCommand::DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{
    
}

void DrawCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mShape->Finalize();
}

void DrawCommand::Update(const wxPoint& newPoint)
{
    Command::Update(newPoint);
    mShape->Update(newPoint);
}

void DrawCommand::Undo(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mShape);
    model->SetCurrSelected(nullptr);
}

void DrawCommand::Redo(std::shared_ptr<PaintModel> model)
{
    model->AddShape(mShape);
}
