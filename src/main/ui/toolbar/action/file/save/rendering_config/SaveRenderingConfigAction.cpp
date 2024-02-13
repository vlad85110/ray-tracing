//
// Created by Влад Кирилов on 09.05.2023.
//

#include "SaveRenderingConfigAction.h"

SaveRenderingConfigAction::SaveRenderingConfigAction(const QString &iconPath, SceneView &scene)
        : SaveFileAction(iconPath, "Save rendering settings", scene) {}

void SaveRenderingConfigAction::handleFile(QString fileName) {

}

QString SaveRenderingConfigAction::getFileExtensions() const {
    return QString();
}

QString SaveRenderingConfigAction::getFileDialogName() const {
    return QString();
}
