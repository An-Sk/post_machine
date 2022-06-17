#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <cassert>

using namespace std;

struct STATE_OUT
{
    
    void print_tape(vector<char>& tape){
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
    int output_mode;
    cout <<"how do you want to proccess:\n" << "0-automatically\n1-by pressing the button\n->";
    cin >> output_mode;
    cout<<'\n';
    STATE_OUT step;

    vector <char> tape;
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
    else cout << "Unable to open file";

    int command_line_num=0;
    string karetka(tape.size(), '.');
    karetka[start_poz]='|';


    while (1==1)
    {
        step.print_tape(tape);
        cout << karetka << endl;
        sleep(1);

        switch (rules[command_line_num][0]) {
            case '-':
                karetka[start_poz]='.';
                start_poz -= 1;
                break;
            case '+':
                karetka[start_poz]='.';
                start_poz += 1;
                break;
            case 'X':
                tape[start_poz] = '0';
                break;
            case 'V':
                tape[start_poz] = '1';
                break;
            case '?':
                step.print_tape(tape);
                cout << karetka << endl;
                step.print_rule(rules[command_line_num]);
                if (tape[start_poz]=='0')
                    command_line_num= (int)rules[command_line_num][1] - 49;
                else
                    command_line_num = (int)rules[command_line_num][2] - 49;
                goto next;
                break;
            case '!':
                step.print_tape(tape);
                cout << karetka << endl;
                step.print_rule(rules[command_line_num]);
                goto exit;
        }
        karetka[start_poz]='|';
        step.print_tape(tape);
        cout << karetka << endl;
        step.print_rule(rules[command_line_num]);
        command_line_num += 1;
        next: ;
        sleep(1);
        if (output_mode == 1)system("pause");
    }
    exit: ;

    return 0;
}
