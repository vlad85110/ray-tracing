//
// Created by Влад Кирилов on 08.05.2023.
//

#include "RenderAction.h"
#include "main/scene/view/SceneView.h"

RenderAction::RenderAction(const QString &iconPath, SceneView &scene)
        : SceneAction(iconPath, "Render", scene) {
    setCheckable(true);
}

void RenderAction::onMouseClicked() {
    scene.changeSceneState(true);
}
