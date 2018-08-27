//
//  Translator.h
//  pa3
//
//  Created by Zhong Chu on 2/19/18.
//

#ifndef Translator_h
#define Translator_h
#include <string>
#include <unordered_map>

class Translator
{
public:
    Translator();
    char mStateMachine [24][4] =
    {
    //St|T|C|A|G|
        {0,0,1,0},//0, A in start codon
        {2,0,1,0},//1, T in start codon
        {0,0,1,'M'},//2, G in start codon
        {4,9,14,19},//3, First letter of next amino acid
        {5,6,7,8},//4, T**
        {'F','F','L','L'},//5, TT*
        {'S','S','S','S'},//6, TC*
        {'Y','Y',0,0},//7, TA*
        {'C','C',0,'W'},//8, TG*
        {10,11,12,13},//9, C**
        {'L','L','L','L'},//10, CT*
        {'P','P','P','P'},//11, CC*
        {'H','H','Q','Q'},//12, CA*
        {'R','R','R','R'},//13, CG*
        {15,16,17,18},//14, A**
        {'I','I','I','M'},//15, AT*
        {'T','T','T','T'},//16, AC*
        {'N','N','K','K'},//17, AA*
        {'S','S','R','R'},//18, AG*
        {20,21,22,23},//19, G**
        {'V','V','V','V'},//20, GT*
        {'A','A','A','A'},//21, GC*
        {'D','D','E','E'},//22, GA*
        {'G','G','G','G'}
    };
    std::string StartCodon(std::string sequence);
    int mAminoAcidCount = 0;
    std::unordered_map<char, int> mAminoAcidMap;
};
#endif /* Translator_h */
