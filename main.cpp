#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <cassert>
#include <dirent.h>
#include <deque>

using namespace std;

struct STATE_OUT
{

    void print_tape(deque<char>& tape, string& karetka){
        for (int i = 0; i < tape.size(); i++)
        {
            cout << tape[i];
        }
        cout << endl;
        cout << karetka << endl;

    }
    void print_rule(vector <char>& rule){ // 166 linia
        for (int val = 0; val != 3; val++)
            if (rule[val] == '0')
                continue;
            else
                cout << rule[val] << ' ';
        cout<<"\n\n";
    }
    void print_test_files(vector <string> test_files){
        for (int i=0; i<test_files.size(); ++i)
            cout << test_files[i] << ' ';
        cout<<"\n\nChoose file->";
    }
};

struct DATA_MANAGE{
    vector <string> test_files;
    string file;
    deque<char> tape;
    int start_poz;
    vector < vector <char> >rules;
    string karetka;
    int command_line_num=0;
    char action, command;

    void get_test_files(){
        char cwd[256];
        getcwd(cwd, 256);
        if (auto dir = opendir(cwd)) {
            while (auto f = readdir(dir)) {
                if (!f->d_name || f->d_name[0] == '.')
                    continue;
                if (((string)(f->d_name)).find("test") != string::npos){

                    test_files.push_back(f->d_name);                 }
            }
            closedir(dir);
        }
    }
    void get_test_file_input(){
        string line, token;
        char chr;
        ifstream test_file (file);
        if (test_file.is_open())
        {
            while ( getline (test_file, line) ) {

                if (line.find("tape") != string::npos){

                    line = line.substr(line.find('(')+1, line.find(')')-line.find('(')-1);
                    stringstream ss(line);

                    while(getline(ss, token, ',')){
                        assert(token.size() == 1);
                        chr = token[0];
                        tape.push_back(chr);
                    }

                }else if(line.find("pos") != string::npos){
                    start_poz = stoi(line.substr(line.find(',') + 1));
                }else{
                    vector<char> row;

                    for (char &c : line) {
                        if (c != ' ') {
                            row.push_back(c);
                        }
                    }
                    while (row.size() != 3)
                        row.push_back('0');

                    rules.push_back(row);
                    if (row[0]=='!')break;
                }
            }
            test_file.close();
            karetka=string(tape.size(), '.');
            karetka[start_poz]='|';
        }
        else {
            assert(test_file.is_open()!= true);
            cout << "Unable to open file";
        }
    }
    void post(){
        action='0';
        command = rules[command_line_num][0];
        if (command=='-'){
            karetka[start_poz]='.';
            start_poz -= 1;
        }else if (command=='+'){
            karetka[start_poz]='.';
            start_poz += 1;
        }else if (command=='X')
            tape[start_poz] = '0';
        else if (command=='V')
            tape[start_poz] = '1';
        else if (command=='?'){
            action = 'n';
        }else {
            action = 'e';
        }
    }
    void post_line_check(){
        if (tape[start_poz]=='0')
            command_line_num= (int)rules[command_line_num][1] - 49;
        else
            command_line_num = (int)rules[command_line_num][2] - 49;
    }
    void out_of_range_check(){
        if(start_poz==tape.size()){
            karetka.insert(0, 1, '.');
            tape.push_back('0');
        } else if (start_poz<0){
            karetka.insert(0, 1, '.');
            tape.push_front('0');
            start_poz = 0;
        }
    }
};

int main() {
    STATE_OUT step;
    DATA_MANAGE data;

    data.get_test_files();
    step.print_test_files(data.test_files);
    cin>>data.file;
    data.get_test_file_input();


    while (1==1)
    {
        step.print_tape(data.tape, data.karetka);
        sleep(1);

        data.post();
        data.out_of_range_check();
        data.karetka[data.start_poz] = '|';

        step.print_tape(data.tape,data.karetka);
        step.print_rule(data.rules[data.command_line_num]);
        sleep(1);
        if (data.action=='n'){
            data.post_line_check();
            continue;
        }
        data.command_line_num += 1;
        if (data.action == 'e')
            break;
    }


    return 0;
}