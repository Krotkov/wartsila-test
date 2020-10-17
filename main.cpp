#include <iostream>
#include <fstream>
#include "Picture.h"
#include "Square.h"
#include "Circle.h"
#include <optional>

namespace checker {
    template<typename T>
    static std::optional<std::string> checkOne(const Picture &pic) {
        Picture templatePicture = T::drawShape(pic.height(), pic.width());
        if (templatePicture.compare(pic) >= 0.93) {
            return std::make_optional(T::printInfo(pic));
        } else {
            return std::nullopt;
        }
    }

    template<typename Arg>
    static std::optional<std::string> checkFigures(const Picture &i) {
        return checkOne<Arg>(i);
    }

    template<typename Arg, typename Arg1, typename... Args>
    static std::optional<std::string> checkFigures(const Picture &i) {
        auto ans = checkOne<Arg>(i);
        if (ans.has_value()) {
            return ans;
        } else {
            return checkFigures<Arg1, Args...>(i);
        }
    }
}

Picture readDataFromFile(const std::string& path) {
    std::ifstream myFile;
    myFile.open(path);
    char *data = new char[225];
    for (int i = 0; i < 15; ++i) {
        myFile.read(data + i * 15, 15);
        myFile.ignore(1);
    }
    myFile.close();
    Picture pic(15, 15);
    pic.set(data, data + 225);
    delete[] data;
    return pic;
}

void cutPicture(Picture& pic) {
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
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Must be one";
        return 0;
    }

    Picture pic = readDataFromFile(argv[1]);

    cutPicture(pic);

    if (pic.height() < 5 || pic.width() < 5) {
        std::cout << "Неизвестная фигура\n";
        return 0;
    }

    auto ans = checker::checkFigures<Square, Circle>(pic);
    if (ans.has_value()) {
        std::cout << *ans;
    } else {
        std::cout << "Неизвестная фигура\n";
    }
    return 0;
}
