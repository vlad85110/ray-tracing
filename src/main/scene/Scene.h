//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include <QWidget>
#include "main/config/scene/SceneConfig.h"
#include "main/Fwd.h"
#include "main/render/PhongRendering.h"
#include "main/config/render/RenderConfig.h"

class Scene {
private:
    SceneView &view;
    ptr<PhongRendering> rendering;

    bool isRendered;
    ptr<QImage> renderedImage;

    Vector<ptr<Primitive>> primitives;
    Vector<LightSource> lightSources;
    ScatteredLight scatteredLight;
//    Box dimension;
    Point boxCenter, viewPoint, cam;
    QVector3D up;
    float zn, zf, sW, sH, camRadius, minCamRadius;

    RenderConfig config;
public:

    explicit Scene(SceneView &view);

    friend class SceneView;

    void loadSceneConfig(const SceneConfig &config);

    void initScene();

    void handlePrimitives(float angleY, float angleZ);

    void moveCam(float x, float y);

    void defineCam(float angleZ, float angleY);

    void moveCamToViewPoint(int delta);

    void moveNearPlane(int delta);

    [[nodiscard]] QMatrix4x4 lookAt() const;

    [[nodiscard]] QMatrix4x4 projection() const;

    [[nodiscard]] const Vector<ptr<Primitive>> &getPrimitives() const;

    void setIsRendered(bool isRendered);

    [[nodiscard]] const RenderConfig &getConfig() const;

    void setConfig(const RenderConfig &config);

    [[nodiscard]] const ptr<QImage> &getRenderedImage() const;

};


#endif //RAY_TRACING_SCENE_H
