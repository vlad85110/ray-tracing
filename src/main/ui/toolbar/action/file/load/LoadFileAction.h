//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_LOADFILEACTION_H
#define RAY_TRACING_LOADFILEACTION_H


#include <QFile>
#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/file/AbstractFileAction.h"

class LoadFileAction : public AbstractFileAction {
public:
    LoadFileAction(const QString &iconPath, const QString &name, SceneView &scene);

protected:
    [[nodiscard]] QString getFileName(const QString &fileDialogName, const QString &FileExtensionName) const override;
};


#endif //RAY_TRACING_LOADFILEACTION_H
