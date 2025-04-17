#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
string addition(string expression){

    //step one, find which string has more decimal values
    //add the unadded values to the sum string
    //add together the decimal values from each string
    //carry to the integer addition if necessary.

    string number = "-123.456";
    string sum;
    bool add = 0; //if the input number is negative, we add instead of subtracting.

    if(expression[0]=='-'){
        add = 1;
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
    int sum_size = 0;
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
    int dec_dif = max_dec_len-min_dec_len;
    int int_dif = (max_string.length()-max_dec_len)-(min_string.length()-min_dec_len);
    for(int i = 0;i < dec_dif;i++){
        min_string.push_back('0');
    }
    while(max_string.length()!=min_string.length()){
        if(max_string.length()>min_string.length()){
            min_string.insert(0,1,'0');
        }
        else if (min_string.length()>max_string.length()){
            max_string.insert(0,1,'0');
        }
    }
    
    max_pos = max_string.find_first_of(".");
    min_pos = max_pos;

    cout << "max decimal string: " << max_string << ", " << max_dec_len << "\n";
    cout << "min decimal string: " << min_string << ", " << min_dec_len << "\n";

    cout << "max_pos: " << max_pos << ", min_pos: " << min_pos << "\n"; 
    


    for(int i = max_string.length()-1;i > max_pos;--i){
        int summand_1 = min_string[i] - '0';
        int summand_2 = max_string[i] - '0';
        result = summand_1 + summand_2+carry;
        cout << min_string[i] << ", " << max_string[i];
        cout <<", "<< result <<"\n";
        if(result>=10){
            carry = 1;
            part_sum = result-10;
            sum.insert(0,1,'0'+part_sum);
            cout << sum << "\n";
        }
        else{
            carry = 0;
            sum.insert(0,1,'0'+result);
            cout << sum << "\n";
        }

    }
    sum.insert(0,1,'.');
    cout << sum << "\n";
    cout << "-----\n";

    for(int i = max_pos-1;i >= 0;--i){
        int summand_1 = min_string[i] - '0';
        int summand_2 = max_string[i] - '0';
        result = summand_1 + summand_2+carry;
        cout << "i: "<<i<<", "<<min_string[i] << ", " << max_string[i];
        cout <<", "<< result <<"\n";
        if(result>=10){
            carry = 1;
            part_sum = result-10;
            sum.insert(0,1,'0'+part_sum);
            cout << sum << "\n";
        }
        else{
            carry = 0;
            sum.insert(0,1,'0'+result);
            cout << sum << "\n";
        }
    }
    sum.insert(0,1,'-');
    cout << sum << "\n";
    return sum;
}
double convert_expression(const string &expression){
    double parsed_num = 0.0;
    int offset = 0;
    if(expression[0]=='-'){
        offset=1;
    }
    size_t found = expression.find_first_of("."); 
    for(int i = offset;i < found;++i){
        int val = expression[i]-'0';
        parsed_num+=(val)*pow(10,found-i-1);
    }
    int dec_place = 0;
    for(int i = found+1;i < expression.length();++i){
        dec_place++;
        int val = expression[i]-'0';
        parsed_num+=(val)*pow(0.1,dec_place);
    }
    if(expression[0]=='-'){
        parsed_num*=-1;
    }
    cout << "Expression " << expression << " , Double: " << parsed_num << "\n";
    return parsed_num;
}
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
            //cout << "string: " << file_data[i] << "\n";
            addition(file_data[i]);
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