#include <opencv2/opencv.hpp>
#include "ProcessCSV.h"

std::vector <ImageTransform> Command;

int ProcessImage(ImageTransform command);

int main() {
    ProcessFile("./dataset/experiment1.csv", Command);

    for (auto& cmd : Command) {
        ProcessImage(cmd);
    }
}

int ProcessImage(ImageTransform command) {
    cv::Mat src, res;
    int interpolation;
    src = cv::imread("./dataset/" + command.img_name, cv::IMREAD_COLOR);

    if (src.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return 1;
    }

    if (strcmp(command.interpolation.c_str(), "NEAREST") == 0) {
        interpolation = cv::INTER_NEAREST;
    }
    else if (strcmp(command.interpolation.c_str(), "LINEAR") == 0) {
        interpolation = cv::INTER_LINEAR;
    }
    else    return 1;

    int img_Horizontal = 0, img_Vertical = 0;
    if (command.img_scale.size() < 4) {
        img_Horizontal = std::stof(command.img_scale) * src.cols;
        img_Vertical = std::stof(command.img_scale) * src.rows;
    }
    else{
        std::string width, height;
        std::stringstream sin;
        sin.str(command.img_scale);
        std::getline(sin, width, ',');
        std::getline(sin, height, ',');
        img_Horizontal = std::stoi(width);
        img_Vertical = std::stoi(height);
    }
    cv::Size newSize(img_Horizontal, img_Vertical);
    cv::resize(src, res, newSize, 0.0, 0.0, interpolation);

    if (strcmp(command.Rotation_center.c_str(), "center") == 0) {
        cv::Point2f center(res.cols / 2.0, res.rows / 2.0);
        cv::Mat M = (cv::Mat_<double>(2,3) << 1, 0, command.img_Horizontal, 0, 1, command.img_Vertical);
        cv::warpAffine(res, res, M, res.size(),1,0,cv::Scalar(255,255,255));
        cv::Mat rot = cv::getRotationMatrix2D(center, command.Rotation_angle, 1.0);
        cv::warpAffine(res, res, rot, res.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    }
    else if (strcmp(command.Rotation_center.c_str(), "origin") == 0) {
        cv::Point2f center(0, 0);
        cv::Mat M = (cv::Mat_<double>(2,3) << 1, 0, command.img_Horizontal, 0, 1, command.img_Vertical);
        cv::warpAffine(res, res, M, res.size(),1,0,cv::Scalar(255,255,255));
        cv::Mat rot = cv::getRotationMatrix2D(center, command.Rotation_angle, 1.0);
        cv::warpAffine(res, res, rot, res.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    }
    else    return 1;

    cv::imwrite("./Result/" + command.img_name, res);
    std::cout << "TransOK" << std::endl;
    return 0;
}

