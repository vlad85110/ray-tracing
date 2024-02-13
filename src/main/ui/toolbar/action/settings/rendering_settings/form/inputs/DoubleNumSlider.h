//
// Created by Влад Кирилов on 21.03.2023.
//

#ifndef FILTERS_DOUBLENUMSLIDER_H
#define FILTERS_DOUBLENUMSLIDER_H

#include <QSlider>

class DoubleNumSlider : public QSlider {
private:
    int accuracy;
public:
    DoubleNumSlider(int accuracy, double min, double max);

    [[nodiscard]] double getValue() const;

    void setValue(double value);

};


#endif //FILTERS_DOUBLENUMSLIDER_H
