//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_PRIMITIVE_H
#define RAY_TRACING_PRIMITIVE_H

#include "main/types.h"
#include "main/render/ray/Ray.h"

class Primitive {
private:
    float KDr, KDg, Kdb, KSr, KSg, Ksb;
    float power;
protected:
    Vector<Point> originalPoints;
    Vector<Point> handledPoints;
public:
    Primitive(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power);

    [[nodiscard]] virtual Vector<Line> getLines() const { return {}; };

    [[nodiscard]] virtual Point getMin() const;;

    [[nodiscard]] virtual Point getMax() const;;

    virtual void handlePoints(const QMatrix4x4 &matrix);

    [[nodiscard]] virtual Optional<Point> getIntersectionPoint(const Ray &ray) const { return std::nullopt; };

    [[nodiscard]] virtual QVector3D getNormal(const Point &point) const { return {}; };

    [[nodiscard]] const Vector<Point> &getOriginalPoints() const;

    [[nodiscard]] const Vector<Point> &getHandledPoints() const;

    [[nodiscard]] float getKDr() const;

    [[nodiscard]] float getKDg() const;

    [[nodiscard]] float getKdb() const;

    [[nodiscard]] float getKSr() const;

    [[nodiscard]] float getKSg() const;

    [[nodiscard]] float getKsb() const;

    [[nodiscard]] float getPower() const;
};


#endif //RAY_TRACING_PRIMITIVE_H
