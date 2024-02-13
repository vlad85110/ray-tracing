//
// Created by Влад Кирилов on 21.03.2023.
//

#include "DoubleNumSlider.h"

DoubleNumSlider::DoubleNumSlider(int accuracy, double min, double max) : accuracy(accuracy) {
    setMinimum((int) (min * pow(10, accuracy)));
    setMaximum((int) (max * pow(10, accuracy)));
    setOrientation(Qt::Horizontal);
}

double DoubleNumSlider::getValue() const {
    return QSlider::value() * pow(10, -accuracy);
}

void DoubleNumSlider::setValue(double value) {
    auto newVal = (int) (value * pow(10, accuracy));
    QSlider::setValue(newVal);
}


