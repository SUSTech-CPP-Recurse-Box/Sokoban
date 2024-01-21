#ifndef _USER_LEVEL_MANAGER_H_
#define _USER_LEVEL_MANAGER_H_

#include "cocos2d.h"
#include "Boxes/DesignControler.h"

using pii = std::pair<int, int>;

class UserLevelManager {
private:
    static UserLevelManager* userLevelManagerInstance;

    UserLevelManager();

    ~UserLevelManager();

public:

    static UserLevelManager* getInstance();

    bool saveLevel(std::vector<dataset*> levelData);

};
#endif