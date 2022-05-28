#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

struct STATE_OUT
{
    
    void print_tape(char tape[]){
        for (int i = 0; tape[i] != '\0'; i++)
        {
            cout << tape[i];
        }
        cout << endl;
    }
    void print_rule(char rule[]){
        for (int val = 0; val != 3; val++)
            if (rule[val] == '0')
                continue;
            else
                cout << rule[val] << ' ';
        cout<<"\n\n";
    }
};

int main() {
    STATE_OUT step;
    int tape_size=8;
    char tape[tape_size]={'0', '1', '0', '1', '0', '1', '1', '0'};
    int start_poz=3;
    string start_rule;
    char rules[10][3]={
            {'-', '0', '0'},
            {'?', '1', '3'},
            {'X', '0', '0'},
            {'+', '0', '0'},
            {'?', '4', '6'},
            {'X', '0', '0'},
            {'+', '0', '0'},
            {'?', '9', '1'},
            {'V', '0', '0'},
            {'!', '0', '0'}
    };
    int comi=0;

    string st(sizeof(tape)/ sizeof(tape[1]), '.');
    st[start_poz]='|';


    while (1==1)
    {
        step.print_tape(tape);
        cout<<st<<endl;
        sleep(1);

        switch (rules[comi][0]) {
            case '-':
                st[start_poz]='.';
                start_poz -= 1;
                break;
            case '+':
                st[start_poz]='.';
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
                cout<<st<<endl;
                step.print_rule(rules[comi]);
                if (tape[start_poz]=='0')
                    comi= (int)rules[comi][1] - 49;
                else
                    comi = (int)rules[comi][2] - 49;
                goto next;
                break;
            case '!':
                step.print_tape(tape);
                cout<<st<<endl;
                step.print_rule(rules[comi]);
                goto exit;
        }
        st[start_poz]='|';
        step.print_tape(tape);
        cout<<st<<endl;
        step.print_rule(rules[comi]);
        comi += 1;
        next: ;
        sleep(1);
    }
    exit: ;
    return 0;
}
