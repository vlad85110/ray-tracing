//
// Created by Влад Кирилов on 20.03.2023.
//

#ifndef FILTERS_MENUWIDGET_H
#define FILTERS_MENUWIDGET_H

#include <QMenuBar>
#include "main/ui/toolbar/ToolbarWidget.h"

class MenuWidget : public QMenuBar {
Q_OBJECT
public:
    explicit MenuWidget(const ToolbarWidget& widget);
};


#endif //FILTERS_MENUWIDGET_H
