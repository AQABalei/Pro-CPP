#include "Node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.emplace_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
	// TODO: Loop through statements in list and code gen them
    for(int i=0; i<mStatements.size(); ++i)
    {
        mStatements[i]->CodeGen(context);
    }
    if(mMainBlock)
    {
        context.mOps.emplace_back("goto,1");
        context.mGotoChain[context.mOps.size()] = 1;
    }
}

NNumeric::NNumeric(std::string& value)
{
	mValue = std::stoi(value);
}

NRotate::NRotate(NNumeric* dir)
	: mDir(dir)
{
}

void NRotate::CodeGen(CodeContext& context) const
{
	if (mDir->mValue == 0)
	{
		context.mOps.emplace_back("rotate,0");
	}
	else if (mDir->mValue == 1)
	{
		context.mOps.emplace_back("rotate,1");
	}
}

void NForward::CodeGen(CodeContext& context) const
{
    context.mOps.emplace_back("forward");
}

void NAttack::CodeGen(CodeContext& context) const
{
    context.mOps.emplace_back("attack");
}

void NRangedAttack::CodeGen(CodeContext& context) const
{
    context.mOps.emplace_back("ranged_attack");
}

void NIf::CodeGen(CodeContext& context) const
{
    mCondition->CodeGen(context);//test flag
    context.mOps.emplace_back("je,");//je to if block
    int ifLineNum = context.mOps.size() - 1;
    mElseBlock->CodeGen(context);//else block code
    context.mOps.emplace_back("goto,");//goto passs the if block
    int elseLineNum = context.mOps.size() - 1;
    int ifBegin = context.mOps.size() + 1;
    mIfBlock->CodeGen(context);//if block
    int ifEnd = context.mOps.size() + 1;
    
    context.mOps[ifLineNum] = context.mOps[ifLineNum] + std::to_string(ifBegin);
    context.mOps[elseLineNum] = context.mOps[elseLineNum] + std::to_string(ifEnd);
    
    context.mGotoChain[elseLineNum + 1] = ifEnd;
}

void NIsHuman::CodeGen(CodeContext& context) const
{
    if(mDist->mValue == 1)
    {
        context.mOps.emplace_back("test_human,1");
    }
    else if(mDist->mValue == 2)
    {
        context.mOps.emplace_back("test_human,2");
    }
}

void NIsZombie::CodeGen(CodeContext& context) const
{
    if(mDist->mValue == 1)
    {
        context.mOps.emplace_back("test_zombie,1");
    }
    else if(mDist->mValue == 2)
    {
        context.mOps.emplace_back("test_zombie,2");
    }
}

void NIsPassable::CodeGen(CodeContext& context) const
{
    context.mOps.emplace_back("test_passable");
}

void NIsRandom::CodeGen(CodeContext& context) const
{
    context.mOps.emplace_back("test_random");
}
