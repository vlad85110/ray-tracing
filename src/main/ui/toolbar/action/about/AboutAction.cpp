//
// Created by Влад Кирилов on 04.04.2023.
//

#include "AboutAction.h"

#include <QMessageBox>
#include <QFile>

AboutAction::AboutAction(const QString &iconPath) : ToolbarAction(iconPath, "About") {

    QFile file("/Users/vladkirilov/CLionProjects/ray tracing/src/main/ui/toolbar/action/about/about");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream textStream(&file);
    text = textStream.readAll();
    file.close();
}

void AboutAction::onMouseClicked() {
    QMessageBox::information(nullptr, "about", text);
}
