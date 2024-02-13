//
// Created by Влад Кирилов on 15.03.2023.
//

#include "ToolbarAction.h"

#include <QIcon>
#include <iostream>
#include <QSignalMapper>

ToolbarAction::ToolbarAction(const QString &iconPath, const QString &name) : QAction(), name(name) {
    auto *icon = new QIcon(iconPath);
    setText(name);
    setIconVisibleInMenu(false);
    setIcon(*icon);
    setToolTip(name);

    connect(this, &QAction::triggered, this, &ToolbarAction::onTrigger);
}

void ToolbarAction::onTrigger() {
    onMouseClicked();
}

ToolbarAction::~ToolbarAction() = default;
