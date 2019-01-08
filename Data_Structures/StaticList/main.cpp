#include "staticList.h"

int main(int argc, char const *argv[])
{
    StaticLink<string> stlink;
    string s, mode;
    int n;

    cout << "1.add\n2.delete\n3.insert\n4.findByNum\n5.findByVal\n0.exit\nMODE: ";
    while (cin >> mode) {
        if (mode == "1") {
            cout << "\nInput data ('fin' to quit): ";
            while (cin >> s) {
                if (s == "fin")
                    break;
                stlink.add(s);
                cout << "\nInput data ('fin' to quit): ";
            }
            cout << endl;
            stlink.print();
        }
        else if (mode == "2") {
            cout << "\nDelete data by serial number ('-1' to quit): ";
            while (cin >> n) {
                if (n == -1)
                    break;
                stlink.del(n);
                stlink.print();
                cout << "\n\nDelete data by serial number ('-1' to quit): ";
            }
        }
        else if (mode == "3") {
            cout << "\nInsert place ('-1' to quit): ";
            while (cin >> n) {
                if (n == -1)
                    break;
                cout << "Insert data: ";
                cin >> s;
                stlink.insert(n, s);
                cout << "\nInput place ('-1' to quit): ";
            }
            cout << endl;
            stlink.print();
        }
        else if (mode == "4") {
            cout << "\nFind data by serial number ('-1' to quit): ";
            while (cin >> n) {
                if (n == -1)
                    break;
                stlink.findByNum(n);
                cout << "\nFind data by serial number ('-1' to quit): ";
            }
        }
        else if (mode == "5") {
            cout << "\nFind data by value ('fin' to quit): ";
            while (cin >> s) {
                if (s == "fin")
                    break;
                stlink.findByVal(s);
                cout << "\nFind data by value ('fin' to quit): ";
            }
        }
        else if (mode == "0")
            break;
        cout << "\n\n1.add\n2.delete\n3.insert\n4.findByNum\n5.findByVal\n0.exit\nMODE: ";
    }
    return 0;
}
