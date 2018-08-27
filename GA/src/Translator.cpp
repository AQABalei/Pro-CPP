//
//  Translator.cpp
//  main
//
//  Created by Zhong Chu on 2/19/18.
//
#include "Translator.h"

Translator::Translator()
{
    mAminoAcidMap['A'] = 0;
    mAminoAcidMap['C'] = 0;
    mAminoAcidMap['D'] = 0;
    mAminoAcidMap['E'] = 0;
    mAminoAcidMap['F'] = 0;
    mAminoAcidMap['G'] = 0;
    mAminoAcidMap['H'] = 0;
    mAminoAcidMap['I'] = 0;
    mAminoAcidMap['K'] = 0;
    mAminoAcidMap['L'] = 0;
    mAminoAcidMap['M'] = 0;
    mAminoAcidMap['N'] = 0;
    mAminoAcidMap['P'] = 0;
    mAminoAcidMap['Q'] = 0;
    mAminoAcidMap['R'] = 0;
    mAminoAcidMap['S'] = 0;
    mAminoAcidMap['T'] = 0;
    mAminoAcidMap['V'] = 0;
    mAminoAcidMap['W'] = 0;
    mAminoAcidMap['Y'] = 0;
}

std::string Translator::StartCodon(std::string sequence)//using state machine to translate
{
    int currRow = 0;
    int currCol = 0;
    std::string toReturn;
    for(int i=0; i<sequence.size(); ++i)
    {
        if(sequence[i] == 'T')
        {
            currCol = 0;
        }
        else if(sequence[i] == 'C')
        {
            currCol = 1;
        }
        else if(sequence[i] == 'A')
        {
            currCol = 2;
        }
        else
        {
            currCol = 3;
        }
        if(mStateMachine[currRow][currCol] >= 'A' && mStateMachine[currRow][currCol] <= 'Z')
        {
            toReturn = toReturn + mStateMachine[currRow][currCol];
            mAminoAcidCount += 1;
            mAminoAcidMap[mStateMachine[currRow][currCol]] += 1;
            currRow = 3;
        }
        else
        {
            currRow = mStateMachine[currRow][currCol];
        }
    }
    return toReturn;
}
