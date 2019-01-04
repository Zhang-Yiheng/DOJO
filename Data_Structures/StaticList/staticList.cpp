#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data;
    int prev;
    int next;
};

template <typename T>
class StaticLink final {
public:
    StaticLink() {node[0].next = node[0].prev = NULL;};
    ~StaticLink(){};
    void add(T);
    void del(int);
    void print();
    void findByNum(int);
    void findByVal(T);
    void insert(int, T);
    int pointTo(int);
private:
    Node<T> nd;
    vector<Node<T>> node = {nd};
    int size = 0;                       // size of static list
    vector<int> vacant;                 // list of vacant address
};

template <typename T>
void StaticLink<T>::add(T data) {
    if (vacant.empty()) {       // push back a new node
        nd.data = data;
        nd.next = NULL;
        node.push_back(nd);
        size++;
        node[node[0].prev].next = size;
        node[size].prev = node[0].prev;
        node[0].prev = size;
        cout << "New node | data = " << node.back().data << endl;
    }
    else {                      // reuse a discarded node
        int i = vacant.back();
        vacant.pop_back();
        node[i].data = data;
        node[i].next = NULL;
        node[i].prev = node[0].prev;
        node[node[0].prev].next = i;
        node[0].prev = i;
        size++;
        cout << "Node reused | data = " << node[i].data << endl;
    }
}

template <typename T>
int StaticLink<T>::pointTo(int n) {
    if (size == 0) 
        return NULL;
    else if (n <= 0 || size < n) 
        return NULL;
    else {
        int pointer;
        if (n <= size/2) {
            pointer = node[0].next;
            for (int i = 1; i < n; i++) 
                pointer = node[pointer].next; 
        } else {
            pointer = node[0].prev;
            for (int i = size ; i > n; i--) 
                pointer = node[pointer].prev; 
        }
        return pointer;
    }
}

template <typename T>
void StaticLink<T>::del(int n) {          // delete nth node
    if (size == 0) 
        cout << "List is empty!\n";
    else if (n <= 0 || size < n) 
        cout << "No such node! Avaliable range (1 ~ " << size << ")\n";
    else {
        int pointer = pointTo(n);
        node[node[pointer].prev].next = node[pointer].next;
        node[node[pointer].next].prev = node[pointer].prev;
        node[pointer].next = node[pointer].prev = NULL;
        vacant.push_back(pointer);
        size--;
    }
}

template <typename T>
void StaticLink<T>::findByNum(int n) {
    if (size == 0) 
        cout << "List is empty!\n";
    else if (n <= 0 || size < n) 
        cout << "No such node! Avaliable range (1 ~ " << size << ")\n";
    else {
        int pointer = pointTo(n);
        cout << "[←:" << node[pointer].prev << "|addr:" << pointer << "|data:" << node[pointer].data << "|→:" << node[pointer].next << "]\n";
    }
}

template <typename T>
void StaticLink<T>::findByVal(T val) {
    if (size == 0) 
        cout << "List is empty!\n";
    else {
        int pointer = node[0].next;
        bool match = false;
        do {
            if (node[pointer].data == val) {
                cout << "[←:" << node[pointer].prev << "|addr:" << pointer << "|data:" << node[pointer].data << "|→:" << node[pointer].next << "]\n";
                match = true;
            }
            pointer = node[pointer].next; 
        } while (pointer != NULL);
        if (!match)
            cout << "No matching data!\n";
    }
}

template <typename T>
void StaticLink<T>::insert(int n, T data) {
    if (n <= 0 || size + 1 < n) 
        cout << "Avaliable range (1 ~ " << size + 1 << ")\n";
    else if (n == size + 1)
        add(data);
    else if (vacant.empty()) {       // push back a new node
        int pointer = pointTo(n);
        nd.data = data;
        nd.next = pointer;
        nd.prev = node[pointer].prev;
        node.push_back(nd);
        size++;
        node[node[size].prev].next = size;
        node[node[size].next].prev = size;
        cout << "New node | data = " << node.back().data << endl;
    }
    else {                      // reuse a discarded node
        int pointer = pointTo(n);
        int i = vacant.back();
        vacant.pop_back();
        node[i].data = data;
        node[i].next = pointer;
        node[i].prev = node[pointer].prev;
        node[node[i].prev].next = i;
        node[node[i].next].prev = i;
        size++;
        cout << "Node reused | data = " << node[i].data << endl;
    }
}

template <typename T>
void StaticLink<T>::print() {
    if (size == 0) 
        cout << "List is empty!\n";
    else {
        cout << "list size: " << size << endl; 
        int i = node[0].next, num = 2;
        cout << "1.[←:" << node[i].prev << "|addr:" << i << "|data:" << node[i].data << "|→:" << node[i].next << ']';
        i = node[i].next;
        while(i != NULL) {
            cout << "——" << num++ << ".[←:" << node[i].prev << "|addr:" << i << "|data:" << node[i].data << "|→:" << node[i].next << ']';
            i = node[i].next;
        } 
        cout << endl;
    }
}

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
