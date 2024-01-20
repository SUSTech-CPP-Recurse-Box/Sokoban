#ifndef _SAVE_MANAGER_H_
#define _SAVE_MANAGER_H_

#include "cocos2d.h"

using pii = std::pair<int, int>;

class SaveInfo {
public:
    int level_id;
    std::vector<pii> actions;
    std::string time_str;

    SaveInfo(int id, std::vector<pii> acts, std::string time) :
        level_id(id), actions(acts), time_str(time) {}
};

class SaveManager {
private:
    static SaveManager* saveManagerInstance;

    SaveManager();

    ~SaveManager();

public:
    SaveInfo* info;

    static SaveManager* getInstance();

    bool saveGame(int level_id, std::vector<pii> steps);

    SaveInfo* loadGame();
};

#endif