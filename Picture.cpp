//
// Created by kranya on 16.10.2020.
//

#include "Picture.h"

Picture::Picture(int height, int width) : _data(std::shared_ptr<char[]>(new char[height * width])),
                                          _height(height),
                                          _width(width),
                                          _realHeight(height),
                                          _realWidth(width),
                                          _dataShiftWidth(0),
                                          _dataShiftHeight(0){
}

char Picture::get(int x, int y) const {
    return _data[(x + _dataShiftHeight) * _realWidth + y + _dataShiftWidth];
}

Picture Picture::getSubPicture(int height, int width, int shiftH, int shiftW) const {
    return Picture(_data, height, width, shiftH, shiftW, _realHeight, _realWidth);
}

Picture::Picture(const std::shared_ptr<char[]> &data, int height, int width, int shiftH, int shiftW, int realH,
                 int realW) {
    _data = data;
    _height = height;
    _width = width;
    _dataShiftHeight = shiftH;
    _dataShiftWidth = shiftW;
    _realHeight = realH;
    _realWidth = realW;
}

bool Picture::operator==(const Picture &other) const {
    if (_width != other._width || _height != other._height) {
        return false;
    }
    for (auto i = 0; i < _height; i++) {
        for (auto j = 0; j < _width; j++) {
            if (this->get(i, j) != other.get(i, j)) {
                return false;
            }
        }
    }
    return true;
}

double Picture::compare(const Picture &other) const {
    if (_width != other._width || _height != other._height) {
        return false;
    }
    double sum = 0;
    double num = 0;
    for (auto i = 0; i < _height; i++) {
        for (auto j = 0; j < _width; j++) {
            if (this->get(i, j) == '1') {
                sum++;
                if (other.get(i, j) == '1') {
                    num++;
                }
            } else {
                if (other.get(i, j) == '1') {
                    return 0;
                }
            }
        }
    }
    return num / sum;
}

void Picture::print() const {
    for (auto i = 0; i < _height; ++i) {
        for (auto j = 0; j < _width; ++j) {
            std::cout << this->get(i, j);
        }
        std::cout << "\n";
    }
}

void Picture::set(char *beg, char *end) {
    std::copy(beg, end, _data.get());
}

void Picture::set(int i, int j, char val) {
    _data.get()[(i + _dataShiftHeight) * _realWidth + j + _dataShiftWidth] = val;
}

int Picture::width() const {
    return _width;
}

int Picture::height() const {
    return _height;
}

int Picture::heightShift() const {
    return _dataShiftHeight;
}

int Picture::widthShift() const {
    return _dataShiftWidth;
}
