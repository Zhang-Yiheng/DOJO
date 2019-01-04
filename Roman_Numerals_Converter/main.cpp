#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct segment
{
	const string bar   = " - ";
	const string side  = "| |";
	const string left  = "|  ";
	const string right = "  |";
	const string space = "   ";
}segment;

struct table
{
	const string  zero[5] = {segment.bar,   segment.side,  segment.space, segment.side,  segment.bar  };
    const string   one[5] = {segment.space, segment.right, segment.space, segment.right, segment.space};
    const string   two[5] = {segment.bar,   segment.right, segment.bar,   segment.left,  segment.bar  };
    const string three[5] = {segment.bar,   segment.right, segment.bar,   segment.right, segment.bar  };
    const string  four[5] = {segment.space, segment.side,  segment.bar,   segment.right, segment.space};
    const string  five[5] = {segment.bar,   segment.left,  segment.bar,   segment.right, segment.bar  };
    const string   six[5] = {segment.bar,   segment.left,  segment.bar,   segment.side,  segment.bar  };
    const string seven[5] = {segment.bar,   segment.right, segment.space, segment.right, segment.space};
    const string eight[5] = {segment.bar,   segment.side,  segment.bar,   segment.side,  segment.bar  };
    const string  nine[5] = {segment.bar,   segment.side,  segment.bar,   segment.right, segment.bar  };
    const char   comma[5] = {' ', ' ', ' ', ' ', ','};
    const char    mono[5] = {' ', '|', ' ', '|', ' '};
}table;

struct Segment
{
	const string bar   = " -- ";
	const string side  = "|  |";
	const string left  = "|   ";
	const string right = "   |";
	const string space = "    ";
}Segment;

struct Table
{
	const string  zero[7] = {Segment.bar,   Segment.side,  Segment.side,  Segment.space, Segment.side,  Segment.side,  Segment.bar  };
    const string   one[7] = {Segment.space, Segment.right, Segment.right, Segment.space, Segment.right, Segment.right, Segment.space};
    const string   two[7] = {Segment.bar,   Segment.right, Segment.right, Segment.bar,   Segment.left,  Segment.left,  Segment.bar  };
    const string three[7] = {Segment.bar,   Segment.right, Segment.right, Segment.bar,   Segment.right, Segment.right, Segment.bar  };
    const string  four[7] = {Segment.space, Segment.side,  Segment.side,  Segment.bar,   Segment.right, Segment.right, Segment.space};
    const string  five[7] = {Segment.bar,   Segment.left,  Segment.left,  Segment.bar,   Segment.right, Segment.right, Segment.bar  };
    const string   six[7] = {Segment.bar,   Segment.left,  Segment.left,  Segment.bar,   Segment.side,  Segment.side,  Segment.bar  };
    const string seven[7] = {Segment.bar,   Segment.right, Segment.right, Segment.space, Segment.right, Segment.right, Segment.space};
    const string eight[7] = {Segment.bar,   Segment.side,  Segment.side,  Segment.bar,   Segment.side,  Segment.side,  Segment.bar  };
    const string  nine[7] = {Segment.bar,   Segment.side,  Segment.side,  Segment.bar,   Segment.right, Segment.right, Segment.bar  };
    const char   comma[7] = {' ', ' ', ' ', ' ', ' ', ' ', ','};
    const char    mono[7] = {' ', '|', '|', ' ', '|', '|', ' '};
}Table;

class RomanNumeralsConverter {
public: 
	RomanNumeralsConverter(){
	    index['I'] = 1;
	    index['V'] = 5;
	    index['X'] = 10;
	    index['L'] = 50;
	    index['C'] = 100;
	    index['D'] = 500;
	    index['M'] = 1000;
	};
	virtual ~RomanNumeralsConverter(){};

	void readMe() {cout << "\nInput Roman Numerals to show digits;\nInput 'set size 2' to double display size;\n";
                   cout << "Input 'set monospaced off' to turn off monospaced font\nInput 'exit' to quit.\n";}

	void err() {cout << " - \n|  \n - \n|  \n - \n";}
	void Err() {cout << " -- \n|   \n|   \n -- \n|   \n|   \n -- \n";}

	int roman_to_int(string);
	void int_to_digit(int, int, bool);

private:
	int index[256];
	void digit(string, bool);
	void Digit(string, bool);
};


