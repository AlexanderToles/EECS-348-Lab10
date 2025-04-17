//  EECS 348 LAB 10
//  Addition of doubles using string manipulation
//  INPUT: Test file
//  OUTPUT: String invalidity, string addition/subtraction
//  ALEXANDER TOLES      
//  APRIL 14 2025
//  COLLABORATORS: ChatGPT (See line 77)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// checks if the given expression has a larger absolute value.
// the result is used to make a result negative or positive

bool compare(string expression){ 

    string number = "123.456";

    size_t exp_pos = expression.find_first_of(".");
    size_t num_pos = number.find_first_of(".");

    string max_string = expression;
    string min_string = number;

    bool exp = 1;

    int max_pos = exp_pos;
    int min_pos = num_pos;
    

    int max_dec_len = max(expression.length()-1-exp_pos,number.length()-1-num_pos);
    int min_dec_len = min(number.length()-1-num_pos,expression.length()-1-exp_pos);

    
    if(expression.length()-1-exp_pos < number.length()-1-num_pos){
        exp = 0;
        max_string = number;
        min_string = expression;
        max_pos = num_pos;
        min_pos = exp_pos;
    }

    //this code block takes the number with less decimal places, and adds trailing
    //zeros until it has the same number of decimal places.

    int dec_dif = max_dec_len - min_dec_len; //difference in decimal palces

    for (int i = 0; i < dec_dif; i++) {
        min_string.push_back('0');
    }

    //since they have the same number of decimal places, we can add leading zeros until
    //the two strings are of the same length

    while (max_string.length() != min_string.length()) {
        if (max_string.length() > min_string.length()) {
            min_string.insert(0, 1, '0');
        } else {
            max_string.insert(0, 1, '0');
        }
    }

    for(int i = 0;i < max_pos;i++){
        if(max_string[i] > min_string[i]){
            if(exp){return 1;}else{return 0;}
        }
    }
    for(int i = max_pos+1;i < max_string.length();++i){
        if(max_string[i] > min_string[i]){
            if(exp){return 1;}else{return 0;}
        }
    }
    if(exp){return 0;}else{return 1;}
}

//to make this function easier to program, it always subtracts the larger number from 
//the smaller, adding a sign afterwards if needed.

