//
// Created by Влад Кирилов on 09.05.2023.
//

#include "AbstractFileAction.h"

void AbstractFileAction::onMouseClicked() {
    auto name = getFileName(getFileDialogName(), getFileExtensions());
    if (name.isEmpty()) return;
    handleFile(name);
}

AbstractFileAction::AbstractFileAction(const QString &iconPath, const QString &name, SceneView &scene) : SceneAction(
        iconPath, name, scene) {}


