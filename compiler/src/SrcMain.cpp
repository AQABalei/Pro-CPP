#include "SrcMain.h"
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "Node.h"
#include <fstream>
#include <string>

extern int gLineNumber;
extern NBlock* gMainBlock;

extern int zompilerparse(); // NOLINT
struct yy_buffer_state; // NOLINT
extern void zompiler_flush_buffer(yy_buffer_state* b); // NOLINT
extern FILE* zompilerin; // NOLINT

void ProcessCommandArgs(int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cout << "You must pass the input file as a command line parameter." << std::endl;
		return;
	}
    
	// Read input from the first command line parameter
	zompilerin = fopen(argv[1], "r");
	if (zompilerin == nullptr)
	{
		std::cout << "File not found: " << argv[1] << std::endl;
		return;
	}
	zompiler_flush_buffer(nullptr);

	// Start the parse
	zompilerparse();
    
	// TODO: CodeGen from gMainBlock
    if(gMainBlock != nullptr)
    {
        CodeContext myContext;
        gMainBlock->CodeGen(myContext);
        std::ofstream output("out.zom");
        if(argc == 3)
        {
            std::string argv2(argv[2]);
            if(argv2 == "-o")//do optimize
            {
                for(auto it = myContext.mGotoChain.begin(); it != myContext.mGotoChain.end(); ++it)
                {
                    int gotoLine = it->second;
                    while(myContext.mGotoChain.find(gotoLine) != myContext.mGotoChain.end())
                    {
                        gotoLine = myContext.mGotoChain.find(gotoLine)->second;
                    }
                    myContext.mOps[it->first - 1] = "goto," + std::to_string(gotoLine);
                }
            }
        }
        for(int i=0; i<myContext.mOps.size(); ++i)//output to out.zom
        {
            output << myContext.mOps[i] << std::endl;
        }
    }
    else
    {
        std::cout << "error!" << std::endl;
    }
    
	// Close the file stream
	fclose(zompilerin);
    
}

void zompilererror(const char* s) // NOLINT
{
	std::cout << s << " on line " << gLineNumber << std::endl;
}
