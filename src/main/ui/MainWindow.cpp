//
// Created by Влад Кирилов on 16.04.2023.
//

#include "MainWindow.h"
#include "main/ui/toolbar/ToolbarWidget.h"
#include "main/ui/menu/MenuWidget.h"
#include "main/scene/view/SceneView.h"

MainWindow::MainWindow() : QMainWindow() {
    resize(640,480);

    auto sceneView = new SceneView(this);
    setCentralWidget(sceneView);

    auto toolbar = new ToolbarWidget(this, *sceneView);

    auto menu = new MenuWidget(*toolbar);
    setMenuBar(menu);
    addToolBar(toolbar);
}
