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
    
    void print_tape(deque<char>& tape){
        for (int i = 0; i < tape.size(); i++)
        {
            cout << tape[i];
        }
        cout << endl;
    }
    void print_rule(vector <char> rule){
        for (int val = 0; val != 3; val++)
            if (rule[val] == '0')
                continue;
            else
                cout << rule[val] << ' ';
        cout<<"\n\n";
    }
};

int main() {
//    int output_mode;
//    cout <<"how do you want to proccess:\n" << "0-automatically\n1-by pressing the button\n->";
//    cin >> output_mode;
//    cout<<'\n';
    STATE_OUT step;

    vector <string> test_files;
    deque<char> tape;
//    vector <char> tape;
    int start_poz;
    vector < vector <char> >rules;
    string line, token;
    char chr;

    

    ifstream test_file ("test.txt");
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
    }
    else {
        assert(test_file.is_open()!= true);
        cout << "Unable to open file";
    }

    int command_line_num=0;
    string karetka(tape.size(), '.');
    karetka[start_poz]='|';
    char action, command;


    while (1==1)
    {
        action='0';
        step.print_tape(tape);
        cout << karetka << endl;
        sleep(1);
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

        if(start_poz==tape.size()){
            karetka.insert(0, 1, '.');
            tape.push_back('0');
        } else if (start_poz<0){
            karetka.insert(0, 1, '.');
            tape.push_front('0');
            start_poz = 0;
        }

        karetka[start_poz] = '|';
        step.print_tape(tape);
        cout << karetka << endl;
        step.print_rule(rules[command_line_num]);
        sleep(1);
        if (action == 'n'){
            if (tape[start_poz]=='0')
                command_line_num= (int)rules[command_line_num][1] - 49;
            else
                command_line_num = (int)rules[command_line_num][2] - 49;
            continue;
        }
        command_line_num += 1;
//        if (output_mode == 1)system("pause");
        if (action == 'e')
            break;
    }


    return 0;
}
