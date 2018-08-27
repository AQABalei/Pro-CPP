//
//  Parser.h
//  pa3
//
//  Created by Zhong Chu on 2/19/18.
//

#ifndef Parser_h
#define Parser_h
#include <string>
#include <fstream>

class Parser
{
public:
    std::string mHeader;
    std::string mSequence;
    Parser(std::string fileName);
};
#endif /* Parser_h */
