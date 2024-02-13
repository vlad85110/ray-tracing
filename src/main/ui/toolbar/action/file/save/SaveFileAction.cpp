//
// Created by Влад Кирилов on 08.05.2023.
//

#include "SaveFileAction.h"
#include <QFileDialog>

SaveFileAction::SaveFileAction(const QString &iconPath, const QString &name, SceneView &scene)
        : AbstractFileAction(iconPath, name, scene) {}

QString SaveFileAction::getFileName(const QString &fileDialogName, const QString &FileExtensionName) const {
    return QFileDialog::getSaveFileName(nullptr, getFileDialogName(),
                                        QString(), getFileExtensions());
}


