#ifndef HMI_COLOR_H
#define HMI_COLOR_H
using namespace std;

const int DEFAULT_COLOR[] = {255, 255, 255};

class Color {
public:
    Color() = default;
    Color(int r, int g, int b) {
        this->r = max(0, min(255, r));
        this->g = max(0, min(255, g));
        this->b = max(0, min(255, b));
    };
    Color(int r, int g, int b, float a) {
        this->r = max(0, min(255, r));
        this->g = max(0, min(255, g));
        this->b = max(0, min(255, b));
        this->a = max(0.0f, min(1.0f, a));
    };
    int r = DEFAULT_COLOR[0];
    int g = DEFAULT_COLOR[1];
    int b = DEFAULT_COLOR[2];
    float a = 1.0f;
};

#endif //HMI_COLOR_H