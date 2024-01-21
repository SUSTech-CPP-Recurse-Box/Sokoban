#include "Panel.h"

#include "json/rapidjson.h"
#include "json/document.h"

Panel* Panel::instance = new Panel();

ResBox* wall = new ResBox(4, { 0,0 });

Panel* Panel::getInstance()
{
    if (instance == nullptr) {
        instance = new Panel();
    }
    return instance;
}

bool Panel::levelInit(int id)
{
    this->targets.clear();
    this->boxes.clear();
    this->infs.clear();
    this->epss.clear();

    rapidjson::Document readdoc;
    // getFileData 如果不指定，读取根目录是 Resource 文件夹
    std::string fileName = "level/level" + std::to_string(id) + ".json";
    if (id == 100) {
        fileName = "level/user.json";
    }
    std::string levelStr = FileUtils::getInstance()->getStringFromFile(fileName);

    if (levelStr == "") {
        return false;
    }

    readdoc.Parse<0>(levelStr.c_str());
    if (readdoc.HasParseError())
    {
        return false;
    }

    rapidjson::Value& boxInfoJson = readdoc["boxInfo"];
    for (int i = 0; i < boxInfoJson.Size(); i++) {
        rapidjson::Value& curInfoJson = boxInfoJson[i];
        int size_x = curInfoJson["size_x"].GetInt();
        int size_y = curInfoJson["size_y"].GetInt();
        ResBox* box = new ResBox(1, { size_x,size_y });
        this->boxes.emplace_back(box);
    }


    rapidjson::Value& innerBoxes = readdoc["innerBoxes"];
    if (innerBoxes.IsArray())
    {
        for (int i = 0; i < innerBoxes.Size(); i++)
        {
            rapidjson::Value& panJson = innerBoxes[i]["pan"];

            ResBox* curBox = this->boxes[i];
            for (int x = 0; x < curBox->size.first; x++)
            {
                for (int y = 0; y < curBox->size.second; y++)
                {
                    std::string str = panJson[curBox->size.second - y - 1][x].GetString();

                    if (str[1] != ' ') {
                        int id = str[1] - '1';
                        if (str[0] == 'T') {
                            curBox->addBox(this->boxes[id], { x,y }, true);
                        }
                        else if (str[0] == 'F') {
                            curBox->addBox(this->boxes[id], { x,y }, false);
                        }
                        continue;
                    }


                    ResBox* smallBox = nullptr;
                    if (str == "- ") {
                        this->targets.emplace_back(1, i, x, y);
                        curBox->setTarget({ x,y }, 1);
                    }
                    else if (str == "= ") {
                        this->targets.emplace_back(2, i, x, y);
                        curBox->setTarget({ x,y }, 2);
                    }
                    else if (str == ". ") {

                    }
                    else if (str == "# ") {
                        smallBox = wall;
                    }
                    else if (str == "O ") {
                        smallBox = new ResBox(2, { x,y });
                    }
                    else if (str == "o ") {
                        smallBox = new ResBox(2, { x,y });
                        this->targets.emplace_back(1, i, x, y);
                        curBox->setTarget({ x,y }, 1);
                    }
                    else if (str == "P ") {
                        smallBox = new ResBox(3, { x,y });
                        this->player = smallBox;
                    }
                    else if (str == "p ") {
                        smallBox = new ResBox(3, { x,y });
                        this->targets.emplace_back(2, i, x, y);
                        this->player = smallBox;
                        curBox->setTarget({ x,y }, 2);
                    }
                    if (smallBox != nullptr) {
                        curBox->addBox(smallBox, { x, y }, true);
                    }
                }
            }
        }
    }

    int startId = -1;
    for (int i = 0; i < boxInfoJson.Size(); i++) {
        rapidjson::Value& curInfoJson = boxInfoJson[i];
        if (curInfoJson.HasMember("special")) {
            if (startId < 0) {
                startId = i;
            }
            std::string type = curInfoJson["special"].GetString();
            if (type == "inf") {
                infs.push_back(boxes[i]);
            }
            else if (type == "eps") {
                epss.push_back(boxes[i]);
            }
        }
    }


    if (startId >= 0) {
        int box_sz = boxes.size();
        for (int id = startId; id < box_sz; ++id) {
            boxes.pop_back();
        }
    }

    log(printCLI(Panel::getInstance()).c_str());
    //boxes[0]->son[6][4] = new ResBox(2, { 0,0 });
    //log(printCLI(Panel::getInstance()).c_str());
}

std::string printCLI(Panel* panel) {
    std::string cli;
    for (size_t i = 0; i < panel->boxes.size(); i++)
    {
        ResBox* box = panel->boxes[i];
        cli += "Box " + std::to_string(i + 1) + '\n';
        for (int y = box->size.second - 1; y >= 0; y--)
        {
            for (int x = 0; x < box->size.first; x++)
            {
                ResBox* curSon = box->son[x][y];
                bool find = false;
                for (Target tar : panel->targets) {

                    if (tar.boxId == i && tar.pos.first == x && tar.pos.second == y)
                    {
                        if (tar.type == 1) {
                            if (curSon != nullptr && curSon->type == 2) {
                                cli += "o ";
                            }
                            else {
                                cli += "- ";
                            }
                        }
                        else if (tar.type == 2) {
                            if (curSon != nullptr && curSon->type == 3) {
                                cli += "p ";
                            }
                            else {
                                cli += "= ";
                            }
                        }
                        find = true;
                        break;
                    }
                }
                if (find) {
                    continue;
                }

                if (curSon == nullptr) {
                    cli += ". ";
                    continue;
                }
                int type = curSon->type;
                if (type == 1) {
                    for (int id = 0; id < panel->boxes.size(); ++id) {
                        ResBox* curbox = panel->boxes[id];
                        if (curbox == curSon) {
                            if (curSon->father == box) {
                                cli += "T";
                            }
                            else {
                                cli += "F";
                            }
                            cli += std::to_string(id + 1);
                        }
                    }
                }
                else if (type == 4) {
                    cli += "# ";
                }
                else if (type == 2) {
                    cli += "O ";
                }
                else if (type == 3) {
                    cli += ("P ");
                }
            }
            cli += '\n';
        }
        cli += '\n';
    }

    return cli;
}
