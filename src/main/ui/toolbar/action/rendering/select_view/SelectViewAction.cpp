//
// Created by Влад Кирилов on 08.05.2023.
//

#include "SelectViewAction.h"
#include "main/scene/view/SceneView.h"

SelectViewAction::SelectViewAction(const QString &iconPath, SceneView &scene) : SceneAction(
        iconPath, "Select view", scene) {
    setCheckable(true);
}

void SelectViewAction::onMouseClicked() {
    scene.changeSceneState(false);
}
