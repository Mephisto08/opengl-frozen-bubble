#ifndef HMI_COLOR_H
#define HMI_COLOR_H
using namespace std;

const int DEFAULT_COLOR[] = {255, 255, 255, 255};

class Color {
public:
    Color() {};
    Color(int r, int g, int b) {
        this->r = max(0, min(255, r));
        this->g = max(0, min(255, g));
        this->b = max(0, min(255, b));
    };
    Color(int r, int g, int b, int a) {
        this->r = max(0, min(255, r));
        this->g = max(0, min(255, g));
        this->b = max(0, min(255, b));
        this->a = max(0, min(255, a));
    };
    int r = DEFAULT_COLOR[1];
    int g = DEFAULT_COLOR[2];
    int b = DEFAULT_COLOR[3];
    int a = DEFAULT_COLOR[4];
};

#endif //HMI_COLOR_H