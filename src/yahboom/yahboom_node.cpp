#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/string.hpp"

#include "YahboomCommunication/yahboom.hpp"

namespace pet
{

using namespace std::chrono_literals;

class YahboomNode : public rclcpp::Node
{
  public:
    YahboomNode()
        : Node("yahboom_node")
    {
        m_diag_publisher = this->create_publisher<std_msgs::msg::String>("yahboom/diagnostics", 10);
        m_timer = this->create_wall_timer(100ms, std::bind(&YahboomNode::timer_callback, this));
        m_cmd_vel_subscriber = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", 10, std::bind(&YahboomNode::cmd_vel_callback, this, std::placeholders::_1));
    }

  private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();

        m_yahboom_connection.tick();
        const auto sensor_data = m_yahboom_connection.getSensorData();
        message.data = "Message number: " + std::to_string(sensor_data.messageNr);

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        m_diag_publisher->publish(message);
    }

    void cmd_vel_callback(const geometry_msgs::msg::Twist &msg)
    {
        if (msg.linear.x > 0.0)
        {
            if (msg.angular.z > 0.0)
            {
                m_yahboom_connection.turnLeft();
            }
            else if (msg.angular.z < 0.0)
            {
                m_yahboom_connection.turnRight();
            }
            else // msg.angular.z == 0.0
            {
                m_yahboom_connection.forward();
            }
        }
        else if (msg.linear.x < 0.0)
        {
            m_yahboom_connection.backwards();
        }
        else // msg.linear.x == 0.0
        {
            if (msg.angular.z > 0.0)
            {
                m_yahboom_connection.rotateLeft();
            }
            else if (msg.angular.z < 0.0)
            {
                m_yahboom_connection.rotateRight();
            }
            else // msg.angular.z == 0.0
            {
                m_yahboom_connection.stop();
            }
        }
    }

  private:
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_diag_publisher;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_cmd_vel_subscriber;

    YahboomC::YahboomConnection m_yahboom_connection{"/dev/ttyACM0"};
};
    
} // namespace pet

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<pet::YahboomNode>());
    rclcpp::shutdown();
    return 0;
}
