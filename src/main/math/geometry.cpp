//
// Created by Влад Кирилов on 20.05.2023.
//

#include "geometry.h"
#include <QMatrix4x4>

int sgn(float number) {
    if (number < 0) {
        return -1;
    } else {
        return 1;
    }
}

int getVectorDominantCoordIndex(const QVector3D &vector3D) {
    auto max = -1.f;
    auto maxIndex = -1;

    for (int i = 0; i < 3; ++i) {
        if (abs(vector3D[i]) > max) {
            max = abs(vector3D[i]);
            maxIndex = i;
        }
    }

    return maxIndex;
}

Optional<Point> getPlaneIntersectionPoint(const QVector3D &normal, const Ray &ray,
                                          const Point &pointOnPlane) {

    auto vD = QVector3D::dotProduct(normal, ray.direction);
    if (vD == 0) return std::nullopt;

    auto d = -QVector3D::dotProduct(normal, pointOnPlane);
    auto v0 = -QVector3D::dotProduct(normal, ray.origin) - d;
    auto t = v0 / vD;

    if (t < 0) return std::nullopt;
    return ray.origin + ray.direction * t;
}

QVector3D getReflectionVector(const Ray &ray, const QVector3D &normal) {
    auto N = normal;

    if (QVector3D::dotProduct(normal, ray.direction) < 0) {
        N = -N;
    }

    return (2 * QVector3D::dotProduct(N, ray.direction) * N - ray.direction).normalized();
}

Point getPointOnSphere(float angleY, float angleZ, float radius, const Point &center) {
    angleY = qDegreesToRadians(angleY);
    angleZ = qDegreesToRadians(angleZ);

    auto r = radius;

    QMatrix4x4 matrix(
            0, 0, 0, r * sin(angleY) * cos(angleZ) + center.x(),
            0, 0, 0, r * sin(angleY) * sin(angleZ) + center.y(),
            0, 0, 0, r * cos(angleY) + center.z(),
            0, 0, 0, 1
    );

    return matrix.map({0, 0, 0});
}

QVector3D getH(const QVector3D &eye, const QVector3D &lightRay) {
    auto LE = lightRay + eye;
    return LE / LE.length();
}
