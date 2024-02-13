//
// Created by Влад Кирилов on 09.05.2023.
//

#include "LoadRenderingConfigAction.h"


LoadRenderingConfigAction::LoadRenderingConfigAction(const QString &iconPath, SceneView &scene)
        : LoadFileAction(iconPath, "Load rendering config", scene) {}

void LoadRenderingConfigAction::handleFile(QString fileName) {

}

QString LoadRenderingConfigAction::getFileExtensions() const {
    return QString();
}

QString LoadRenderingConfigAction::getFileDialogName() const {
    return QString();
}