//I used a suggestion by chatgpt, changing the variable names to 'a' and 'b' to be
//more clear and concise
string subtraction(string expression) {
    
    int sign = 0; //create sign variable, if sign is 1, then a sign is added to the result

    if (compare(expression)) {
        sign = 1;
    }

    string number = "-123.456"; 
    string sum;

    number.erase(0, 1); //remove the sign from the number 


    // this code block finds the number of decimal and integer places

    size_t exp_pos = expression.find_first_of("."); //gets the decimal postion
    size_t num_pos = number.find_first_of(".");

    string max_string = expression;
    string min_string = number;
    
    int max_pos = exp_pos;

    //finds the number of decimals in each

    int max_dec_len = max(expression.length() - 1 - exp_pos, number.length() - 1 - num_pos);
    int min_dec_len = min(expression.length() - 1 - exp_pos, number.length() - 1 - num_pos);


    //makes sure the number with more decimal places is the max

    if ((expression.length() - 1 - exp_pos) < (number.length() - 1 - num_pos)) {
        max_string = number;
        min_string = expression;
        max_pos = num_pos;
    }


    //this code block is identical to the above block, adds leading and trailing zeros
    //to make strings the same length

    int dec_dif = max_dec_len - min_dec_len; //difference in decimal palces

    for (int i = 0; i < dec_dif; i++) {
        min_string.push_back('0');
    }


    while (max_string.length() != min_string.length()) {
        if (max_string.length() > min_string.length()) {
            min_string.insert(0, 1, '0');
        } else {
            max_string.insert(0, 1, '0');
        }
    }

    max_pos = max_string.find_first_of(".");

    int carry = 0;
    int result = 0;

    if (!sign) { //if the expression is less than, we swap the strings so num is the max
        swap(max_string, min_string);
    }

    //start from the back of the strings, and end at the decimal place.

    for (int i = max_string.length() - 1; i > max_pos; --i) {
        //math is done by taking the ascii value of the digit, and subtracting the ascii
        //value of the character '0'. since the values are in order, this will give a
        //correspoding integer value.

        int a = max_string[i] - '0';
        int b = min_string[i] - '0' + carry;

        //if the bottom is less than the top, we add 10 and subtract
        if (b > a) {
            a += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result = a - b;
        sum.insert(0, 1, '0' + result); //insert the result into the sum string
    }

    // insert the decimal point
    sum.insert(0, 1, '.');

    //start from the 1s place in the integer, going to the start of the string
    for (int i = max_pos - 1; i >= 0; --i) {
        int a = max_string[i] - '0';
        int b = min_string[i] - '0' + carry;

        if (b > a) {
            a += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result = a - b;
        sum.insert(0, 1, '0' + result);
    }

    //add negative sign to the string
    sum.insert(0, 1, '-');

    cout << "sum: " <<sum << "\n";
    return sum;
}

string addition(string expression){

    //step one, find which string has more decimal values
    //add the unadded values to the sum string
    //add together the decimal values from each string
    //carry to the integer addition if necessary.

    string number = "-123.456";
    string sum;

    if(expression[0]=='-'){
        expression.erase(0,1);
        number.erase(0,1);
    }

    

    //get the position of the decimal in each

    size_t exp_pos = expression.find_first_of(".");
    size_t num_pos = number.find_first_of(".");

    
    
    //max_string and max_pos are the larger number, for decimals its the string with more decimal places,
    // and for integers, its the string with more integer places.

    int part_sum;
    int result;
    int carry = 0;

    string max_string = expression;
    string min_string = number;

    int max_pos = exp_pos;
    int min_pos = num_pos;
    

    int max_dec_len = max(expression.length()-1-exp_pos,number.length()-1-num_pos);
    int min_dec_len = min(number.length()-1-num_pos,expression.length()-1-exp_pos);
    
    if(expression.length()-1-exp_pos < number.length()-1-num_pos){
        max_string = number;
        min_string = expression;
        max_pos = num_pos;
        min_pos = exp_pos;
    }


    
    
    //this code block is identical to the above block, adds leading and trailing zeros
    //to make strings the same length

    int dec_dif = max_dec_len - min_dec_len; //difference in decimal palces

    for (int i = 0; i < dec_dif; i++) {
        min_string.push_back('0');
    }

    while (max_string.length() != min_string.length()) {
        if (max_string.length() > min_string.length()) {
            min_string.insert(0, 1, '0');
        } else {
            max_string.insert(0, 1, '0');
        }
    }

    max_pos = max_string.find_first_of(".");
    min_pos = max_pos;
    //start form the last decimal place, ending at the first
    for(int i = max_string.length()-1;i > max_pos;--i){

        int summand_1 = min_string[i] - '0';
        int summand_2 = max_string[i] - '0';

        result = summand_1 + summand_2 + carry; //add together each digit, and the carry
       
        if(result>=10){ //carry if if the result is greater than 10
            carry = 1;
            part_sum = result-10; //the partial sum is the 1s place
            sum.insert(0,1,'0'+part_sum); 
        }
        else{ //else insert the result
            carry = 0;
            sum.insert(0,1,'0'+result);
        }

    }

    sum.insert(0,1,'.'); //insert decimal

    //for integer values, start at the 1s place, end at the start of the string.
    for(int i = max_pos-1;i >= 0;--i){
        int summand_1 = min_string[i] - '0';
        int summand_2 = max_string[i] - '0';
        result = summand_1 + summand_2+carry;
        
        if(result>=10){
            carry = 1;
            part_sum = result-10;
            sum.insert(0,1,'0'+part_sum);
            
        }
        else{
            carry = 0;
            sum.insert(0,1,'0'+result);
        }
    }

    //add negative sign
    sum.insert(0,1,'-');

    cout << "sum: " <<sum << "\n";
    return sum;
}


//takes in the file data, goes through each line, checks validity of the number,
//cleans the number, and performs needed operation

void validate_expression(vector<string> file_data){
    string valid_chars = "-+0123456789"; //valid characters,
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
            if((j > 0 ) && ((file_data[i][j] == '+' ) || (file_data[i][j] == '-' ))){
                invalid = 1;
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
                while((file_data[i][file_data[i].length()-1]=='0')&&(file_data[i][file_data[i].length()-2]!='.')){
                    file_data[i].pop_back();
                }
            }
            //remove leading 0s
            if(operator_flag){
                if(file_data[i][0]=='+'){
                    file_data[i].erase(file_data[i].begin(),file_data[i].begin()+1);
                }
                while(file_data[i][1]=='0' && file_data[i][2]!='.'){
                    file_data[i].erase(file_data[i].begin()+1,file_data[i].begin()+2);
                }
            }
            else{
                while(file_data[i][0]=='0' && file_data[i][1]!='.'){
                    file_data[i].erase(file_data[i].begin(),file_data[i].begin()+1);
                }
            }

            //if the sign of the number is negative, we perform addtion, else we perform subtraction.
            if(file_data[i][0]=='-'){
                addition(file_data[i]);
            } else {
                subtraction(file_data[i]);
            }
            
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