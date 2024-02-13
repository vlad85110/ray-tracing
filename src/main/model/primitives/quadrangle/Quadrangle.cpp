//
// Created by Влад Кирилов on 07.05.2023.
//

#include <array>
#include "Quadrangle.h"
#include "main/math/geometry.h"

Quadrangle::Quadrangle(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &point1,
                       const Point &point2, const Point &point3, const Point &point4)
        : Primitive(kDr, kDg, kdb, kSr, kSg, ksb, power) {

    originalPoints.emplace_back(point1);
    originalPoints.emplace_back(point2);
    originalPoints.emplace_back(point3);
    originalPoints.emplace_back(point4);

    handledPoints = originalPoints;
}

Quadrangle::Quadrangle(const Point &point1, const Point &point2, const Point &point3, const Point &point4)
        : Quadrangle(0, 0, 0, 0, 0, 0, 0, point1, point2, point3, point4) {}

Vector<Line> Quadrangle::getLines() const {
    Vector<Line> res;

    auto point1 = handledPoints[0];
    auto point2 = handledPoints[1];
    auto point3 = handledPoints[2];
    auto point4 = handledPoints[3];

    res.emplace_back(point1, point2);
    res.emplace_back(point2, point3);
    res.emplace_back(point3, point4);
    res.emplace_back(point4, point1);

    return res;
}

QVector3D Quadrangle::getNormal(const Point &point) const {
    auto vector1 = handledPoints[3] - handledPoints[1];
    auto vector2 = handledPoints[2] - handledPoints[0];
    return QVector3D::crossProduct(vector2, vector1).normalized();
}

Optional<Point> Quadrangle::getIntersectionPoint(const Ray &ray) const {
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

    std::array<Point, 4> newPoints{
            handledPoints[0] - r,
            handledPoints[1] - r,
            handledPoints[2] - r,
            handledPoints[3] - r
    };

    auto signHolder = 1;
    if (newPoints[0][vInd] < 0) {
        signHolder = -1;
    }

    for (int i = 0; i < 4; ++i) {
        auto uA = newPoints[i][uInd];
        auto uB = newPoints[(i + 1) % 4][uInd];
        auto vA = newPoints[i][vInd];
        auto vB = newPoints[(i + 1) % 4][vInd];

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


