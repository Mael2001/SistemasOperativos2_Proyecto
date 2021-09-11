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
#include <vector>
#include <algorithm>

using namespace std;

struct traceRecord
{
    string memAddress;
    char operationType;
    traceRecord(): memAddress(""), operationType(' ') {}
};
struct Node {
    traceRecord data;
    struct Node* next;
    Node(traceRecord newData)
    {
        data = newData;
        next = new Node();
    }
    Node(){}
    inline string toString(int count)
    {
        string string =" Mem.Address: [";
        string += data.memAddress;
        string += "]";
        string += "\t\tOperation Type: [";
        string += data.operationType;
        string += "]";
       return  string;
    }
};

struct NodeList
{
    Node* origin;
    Node* lastNode;
    inline string toString(int count)
    {
        string toString = "[Origin Node {" + origin->toString(count) + "}]";
        toString+= "\n[Last Node {" + lastNode->toString(count) + "}]";
        return toString;
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
    /*
     07b243a0 R
	00228d40 R
	00228d60 R
	07b243c0 R
	00113360 R
	001fe308 R
	00113380 R
	001fe2f0 R
	001133a0 R
	001133c0 R
	0022ccb0 R
	001133e0 R
	00113400 R  
	0022ccc0 R
	00113420 R
	0020a980 R
	0020a968 R
	00113440 R
	00113460 R
00194730 R*/
    std::fstream fh;
    std::string filename;
    cout << "Archivo a leer" << endl;
    cin >> filename;
    fh.open("C:/Users/Skytech/OneDrive/Documents/Q4 2021/Siso 2/Proyecto/"+filename+".trace", std::fstream::in | std::fstream::binary);
    int count{0};
    if (fh.is_open())
    {
        NodeList* nodeList=new NodeList();
        std::string line;
        while (std::getline(fh, line))
        {
            traceRecord traceLine;
            traceLine = hydrateRecord(traceLine, line);
            cout << "----------------------------------------------------" << endl;
            cout << "--------------------RECORD["<<count<<"]-----------------------" << endl;
            cout << "----------------------------------------------------" << endl;
            Node* newNode = new Node(traceLine);
            if (nodeList->origin==NULL)
            {
                nodeList->origin = newNode;
                nodeList->lastNode = newNode;
            }
            else
            {
                nodeList->lastNode->next = newNode;
                nodeList->lastNode = newNode;
            }
            cout <<nodeList->toString(count)<< endl;
            count++;
        }
    }
    fh.close();
    return 0;
}