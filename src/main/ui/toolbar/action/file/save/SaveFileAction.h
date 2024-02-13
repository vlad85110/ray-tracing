//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_SAVEFILEACTION_H
#define RAY_TRACING_SAVEFILEACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/file/AbstractFileAction.h"

class SaveFileAction : public AbstractFileAction {
public:
    SaveFileAction(const QString &iconPath, const QString &name, SceneView &scene);

protected:
    [[nodiscard]] QString getFileName(const QString &fileDialogName, const QString &FileExtensionName) const override;

};


#endif //RAY_TRACING_SAVEFILEACTION_H
