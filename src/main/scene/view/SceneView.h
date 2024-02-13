//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SCENEVIEW_H
#define RAY_TRACING_SCENEVIEW_H


#include <QWidget>
#include "main/scene/Scene.h"
#include "main/Fwd.h"

class SceneView : public QWidget {
private:
    Scene scene;
    QPoint lastMouseLocation;

    bool isControl;
    float angleZ, angleY, prevAngleZ, prevAngleY;

    void drawPrimitives(QPainter &painter, const QMatrix4x4 &scaleMatrix) const;

    [[maybe_unused]] void drawDimensionBox(QPainter &painter, const QMatrix4x4 &scaleMatrix) const;

    [[nodiscard]] QMatrix4x4 scaleMatrix() const;

public:
    explicit SceneView(QWidget *parent);

    void init();

    [[nodiscard]] const RenderConfig &getConfig() const;

    void setConfig(const RenderConfig &config);

    [[nodiscard]] const ptr<QImage> &getRenderedImage() const;

public slots:
    void changeSceneState(bool isRendered);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#endif //RAY_TRACING_SCENEVIEW_H
