#include "SrcMain.h"
#include <iostream>

void ProcessCommandArgs(int argc, const char* argv[])
{
	// TODO
    std::string singleFileName;
    std::string pairWiseFileName1;
    std::string pairWiseFileName2;
    std::ofstream output;
    if(argc == 2)
    {
        singleFileName = argv[1];
        Parser myParser(singleFileName);
        Translator myTranslator;
        myParser.mHeader.erase(0,1);
        std::string aminoAcids = myTranslator.StartCodon(myParser.mSequence);
        output.open("amino.txt");
        output << myParser.mHeader << std::endl;
        output << "Total amino acids produced: " << myTranslator.mAminoAcidCount << std::endl;
        std::unordered_map<char, int>::iterator itA = myTranslator.mAminoAcidMap.find('A');
        output << "(A) Alanine: " << itA->second << std::endl;
        std::unordered_map<char, int>::iterator itC = myTranslator.mAminoAcidMap.find('C');
        output << "(C) Cysteine: " << itC->second << std::endl;
        std::unordered_map<char, int>::iterator itD = myTranslator.mAminoAcidMap.find('D');
        output << "(D) Aspartic acid: " << itD->second << std::endl;
        std::unordered_map<char, int>::iterator itE = myTranslator.mAminoAcidMap.find('E');
        output << "(E) Glutamic acid: " << itE->second << std::endl;
        std::unordered_map<char, int>::iterator itF = myTranslator.mAminoAcidMap.find('F');
        output << "(F) Phenylalanine: " << itF->second << std::endl;
        std::unordered_map<char, int>::iterator itG = myTranslator.mAminoAcidMap.find('G');
        output << "(G) Glycine: " << itG->second << std::endl;
        std::unordered_map<char, int>::iterator itH = myTranslator.mAminoAcidMap.find('H');
        output << "(H) Histidine: " << itH->second << std::endl;
        std::unordered_map<char, int>::iterator itI = myTranslator.mAminoAcidMap.find('I');
        output << "(I) Isoleucine: " << itI->second << std::endl;
        std::unordered_map<char, int>::iterator itK = myTranslator.mAminoAcidMap.find('K');
        output << "(K) Lysine: " << itK->second << std::endl;
        std::unordered_map<char, int>::iterator itL = myTranslator.mAminoAcidMap.find('L');
        output << "(L) Leucine: " << itL->second << std::endl;
        std::unordered_map<char, int>::iterator itM = myTranslator.mAminoAcidMap.find('M');
        output << "(M) Methionine: " << itM->second << std::endl;
        std::unordered_map<char, int>::iterator itN = myTranslator.mAminoAcidMap.find('N');
        output << "(N) Asparagine: " << itN->second << std::endl;
        std::unordered_map<char, int>::iterator itP = myTranslator.mAminoAcidMap.find('P');
        output << "(P) Proline: " << itP->second << std::endl;
        std::unordered_map<char, int>::iterator itQ = myTranslator.mAminoAcidMap.find('Q');
        output << "(Q) Glutamine: " << itQ->second << std::endl;
        std::unordered_map<char, int>::iterator itR = myTranslator.mAminoAcidMap.find('R');
        output << "(R) Arginine: " << itR->second << std::endl;
        std::unordered_map<char, int>::iterator itS = myTranslator.mAminoAcidMap.find('S');
        output << "(S) Serine: " << itS->second << std::endl;
        std::unordered_map<char, int>::iterator itT = myTranslator.mAminoAcidMap.find('T');
        output << "(T) Threonine: " << itT->second << std::endl;
        std::unordered_map<char, int>::iterator itV = myTranslator.mAminoAcidMap.find('V');
        output << "(V) Valine: " << itV->second << std::endl;
        std::unordered_map<char, int>::iterator itW = myTranslator.mAminoAcidMap.find('W');
        output << "(W) Tryptophan: " << itW->second << std::endl;
        std::unordered_map<char, int>::iterator itY = myTranslator.mAminoAcidMap.find('Y');
        output << "(Y) Tyrosine: " << itY->second << std::endl;
    }
    else if(argc == 3)
    {
        pairWiseFileName1 = argv[1];
        pairWiseFileName2 = argv[2];
        NW myNW(pairWiseFileName1, pairWiseFileName2);
        myNW.NeedlemanWunsch();
        int lineNum = myNW.mSeqA.size() / 70;
        int lastLineSize = myNW.mSeqA.size() % 70;
        output.open("match.result");
        output << "A: " << myNW.mHeader1 << std::endl;
        output << "B: " << myNW.mHeader2 << std::endl;
        output << "Score: " << myNW.mScore << std::endl;
        output << std::endl;
        for(int i=0; i<lineNum; ++i)//70 chars output
        {
            for(int j=0; j<70; ++j)//A sequence output
            {
                if(myNW.mSeqA[70*i+j] == ' ')
                {
                    output << "_";
                }
                else
                {
                    output << myNW.mSeqA[70*i+j];
                }
            }
            output << std::endl;
            for(int j=0; j<70; ++j)//the matching '|' output
            {
                if(myNW.mSeqA[70*i+j] == myNW.mSeqB[70*i+j])
                {
                    output << "|";
                }
                else
                {
                    output << " ";
                }
            }
            output << std::endl;
            for(int j=0; j<70; ++j)//B sequence output
            {
                if(myNW.mSeqB[70*i+j] == ' ')
                {
                    output << "_";
                }
                else
                {
                    output << myNW.mSeqB[70*i+j];
                }
            }
            output << std::endl;
            output << std::endl;
        }
        for(int i=70*lineNum; i<70*lineNum + lastLineSize; ++i)//last line output
        {
            if(myNW.mSeqA[i] == ' ')
            {
                output << "_";
            }
            else
            {
                output << myNW.mSeqA[i];
            }
        }
        output << std::endl;
        for(int i=70*lineNum; i<70*lineNum + lastLineSize; ++i)
        {
            if(myNW.mSeqA[i] == myNW.mSeqB[i])
            {
                output << "|";
            }
            else
            {
                output << " ";
            }
        }
        output << std::endl;
        for(int i=70*lineNum; i<70*lineNum + lastLineSize; ++i)
        {
            if(myNW.mSeqB[i] == ' ')
            {
                output << "_";
            }
            else
            {
                output << myNW.mSeqB[i];
            }
        }
        output << std::endl;
    }
}
