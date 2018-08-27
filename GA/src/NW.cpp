//
//  NW.cpp
//  main
//
//  Created by Zhong Chu on 2/20/18.
//
#include "NW.h"
#include <iostream>

NW::NW(std::string inputFile1, std::string inputFile2)
{
    Parser myParser1(inputFile1);
    Parser myParser2(inputFile2);
    mHeader1 = myParser1.mHeader;
    mHeader2 = myParser2.mHeader;
    mSequence1 = myParser1.mSequence;
    mSequence2 = myParser2.mSequence;
    mScore = 0;
    
    mHeader1.erase(0,1);
    mHeader2.erase(0,1);
    
    mShortVec.resize(mSequence2.size()+1);
    mCharVec.resize(mSequence2.size()+1);
    for(int i=0; i<mShortVec.size(); ++i)
    {
        mShortVec[i].resize(mSequence1.size()+1);
    }
    for(int i=0; i<mCharVec.size(); ++i)
    {
        mCharVec[i].resize(mSequence1.size()+1);
    }
}

void NW::NeedlemanWunsch()//implement the Needleman-Wunsch algorithm
{
    int matchScore = 1;
    int mismatchScore = -1;
    int gapScore = -1;
    for(int i=0; i<mShortVec[0].size(); ++i)
    {
        mShortVec[0][i] = -1*i;
    }
    for(int i=0; i<mShortVec.size(); ++i)
    {
        mShortVec[i][0] = -1*i;
    }
    for(int i=1; i<mShortVec.size(); ++i)
    {
        for(int j=1; j<mShortVec[i].size(); ++j)
        {
            int aboveLeft;
            if(mSequence2[i-1] == mSequence1[j-1])
            {
                aboveLeft = mShortVec[i-1][j-1] + matchScore;
            }
            else
            {
                aboveLeft = mShortVec[i-1][j-1] + mismatchScore;
            }
            int left = mShortVec[i][j-1] + gapScore;
            int above = mShortVec[i-1][j] + gapScore;
            int maximum = std::max(std::max(aboveLeft, left), above);
            if(maximum == aboveLeft)
            {
                mShortVec[i][j] = aboveLeft;
                mCharVec[i][j] = 'S';
            }
            else if(maximum == left)
            {
                mShortVec[i][j] = left;
                mCharVec[i][j] = 'L';
            }
            else if(maximum == above)
            {
                mShortVec[i][j] = above;
                mCharVec[i][j] = 'A';
            }
        }
    }
    mScore = mShortVec[mShortVec.size()-1][mShortVec[0].size()-1];
    mCharVec[0][0] = 'E';
    for(int i=1; i<mCharVec[0].size(); ++i)
    {
        mCharVec[0][i] = 'L';
    }
    for(int i=1; i<mCharVec.size(); ++i)
    {
        mCharVec[i][0] = 'A';
    }
    int currRow = mShortVec.size() - 1;
    int currCol = mShortVec[0].size() - 1;
    while(!(currCol == 0 && currRow == 0))
    {
        if(mCharVec[currRow][currCol] == 'S')
        {
            mSeqA = mSeqA + mSequence1[currCol-1];
            mSeqB = mSeqB + mSequence2[currRow-1];
            currRow -= 1;
            currCol -= 1;
        }
        else if(mCharVec[currRow][currCol] == 'L')
        {
            mSeqA = mSeqA + mSequence1[currCol-1];
            mSeqB = mSeqB + ' ';
            currCol -= 1;
        }
        else if(mCharVec[currRow][currCol] == 'A')
        {
            mSeqA = mSeqA + ' ';
            mSeqB = mSeqB + mSequence2[currRow-1];
            currRow -= 1;
        }
    }
    std::reverse(mSeqA.begin(), mSeqA.end());
    std::reverse(mSeqB.begin(), mSeqB.end());
}