int RomanNumeralsConverter::roman_to_int(string s)
{
    if (s.length() == 1) 
        return index[s[0]];
    
    int count = 1;
    int value = index[s[s.length() - 1]];           // the last number

    for(int i = s.length()-2; i >= 0; i--)          // check from tail to head
    {
        if (index[s[i]] * index[s[i+1]] == 0)       // contain invalid input
            return 0;
        
        if (index[s[i]] == index[s[i+1]])           // left equal then plus left
        {
            count++;                                // no more than three times, 4 could be "IIII"
            if ((count == 4 && s[i] != 'I')||(count == 5 && s[i] == 'I')||(count == 2 && (s[i] == 'D' || s[i] == 'L' || s[i] == 'V'))) 
                return 0;
            value += index[s[i]];
        }
        else if (index[s[i]] > index[s[i+1]])       // left big then plus left
        {
            value += index[s[i]];
            count = 1;
        }
        else if ((s[i]=='I' && (s[i+1]=='V' || s[i+1]=='X')) || (s[i]=='X' && (s[i+1]=='L' || s[i+1]=='C')) || (s[i]=='C' && (s[i+1]=='D' || s[i+1]=='M')))
        {    
            if (i > 0 && index[s[i-1]] < index[s[i+1]])           // only one minus on left
                return 0;
            value -= index[s[i]];                   // left small and is 'I' or 'X' or 'C' and have to be "IV""IX""XL""XC""CD""CM" then minus left
        }
        else
            return 0;
    }
    
    return value;
}

void RomanNumeralsConverter::digit(string s, bool monospaced) {
    for (int i = 0; i < 5; i++)
    {
        for (auto c : s)
        {
            if (c == '0')
            	cout << table.zero[i];
            else if (c == '1') {
                if (monospaced == true)
                   	cout << table.one[i];
                else
                	cout << table.mono[i];
            }
            else if (c == '2')
            	cout << table.two[i];
            else if (c == '3')
            	cout << table.three[i];
            else if (c == '4')
            	cout << table.four[i];
            else if (c == '5')
            	cout << table.five[i];
            else if (c == '6')
            	cout << table.six[i];
            else if (c == '7')
            	cout << table.seven[i];
            else if (c == '8')
            	cout << table.eight[i];
            else if (c == '9')
            	cout << table.nine[i];
            else if (c == ',')
            	cout << table.comma[i];
        }
        cout << endl;
    }
}

void RomanNumeralsConverter::Digit(string s, bool monospaced) {
    for (int i = 0; i < 7; i++)
    {
        for (auto c : s)
        {
            if (c == '0')
            	cout << Table.zero[i];
            else if (c == '1') {
                if (monospaced == true)
                   	cout << Table.one[i];
                else
                	cout << Table.mono[i];
            }
            else if (c == '2')
            	cout << Table.two[i];
            else if (c == '3')
            	cout << Table.three[i];
            else if (c == '4')
            	cout << Table.four[i];
            else if (c == '5')
            	cout << Table.five[i];
            else if (c == '6')
            	cout << Table.six[i];
            else if (c == '7')
            	cout << Table.seven[i];
            else if (c == '8')
            	cout << Table.eight[i];
            else if (c == '9')
            	cout << Table.nine[i];
            else if (c == ',')
            	cout << Table.comma[i];
        }
        cout << endl;
    }
}

void RomanNumeralsConverter::int_to_digit(int val, int size, bool monospaced) {
    if (val == 0)
        (size==1) ? err() : Err();
    else
    {
        string s = to_string(val);
        stringstream ss;
        string value;
        int count = 1;
        
        for (auto c = s.rbegin(); c != s.rend(); c++) {
        	if (count % 4 == 0)
        		ss << ",";
        	ss << *c;
            count++;
        }
        value = ss.str();
        ss.clear(); ss.str("");

        for (auto c = value.rbegin(); c != value.rend(); c++) {
        	ss << *c;
        }
        value = ss.str();
        ss.clear(); ss.str("");
        //cout<< value<<endl;
        (size==1) ? digit(value, monospaced) : Digit(value, monospaced);
    }
}


int main(int argc, char const *argv[])
{
	RomanNumeralsConverter converter;

    converter.readMe();
    string input;
    int size = 1;
    bool monospaced = true;

    while (getline(cin, input)) 
    {
        if (input == "exit")
            break;
        else if (input == "set size 1")
        {
            size = 1;
            converter.readMe();
        }
        else if (input == "set size 2")
        {
            size = 2;
            converter.readMe();
        }
        else if (input == "set monospaced off")
        {
        	monospaced = false;
        	converter.readMe();
        }
        else {
            int val = converter.roman_to_int(input);
            //cout << val << endl;
            converter.int_to_digit(val, size, monospaced);
		    converter.readMe();
        }
    }
    
    return 0;
}
