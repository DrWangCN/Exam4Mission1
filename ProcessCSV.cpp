#include "ProcessCSV.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string field;
    bool inQuotes = false;
    char c;

    while (ss.get(c)) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            result.push_back(trim(field));
            field.clear();
        } else {
            field += c;
        }
    }
    result.push_back(trim(field));

    return result;
}

int ProcessFile(const std::string& filename, std::vector<ImageTransform>& img_transforms) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> fields = splitCSVLine(line);
        if (fields.size() != 7) {
            std::cerr << "Invalid data in line: " << line << std::endl;
            continue;
        }

        try {
            ImageTransform transform;
            transform.img_name = fields[0];
            transform.img_scale = fields[1];
            transform.interpolation = fields[2];
            transform.img_Horizontal = std::stoi(fields[3]);
            transform.img_Vertical = std::stoi(fields[4]);
            transform.Rotation_center = fields[5];
            transform.Rotation_angle = std::stoi(fields[6]);
            img_transforms.push_back(transform);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data in line: " << line << " (" << e.what() << ")" << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range data in line: " << line << " (" << e.what() << ")" << std::endl;
        }
    }

    file.close();

    // Output the data to verify
    for (const auto& transform : img_transforms) {
        std::cout << "Image Name: " << transform.img_name 
                  << ", Scale: " << transform.img_scale 
                  << ", Interpolation: " << transform.interpolation 
                  << ", Horizontal: " << transform.img_Horizontal 
                  << ", Vertical: " << transform.img_Vertical 
                  << ", Rotation Center: " << transform.Rotation_center 
                  << ", Rotation Angle: " << transform.Rotation_angle << std::endl;
    }

    return 0;
}

