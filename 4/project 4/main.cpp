//
//  main.cpp
//  4.1
//
//  Created by 杨博超 on 16/5/27.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

// every bucket stores a 8-byte string and the offset
class Bucket
{
public:
    void add(string s, int i)
    {
        m_s += s;
        offSet = i;
    }
    
    string getM_s()
    {
        return m_s;
    }
    
    int getOffSet()
    {
        return offSet;
    }
    
    Bucket()
    {
        m_s = "";
        offSet = 0;
    }
private:
    string m_s;
    int offSet;
};

// check whether the string is in the original table
// use a vector to store every offset which has identical string with the string passed in
int checkIn(string s, Bucket* hashTree[], int size, vector<int>& v)
{
    for (int m = 0; m < size; m++)
    {
        if (hashTree[m]->getM_s() == s)
        {
            v.push_back(hashTree[m]->getOffSet());
        }
        // put a restriction here to accelerate
        if (v.size() == 50000)
        {
            break;
        }
    }
    
    // return a junk number if empty
    if (v.empty())
    {
        return -2;
    }
    // if not empty, return -1
    else
    {
        return -1;
    }
}
// copied from spec
// never been changed
bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd)  ||  (cmd == '\n'  &&  !inf.get(cmd)) )
    {
        cmd = 'x';
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
    }
    return false;
}

void createDelta(istream& oldf, istream& newf, ostream& deltaf)
{
    // transfer the in-text file to a big string
    std::string inString;
    std::string tool1;
    while (getline(oldf, tool1))
    {
        inString += tool1 + 'n';
    }
    
    // transfer the off-text file to another big string
    std::string offString;
    std::string tool2;
    while (getline(newf, tool2))
    {
        offString += tool2 + 'n';
    }
    // pop the last '\n'
    // so that it won't be copied
    offString.pop_back();
    
    int N = 8;
    int sizeIn;
    // find how many 8-bytes string are there in the inString
    if (inString.size() <= 8)
    {
        sizeIn = 1;
    }
    else
    {
        sizeIn =  static_cast<int>(inString.size() - 7);
    }
    
    // create an array of buckets of sizeIn
    Bucket* hashTree[sizeIn];
    
    for (int m = 0; m < sizeIn; m++)
    {
        string s;
        for (int n = 0; n < N; n++)
        {
            s = s + inString[m + n];
        }
        hashTree[m] = new Bucket();
        hashTree[m]->add(s, m);
    }
    
    for (int j = 0; j < static_cast<int>(offString.size()); j++)
    {
        // get every 8-bytes string from the offString
        string s1;
        for (int i = 0; i < N; i++)
        {
            s1 = s1 + offString[j + i];
        }
        // create a vector here to store different offset which satisfy the condition
        vector<int> v;
        // if found, copy
        if (checkIn(s1, hashTree, sizeIn, v) == -1)
        {
            int maxLength = 0;
            int offsetOut = -1;
            // for each offset, see how long is the matching length
            for (int i = 0; i != v.size(); i++)
            {
                int copyJ = j;
                int curC = v[i];
                int L = 0;
                while (inString[curC] == offString[j])
                {
                    L++;
                    curC++;
                    j++;
                }
                // find the longest matching length
                if (L > maxLength)
                {
                    maxLength = L;
                    offsetOut = v[i];
                    j = copyJ;
                }
                // else, increment to next offset
                else
                {
                    j = copyJ;
                }
            }
            j = j + maxLength;
            j--;
            deltaf << "C" << maxLength << "," << offsetOut;
        }
        // if not found, add
        else if (checkIn(s1, hashTree, sizeIn, v) == -2)
        {
            int countAdd = 0;
            // store each first letter in a string
            // at the end, add the string
            string s2;
            while (checkIn(s1, hashTree, sizeIn, v) == -2 && (countAdd + j) != static_cast<int>(offString.size()))
            {
                s2 += s1[0];
                countAdd++;
                s1 = "";
                for (int i = 0; i < N; i++)
                {
                    s1 = s1 + offString[countAdd + j + i];
                }
            }
            j = j + static_cast<int>(s2.size()) - 1;
            deltaf << "A" << static_cast<int>(s2.size()) << ":" << s2;
        }
    }
    // free the memory
    for (int m = 0; m < sizeIn; m++)
    {
        delete hashTree[m];
    }
}

