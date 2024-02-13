//
// Created by Влад Кирилов on 04.04.2023.
//

#ifndef FILTERS_ABOUTACTION_H
#define FILTERS_ABOUTACTION_H

#include "main/types.h"

#include "main/ui/toolbar/action/ToolbarAction.h"

class AboutAction : public ToolbarAction {
private:
    QString text;
public:
    explicit AboutAction(const QString &iconPath);

public:

    void onMouseClicked() override;
};


#endif //FILTERS_ABOUTACTION_H
