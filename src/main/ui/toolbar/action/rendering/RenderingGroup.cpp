//
// Created by Влад Кирилов on 08.05.2023.
//

#include <QShortcut>
#include "RenderingGroup.h"

RenderingGroup::RenderingGroup(QObject *parent, SceneView &scene)
        : ActionGroup(parent, "Rendering") {

    QString iconPathPrefix = "/Users/vladkirilov/CLionProjects/ray tracing/resources/icons/";

    setExclusive(true);

    auto shortcut = new QShortcut(Qt::Key_R, this);
    auto shortcut1 = new QShortcut(Qt::Key_V, this);// Например, F1


    selectViewAction = make_shared<SelectViewAction>(iconPathPrefix + "view.png", scene);
    renderAction = make_shared<RenderAction>(iconPathPrefix + "render.png", scene);

    QObject::connect(shortcut, &QShortcut::activated,
                     renderAction.get(), &QAction::trigger);

    QObject::connect(shortcut1, &QShortcut::activated,
                     selectViewAction.get(), &QAction::trigger);

    addAction(selectViewAction.get());
    addAction(renderAction.get());
}
