// Subscriber.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

// 定义消息类型
struct LaserRadarMessage {
    std::string obstacleStatus;
};

// 定义订阅者类
class ChassisSubscriber {
public:
    ChassisSubscriber(const std::string& topic) : topic_(topic) {}

    void subscribe() {
        std::cout << "底盘订阅者订阅了话题: " << topic_ << std::endl;
        while (true) {
            std::ifstream inFile(topic_ + ".txt");
            if (inFile.is_open()) {
                std::string line, lastLine;
                while (std::getline(inFile, line)) {
                    lastLine = line;
                }
                inFile.close();
                
                if (!lastLine.empty()) {
                    LaserRadarMessage message{lastLine};
                    onMessageReceived(message);
                }
            } else {
                std::cerr << "无法打开文件进行读取: " << topic_ << ".txt" << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟实时接收消息
        }
    }

    void onMessageReceived(const LaserRadarMessage& message) {
        // 根据雷达消息更新底盘状态
        std::cout << "底盘订阅者收到消息: " << message.obstacleStatus << std::endl;
        if (message.obstacleStatus == "1") {
            std::cout << "底盘执行后退操作。" << std::endl;
        } else if (message.obstacleStatus == "2") {
            std::cout << "底盘执行右转操作。" << std::endl;
        } else if (message.obstacleStatus == "3") {
            std::cout << "底盘执行左转操作。" << std::endl;
        }
        std::cout << std::endl;
    }

private:
    std::string topic_;
};

int main() {
    ChassisSubscriber chassisSubscriber("Lidar");
    std::cout << "底盘订阅者启动..." << std::endl;
    chassisSubscriber.subscribe();
    return 0;
}