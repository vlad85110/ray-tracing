//
// Created by Влад Кирилов on 07.05.2023.
//

#include <array>
#include "Triangle.h"
#include "main/math/geometry.h"

Triangle::Triangle(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &point1,
                   const Point &point2, const Point &point3)
        : Primitive(kDr, kDg, kdb, kSr, kSg, ksb, power) {
    originalPoints.emplace_back(point1);
    originalPoints.emplace_back(point2);
    originalPoints.emplace_back(point3);

    handledPoints = originalPoints;
}

Triangle::Triangle(const Point &point1, const Point &point2, const Point &point3)
        : Triangle(0, 0, 0, 0, 0, 0, 0, point1, point2, point3) {}

Triangle::Triangle(const Primitive &primitive, const Point &point1, const Point &point2, const Point &point3)
        : Primitive(primitive) {

    originalPoints.emplace_back(point1);
    originalPoints.emplace_back(point2);
    originalPoints.emplace_back(point3);

    handledPoints = originalPoints;
}

Vector<Line> Triangle::getLines() const {
    Vector<Line> res;

    res.emplace_back(handledPoints[0], handledPoints[1]);
    res.emplace_back(handledPoints[1], handledPoints[2]);
    res.emplace_back(handledPoints[2], handledPoints[0]);

    return res;
}

QVector3D Triangle::getNormal(const Point &point) const {
    auto vector1 = handledPoints[1] - handledPoints[0];
    auto vector2 = handledPoints[2] - handledPoints[0];
    return QVector3D::crossProduct(vector1, vector2).normalized();
}

Optional<Point> Triangle::getIntersectionPoint(const Ray &ray) const {
    auto pN = getNormal({});

    auto pointOpt = getPlaneIntersectionPoint(pN, ray, handledPoints[0]);
    if (!pointOpt.has_value()) return std::nullopt;
    auto &r = pointOpt.value();

    auto maxIndex = getVectorDominantCoordIndex(pN);

    auto uInd = 0;
    auto vInd = 2;

    if (maxIndex == 0) uInd = 1;
    if (maxIndex == 2) vInd = 1;

    int nextSighHolder;
    auto numCrossing = 0;

    std::array<Point, 3> newPoints{
            handledPoints[0] - r,
            handledPoints[1] - r,
            handledPoints[2] - r
    };

    auto signHolder = 1;
    if (newPoints[0][vInd] < 0) {
        signHolder = -1;
    }

    for (int i = 0; i < 3; ++i) {
        auto uA = newPoints[i][uInd];
        auto uB = newPoints[(i + 1) % 3][uInd];
        auto vA = newPoints[i][vInd];
        auto vB = newPoints[(i + 1) % 3][vInd];

        if (vB < 0) {
            nextSighHolder = -1;
        } else nextSighHolder = 1;

        if (nextSighHolder != signHolder) {
            if ((uA > 0 && uB > 0) || ((uA > 0 || uB > 0) && (uA - (vA * (uB - uA)) / (vB - vA)) > 0)) {
                numCrossing++;
            }
        }

        signHolder = nextSighHolder;
    }

    if (numCrossing % 2 == 1) {
        return r;
    } else {
        return std::nullopt;
    }
}



