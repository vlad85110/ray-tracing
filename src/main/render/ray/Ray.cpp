//
// Created by Влад Кирилов on 16.05.2023.
//

#include "Ray.h"

Ray::Ray(const Point &origin, const QVector3D &direction)
        : origin(origin), direction(direction.normalized()) {}

Point Ray::at(float t) const {
    return origin + direction * t;
}

