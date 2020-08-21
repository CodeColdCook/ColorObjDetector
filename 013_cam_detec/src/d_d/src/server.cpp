#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <d_d/ChangeConfig.h>

#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <json/json.h>


#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <detector.h>
using namespace std;

Detector *pdet;
bool config_init = false;
bool detector_is_alive = true;
int index_dataSave = 1;
vector<int> color_begin(3,0), color_end(3,0);

string json_add;
string json_file_add;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{

    Mat img = cv_bridge::toCvCopy(msg, "bgr8")->image;
    cv::imshow("view_usb", img);
    pdet->detect(img);
}

void callback(d_d::ChangeConfig &config, uint32_t level) {
    ROS_INFO("Reconfigure Request: %d %d %d %d %d %d Config saved: %s", 
              config.R1, config.G1,config.B1,
             config.R2, config.G2, config.B2,
             config.save_param?"True":"False");
    if(detector_is_alive)
    {
        if(config_init)
        {
            vector<int> color_begin_(3,0), color_end_(3,0);
            color_begin_[0] = config.R1;
            color_begin_[1] = config.G1;
            color_begin_[2] = config.B1;
            color_end_[0] = config.R2;
            color_end_[1] = config.G2;
            color_end_[2] = config.B2;
            pdet->adjust_colorRange(color_begin_,color_end_);
        }
        else
            config_init = true; 
    }
    if(config.save_param)
    {
        ROS_INFO("Config is saving...");
        string json_save_add;
        json_save_add += (json_file_add + "RGBdata_V" + to_string(index_dataSave ++) + ".json");
        Json::Value json_obj_w;

        json_obj_w["R1"] = Json::Value(config.R1);
        json_obj_w["G1"] = Json::Value(config.G1);
        json_obj_w["B1"] = Json::Value(config.B1);
        json_obj_w["R2"] = Json::Value(config.R2);
        json_obj_w["G2"] = Json::Value(config.G2);
        json_obj_w["B2"] = Json::Value(config.B2);

        Json::StyledWriter style_writer;
        string str_w = style_writer.write(json_obj_w);
        ofstream ofs(json_save_add);
        ofs << str_w;
        ofs.close();
        cout << "Json saved at: "  << json_save_add << endl <<  str_w << endl;
    }
    
}

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "d_d");
    ros::NodeHandle nh("~");
    nh.getParam("json_add", json_add);
    nh.getParam("json_file_add", json_file_add);

    Json::Reader reader;
    Json::Value json_obj;
    ifstream ifs(json_add);
    if(!reader.parse(ifs,json_obj))
        ROS_INFO("file error!");
    else
    {
        ROS_INFO("json file is loading:");
        color_begin[0] = json_obj["R1"].asInt();
        color_begin[1] = json_obj["G1"].asInt();
        color_begin[2] = json_obj["B1"].asInt();
        color_end[0] = json_obj["R2"].asInt();
        color_end[1] = json_obj["G2"].asInt();
        color_end[2] = json_obj["B2"].asInt();
    }
    pdet = new Detector();
    if(pdet->initialize(color_begin, color_end))
    {
        ROS_INFO("Detector is initialized, start detect obj...");
    }

    cv::namedWindow("view_usb");
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("image", 1, imageCallback);

    dynamic_reconfigure::Server<d_d::ChangeConfig> server;
    dynamic_reconfigure::Server<d_d::ChangeConfig>::CallbackType f;

    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);

    ROS_INFO("Spinning node");
    ros::spin();

    cv::destroyWindow("view_usb");
    delete pdet;

    return EXIT_SUCCESS;
}
