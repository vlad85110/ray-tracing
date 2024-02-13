//
// Created by Влад Кирилов on 09.05.2023.
//

#ifndef RAY_TRACING_ABSTRACTFILEACTION_H
#define RAY_TRACING_ABSTRACTFILEACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/SceneAction.h"

class AbstractFileAction : public SceneAction {
protected:
    virtual void handleFile(QString fileName) = 0;

    [[nodiscard]] virtual QString getFileExtensions() const = 0;

    [[nodiscard]] virtual QString getFileDialogName() const = 0;

    [[nodiscard]] virtual QString getFileName(const QString &fileDialogName,
                                              const QString &FileExtensionName) const = 0;

public:
    AbstractFileAction(const QString &iconPath, const QString &name, SceneView &scene);

    void onMouseClicked() override;
};


#endif //RAY_TRACING_ABSTRACTFILEACTION_H
