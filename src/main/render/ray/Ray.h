//
// Created by Влад Кирилов on 16.05.2023.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "main/types.h"

struct Ray {
    Point origin;
    QVector3D direction;

    Ray(const Point &origin, const QVector3D &direction);

    [[nodiscard]] Point at(float t) const;
};


#endif //RAY_TRACING_RAY_H