bool applyDelta(istream& oldf, istream& deltaf, ostream& newf)
{
    char CMD;
    char next;
    int length = 0;
    int offset = 0;
    
    // while the deltaF is not empty
    do
    {
        if(!getCommand(deltaf, CMD, length, offset))
        {
            return false;
        }
        
        // while invalid things happen, return false
        if ((CMD != 'A' && CMD != 'C' && CMD != 'x') || length < 0 || offset < 0)
        {
            return false;
        }
        
        // command is add, add the string to newfile from deltafile
        if(CMD == 'A')
        {
            for(int i = 1; i < length + 1; i++)
            {
                deltaf.get(next);
                newf << next;
            }
        }
        
        // command is copy, copy the string from oldfile to newfile
        else if(CMD == 'C')
        {
            oldf.seekg(offset);
            
            for(int i = 1; i < length + 1; i++)
            {
                oldf.get(next);
                newf << next;
            }
        }
        
    } while(CMD != 'x');
    
    return true;
}

//void runtest(string oldtext, string newtext)
//{
//    string s;
//    istringstream oldfile(oldtext);
//    istringstream newfile(newtext);
//    ostringstream deltafile;
//    createDelta(oldfile, newfile, deltafile);
//    string result = deltafile.str();
//    cout << "The delta length is " << result.size()
//    << " and its text is " << endl;
//    cout << result << endl;
//    
//    oldfile.clear();   // clear the end of file condition
//    oldfile.seekg(0);  // reset back to beginning of the stream
//    istringstream deltafile2(result);
//    ostringstream newfile2;
//    assert(applyDelta(oldfile, deltafile2, newfile2));
//    s = newfile2.str();
//    assert(newtext == newfile2.str());
//}
//
//int main()
//{
//    runtest("There's a bathroom on the right.",
//            "There's a bad moon on the rise.");
//    runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//            "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
//    cout << "All tests passed" << endl;

//bool runtest(string oldname, string newname, string deltaname, string newname2)
//{
//    ifstream oldfile(oldname);
//    if (!oldfile)
//    {
//        cerr << "Cannot open " << oldname << endl;
//        return false;
//    }
//    ifstream newfile(newname);
//    if (!newfile)
//    {
//        cerr << "Cannot open " << newname << endl;
//        return false;
//    }
//    ofstream deltafile(deltaname);
//    if (!deltafile)
//    {
//        cerr << "Cannot create " << deltaname << endl;
//        return false;
//    }
//    createDelta(oldfile, newfile, deltafile);
//    deltafile.close();
//    
//    oldfile.clear();   // clear the end of file condition
//    oldfile.seekg(0);  // reset back to beginning of the file
//    ifstream deltafile2(deltaname);
//    if (!deltafile2)
//    {
//        cerr << "Cannot read the " << deltaname << " that was just created!" << endl;
//        return false;
//    }
//    ofstream newfile2(newname2);
//    if (!newfile2)
//    {
//        cerr << "Cannot create " << newname2 << endl;
//        return false;
//    }
//    assert(applyDelta(oldfile, deltafile2, newfile2));
//    cout << "You must compare " << newname << " and " << newname2 << endl;
//    cout << "If they are not identical, you failed this test." << endl;
//    return true;
//}
//
//int main()
//{
//    assert(runtest("/Users/StevenYang/Desktop/greeneggs1.txt", "/Users/StevenYang/Desktop/greeneggs2.txt", "/Users/StevenYang/Desktop/empty.txt", "/Users/StevenYang/Desktop/test2.txt"));




