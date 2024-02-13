#include <QApplication>
#include <QTest>
#include "test/scene_config_parser/SceneConfigParserTest.h"
#include "main/ui/MainWindow.h"
#include "test/primitive/PrimitiveTest.h"


#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "main/types.h"
#include "test/obj_config_parser/ObjConfigParserTest.h"
#include "test/grid/GridTest.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

//    QTest::qExec(new SceneConfigParserTest, argc, argv);
//    QTest::qExec(new CamTest, argc, argv);
//    QTest::qExec(new PrimitiveTest, argc, argv);
//    QTest::qExec(new ObjConfigParserTest, argc, argv);
//    QTest::qExec(new GridTest, argc, argv);

    return QApplication::exec();
}
