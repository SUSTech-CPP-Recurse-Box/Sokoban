#include <vector>

#include "ResBox.h"

using pii = std::pair<int, int>;

class Target {
public:
    int type;
    int boxId;
    pii pos;
    Target(int type, int id, int x, int y) :type(type), boxId(id), pos({ x, y }) {}
};

class Panel {
private:
    static Panel* instance;
    std::vector<Target> targets;
    std::vector<ResBox*> boxes;
    ResBox * initBox;
    ResBox * player;
    Panel() {};
    ~Panel() {};
public:
    static Panel* getInstance();
    bool levelInit(int id);

    friend std::string printCLI(Panel* panel);
};