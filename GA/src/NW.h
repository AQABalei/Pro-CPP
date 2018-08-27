//
//  NW.h
//  pa3
//
//  Created by Zhong Chu on 2/20/18.
//

#ifndef NW_h
#define NW_h
#include <string>
#include <vector>
#include <algorithm>
#include "Parser.h"
class NW
{
public:
    NW(std::string inputFile1, std::string inputFile2);
    void NeedlemanWunsch();
    std::string mHeader1;
    std::string mHeader2;
    std::string mSequence1;
    std::string mSequence2;
    std::string mSeqA;
    std::string mSeqB;
    int mScore;
    
    std::vector<std::vector<short> > mShortVec;
    std::vector<std::vector<char> > mCharVec;
};

#endif /* NW_h */
