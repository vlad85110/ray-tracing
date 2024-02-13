//
// Created by Влад Кирилов on 08.05.2023.
//

#include <QFileDialog>
#include "LoadFileAction.h"


QString LoadFileAction::getFileName(const QString &fileDialogName, const QString &FileExtensionName) const {
    return QFileDialog::getOpenFileName(nullptr, getFileDialogName(),
                                        QString(),getFileExtensions());
}

LoadFileAction::LoadFileAction(const QString &iconPath, const QString &name, SceneView &scene) : AbstractFileAction(
        iconPath, name, scene) {}


