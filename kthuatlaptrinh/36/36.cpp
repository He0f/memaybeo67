#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

char KEY = 'K'; 

struct Person {
    int id, age;
    string name, hometown;

    friend istream& operator>>(istream& in, Person& p) {
        cout << "Enter person information:" << endl;
        cout << "\t+ Id: ";
        in >> p.id;
        in.ignore();
        cout << "\t+ Name: ";
        getline(in, p.name);
        cout << "\t+ Age: ";
        in >> p.age;
        in.ignore();
        cout << "\t+ Home town: ";
        getline(in, p.hometown);
        return in;
    }

    friend ostream& operator<<(ostream& out, Person p) {
        out << "Person information:" << endl;
        out << "\t+ Id: " << p.id << endl;
        out << "\t+ Name: " << p.name << endl;
        out << "\t+ Age: " << p.age << endl;
        out << "\t+ Home town: " << p.hometown << endl;
        return out;
    }
};

string encryptDecrypt(string toEncrypt) {
    string output = toEncrypt;
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ KEY;
    return output;
}

void show(vector<Person> p) {
    if (p.empty()) {
        cout << "An empty list" << endl;
    }
    else {
        for (int i = p.size() - 1; i >= 0; i--) {
            cout << p[i] << endl;
        }
    }
}

bool Remove(vector<Person>& p, int id) {
    for (int i = 0; i < p.size(); i++) {
        if (p[i].id == id) {
            p.erase(p.begin() + i);
            return true;
        }
    }
    return false;
}

void Find(vector<Person> p, string name) {
    bool found = false;
    for (int i = p.size() - 1; i >= 0; i--) {
        if (p[i].name == name) {
            found = true;
            cout << p[i];
        }
    }
    if (!found) cout << "No person is found with name " << name << endl;
}

void exportToFile(vector<Person> p) {
    ofstream f("367.txt");
    if (f.is_open()) {
        for (const auto& x : p) {
            f << encryptDecrypt(to_string(x.id)) << endl;
            f << encryptDecrypt(x.name) << endl;
            f << encryptDecrypt(to_string(x.age)) << endl;
            f << encryptDecrypt(x.hometown) << endl;
        }
        f.close();
        cout << "Exported and Encrypted successfully!" << endl;
    }
}

void importFromFile(vector<Person>& p) {
    ifstream f("367.txt");
    if (f.is_open()) {
        p.clear();
        string sId, sName, sAge, sHometown;
        while (getline(f, sId)) {
            getline(f, sName);
            getline(f, sAge);
            getline(f, sHometown);

            Person tmp;
            tmp.id = stoi(encryptDecrypt(sId));
            tmp.name = encryptDecrypt(sName);
            tmp.age = stoi(encryptDecrypt(sAge));
            tmp.hometown = encryptDecrypt(sHometown);
            p.push_back(tmp);
        }
        f.close();
        cout << "Imported and Decrypted successfully!" << endl;
    }
    else {
        cout << "File not found!" << endl;
    }
}

int main() {
    vector<Person> list;
    int cmd;
    do {
        system("cls");
        cout << "---- HUMAN RESOURCE MANAGEMENT ----" << endl;
        cout << "1. Show person list" << endl;
        cout << "2. Add a person" << endl;
        cout << "3. Remove a person by id" << endl;
        cout << "4. Find people by name" << endl;
        cout << "5. Export File" << endl;
        cout << "6. Import File" << endl;
        cout << "0. Quit" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Your command: ";
        cin >> cmd;

        switch (cmd) {
        case 1: show(list); break;
        case 2: { Person a; cin >> a; list.push_back(a); break; }
        case 3: {
            int rId; cout << "Enter id: "; cin >> rId;
            if (Remove(list, rId)) cout << "Success!" << endl;
            else cout << "Not found!" << endl;
            break;
        }
        case 4: {
            string n; cout << "Enter name: "; cin.ignore(); getline(cin, n);
            Find(list, n);
            break;
        }
        case 5: exportToFile(list); break;
        case 6: importFromFile(list); break;
        case 0: return 0;
        }
        cout << "Press Enter to continue...";
        cin.ignore(); cin.get();
    } while (true);
    return 0;
}