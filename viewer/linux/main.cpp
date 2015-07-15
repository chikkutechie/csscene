
#include "rviewer.h"
#include "rcommandlineparser.h"
#include "rcontext.h"

#include <iostream>
#include <cstdlib>

namespace 
{

const int MenuItemPause = 100;
const int MenuItemResume = 200;

void menu(int id)
{
    switch (id) {
        case MenuItemPause:
        chikkooos::RBinder::instance().pause();
        return;

        case MenuItemResume:
        chikkooos::RBinder::instance().resume();
        return;

    }
}

}

void printHelp(char *prg)
{
    std::cout << "NAME" << std::endl
              << "    " << prg << " : viewer for scene map file" << std::endl
              << std::endl
              << "SYNOPSIS" << std::endl
              << "    " << prg << " [OPTIONS]" << std::endl
              << std::endl
              << "DESCRIPTION" << std::endl
              << "    " << "--scene <filename>" << std::endl
              << "    " << "  displays the given file" << std::endl
              << "    " << "--gc <gc name>" << std::endl
              << "    " << "  uses the mentioned gc for rendering. Currently gles1 and gles2 are supported" << std::endl
              << "    " << "--help" << std::endl
              << "    " << "  displays this option" << std::endl
              << std::endl
              ;
}

int main(int argc, char ** argv)
{
    chikkooos::RBinder &scene = chikkooos::RBinder::instance();

    std::string sceneMap;

    chikkooos::RCommandLineParser parser;
    parser.addOption("scene", true);
    parser.addOption("help", false);
    chikkooos::RCommandLineParser::Iterator iter = parser.begin(argc, (const char **)argv);
    for(; iter != parser.end(); ++iter) {
        if (iter->option.compare("--scene") == 0) {
            sceneMap = iter->argument;
        } 
        if (iter->option.compare("--help") == 0) {
            printHelp(argv[0]);
            std::exit(0);
        }
    }

    chikkooos::ViewerRenderer * hw = new chikkooos::ViewerRenderer();
    if (!sceneMap.empty()) {
        hw->setSceneMap(sceneMap);
    }

    scene.setRenderer(hw);

    if (!scene.initialize(argc, argv)) {
        rLogE() << "scene initialization failed" << std::endl;
        return 1;
    }

#if !defined(NO_GLUT)
    glutSetMenu(glutCreateMenu(menu));

    glutAddMenuEntry("Pause", MenuItemPause);
    glutAddMenuEntry("Resume", MenuItemResume);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

#endif

    return scene.exec();
}

