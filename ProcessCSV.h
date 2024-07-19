#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

struct ImageTransform {
    std::string img_name;
    std::string img_scale; // This could be a string like "512, 512"
    std::string interpolation;
    int img_Horizontal;
    int img_Vertical;
    std::string Rotation_center;
    int Rotation_angle;
};

std::string trim(const std::string& str);

std::vector<std::string> splitCSVLine(const std::string& line);

int ProcessFile(const std::string& filename, std::vector<ImageTransform>& img_transforms);

