//
//  Parser.cpp
//  main
//
//  Created by Zhong Chu on 2/19/18.
//

#include "Parser.h"
#include "iostream"

Parser::Parser(std::string fileName)
{
    std::ifstream file (fileName.c_str(), std::ios::in|std::ios::ate);
    std::ifstream::pos_type size;
    std::string firstLine;
    std::string followingLines;
    if(file.is_open())
    {
        size = file.tellg();
    }
    std::ifstream input (fileName.c_str());
    getline(input, firstLine);
    mHeader = firstLine;
    while(static_cast<bool>(getline(input, followingLines)))
    {
        for(int i=0; i<followingLines.size(); ++i)
        {
            if(followingLines[i] != 'A' && followingLines[i] != 'G' && followingLines[i] != 'C' && followingLines[i] != 'T')//Clear out the invalid characters
            {
                followingLines.erase(i, 1);
            }
        }
        mSequence += followingLines;
    }
}
