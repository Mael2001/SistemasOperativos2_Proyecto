#define STDC_FORMAT_MACROS
#ifdef _MSC_VER
#define CRT_SECURE_NO_WARNINGS
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

struct traceRecord
{
    string memAddress;
    char operationType;
    traceRecord(): memAddress(""), operationType('R') {

    }
};

traceRecord hydrateRecord(traceRecord traceLine, string line) {
    vector<string> words{};
    stringstream sstream(line);
    string word;
    while (std::getline(sstream, word, ' ')) {
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        words.push_back(word);
    }
    traceLine.memAddress = words.at(0);
    traceLine.operationType = words.at(1).at(0);
    return traceLine;
}

int main() {
    std::fstream fh;
    std::string filename;
    cout << "Archivo a leer" << endl;
    cin >> filename;
    fh.open("C:/Users/Marzo/OneDrive/Documents/Q4 2021/Siso 2/Proyecto/"+filename+".trace", std::fstream::in | std::fstream::binary);
    int count{0};
    if (fh.is_open())
    {
        std::string line;
        while (std::getline(fh, line))
        {
            traceRecord traceLine;
            traceLine = hydrateRecord(traceLine, line);
            cout << "----------------------------------------------------" << endl;
            cout <<"Record ["<<count<<"]"<<" Mem.Address: [" << traceLine.memAddress << "]"<<"Operation Type: [" << traceLine.operationType<<"]" << endl;
            count++;
        }
    }
    fh.close();
    return 0;
}