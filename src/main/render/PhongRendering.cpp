//
// Created by Влад Кирилов on 15.05.2023.
//

#include "PhongRendering.h"
#include "main/render/ray/Ray.h"
#include "main/config/render/RenderConfig.h"
#include <QVector3D>
#include <QImage>
#include <utility>
#include <unordered_set>
#include "main/math/geometry.h"
#include <QThreadPool>
#include <QMutex>
#include <QMatrix4x4>

PhongRendering::PhongRendering(const Scene &scene, const RenderConfig &renderConfig, SceneConfig sceneConfig)
        : scene(scene), grid(scene.getPrimitives(), 100),
          depth(renderConfig.depth), sceneConfig(std::move(sceneConfig)), gamma(renderConfig.gamma) {}

QImage PhongRendering::renderScene(int height, int width) {
    QImage image(width, height, QImage::Format_ARGB32);

    auto start = std::chrono::high_resolution_clock::now();
    auto maxR = -1.f, maxG = -1.f, maxB = -1.f;

    Vector<float> rS(height * width);
    Vector<float> gS(height * width);
    Vector<float> bS(height * width);

    QThreadPool::globalInstance()->setMaxThreadCount(threadCnt);

    for (int i = 0; i < height; ++i) {
        QThreadPool::globalInstance()->start([width, i, height, &rS, &gS, &bS, this] {
            for (int j = 0; j < width; ++j) {
                auto x = (2 * static_cast<float>(j) / static_cast<float>(width)) - 1;
                auto y = 1 - (2 * static_cast<float>(i) / static_cast<float>(height));
                auto z = 0.f;

                auto ray = Ray({x, y, z}, QVector3D(0, 0, 1));
                auto color = traceRay(ray);

                auto red = color[0];
                auto green = color[1];
                auto blue = color[2];

                rS[i * width + j] = red;
                gS[i * width + j] = green;
                bS[i * width + j] = blue;
            }
        });
    }

    QThreadPool::globalInstance()->waitForDone();

    for (int i = 0; i < rS.size(); ++i) {
        auto red = rS[i];
        auto green = gS[i];
        auto blue = bS[i];

        if (red > maxR) maxR = red;
        if (green > maxG) maxG = green;
        if (blue > maxB) maxB = blue;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto red = rS[i * width + j];
            auto green = gS[i * width + j];
            auto blue = bS[i * width + j];

            auto newRed = static_cast<int>(red / maxR * 255.f);
            auto newGreen = static_cast<int>(green / maxG * 255.f);
            auto newBlue = static_cast<int>(blue / maxB * 255.f);

            image.setPixel(j, i, qRgb(newRed, newGreen, newBlue));
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto pixel = image.pixel(j, i);

            auto r = qRed(pixel);
            auto g = qGreen(pixel);
            auto b = qBlue(pixel);

            r = (int) (pow((double) r / 255, gamma) * 255);
            g = (int) (pow((double) g / 255, gamma) * 255);
            b = (int) (pow((double) b / 255, gamma) * 255);

            image.setPixel(j, i, qRgb(r, g, b));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;

    return image;
}

std::array<float, 3> PhongRendering::traceRay(const Ray &ray) {
    Vector<Point> points;
    Vector<const ptr<Primitive>> primitives;
    Vector<QVector3D> normals;
    Vector<Ray> rays;

    auto currentRay = ray;

    for (int i = 0; i < depth; ++i) {
        rays.emplace_back(currentRay);
        auto pairOpt = getRayIntersectionPrimitive(currentRay);

        if (pairOpt.has_value()) {
            auto &intersectionPoint = pairOpt.value().first;
            auto &intersectedPrimitive = pairOpt.value().second;

            points.emplace_back(intersectionPoint);
            primitives.emplace_back(intersectedPrimitive);

            auto normal = intersectedPrimitive->getNormal(intersectionPoint);
            normals.emplace_back(normal);

            auto reflected = getReflectionVector(currentRay, normal).normalized();
            currentRay = Ray(intersectionPoint, reflected);
        } else {
            break;
        }
    }

    auto ambient = sceneConfig.scatteredLight;

    float iR, iG, iB;

    auto ambientR = static_cast<float>(qRed(ambient)) / 255.f;
    auto ambientG = static_cast<float>(qGreen(ambient)) / 255.f;
    auto ambientB = static_cast<float>(qBlue(ambient)) / 255.f;
    float prevIR = 0, prevIG = 0, prevIB = 0;

    auto raysSizeInt = static_cast<int>(rays.size());

    for (auto i = raysSizeInt - 1; i >= 0; --i) {
        if (i >= points.size()) {
            iR = ambientR;
            iG = ambientG;
            iB = ambientB;
        } else {
            float lIr = 0, lIg = 0, lIb = 0;

            auto &point = points[i];
            auto &primitive = primitives[i];
            auto &N = normals[i];

            auto kDr = static_cast<float>(primitive->getKDr());
            auto kDg = static_cast<float>(primitive->getKDg());
            auto kDb = static_cast<float>(primitive->getKdb());

            auto kSr = static_cast<float>(primitive->getKSr());
            auto kSg = static_cast<float>(primitive->getKSg());
            auto kSb = static_cast<float>(primitive->getKsb());

            for (const auto &ls: sceneConfig.lightSources) {
                if (isInLightSourceVision(point, ls)) {
                    auto lightSourceDirection = point - ls.getPoint();
                    auto lightRay = Ray(ls.getPoint(), lightSourceDirection);

                    auto Ri = getReflectionVector(lightRay, N);

                    auto dotNL = QVector3D::dotProduct(N, -lightRay.direction);
                    auto dotRV = QVector3D::dotProduct(N, Ri);

                    dotNL = std::max(0.f, dotNL);
                    dotRV = std::max(0.f, dotRV);

                    auto lightSourceColor = ls.getColor();
                    auto lightSourceR = static_cast<float>(qRed(lightSourceColor)) / 255.f;
                    auto lightSourceG = static_cast<float>(qGreen(lightSourceColor)) / 255.f;
                    auto lightSourceB = static_cast<float>(qBlue(lightSourceColor)) / 255.f;

                    auto power = primitive->getPower();

                    auto d = lightSourceDirection.length();
                    auto fAtt = 1 / (1.f + d);

                    lIr += fAtt * lightSourceR * (kDr * dotNL + kSr * pow(dotRV, power));
                    lIg += fAtt * lightSourceG * (kDg * dotNL + kSg * pow(dotRV, power));
                    lIb += fAtt * lightSourceB * (kDb * dotNL + kSb * pow(dotRV, power));
                } else {
                    lIr += 0;
                    lIg += 0;
                    lIb += 0;
                }
            }

            auto prevPoint = points[i + 1];
            auto d = (point - prevPoint).length();
            auto fAtt = 1 / (1.f + d);

            iR = lIr + ambientR * kDr + prevIR * kSr * fAtt;
            iG = lIg + ambientG * kDg + prevIG * kSg * fAtt;
            iB = lIb + ambientB * kDb + prevIB * kSb * fAtt;
        }

        prevIR = iR;
        prevIG = iG;
        prevIB = iB;
    }

    return {iR, iG, iB};
}

Optional<std::pair<Point, const ptr<Primitive>>> PhongRendering::getRayIntersectionPrimitive(const Ray &ray) {
    std::unordered_set<long> ids;

    auto dominantCoordIndex = getVectorDominantCoordIndex(ray.direction);
    auto normal = QVector3D(0, 0, 0);
    normal[dominantCoordIndex] = 1;

    auto gridDirection = sgn(ray.direction[dominantCoordIndex]);

    auto pair = Grid::getMinAndMax(dominantCoordIndex);
    auto step = grid.getStep(dominantCoordIndex);

    auto coord = ray.origin[dominantCoordIndex];

    while (true) {
        if (coord < pair.first || coord > pair.second) break;

        auto pointOnPlane = Point(0, 0, 0.5);
        pointOnPlane[dominantCoordIndex] = coord;
        auto intersectionPoint = getPlaneIntersectionPoint(normal, ray, pointOnPlane).value();

        auto intersectionPointIndex = grid.getPointIndex(intersectionPoint);

        if (intersectionPointIndex == -1) break;

        auto &currentCell = grid[intersectionPointIndex];

        if (!currentCell.empty()) {
            int minDistanceIndex = -1;
            float minDist = INFINITY;
            Point minPoint;

            for (auto i = 0; i < currentCell.size(); ++i) {
                const auto &pair = currentCell[i];

                auto &primitive = pair.second;
                auto pointOpt = primitive->getIntersectionPoint(ray);

                if (pointOpt.has_value()) {
                    auto point = pointOpt.value();
                    if (grid.getPointCoordIndex(point, dominantCoordIndex) ==
                        grid.getPointCoordIndex(intersectionPoint, dominantCoordIndex)) {
                        auto dist = (ray.origin - point).length();

                        if (dist < minDist) {
                            minDist = dist;
                            minDistanceIndex = i;
                            minPoint = point;
                        }
                    }
                }
            }

            if (minDistanceIndex != -1) {
                return std::make_pair(minPoint, currentCell[minDistanceIndex].second);
            }

        }

        coord += step * static_cast<float>(gridDirection);
    }

    return std::nullopt;
}

bool PhongRendering::isInLightSourceVision(const Point &originPoint, const LightSource &lightSource) const {
    std::unordered_set<long> ids;

    auto ray = Ray(originPoint, lightSource.getPoint() - originPoint);

    auto dominantCoordIndex = getVectorDominantCoordIndex(ray.direction);

    auto normal = QVector3D(0, 0, 0);
    normal[dominantCoordIndex] = 1;

    auto gridDirection = sgn(ray.direction[dominantCoordIndex]);

    auto pair = Grid::getMinAndMax(dominantCoordIndex);
    auto step = grid.getStep(dominantCoordIndex);

    auto coord = ray.origin[dominantCoordIndex];

    if (coord < pair.first) {
        coord = pair.first + 0.0001f;
    } else if (coord > pair.second) {
        coord = pair.second - 0.0001f;
    }

    coord += step * static_cast<float>(gridDirection);

    auto cellCnt = grid.getCellCnt();

    while (true) {
        if (coord < pair.first || coord > pair.second) break;

        auto pointOnPlane = Point(0, 0, 0.5);
        pointOnPlane[dominantCoordIndex] = coord;
        auto intersectionPoint = getPlaneIntersectionPoint(normal, ray, pointOnPlane).value();

        auto x = grid.getPointXIndex(intersectionPoint);
        auto y = grid.getPointYIndex(intersectionPoint);
        auto z = grid.getPointZIndex(intersectionPoint);

        int c_x, c_y, c_z;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (dominantCoordIndex == 0) {
                    c_x = x;
                    c_y = y + i;
                    c_z = z + j;
                } else if (dominantCoordIndex == 1) {
                    c_x = x + i;
                    c_y = y;
                    c_z = z + j;
                } else {
                    c_x = x + i;
                    c_y = y + j;
                    c_z = z;
                }

                c_x = qBound(0, c_x, cellCnt - 1);
                c_y = qBound(0, c_y, cellCnt - 1);
                c_z = qBound(0, c_z, cellCnt - 1);

                auto &currentCell = grid.at(c_x, c_y, c_z);

                if (!currentCell.empty()) {
                    for (const auto &pair: currentCell) {
                        auto &primitive = pair.second;

                        auto pointOpt = primitive->getIntersectionPoint(ray);

                        if (pointOpt.has_value() &&
                            (pointOpt.value() - originPoint).length() > pow(10, -2)) {
                            return false;
                        }

                    }
                }
            }
        }

        coord += step * static_cast<float>(gridDirection);
    }

    return true;
}