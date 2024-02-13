//
// Created by Влад Кирилов on 15.05.2023.
//

#ifndef RAY_TRACING_PHONGRENDERING_H
#define RAY_TRACING_PHONGRENDERING_H

#include <QImage>
#include "main/scene/Scene.h"
#include "main/render/grid/Grid.h"
#include "main/render/ray/Ray.h"
#include "main/config/render/RenderConfig.h"

class PhongRendering {
private:
    const Scene &scene;
    SceneConfig sceneConfig;
    Grid grid;
    const int depth;
    float gamma;

    const int threadCnt = 4;

public:
    explicit PhongRendering(const Scene &scene, const RenderConfig &config, SceneConfig sceneConfig);

    QImage renderScene(int height, int width);

    Optional<std::pair<Point, const ptr<Primitive>>> getRayIntersectionPrimitive(const Ray &ray);

    std::array<float, 3> traceRay(const Ray &ray);

    [[nodiscard]] bool
    isInLightSourceVision(const Point &originPoint, const LightSource &lightSource) const;
};


#endif //RAY_TRACING_PHONGRENDERING_H
