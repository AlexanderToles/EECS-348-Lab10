#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void scanFile(vector<string> fileData){

}


bool verify(string fileName){ //check if the input file is able to be opened
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){
        string line;
        vector<string> fileData;
        while(getline(inputFile,line)){ //create a vector containing each of the lines
            fileData.push_back(line);
        }
        scanFile(fileData);    //pass vector to the scanFile function
        return 1;
    }
    else{
        cout << "File not found.\n";
        return 0;
    }
}

int main() {
    while(true){ //prompt user for input file name until valid name is chosen
        string fileName;
        cout << "Enter file name: ";
        cin >> fileName;
        if(verify(fileName)){ //check if file was able to be opened
            break;
        }
    }
    return 0;
}