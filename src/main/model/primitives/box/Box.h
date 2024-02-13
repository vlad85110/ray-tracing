//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_BOX_H
#define RAY_TRACING_BOX_H

#include "main/types.h"
#include "main/model/primitives/Primitive.h"
#include "main/model/primitives/quadrangle/Quadrangle.h"
#include <array>

class Box : public Primitive {
private:
    Vector<Quadrangle> quadrangles;

public:
    Box(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &min,
        const Point &max);

    Box(const Point &min, const Point &max);

    [[nodiscard]] Vector<Line> getLines() const override;

    [[nodiscard]] Optional<Point> getIntersectionPoint(const Ray &ray) const override;

    [[nodiscard]] QVector3D getNormal(const Point &point) const override;

    void handlePoints(const QMatrix4x4 &matrix) override;

    const Vector<Quadrangle> &getQuadrangles() const;


};


#endif //RAY_TRACING_BOX_H
