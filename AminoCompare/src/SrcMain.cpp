#include "SrcMain.h"

void ProcessCommandArgs(int argc, const char* argv[])
{
    std::ofstream output;
    if(argc == 3)
    {
        std::string dictionaryFileName = argv[1];
        std::string passwordFileName = argv[2];
        std::unordered_map<std::string, std::string> dictionaryMap;
        std::unordered_map<std::string, std::string> unsolvedList;
        std::unordered_map<std::string, std::string> totalList;
        std::vector<std::string> trackList;
        
        std::ifstream input(dictionaryFileName.c_str());
        std::string line;
        while(static_cast<bool>(getline(input, line)))//read from dictionary file and set up dictionary
        {
            unsigned char hash[20];
            sha1::Calc(line.c_str(), line.size(), hash);
            char key[41];
            sha1::ToHexString(hash, key);
            std::pair<std::string, std::string> templatePair;
            templatePair.first = key;
            templatePair.second = line;
            dictionaryMap.insert(templatePair);
        }
        std::ifstream passwordInput(passwordFileName.c_str());
        output.open("solved.txt");
        while(static_cast<bool>(getline(passwordInput, line)))//read from password file and set up the unsolved list
        {
            std::unordered_map<std::string, std::string>::iterator it = dictionaryMap.find(line);
            trackList.push_back(line);
            if(it != dictionaryMap.end())//if the password is in the dictionary
            {
                totalList.insert({line, dictionaryMap[line]});
            }
            else//if not
            {
                unsolvedList.insert({line, ""});
            }
        }
        tbb::parallel_invoke(//the core parallel programming part
             [&unsolvedList] { BruteForce(unsolvedList, "a", "d999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "eaaa", "h999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "iaaa", "l999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "maaa", "p999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "qaaa", "t999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "uaaa", "x999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "yaaa", "1999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "2aaa", "5999"); },
             [&unsolvedList] { BruteForce(unsolvedList, "6aaa", "9999"); }
        );
        for(auto it = unsolvedList.begin(); it != unsolvedList.end(); ++it)
        {
            if(it->second != "")
            {
                totalList.insert({it->first, it->second});
            }
            else
            {
                totalList.insert({it->first, "??"});
            }
        }
        for(int i=0; i<trackList.size(); ++i)//print the result
        {
            output << trackList[i] << "," << totalList.find(trackList[i])->second << std::endl;
        }
    }
}

void BruteForce(std::unordered_map<std::string, std::string>& unsolved, std::string start, std::string end)
{
    std::vector<int> startPwd = PwdStrToVec(start);
    std::vector<int> endPwd = PwdStrToVec(end);
    while(startPwd != endPwd)
    {
        std::string currPwdStr = VecToPwdStr(startPwd);
        unsigned char hash[20];
        sha1::Calc(currPwdStr.c_str(), currPwdStr.size(), hash);
        char key[41];
        sha1::ToHexString(hash, key);
        if(unsolved.find(key) != unsolved.end())//compare if the currHash is any password in the unsolvedList
        {
            unsolved[key] = currPwdStr;
        }
        ++startPwd[startPwd.size() - 1];
        int currPtr = startPwd.size() - 1;
        while(currPtr >= 1 && startPwd[currPtr] == 36)//handle carry until no need to carry
        {
            startPwd[currPtr] = 0;
            ++startPwd[currPtr - 1];
            currPtr--;
        }
    }
}

std::vector<int> PwdStrToVec(std::string pwdStr)//translate a real password like "aaaa" or "00ab" to a vector of base 36
{
    int diff = 4 - pwdStr.size();
    std::vector<int> toReturn(diff, -1);
    for(int i=0; i<pwdStr.size(); ++i)
    {
        if(pwdStr[i] >= 'a' && pwdStr[i] <= 'z')
        {
            toReturn.push_back(pwdStr[i] - 'a');
        }
        else
        {
            toReturn.push_back(static_cast<int>(pwdStr[i]) - 22);
        }
    }
    return toReturn;
}

std::string VecToPwdStr(std::vector<int> pwdVec)//translate a base 36 vector to a real password like "aaaa" or "00ab" ,etc.
{
    std::string toReturn;
    for(int i=0; i<pwdVec.size(); ++i)
    {
        if(pwdVec[i] >= 0 && pwdVec[i] <= 25)
        {
            toReturn += 'a' + pwdVec[i];
        }
        else if(pwdVec[i] < 0)
        {
            continue;
        }
        else
        {
            toReturn += std::to_string(pwdVec[i] - 26);
        }
    }
    return toReturn;
}
