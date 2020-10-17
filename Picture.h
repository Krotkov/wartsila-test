//
// Created by kranya on 16.10.2020.
//

#ifndef WARTSILA_PICTURE_H
#define WARTSILA_PICTURE_H

#include <memory>
#include <cstring>
#include <iostream>

class Picture {

public:
    Picture(int h, int w);

    [[nodiscard]] Picture getSubPicture(int height, int width, int shiftH, int shiftW) const;

    [[nodiscard]] char get(int x, int y) const;

    void set(char *beg, char *end);

    void set(int i, int j, char val);

    [[nodiscard]] int width() const;

    [[nodiscard]] int height() const;

    [[nodiscard]] int heightShift() const;

    [[nodiscard]] int widthShift() const;

    bool operator==(const Picture &other) const;

    [[nodiscard]] double compare(const Picture& other) const;

    void print() const;

private:

    Picture(const std::shared_ptr<char[]> &data, int height, int width, int shiftH, int shiftW, int realH, int realW);

    std::shared_ptr<char[]> _data;
    int _dataShiftHeight;
    int _dataShiftWidth;
    int _realHeight;
    int _realWidth;
    int _height;
    int _width;
};


#endif //WARTSILA_PICTURE_H
