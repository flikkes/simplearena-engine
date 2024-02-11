#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct configentry {
  string name;
  string value;
};

class ConfigReader {
public:
  static vector<configentry> getConfig(string filename) {
    vector<configentry> entries;
    string line;
    ifstream PropFile(filename);
    while (getline(PropFile, line)) {
        int delimiterPos = line.find("=");
        cout << "Delimiter pos: " << delimiterPos << endl;
        if (line.length() >= 3 && line[0] != '=' && line[line.length() -1 ] != '=') {
            configentry entry;
            string name = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1, line.length());
            cout << "CONFIG ENTRY: " << name << " : " << value << endl;
            entry.name = name;
            entry.value = value;
            entries.push_back(entry);
        }
    }
    return entries;
  }
};

#endif