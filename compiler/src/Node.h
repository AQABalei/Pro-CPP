#pragma once

#include <vector>
#include <string>
#include <map>

struct CodeContext
{
	std::vector<std::string> mOps;
    std::map<int, int> mGotoChain;
};

class Node
{
public:
	virtual void CodeGen(CodeContext& context) const = 0;
};

class NNumeric : public Node
{
public:
	NNumeric(std::string& value);
	int mValue;
	void CodeGen(CodeContext& context) const override { }
};

class NStatement : public Node
{
    
};

class NRotate : public NStatement
{
public:
	NRotate(NNumeric* dir);
	void CodeGen(CodeContext& context) const override;
private:
	NNumeric* mDir;
};

class NForward : public NStatement
{
public:
    void CodeGen(CodeContext& context) const override;
};

class NAttack : public NStatement
{
public:
    void CodeGen(CodeContext& context) const override;
};

class NRangedAttack : public NStatement
{
public:
    void CodeGen(CodeContext& context) const override;
};

class NBoolean : public Node
{
    
};

class NBlock : public Node
{
public:
	NBlock() { mMainBlock = false; }
	void CodeGen(CodeContext& context) const override;
	void AddStatement(NStatement* statement);
	void SetMainBlock() { mMainBlock = true; }
	void Optimize() { mOptimize = true; }
private:
	std::vector<NStatement*> mStatements;
	bool mMainBlock;
	bool mOptimize = false;
};

class NIf : public NStatement
{
public:
    NIf(NBoolean* condition, NBlock* block)
    {
        mCondition = condition;
        mIfBlock = block;
        mElseBlock = nullptr;
    }
    NIf(NBoolean* condition, NBlock* block, NBlock* nelse)
    {
        mCondition = condition;
        mIfBlock = block;
        mElseBlock = nelse;
    }
    void CodeGen(CodeContext& context) const override;
private:
    NBoolean* mCondition;
    NBlock* mIfBlock;
    NBlock* mElseBlock;
};

class NIsHuman : public NBoolean
{
public:
    NIsHuman(NNumeric* dist)
    {
        mDist = dist;
    }
    void CodeGen(CodeContext& context) const override;
private:
    NNumeric* mDist;
};

class NIsZombie : public NBoolean
{
public:
    NIsZombie(NNumeric* dist)
    {
        mDist = dist;
    }
    void CodeGen(CodeContext& context) const override;
private:
    NNumeric* mDist;
};

class NIsPassable : public NBoolean
{
public:
    void CodeGen(CodeContext& context) const override;
};

class NIsRandom : public NBoolean
{
public:
    void CodeGen(CodeContext& context) const override;
};
