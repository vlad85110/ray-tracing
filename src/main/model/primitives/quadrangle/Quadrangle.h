//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_QUADRANGLE_H
#define RAY_TRACING_QUADRANGLE_H


#include "main/model/primitives/Primitive.h"
#include "main/types.h"

class Quadrangle : public Primitive {
public:
    Quadrangle(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &point1,
               const Point &point2, const Point &point3, const Point &point4);

    Quadrangle(const Point &point1, const Point &point2, const Point &point3, const Point &point4);

    [[nodiscard]] Vector<Line> getLines() const override;

    [[nodiscard]] QVector3D getNormal(const Point &point) const override;

    [[nodiscard]] Optional<Point> getIntersectionPoint(const Ray &ray) const override;

};


#endif //RAY_TRACING_QUADRANGLE_H
