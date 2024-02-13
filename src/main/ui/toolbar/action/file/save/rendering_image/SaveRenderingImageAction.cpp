//
// Created by Влад Кирилов on 09.05.2023.
//

#include "SaveRenderingImageAction.h"
#include "main/scene/view/SceneView.h"

SaveRenderingImageAction::SaveRenderingImageAction(const QString &iconPath, SceneView &scene)
        : SaveFileAction(iconPath, "Save rendering image", scene) {}

void SaveRenderingImageAction::handleFile(QString fileName) {
    auto image = scene.getRenderedImage();

    if (image != nullptr) {
        image->save(fileName);
    }
}

QString SaveRenderingImageAction::getFileExtensions() const {
    return "Images (*.png)";
}

QString SaveRenderingImageAction::getFileDialogName() const {
    return "Save rendering image";
}
