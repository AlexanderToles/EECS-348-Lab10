#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void validate_expression(vector<string> file_data){
    string valid_chars = "-+0123456789";
    for(int i = 0; i < file_data.size();++i){
        bool invalid = 0;
        bool operator_flag = 0;
        bool decimal_flag = 0;

        //check if any of the characters are not valid.
        size_t found = file_data[i].find_first_not_of("-+0123456789."); 
        if(found!=string::npos){
            invalid = 1;
        }

        //check for operator, set flag
        if((file_data[i][0] == '+')||( file_data[i][0] == '-')){
            operator_flag = 1;
        }

        //go through every char, check validation
        for(int j = 0; j < file_data[i].length();++j){
            //check for duplicated decimals
            if(file_data[i][j] == '.'){
                if(decimal_flag){
                    invalid = 1;
                }
                else{
                    decimal_flag = 1;
                }
            }
            //check for duplicated operators
            if(j>0 && ((file_data[i][j] == '+' )|| (file_data[i][j] == '-' ))){
                if(operator_flag){
                    invalid = 1;
                }
            }
        }
        
        if(invalid){
            cout << "string: " << file_data[i] << " is invalid.\n";
        }
        else{ //clean the string, adding a decimal if needed, removing trailing zeros.
            //if there is not a decimal, add a decimal and a 0
            //if there is a decimal, remove trailing 0s
            if(!decimal_flag){
                file_data[i] = file_data[i]+".0";
            }
            else{
                while(file_data[i][file_data[i].length()-1]=='0'){
                    file_data[i].pop_back();
                }
            }
            //remove leading 0s
            if(operator_flag){
                while(file_data[i][1]=='0' && file_data[i][2]!='.'){
                    file_data[i].erase(file_data[i].begin()+1,file_data[i].begin()+2);
                }
            }
            else{
                while(file_data[i][0]=='0' && file_data[i][1]!='.'){
                    file_data[i].erase(file_data[i].begin(),file_data[i].begin()+1);
                }
            }
            cout << "string: " << file_data[i] << "\n";
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