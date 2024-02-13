cmake_minimum_required(VERSION 3.25)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/vladkirilov/Qt/6.4.2/macos/lib/cmake:/Users/vladkirilov/CLionProjects/ray tracing/src")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories("src")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED)

enable_testing()


add_executable(ray_tracing main.cpp src/main/scene/Scene.cpp src/main/scene/Scene.h src/main/scene/view/SceneView.cpp src/main/scene/view/SceneView.h src/main/config/scene/SceneConfig.cpp src/main/config/scene/SceneConfig.h src/main/config/scene/parser/SceneConfigParser.cpp src/main/config/scene/parser/SceneConfigParser.h src/main/Fwd.h src/main/types.h src/main/model/primitives/box/Box.cpp src/main/model/primitives/box/Box.h src/main/model/primitives/quadrangle/Quadrangle.cpp src/main/model/primitives/quadrangle/Quadrangle.h src/main/model/primitives/sphere/Sphere.cpp src/main/model/primitives/sphere/Sphere.h src/main/model/primitives/triangle/Triangle.cpp src/main/model/primitives/triangle/Triangle.h src/main/model/light/LightSource.h src/main/model/light/ScatteredLight.h src/main/model/primitives/Primitive.cpp src/main/model/primitives/Primitive.h src/main/config/AbstractParser.cpp src/main/config/AbstractParser.h src/test/scene_config_parser/SceneConfigParserTest.cpp src/test/scene_config_parser/SceneConfigParserTest.h src/main/model/light/LightSource.cpp
        src/main/ui/toolbar/ToolbarWidget.cpp src/main/ui/menu/MenuWidget.h src/main/ui/MainWindow.cpp src/main/ui/toolbar/action/about/AboutAction.cpp src/main/ui/toolbar/action/ToolbarAction.cpp src/main/ui/menu/MenuWidget.cpp src/main/ui/toolbar/action/file/FileGroup.cpp src/main/ui/toolbar/action/file/FileGroup.h src/main/ui/toolbar/action/rendering/RenderingGroup.cpp src/main/ui/toolbar/action/rendering/RenderingGroup.h src/main/ui/toolbar/action/settings/SettingsGroup.cpp src/main/ui/toolbar/action/settings/SettingsGroup.h src/main/ui/toolbar/action/ActionGroup.h src/main/ui/toolbar/action/ActionGroup.cpp src/main/ui/toolbar/action/file/load/LoadFileAction.cpp src/main/ui/toolbar/action/file/load/LoadFileAction.h src/main/ui/toolbar/action/file/save/SaveFileAction.cpp src/main/ui/toolbar/action/file/save/SaveFileAction.h src/main/ui/toolbar/action/settings/init/InitAction.cpp src/main/ui/toolbar/action/settings/init/InitAction.h src/main/ui/toolbar/action/settings/rendering_settings/RenderingSettingsAction.cpp src/main/ui/toolbar/action/settings/rendering_settings/RenderingSettingsAction.h src/main/ui/toolbar/action/rendering/render/RenderAction.cpp src/main/ui/toolbar/action/rendering/render/RenderAction.h src/main/ui/toolbar/action/rendering/select_view/SelectViewAction.cpp src/main/ui/toolbar/action/rendering/select_view/SelectViewAction.h src/main/ui/toolbar/action/file/AbstractFileAction.cpp src/main/ui/toolbar/action/file/AbstractFileAction.h src/main/ui/toolbar/action/file/load/rendering/LoadRenderingConfigAction.cpp src/main/ui/toolbar/action/file/load/rendering/LoadRenderingConfigAction.h src/main/ui/toolbar/action/file/load/scene/LoadSceneConfigAction.cpp src/main/ui/toolbar/action/file/load/scene/LoadSceneConfigAction.h src/main/ui/toolbar/action/file/save/rendering_image/SaveRenderingImageAction.cpp src/main/ui/toolbar/action/file/save/rendering_image/SaveRenderingImageAction.h src/main/ui/toolbar/action/file/save/rendering_config/SaveRenderingConfigAction.cpp src/main/ui/toolbar/action/file/save/rendering_config/SaveRenderingConfigAction.h src/test/cam/CamTest.cpp src/test/cam/CamTest.h src/test/primitive/PrimitiveTest.cpp src/test/primitive/PrimitiveTest.h src/main/config/obj/ObjParser.cpp src/main/config/obj/ObjParser.h src/test/obj_config_parser/ObjConfigParserTest.cpp src/test/obj_config_parser/ObjConfigParserTest.h src/main/render/PhongRendering.cpp src/main/render/PhongRendering.h src/main/render/grid/Grid.cpp src/main/render/grid/Grid.h src/main/render/ray/Ray.cpp src/main/render/ray/Ray.h src/main/config/render/RenderConfig.cpp src/main/config/render/RenderConfig.h src/test/grid/GridTest.cpp src/test/grid/GridTest.h src/test/geometry/GeometryTest.cpp src/test/geometry/GeometryTest.h src/main/math/geometry.cpp src/main/math/geometry.h src/main/ui/toolbar/action/SceneAction.cpp src/main/ui/toolbar/action/SceneAction.h src/main/ui/toolbar/action/SceneAction.h src/main/ui/toolbar/action/settings/rendering_settings/form/RenderingForm.cpp src/main/ui/toolbar/action/settings/rendering_settings/form/RenderingForm.h src/main/ui/toolbar/action/settings/rendering_settings/form/inputs/DoubleInputWithErrorLabel.h src/main/ui/toolbar/action/settings/rendering_settings/form/inputs/DoubleNumSlider.cpp src/main/ui/toolbar/action/settings/rendering_settings/form/inputs/DoubleWithErrorLabel.cpp src/main/ui/toolbar/action/settings/rendering_settings/form/inputs/InputWithErrorLabel.cpp)


target_link_libraries(ray_tracing
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Test
        )

