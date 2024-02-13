//
// Created by Влад Кирилов on 07.05.2023.
//

#include "LightSource.h"

LightSource::LightSource(const Point &point, QRgb color)
        : Primitive(0, 0, 0, 0, 0, 0, 0), color(color) {

    originalPoints.emplace_back(point);
    handledPoints = originalPoints;
}

QRgb LightSource::getColor() const {
    return color;
}

void LightSource::setColor(QRgb color) {
    LightSource::color = color;
}

const Point &LightSource::getPoint() const {
    return handledPoints[0];
}

