//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H


#include "main/model/primitives/Primitive.h"
#include "main/types.h"

class Sphere : public Primitive {
private:
    Point center;
    float radius;

    const int M = 30;

public:

    Sphere(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &center,
           float radius);

    [[nodiscard]] const Point &getCenter() const;

    void setCenter(const Point &center);

    [[nodiscard]] float getRadius() const;

    void setRadius(float radius);

    [[nodiscard]] Vector<Line> getLines() const override;

    [[nodiscard]] Optional<Point> getIntersectionPoint(const Ray &ray) const override;

    [[nodiscard]] QVector3D getNormal(const Point &point) const override;

};


#endif //RAY_TRACING_SPHERE_H
