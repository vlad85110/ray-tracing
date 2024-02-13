//
// Created by Влад Кирилов on 07.05.2023.
//

#include "Sphere.h"
#include <QMatrix4x4>
#include <set>
#include "main/math/geometry.h"

Sphere::Sphere(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &center,
               float radius) : Primitive(kDr, kDg, kdb, kSr, kSg, ksb, power), center(center), radius(radius) {

    originalPoints.emplace_back(center);

    for (int j = 0; j < M; ++j) {
        auto angleY = (float) j * 360.f / (float) M;
        auto angleZ = 90.f;
        originalPoints.emplace_back(getPointOnSphere(angleY, angleZ, radius, center));
    }

    for (int j = 0; j < M; ++j) {
        auto angleZ = (float) j * 360.f / (float) M;
        auto angleY = 90.f;
        originalPoints.emplace_back(getPointOnSphere(angleY, angleZ, radius, center));
    }

    for (int j = 0; j < M; ++j) {
        auto angleY = (float) j * 360.f / (float) M;
        auto angleZ = 0.f;
        originalPoints.emplace_back(getPointOnSphere(angleY, angleZ, radius, center));
    }

    originalPoints.emplace_back(0, 0, radius);


    handledPoints = originalPoints;
}

Vector<Line> Sphere::getLines() const {
    Vector<Line> res;

    for (int i = 1; i < M; ++i) {
        res.emplace_back(handledPoints[i], handledPoints[i + 1]);
    }
    res.emplace_back(handledPoints[M], handledPoints[1]);

    for (int i = M + 1; i < 2 * M; ++i) {
        res.emplace_back(handledPoints[i], handledPoints[i + 1]);
    }
    res.emplace_back(handledPoints[M + 1], handledPoints[2 * M]);

    for (int i = 2 * M + 1; i < 3 * M; ++i) {
        res.emplace_back(handledPoints[i], handledPoints[i + 1]);
    }
    res.emplace_back(handledPoints[2 * M + 1], handledPoints[3 * M]);

    return res;
}

const Point &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Point &center) {
    Sphere::center = center;
}

float Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}

Optional<Point> Sphere::getIntersectionPoint(const Ray &ray) const {
    auto OC = handledPoints[0] - ray.origin;
    auto tCa = QVector3D::dotProduct(OC, ray.direction);

    std::set<float> rs{
            (handledPoints[1] - handledPoints[0]).length(),
            (handledPoints[M] - handledPoints[0]).length(),
            (handledPoints[2 * M] - handledPoints[0]).length()
    };

    auto radius = *rs.rbegin();

    auto r2 = pow(radius, 2.f);
    auto OC2 = QVector3D::dotProduct(OC, OC);

    if (tCa < 0 && OC2 > r2) {
        return std::nullopt;
    }

    auto D2 = OC2 - pow(tCa, 2.f);
    auto thc2 = r2 - D2;

    if (thc2 < 0) {
        return std::nullopt;
    }

    float t;
    if (OC2 < r2) {
        t = tCa - sqrt(thc2);
    } else {
        t = tCa + sqrt(thc2);
    }

    return ray.at(t);
}

QVector3D Sphere::getNormal(const Point &point) const {
    return -(point - handledPoints[0]).normalized();
}