#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void validate_expression(vector<string> file_data){
    string valid_chars = "-+0123456789";
    for(int i = 0; i < file_data.size();++i){
        cout << "String: " << file_data[i] << "\n";
        bool valid;
        bool operator_flag;
        size_t found = file_data[i].find_first_not_of("-+0123456789.");
        if(found!=string::npos){
            valid = 0;
            cout << file_data[i] << ": not valid.\n";
        }
        if(file_data[i][0] == '+'|| file_data[i][0] == '-'){
            operator_flag = 1;
        }
    }
    
}


bool verify(string file_name){ //check if the input file is able to be opened
    fstream input_file;
    input_file.open(file_name, fstream::in);
    if(input_file.is_open()){
        string line;
        vector<string> file_data;
        while(getline(input_file,line)){ //create a vector containing each of the lines
            file_data.push_back(line);
        }
        validate_expression(file_data);    //pass vector to the scanFile function
        return 1;
    }
    else{
        cout << "File not found.\n";
        return 0;
    }
}

int main() {
    while(true){ //prompt user for input file name until valid name is chosen
        string file_name;
        cout << "Enter file name: ";
        cin >> file_name;
        if(verify(file_name)){ //check if file was able to be opened
            break;
        }
    }
    return 0;
}