//
// Created by Влад Кирилов on 20.03.2023.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(const ToolbarWidget &widget) {
    auto fileMenu = widget.getFileGroup()->getMenu();

    auto renderMenu = widget.getRenderGroup()->getMenu();

    auto helpMenu = new QMenu("Help");
    helpMenu->addAction(widget.getAboutAction());

    auto settingsMenu = widget.getSettingsGroup()->getMenu();

    addMenu(fileMenu);
    addMenu(renderMenu);
    addMenu(settingsMenu);
    addMenu(helpMenu);
}
