//
// Created by Влад Кирилов on 24.05.2023.
//

#include "SceneAction.h"

SceneAction::SceneAction(const QString &iconPath, const QString &name, SceneView &scene)
        : ToolbarAction(iconPath, name), scene(scene) {}