int main()
{
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/smallmart1.txt", ifstream::in);
//    ifstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/smallmart2.txt", ifstream::in);
//    ofstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty.txt", ifstream::out);
//    createDelta(oldFile, newFile, deltaF); //93 94
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/smallmart1.txt", ifstream::in);
//    ifstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty.txt", ifstream::in);
//    ofstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/test2.txt", ifstream::out);
//    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/greeneggs1.txt", ifstream::in);
//    ifstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/greeneggs2.txt", ifstream::in);
//    ofstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 2.txt", ifstream::out);
//    createDelta(oldFile, newFile, deltaF); //65 69
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/greeneggs1.txt", ifstream::in);
//    ifstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 2.txt", ifstream::in);
//    ofstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/test2 2.txt", ifstream::out);
//    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/strange1.txt", ifstream::in);
//    ifstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/strange2.txt", ifstream::in);
//    ofstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 3.txt", ifstream::out);
//    createDelta(oldFile, newFile, deltaF); //7213 8746
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/strange1.txt", ifstream::in);
//    ifstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 3.txt", ifstream::in);
//    ofstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/test2 3.txt", ifstream::out);
//    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/warandpeace1.txt", ifstream::in);
//    ifstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/warandpeace2.txt", ifstream::in);
//    ofstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 4.txt", ifstream::out);
//    createDelta(oldFile, newFile, deltaF); //380 393
    
//    ifstream oldFile;
//    oldFile.open("/Users/StevenYang/Desktop/warandpeace1.txt", ifstream::in);
//    ifstream deltaF;
//    deltaF.open("/Users/StevenYang/Desktop/empty 4.txt", ifstream::in);
//    ofstream newFile;
//    newFile.open("/Users/StevenYang/Desktop/test2 4.txt", ifstream::out);
//    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/smallmart1.txt", ifstream::in);
    //    ifstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/smallmart2.txt", ifstream::in);
    //    ofstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 5.txt", ifstream::out);
    //    createDelta(oldFile, newFile, deltaF); //93
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/smallmart1.txt", ifstream::in);
    //    ifstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 5.txt", ifstream::in);
    //    ofstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/test2 5.txt", ifstream::out);
    //    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/greeneggs1.txt", ifstream::in);
    //    ifstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/greeneggs2.txt", ifstream::in);
    //    ofstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 6.txt", ifstream::out);
    //    createDelta(oldFile, newFile, deltaF); //65
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/greeneggs1.txt", ifstream::in);
    //    ifstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 6.txt", ifstream::in);
    //    ofstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/test2 6.txt", ifstream::out);
    //    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
//        ifstream oldFile;
//        oldFile.open("/Users/StevenYang/Desktop/strange1.txt", ifstream::in);
//        ifstream newFile;
//        newFile.open("/Users/StevenYang/Desktop/strange2.txt", ifstream::in);
//        ofstream deltaF;
//        deltaF.open("/Users/StevenYang/Desktop/empty 7.txt", ifstream::out);
//        createDelta(oldFile, newFile, deltaF); //7213
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/strange1.txt", ifstream::in);
    //    ifstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 7.txt", ifstream::in);
    //    ofstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/test2 7.txt", ifstream::out);
    //    applyDelta(oldFile, deltaF, newFile);
    
    
    
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/warandpeace1.txt", ifstream::in);
    //    ifstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/warandpeace2.txt", ifstream::in);
    //    ofstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 8.txt", ifstream::out);
    //    createDelta(oldFile, newFile, deltaF); //394
    
    //    ifstream oldFile;
    //    oldFile.open("/Users/StevenYang/Desktop/warandpeace1.txt", ifstream::in);
    //    ifstream deltaF;
    //    deltaF.open("/Users/StevenYang/Desktop/empty 8.txt", ifstream::in);
    //    ofstream newFile;
    //    newFile.open("/Users/StevenYang/Desktop/test2 8.txt", ifstream::out);
    //    applyDelta(oldFile, deltaF, newFile);
}