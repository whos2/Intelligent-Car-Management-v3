// Publisher.cpp

#include <iostream>
#include <fstream>
#include <string>

// 定义消息类型
struct LaserRadarMessage {
    std::string obstacleStatus;
};

// 定义发布者类
class LaserRadarPublisher {
public:
    LaserRadarPublisher(const std::string& topic) : topic_(topic) {}

    void publish(const LaserRadarMessage& message) {
        std::ofstream outFile(topic_ + ".txt", std::ios::out | std::ios::trunc);
        if (outFile.is_open()) {
            outFile << message.obstacleStatus << std::endl;
            outFile.close();
        } else {
            std::cerr << "无法打开文件进行写入: " << topic_ << ".txt" << std::endl;
        }
    }

    void run() {
        LaserRadarMessage message;
        while (true) {
            std::cout << "1代表前方障碍，2代表左前方障碍，3代表右前方障碍。" << std::endl;
            std::cout << "请输入障碍物状态（1，2，3），或输入'exit'退出：" << std::endl;
            std::cin >> message.obstacleStatus;
            if (message.obstacleStatus == "exit") {
                break;
            }
            publish(message);
            std::cout << std::endl;
        }
    }

private:
    std::string topic_;
};

int main() {
    LaserRadarPublisher radarPublisher("Lidar");
    std::cout << "激光雷达发布者启动..." << std::endl;
    radarPublisher.run();
    return 0;
}