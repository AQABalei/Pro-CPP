#include "Command.h"
#include "Shape.h"
#include "DrawCommand.h"
#include "SetPenCommand.h"
#include "SetBrushCommand.h"
#include "DeleteCommand.h"
#include "MoveCommand.h"
#include "PaintModel.h"
#include "RectShape.h"
#include "EllipseShape.h"
#include "Line.h"
#include "PencilShape.h"

Command::Command(const wxPoint& start, std::shared_ptr<Shape> shape)
	:mStartPoint(start)
	,mEndPoint(start)
	,mShape(shape)
{

}

// Called when the command is still updating (such as in the process of drawing)
void Command::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;
}

std::shared_ptr<Command> CommandFactory::Create(std::shared_ptr<PaintModel> model,
	CommandType type, const wxPoint& start)
{
    // TODO: Actually create a command based on the type passed in
	std::shared_ptr<Command> retVal;
    std::shared_ptr<Shape> shapePtr;
    switch(type){
        case CM_DrawRect:
            shapePtr = std::make_shared<RectShape>(start);
            retVal = std::make_shared<DrawCommand>(start, shapePtr);
            model->AddShape(shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
        case CM_DrawEllipse:
            shapePtr = std::make_shared<EllipseShape>(start);
            retVal = std::make_shared<DrawCommand>(start, shapePtr);
            model->AddShape(shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
        case CM_DrawLine:
            shapePtr = std::make_shared<Line>(start);
            retVal = std::make_shared<DrawCommand>(start, shapePtr);
            model->AddShape(shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
        case CM_DrawPencil:
            shapePtr = std::make_shared<PencilShape>(start);
            retVal = std::make_shared<DrawCommand>(start, shapePtr);
            model->AddShape(shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
        case CM_Move:
            shapePtr = model->GetCurrSelected();
            retVal = std::make_shared<MoveCommand>(start, shapePtr);
            break;
        case CM_Delete:
            shapePtr = model->GetCurrSelected();
            retVal = std::make_shared<DeleteCommand>(start, shapePtr);
            break;
        case CM_SetPen:
            shapePtr = model->GetCurrSelected();
            retVal = std::make_shared<SetPenCommand>(start, shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
        case CM_SetBrush:
            shapePtr = model->GetCurrSelected();
            retVal = std::make_shared<SetBrushCommand>(start, shapePtr);
            shapePtr->SetPen(model->GetPen());
            shapePtr->SetBrush(model->GetBrush());
            break;
    }
	return retVal;
}
