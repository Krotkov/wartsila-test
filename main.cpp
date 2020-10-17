#include <iostream>
#include <fstream>
#include <cstring>
#include "Picture.h"
#include "Square.h"
#include "Circle.h"

namespace checker {
    template<typename T>
    static std::pair<bool, std::string> checkOne(const Picture &pic) {
        Picture templatePicture = T::drawShape(pic.height(), pic.width());
        if (templatePicture.compare(pic) >= 0.95) {
            return {true, T::printInfo(pic)};
        } else {
            return {false, ""};
        }
    }

    template<typename Arg>
    static std::pair<bool, std::string> checkFigures(const Picture &i) {
        return checkOne<Arg>(i);
    }

    std::pair<bool, std::string>
    uniteResults(const std::pair<bool, std::string> &a, const std::pair<bool, std::string> &b) {
        std::string ansStr;
        if (a.first && b.first) {
            ansStr = a.second + "\nили\n" + b.second;
        } else {
            if (a.first) {
                ansStr = a.second;
            }
            if (b.first) {
                ansStr = b.second;
            }
        }
        return {a.first || b.first, ansStr};
    }

    template<typename Arg, typename Arg1, typename... Args>
    static std::pair<bool, std::string> checkFigures(const Picture &i) {
        auto ans = checkOne<Arg>(i);
        return uniteResults(checkOne<Arg>(i), checkFigures<Arg1, Args...>(i));
    }
}

int main() {
    std::ifstream myFile;
    myFile.open("../test/sample1.txt");
    char *data = new char[225];
    for (int i = 0; i < 15; ++i) {
        std::string a;
        myFile >> a;
        strcpy(data + i * 15, a.c_str());
    }
    Picture pic(15, 15);
    pic.set(data, data + 225);
    delete[] data;

    int minX = pic.height(), minY = pic.width(), maxX = -1, maxY = -1;
    for (auto i = 0; i < pic.height(); ++i) {
        for (auto j = 0; j < pic.width(); ++j) {
            if (pic.get(i, j) == '1') {
                minX = std::min(minX, i);
                minY = std::min(minY, j);
                maxX = std::max(maxX, i);
                maxY = std::max(maxY, j);
            }
        }
    }
    int n = maxX - minX + 1;
    int m = maxY - minY + 1;
    pic = pic.getSubPicture(n, m, minX, minY);

    std::pair<bool, std::string> ans = checker::checkFigures<Square, Circle>(pic);

    if (ans.first) {
        std::cout << ans.second;
    } else {
        std::cout << "Неизвестная фигура\n";
    }
    return 0;
}
