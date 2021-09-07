#define STDC_FORMAT_MACROS
#ifdef _MSC_VER
#define CRT_SECURE_NO_WARNINGS
#endif
#include <bits-stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

struct traceRecord
{
    int32_t microOpCount;
    uint64_t instructionAddress;
    int32_t sourceRegister1;
    int32_t sourceRegister2;
    int32_t destinationRegister;
    char conditionRegister;
    char TNnotBranch;
    char loadStore;
    int64_t immediate;
    uint64_t addressForMemoryOp;
    uint64_t fallthroughPC;
    uint64_t targetAddressTakenBranch;
    char macroOperation[12];
    char microOperation[23];
};

int main() {
    traceRecord bufferRead = 
    {0,
    	0,
    	0,
    	0,
    	0,
    	' ',
    	' ',
    	' ',
    	0,
    	0,
    	0,
    	0,
    	' ',
    	' '
    };

    std::fstream fh;
    string filename;
    cout << "Archivo a leer" << endl;
    cin >> filename;
    fh.open("C:/Users/Skytech/OneDrive/Documents/Q4 2021/Siso 2/Proyecto/"+filename+".trace", std::fstream::in | std::fstream::binary);
    int count{0};
    if (fh.is_open())
    {
        while (!fh.eof())
        {
            fh.read(reinterpret_cast<char*>(&bufferRead.microOpCount), sizeof(bufferRead.microOpCount));
            fh.read(reinterpret_cast<char*>(&bufferRead.instructionAddress), sizeof(bufferRead.instructionAddress));
            fh.read(reinterpret_cast<char*>(&bufferRead.sourceRegister1), sizeof(bufferRead.sourceRegister1));
            fh.read(reinterpret_cast<char*>(&bufferRead.sourceRegister2), sizeof(bufferRead.sourceRegister2));
            fh.read(reinterpret_cast<char*>(&bufferRead.destinationRegister), sizeof(bufferRead.destinationRegister));
            fh.read(&bufferRead.TNnotBranch, sizeof(bufferRead.TNnotBranch));
            fh.read(&bufferRead.loadStore, sizeof(bufferRead.loadStore));
            fh.read(reinterpret_cast<char*>(&bufferRead.immediate), sizeof(bufferRead.immediate));
            fh.read(reinterpret_cast<char*>(&bufferRead.addressForMemoryOp), sizeof(bufferRead.addressForMemoryOp));
            fh.read(reinterpret_cast<char*>(&bufferRead.fallthroughPC), sizeof(bufferRead.fallthroughPC));
            fh.read(reinterpret_cast<char*>(&bufferRead.targetAddressTakenBranch), sizeof(bufferRead.targetAddressTakenBranch));
            fh.read(reinterpret_cast<char*>(&bufferRead.macroOperation), sizeof(bufferRead.macroOperation));
            fh.read(reinterpret_cast<char*>(&bufferRead.microOperation), sizeof(bufferRead.microOperation));
            cout << "=================================================================================================================================================================" << endl;
            cout << "========================================================================="<<"RECORD NO." << count << "========================================================================" << endl;
        	cout << "=================================================================================================================================================================" << endl;
            cout <<"1.Uop: ["<< bufferRead.microOpCount<<']'
        	<< "||2.PC:[" << bufferRead.instructionAddress << ']'
        	<< "||3.Src1:[" <<bufferRead.sourceRegister1 << ']'
        	<< "||4.Src2:[" <<bufferRead.sourceRegister2 << ']'
        	<< "||5.Dest:["<<bufferRead.destinationRegister << ']'
        	<< "||6.Flags: [" <<bufferRead.conditionRegister << ']'
        	<< "||7.Branch: [" <<bufferRead.TNnotBranch << ']'
        	<< "||8.Ld/St: [" <<bufferRead.loadStore << ']'
        	<< "||9.Immediate: ["<<bufferRead.immediate << ']'
        	<< "||10.Mem.Address: [" <<bufferRead.addressForMemoryOp << ']'
        	<< "||11.Fallthrough PC: [" <<bufferRead.fallthroughPC << ']'
        	<< "||12.Target PC: ["<<bufferRead.targetAddressTakenBranch << ']'
        	<< "||13.Macro Opcode: [" <<bufferRead.macroOperation << ']'
        	<< "||14.Micro Opcode: [" <<bufferRead.microOperation << ']'
        	<<std::endl<<std::endl;
        	cout << "=================================================================================================================================================================" << endl;
            count++;
        }
    }
    fh.close();
    return 0;
}