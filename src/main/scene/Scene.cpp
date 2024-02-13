//
// Created by Влад Кирилов on 07.05.2023.
//

#include "Scene.h"
#include "main/config/scene/parser/SceneConfigParser.h"
#include "main/scene/view/SceneView.h"
#include "main/config/obj/ObjParser.h"
#include "main/math/geometry.h"
#include <QMatrix4x4>
#include <set>
#include <QVector3D>
#include <QFile>

Scene::Scene(SceneView &view) : //dimension({0, 0, 0}, {0, 0, 0}),
        scatteredLight(qRgb(156, 23, 23)), isRendered(false),
        zn(0), zf(0), view(view), camRadius(0), minCamRadius(0), sW(0), sH(0),
        config{255, 255, 255, 1, 1} {

    SceneConfigParser parser("/Users/vladkirilov/CLionProjects/ray tracing/resources/data/config1.scene");
    ObjParser objParser("/Users/vladkirilov/CLionProjects/ray tracing/resources/data/girl OBJ.obj");

    auto configOpt = parser.parse();
    auto config1Opt = objParser.parse();

    if (configOpt.has_value()) {
        auto &primitives = configOpt.value().primitives;
        primitives.insert(primitives.begin(), config1Opt.value().primitives.begin(),
                          config1Opt.value().primitives.end());
        loadSceneConfig(configOpt.value());
        initScene();
    }
}

void Scene::setIsRendered(bool isRendered) {
    Scene::isRendered = isRendered;
    rendering = make_shared<PhongRendering>(*this, config,
                                            SceneConfig{scatteredLight, lightSources, primitives});

    if (isRendered) {
        renderedImage = make_shared<QImage>(std::move(rendering->renderScene(view.height(), view.width())));
    }
}

void Scene::loadSceneConfig(const SceneConfig &config) {
    primitives.clear();
    primitives = config.primitives;
    lightSources = config.lightSources;
    scatteredLight = config.scatteredLight;
}

void Scene::initScene() {
    std::set<float> xs;
    std::set<float> ys;
    std::set<float> zs;

    for (const auto &primitive: primitives) {
        for (const auto &point: primitive->getOriginalPoints()) {
            xs.emplace(point.x());
            ys.emplace(point.y());
            zs.emplace(point.z());
        }
    }

    auto minX = *xs.begin();
    auto minY = *ys.begin();
    auto minZ = *zs.begin();

    auto maxX = *xs.rbegin();
    auto maxY = *ys.rbegin();
    auto maxZ = *zs.rbegin();

//    dimension = Box({minX, minY, minZ}, {maxX, maxY, maxZ});
    boxCenter = Point((maxX + minX) / 2.f, (maxY + minY) / 2.f, (maxZ + minZ) / 2.f);
    viewPoint = boxCenter;

    minCamRadius = (viewPoint - QVector3D{minX, minY, minZ}).length() * 2;
    zn = 2.f;
    sH = (maxY - minY) / 2;

    camRadius = 10;
    zf = 20.f;
    up = QVector3D(0, 0, 1);
}

void Scene::handlePrimitives(float angleY, float angleZ) {
    defineCam(angleZ, angleY);

    if (cos(qDegreesToRadians(angleY)) < 0) {
        up = {0, 0, -1};
    } else {
        up = {0, 0, 1};
    }

    auto width = (float) this->view.width();
    auto height = (float) this->view.height();
    auto lookAt = Scene::lookAt();

//    auto newBox = Box(dimension);
//    newBox.handlePoints(lookAt);

    auto aspect = width / height;
    sW = sH * aspect;

    auto res = projection() * lookAt;
    for (auto &primitive: primitives) {
        primitive->handlePoints(res);
    }

    for (auto &lightSource: lightSources) {
        lightSource.handlePoints(res);
    }

//    dimension.handlePoints(res);
}

void Scene::moveCam(float x, float y) {
    cam.setY(cam.y() + x);
    cam.setZ(cam.z() + y);

    viewPoint.setY(viewPoint.y() + x);
    viewPoint.setZ(viewPoint.z() + y);

    view.update();
}

void Scene::defineCam(float angleZ, float angleY) {
    angleY = 90 - angleY;
    auto r = camRadius;
    auto newCam = getPointOnSphere(angleY, angleZ, r, viewPoint);
    cam = newCam;
}

void Scene::moveCamToViewPoint(int delta) {
    camRadius += 0.05f * (float) delta;
    camRadius = qBound(minCamRadius, camRadius, 200.f);
}

void Scene::moveNearPlane(int delta) {
    zn += 0.05f * (float) delta;
    zn = qBound(0.f, zn, zf - 1);
}

QMatrix4x4 Scene::lookAt() const {
    auto w = (viewPoint - cam).normalized();
    auto u = QVector3D::crossProduct(up, w).normalized();
    auto v = QVector3D::crossProduct(w, u).normalized();

    auto x0 = -QVector3D::dotProduct(cam, u);
    auto y0 = -QVector3D::dotProduct(cam, v);
    auto z0 = -QVector3D::dotProduct(cam, w);

    return {
            u.x(), u.y(), u.z(), x0,
            v.x(), v.y(), v.z(), y0,
            w.x(), w.y(), w.z(), z0,
            0, 0, 0, 1
    };
}

QMatrix4x4 Scene::projection() const {
    return {
            (float) 2 * zn / sW, 0, 0, 0,
            0, (float) 2 * zn / sH, 0, 0,
            0, 0, zf / (zf - zn), -zn * zf / (zf - zn),
            0, 0, 1, 0
    };
}

const Vector<ptr<Primitive>> &Scene::getPrimitives() const {
    return primitives;
}

const RenderConfig &Scene::getConfig() const {
    return config;
}

void Scene::setConfig(const RenderConfig &config) {
    Scene::config = config;
    scatteredLight = qRgb(config.bR, config.bB, config.bB);
}

const ptr<QImage> &Scene::getRenderedImage() const {
    return renderedImage;
}



