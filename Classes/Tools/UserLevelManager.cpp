#include "UserLevelManager.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "platform/CCFileUtils.h"

using namespace rapidjson;
USING_NS_CC;

UserLevelManager* UserLevelManager::userLevelManagerInstance = nullptr;

UserLevelManager::UserLevelManager()
{
}

UserLevelManager::~UserLevelManager()
{
}

UserLevelManager* UserLevelManager::getInstance()
{
    if (userLevelManagerInstance == nullptr) {
        userLevelManagerInstance = new UserLevelManager();
    }
    return userLevelManagerInstance;
}

bool UserLevelManager::saveLevel(std::vector<dataset*> levelData)
{
    rapidjson::Document writedoc; //创建Document
    writedoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();

    rapidjson::Value boxInfo_arr(rapidjson::kArrayType);
    for (dataset* setPtr : levelData) {
        rapidjson::Value boxInfo_obj(rapidjson::kObjectType);
        boxInfo_obj.AddMember("size_x", setPtr->x, allocator);
        boxInfo_obj.AddMember("size_y", setPtr->y, allocator);

        boxInfo_arr.PushBack(boxInfo_obj, allocator);
    }
    writedoc.AddMember("boxInfo", boxInfo_arr, allocator);

    rapidjson::Value innerBox_arr(rapidjson::kArrayType);

    for (dataset* setPtr : levelData) {
        rapidjson::Value innerBox_obj(rapidjson::kObjectType);
        rapidjson::Value pan_arr(rapidjson::kArrayType);
        for (int y = setPtr->y - 1; y >= 0; --y) {
            rapidjson::Value row_arr(rapidjson::kArrayType);
            for (int x = 0; x < setPtr->x; ++x) {
                rapidjson::Value itemStr_obj(rapidjson::kStringType);
                std::string str = "";
                str += setPtr->data1[x][y];
                char ch2 = (str == "T") ? (setPtr->data2[x][y] + 1) : setPtr->data2[x][y];
                str += ch2;
                itemStr_obj.SetString(str.c_str(), allocator);
                row_arr.PushBack(itemStr_obj, allocator);
            }
            pan_arr.PushBack(row_arr, allocator);
        }
        innerBox_obj.AddMember("pan", pan_arr, allocator);
        innerBox_arr.PushBack(innerBox_obj, allocator);
    }

    writedoc.AddMember("innerBoxes", innerBox_arr, allocator);

    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    writedoc.Accept(writer);

    std::string save_path = FileUtils::getInstance()->fullPathForFilename("level/user.json");
    FILE* file = fopen(save_path.c_str(), "wb");

    if (file)
    {
        fputs(buffer.GetString(), file);
        fclose(file);
    }
    else {
        printf("File not found\n");
    }
    CCLOG("%s", buffer.GetString());
    return true;
}
