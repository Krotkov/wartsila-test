//
// Created by kranya on 16.10.2020.
//

#ifndef WARTSILA_CIRCLE_H
#define WARTSILA_CIRCLE_H

#include "Picture.h"

class Circle {
public:
    static Picture drawShape(int n, int m) {
        int diameter = std::min(n, m);
        double radius = diameter / 2;
        Picture pica(diameter, diameter);
        double centerX = radius, centerY = radius;
        if (diameter % 2 == 0) {
            centerX -= 0.5;
            centerY -= 0.5;
        }
        for (int i = 0; i < diameter; i++) {
            for (int j = 0; j < diameter; j++) {
                if ((centerX - i) * (centerX - i) + (centerY - j) * (centerY - j) <= radius * radius) {
                    pica.set(i, j, '1');
                } else {
                    pica.set(i, j, '0');
                }
            }
        }
        return pica;
    }

    static std::string printInfo(const Picture &pic) {
        int diameter = std::min(pic.height(), pic.width());
        Picture pica(diameter, diameter);
        double centerX = diameter / 2 + pic.heightShift(), centerY = diameter / 2 + pic.widthShift();
        if (diameter % 2 == 0) {
            centerX -= 0.5;
            centerY -= 0.5;
        }
        return std::string("Круг\n") + "Диаметр: " + std::to_string(pic.height()) + "\nКоординаты центра: " +
               std::to_string(centerX) + " " + std::to_string(centerY) + "\n";
    }
};


#endif //WARTSILA_CIRCLE_H
