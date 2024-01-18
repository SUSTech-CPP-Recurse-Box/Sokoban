#include "SaveManager.h"

#include <chrono>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "platform/CCFileUtils.h"
//#include "json/filestream.h"
//#include "json/prettywriter.h"

using namespace rapidjson;
USING_NS_CC;

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
}

SaveManager* SaveManager::saveManagerInstance = nullptr;

SaveManager* SaveManager::getInstance()
{
    if (saveManagerInstance == nullptr) {
        saveManagerInstance = new SaveManager();
    }
    return saveManagerInstance;
}

std::string getTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::string(std::ctime(&now_c));
    return timeStr;
}

bool SaveManager::saveGame(int level_id, std::string actions_in[])
{
    rapidjson::Document writedoc; //创建Document
    writedoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
    writedoc.AddMember("level_id", level_id, allocator); //添加map_level属性值

    rapidjson::Value actions_json(rapidjson::kArrayType);//创建players数组
    for (size_t i = 0; i < 3; i++)
    {
        const char* s = actions_in[i].c_str();
        rapidjson::Value actStr(rapidjson::kStringType);
        actStr.SetString(s, allocator);
        actions_json.PushBack(actStr, allocator);
    }
    writedoc.AddMember("actions", actions_json, allocator);

    rapidjson::Value timeStr(rapidjson::kStringType);
    timeStr.SetString(getTimeString().c_str(), allocator);
    writedoc.AddMember("time", timeStr, allocator);

    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    writedoc.Accept(writer);

    std::string save_path = FileUtils::getInstance()->fullPathForFilename("save/save.json");
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

SaveInfo* SaveManager::loadGame() {
    rapidjson::Document readdoc;
    bool bRet = false;
    ssize_t size = 0;
    std::string load_str;
    // getFileData 如果不指定，读取根目录是 Resource 文件夹
    load_str = FileUtils::getInstance()->getStringFromFile("save/save.json");

    if (load_str == "") {
        return nullptr;
    }

    readdoc.Parse<0>(load_str.c_str());
    if (readdoc.HasParseError())
    {
        return nullptr;
    }

    if (!readdoc.IsObject() || !readdoc.HasMember("level_id") || !readdoc.HasMember("actions") || !readdoc.HasMember("time")) {
        return nullptr;
    }

    //关卡ID载入
    int level_id = readdoc["level_id"].GetInt();
    std::vector<std::string> actions;
    //步数载入
    rapidjson::Value& _actions = readdoc["actions"];
    if (_actions.IsArray())
    {
        for (int i = 0; i < _actions.Size(); i++)
        {
            actions.push_back(_actions[i].GetString());
        }
    }
    std::string timeStr = readdoc["time"].GetString();
    SaveInfo* info = new SaveInfo(level_id, actions, timeStr);
    return info;
}
