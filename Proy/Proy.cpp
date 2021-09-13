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
    inline string toString()
    {
        string string = "";
        string += "|" + data.operationType;
        string += "\nV";
        string += data.memAddress + "\n";
       return  string;
    }
};

struct NodeList
{
    Node* origin;
    Node* lastNode;
    inline string toString()
    {
        string toString = "[Origin Node {" + origin->toString() + "}]";
        toString+= "\n[Last Node {" + lastNode->toString() + "}]";
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
NodeList* memLoader()
{
    std::fstream fh;
    std::string filename;
    NodeList* nodeList = new NodeList();
    cout << "Archivo a leer" << endl;
    cin >> filename;
    fh.open("C:/Users/Skytech/OneDrive/Documents/Q4 2021/Siso 2/Proyecto/" + filename + ".trace", std::fstream::in | std::fstream::binary);
    int count{ 0 };
    if (fh.is_open())
    {
        std::string line;
        while (std::getline(fh, line))
        {
            traceRecord traceLine;
            traceLine = hydrateRecord(traceLine, line);
            Node* newNode = new Node(traceLine);
            if (nodeList->origin == NULL)
            {
                nodeList->origin = newNode;
                nodeList->lastNode = newNode;
            }
            else
            {
                nodeList->lastNode->next = newNode;
                nodeList->lastNode = newNode;
            }
            count++;
        }
    }
    fh.close();
    return nodeList;
}

bool existNode(Node* node, NodeList* list)
{
    Node* currNode = list->origin;
    while (currNode != list->lastNode)
    {
        if (node == currNode)
        {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

NodeList* cleanOperations(NodeList* nodes)
{
    NodeList* cleanList = new NodeList();
    Node* currNode = nodes->origin;
    cleanList->lastNode = currNode;
    cleanList->origin = currNode;
	while (currNode != nodes->lastNode)
	{
		if (!existNode(currNode,cleanList))
		{
            cleanList->lastNode->next = currNode;
            cleanList->lastNode = currNode;
		}
        currNode = currNode->next;
	}
    return cleanList;
}
void DisplayMemOperations(NodeList* nodes)
{
    Node* currNode = nodes->origin;
    while (currNode != nodes->lastNode)
    {
        currNode->toString();
        currNode = currNode->next;
    }
};

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
    NodeList* memOperations = memLoader();
    NodeList* memOperationsClean = cleanOperations(memOperations);
    DisplayMemOperations(memOperationsClean);
    return 0;
}
