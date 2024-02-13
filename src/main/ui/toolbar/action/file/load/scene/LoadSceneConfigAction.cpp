//
// Created by Влад Кирилов on 09.05.2023.
//

#include "LoadSceneConfigAction.h"

LoadSceneConfigAction::LoadSceneConfigAction(const QString &iconPath, SceneView &scene)
        : LoadFileAction(iconPath, "Load scene config", scene) {}


void LoadSceneConfigAction::handleFile(QString fileName) {

}

QString LoadSceneConfigAction::getFileExtensions() const {
    return "SCENE Files (*.scene)";
}

QString LoadSceneConfigAction::getFileDialogName() const {
    return "Load scene config";
}
