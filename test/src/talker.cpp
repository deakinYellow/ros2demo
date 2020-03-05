/**
@file  talker.cpp
@brief  
@author  Deakin
@email  DeakinHwang@163.com
@version  
@date  2020-02-15
@license  
*/
/** talker.cpp **/

#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float32.hpp>
#include <iostream>

using namespace std::chrono_literals;
using namespace std;

class Publisher : public rclcpp::Node{
public:
    Publisher() :
        Node("publisher"), count_(0)
    {
        publisher_ = this ->create_publisher<std_msgs::msg::String>("topic", 1 );
        f_publisher_ = this ->create_publisher<std_msgs::msg::Float32>("ftopic", 1 );

        //leftMotorSpeedPub = this->create_publisher<std_msgs::msg::Float32>(leftMotorTopic, 1);
        timer_ = this ->create_wall_timer(10ms, std::bind(&Publisher::timer_callback, this));

    }
private:

    void timer_callback(){

        auto message = std_msgs::msg::String();
        message.data = "Hello World! " + std::to_string(count_++);
        RCLCPP_INFO( this->get_logger(), "Publishing: '%s'", message.data.c_str() );
        publisher_->publish(message);


        auto fmsg = std_msgs::msg::Float32();
        fmsg.data = 1.0f;
        f_publisher_->publish( fmsg );


    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr f_publisher_;


    size_t count_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}
