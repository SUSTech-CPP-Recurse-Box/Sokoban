#ifndef _SAVE_MANAGER_H_
#define _SAVE_MANAGER_H_

#include "cocos2d.h"


class SaveInfo {
public:
    int level_id;
    std::vector<std::string> actions;
    std::string time_str;
    SaveInfo(int id, std::vector<std::string> acts, std::string time) :
        level_id(id), actions(acts), time_str(time) {}
};

class SaveManager {
private:
    static SaveManager* saveManagerInstance;
    SaveManager();
    ~SaveManager();
public:
    static SaveManager* getInstance();
    bool saveGame(int level, std::string actions[]);
    SaveInfo* loadGame();
};

#endif