#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
USING_NS_CC;

using pii = std::pair<int, int>;

class GameScene : public Layer {
protected:
    std::string id;
    EventListenerKeyboard* _listener;
    EventListenerMouse* mouseListener;
    Vec2 startPos;
public:
    int lid;
    static Scene* scene(int lid, bool saved);
    virtual bool init();

    CREATE_FUNC(GameScene);

    void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onMouseScroll(Event* event);

    void GameScene::onUndo(Ref* pSender);

    void GameScene::onRestart(Ref* pSender);

    void GameScene::onMouseDown(Event* event);

    void  GameScene::onMouseUp(Event* event);

    void GameScene::setId(network::HttpClient* sender, network::HttpResponse* response) {
        if (!response) {
            CCLOG("HttpRequest failed!");
            return;
        }

        long statusCode = response->getResponseCode();

        if (statusCode == 200) {
            // 如果响应状态码为200，表示请求成功
            CCLOG("HttpRequest succeeded!");

            // 获取响应数据
            std::vector<char>* buffer = response->getResponseData();
            std::string responseData(buffer->begin(), buffer->end());

            // 在这里解析服务器返回的数据
            id=responseData.c_str();
        }
        else {
            // 请求失败，输出错误信息
            CCLOG("HttpRequest failed. Status code: %ld", statusCode);
        }
        
    }
    void getId() {
        // 创建一个HttpRequest对象
        network::HttpRequest* request = new network::HttpRequest();
        // 设置请求的URL
        request->setUrl("http://10.24.50.187:9092/cpp/new");
        // 设置请求方式为POST
        request->setRequestType(network::HttpRequest::Type::POST);

        // 构造要发送的数据
        std::string postData = "121321323";
        // 设置请求体
        request->setRequestData(postData.c_str(), postData.length());

        // 设置回调函数，处理服务器的响应
        request->setResponseCallback(CC_CALLBACK_2(GameScene::setId, this));

        // 发送请求
        network::HttpClient::getInstance()->send(request);
        // 释放HttpRequest对象，避免内存泄漏
        request->release();
        
    }
    void GameScene::setmove(network::HttpClient* sender, network::HttpResponse* response) {
        if (!response) {
            CCLOG("HttpRequest failed!");
            return;
        }

        long statusCode = response->getResponseCode();

        if (statusCode == 200) {
            // 如果响应状态码为200，表示请求成功
            CCLOG("HttpRequest succeeded!");

            // 获取响应数据
            std::vector<char>* buffer = response->getResponseData();
            std::string responseData(buffer->begin(), buffer->end());

            // 在这里解析服务器返回的数据
            id = responseData.c_str();
        }
        else {
            // 请求失败，输出错误信息
            CCLOG("HttpRequest failed. Status code: %ld", statusCode);
        }
    }
    void trymove(std::string str) {
        // 创建一个HttpRequest对象
        network::HttpRequest* request = new network::HttpRequest();
        // 设置请求的URL
        request->setUrl("http://10.24.50.187:9092/cpp/add?c="+id+"&m="+str);
        // 设置请求方式为POST
        request->setRequestType(network::HttpRequest::Type::POST);

        // 构造要发送的数据
        std::string postData = "121321323";
        // 设置请求体
        request->setRequestData(postData.c_str(), postData.length());

        // 设置回调函数，处理服务器的响应
        request->setResponseCallback(CC_CALLBACK_2(GameScene::setmove, this));

        // 发送请求
        network::HttpClient::getInstance()->send(request);
        // 释放HttpRequest对象，避免内存泄漏
        request->release();
    }
    void gm(network::HttpClient* sender, network::HttpResponse* response);
    void getmove(float dt);
    ~GameScene() {}
};

#endif /* defined(__GAME_SCENE_H__) */