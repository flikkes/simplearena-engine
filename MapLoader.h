#ifndef MAPLOADER_H
#define MAPLOADER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"

using namespace std;

static const string entityTkn = "entity(";
static const string playerTkn = "player(";
static const string clsBracketTkn = ")";
static const string delimiter = ",";

class MapLoader {
public:
  static vector<Entity> getMapEntities(string mapName) {
    string line;
    vector<Entity> entities;
    ifstream mapFile(mapName);
    while (getline(mapFile, line)) {
      size_t pos2 = line.find(clsBracketTkn);
      if (pos2 != string::npos) {
        line.erase(pos2, clsBracketTkn.length());
        size_t pos1 = line.find(entityTkn);
        if (pos1 != string::npos) {
          line.erase(pos1, entityTkn.length());
          size_t pos3;
          string token;
          vector<float> tokens;
          while ((pos3 = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos3);
            tokens.push_back(stof(token));
            line.erase(0, pos3 + delimiter.length());
          }
          if (line.size() > 0) {
            token = line;
            tokens.push_back(stof(token));
          }
          if (tokens.size() == 7) {
            Entity e(tokens.at(0), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4),
                     tokens.at(5), tokens.at(6));
            entities.push_back(e);
          }
        }
      }
    }
    mapFile.close();
    return entities;
  }

  static vector<Entity> getPlayerEntities(string mapName) {
    string line;
    vector<Entity> entities;
    ifstream mapFile(mapName);
    while (getline(mapFile, line)) {
      size_t pos2 = line.find(clsBracketTkn);
      if (pos2 != string::npos) {
        line.erase(pos2, clsBracketTkn.length());
        size_t pos1 = line.find(playerTkn);
        if (pos1 != string::npos) {
          line.erase(pos1, playerTkn.length());
          size_t pos3;
          string token;
          vector<float> tokens;
          while ((pos3 = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos3);
            tokens.push_back(stof(token));
            line.erase(0, pos3 + delimiter.length());
          }
          if (line.size() > 0) {
            token = line;
            tokens.push_back(stof(token));
          }
          if (tokens.size() == 7) {
            Entity e(tokens.at(0), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4),
                     tokens.at(5), tokens.at(6));
            entities.push_back(e);
          }
        }
      }
    }
    mapFile.close();
    return entities;
  }
};
#endif
