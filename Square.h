//
// Created by kranya on 16.10.2020.
//

#ifndef WARTSILA_SQUARE_H
#define WARTSILA_SQUARE_H

class Square {
public:
    static Picture drawShape(int n, int m) {
        Picture pica(n, m);
        int squareSize = std::min(n, m);
        for (auto i = 0; i < squareSize; i++) {
            for (auto j = 0; j < squareSize; j++) {
                pica.set(i, j, '1');
            }
        }
        return pica;
    }

    static std::string printInfo(const Picture &pic) {
        return std::string("квадрат\nРазмер стороны: ").append(std::to_string(pic.height())).append(
                "\nКоординаты левого верхнего угла: ").append(std::to_string(pic.heightShift())).append(
                " ").append(std::to_string(pic.widthShift())).append("\n");
    }
};


#endif //WARTSILA_SQUARE_H
