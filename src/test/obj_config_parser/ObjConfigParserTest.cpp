//
// Created by Влад Кирилов on 15.05.2023.
//

#include "ObjConfigParserTest.h"
#include "main/config/obj/ObjParser.h"

ObjConfigParserTest::ObjConfigParserTest() {
    pathPrefix = "/Users/vladkirilov/CLionProjects/"
                 "ray tracing/src/test/obj_config_parser/";
}

void ObjConfigParserTest::test1() const {
    ObjParser parser(pathPrefix + "test1.obj");
    auto conf = parser.parse();
}

void ObjConfigParserTest::test2() const {

}
