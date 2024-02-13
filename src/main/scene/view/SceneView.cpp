//
// Created by Влад Кирилов on 07.05.2023.
//

#include "SceneView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QMatrix4x4>

#include "main/scene/Scene.h"

SceneView::SceneView(QWidget *parent)
        : QWidget(parent), scene(*this),
          angleY(0), angleZ(0), prevAngleY(0), prevAngleZ(0),
          isControl(false) {
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

void SceneView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

    if (scene.isRendered) {
        if (scene.renderedImage != nullptr) {
            painter.drawImage(rect(), *scene.renderedImage);
        }

        painter.end();
        return;
    }

    painter.fillRect(rect(), Qt::black);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);

    scene.handlePrimitives(prevAngleY + angleY, prevAngleZ + angleZ);

    auto scaleMatrix = SceneView::scaleMatrix();
    drawPrimitives(painter, scaleMatrix);
    painter.setPen(QPen(Qt::lightGray));
//    drawDimensionBox(painter, scaleMatrix);
    painter.end();
}

QMatrix4x4 SceneView::scaleMatrix() const {
    auto centerX = width() / 2;
    auto centerY = height() / 2;

    return {
            (float) width() / 2, 0, 0, (float) centerX,
            0, -(float) height() / 2, 0, (float) centerY,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

void SceneView::drawPrimitives(QPainter &painter, const QMatrix4x4 &scaleMatrix) const {
    for (auto &primitive: scene.primitives) {
        auto lines = primitive->getLines();

        for (auto &line: lines) {
            auto point1 = scaleMatrix.map(line.first);
            auto point2 = scaleMatrix.map(line.second);

            if (point1.z() < 0 || point1.z() > 1 || point2.z() < 0 || point2.z() > 1 ) continue;

            auto x1 = point1.x();
            auto x2 = point2.x();

            auto y1 = point1.y();
            auto y2 = point2.y();

            painter.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
        }
    }

    for (auto &ls: scene.lightSources) {
        auto p = scaleMatrix.map(ls.getHandledPoints()[0]);

        if (p.z() >= 0) {
            painter.drawPoint(p.x(), p.y());
        }
    }
}

void SceneView::drawDimensionBox(QPainter &painter, const QMatrix4x4 &scaleMatrix) const {
//    for (auto &line: scene.dimension.getLines()) {
//        auto point1 = scaleMatrix.map(line.first);
//        auto point2 = scaleMatrix.map(line.second);
//
//        auto x1 = point1.x();
//        auto x2 = point2.x();
//
//        auto y1 = point1.y();
//        auto y2 = point2.y();
//
//        painter.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
//    }
}

void SceneView::mousePressEvent(QMouseEvent *event) {
    lastMouseLocation = event->pos();
}

void SceneView::mouseReleaseEvent(QMouseEvent *event) {
    prevAngleY += angleY;
    prevAngleZ += angleZ;

    if (prevAngleY > 360) prevAngleY -= 360;
    if (prevAngleZ > 360) prevAngleZ -= 360;

    if (prevAngleY < -360) prevAngleY += 360;
    if (prevAngleZ < -360) prevAngleZ += 360;

    angleY = 0;
    angleZ = 0;
}

void SceneView::mouseMoveEvent(QMouseEvent *event) {
    auto pos = event->pos();
    auto delta = pos - lastMouseLocation;

    angleZ = 0.4f * (float) delta.x();
    angleY = 0.4f * (float) delta.y();

    update();
}

void SceneView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) {
        scene.moveCam(1, 0);
    }

    if (event->key() == Qt::Key_Left) {
        scene.moveCam(-1, 0);
        update();
    }

    if (event->key() == Qt::Key_Up) {
        scene.moveCam(0, 1);
    }

    if (event->key() == Qt::Key_Down) {
        scene.moveCam(0, -1);
    }

    if (event->key() == Qt::Key_Control) {
        isControl = true;
    }

//    if (event->key() == Qt::Key_R) {
//        changeSceneState(!scene.isRendered);
//    }
}

void SceneView::keyReleaseEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_Control) {
//        isControl = false;
//    }
}

void SceneView::wheelEvent(QWheelEvent *event) {
    if (isControl) {
        scene.moveCamToViewPoint(-event->angleDelta().y());
        update();
    } else {
        scene.moveNearPlane(event->angleDelta().y());
        update();
    }

}

void SceneView::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
}

void SceneView::changeSceneState(bool isRendered) {
    if (isRendered != scene.isRendered) {
        scene.setIsRendered(!scene.isRendered);
        update();
    }
}

void SceneView::init() {
    prevAngleY = 0;
    prevAngleZ = 0;
    angleY = 0;
    angleZ = 0;

    scene.initScene();
    update();
}

const RenderConfig &SceneView::getConfig() const {
    return scene.getConfig();
}

void SceneView::setConfig(const RenderConfig &config) {
    scene.setConfig(config);
}

const ptr<QImage> &SceneView::getRenderedImage() const {
    return scene.getRenderedImage();
}

