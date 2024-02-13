//
// Created by Влад Кирилов on 08.05.2023.
//

#include "InitAction.h"
#include "main/scene/view/SceneView.h"


InitAction::InitAction(const QString &iconPath, SceneView &scene)
        : SceneAction(iconPath, "Init",scene) {}

void InitAction::onMouseClicked() {
    scene.init();
}
