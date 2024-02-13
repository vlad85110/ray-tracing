//
// Created by Влад Кирилов on 07.05.2023.
//

#include <set>
#include <cfloat>
#include "Box.h"

Box::Box(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power, const Point &min,
         const Point &max)
        : Primitive(kDr, kDg, kdb, kSr, kSg, ksb, power) {

    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            Point(min.x(), max.y(), min.z()),
            Point(max.x(), max.y(), min.z()),
            Point(max.x(), min.y(), min.z()),
            min);


    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            Point(min.x(), min.y(), max.z()),
            Point(max.x(), min.y(), max.z()),
            Point(max.x(), max.y(), max.z()),
            Point(min.x(), max.y(), max.z()));

    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            min,
            Point(min.x(), min.y(), max.z()),
            Point(min.x(), max.y(), max.z()),
            Point(min.x(), max.y(), min.z()));

    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            Point(max.x(), min.y(), min.z()),
            Point(max.x(), min.y(), max.z()),
            Point(max.x(), max.y(), max.z()),
            Point(max.x(), max.y(), min.z()));

    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            min,
            Point(min.x(), min.y(), max.z()),
            Point(max.x(), min.y(), max.z()),
            Point(max.x(), min.y(), min.z()));

    quadrangles.emplace_back(
            kDr, kDg, kdb, kSr, kSg, ksb, power,
            Point(min.x(), max.y(), min.z()),
            Point(min.x(), max.y(), max.z()),
            Point(max.x(), max.y(), max.z()),
            Point(max.x(), max.y(), min.z()));


//    originalPoints.emplace_back(min);
//    originalPoints.emplace_back(min.x(), min.y(), max.z());
//    originalPoints.emplace_back(max.x(), min.y(), min.z());
//    originalPoints.emplace_back(min.x(), max.y(), min.z());
//    originalPoints.emplace_back(max.x(), max.y(), min.z());
//    originalPoints.emplace_back(min.x(), max.y(), max.z());
//    originalPoints.emplace_back(max.x(), min.y(), max.z());
//    originalPoints.emplace_back(max);
//
//    handledPoints = originalPoints;
}

Box::Box(const Point &min, const Point &max) : Box(0, 0, 0, 0, 0, 0, 0, min, max) {}

Vector<Line> Box::getLines() const {
    Vector<Line> res;

    for (auto &q: quadrangles) {
        auto lines = q.getLines();

        res.insert(res.end(), lines.begin(), lines.end());
    }

    return res;
}

void Box::handlePoints(const QMatrix4x4 &matrix) {
    for (auto &q: quadrangles) {
        q.handlePoints(matrix);
    }
}

Optional<Point> Box::getIntersectionPoint(const Ray &ray) const {
    auto tNear = -INFINITY;
    auto tFar = INFINITY;

    auto min = getMin();
    auto max = getMax();

    float t1, t2;

    if (ray.direction.x() == 0) {
        if (ray.origin.x() < min.x() || ray.origin.x() > max.x()) {
            return std::nullopt;
        }
    }

    t1 = (min.x() - ray.origin.x()) / ray.direction.x();
    t2 = (max.x() - ray.origin.x()) / ray.direction.x();

    if (t2 < t1) std::swap(t1, t2);
    if (t1 > tNear) tNear = t1;
    if (t2 < tFar) tFar = t2;
    if (tNear > tFar) return std::nullopt;
    if (tFar < 0) return std::nullopt;

    //

    if (ray.direction.y() == 0) {
        if (ray.origin.y() < min.y() || ray.origin.y() > max.y()) {
            return std::nullopt;
        }
    }

    t1 = (min.y() - ray.origin.y()) / ray.direction.y();
    t2 = (max.y() - ray.origin.y()) / ray.direction.y();

    if (t2 < t1) std::swap(t1, t2);
    if (t1 > tNear) tNear = t1;
    if (t2 < tFar) tFar = t2;
    if (tNear > tFar) return std::nullopt;
    if (tFar < 0) return std::nullopt;

    //

    if (ray.direction.z() == 0) {
        if (ray.origin.z() < min.z() || ray.origin.z() > max.z()) {
            return std::nullopt;
        }
    }

    t1 = (min.z() - ray.origin.z()) / ray.direction.z();
    t2 = (max.z() - ray.origin.z()) / ray.direction.z();

    if (t2 < t1) std::swap(t1, t2);
    if (t1 > tNear) tNear = t1;
    if (t2 < tFar) tFar = t2;
    if (tNear > tFar) return std::nullopt;
    if (tFar < 0) return std::nullopt;

    return ray.at(tNear);
}

QVector3D Box::getNormal(const Point &point) const {}

const Vector<Quadrangle> &Box::getQuadrangles() const {
    return quadrangles;
}






