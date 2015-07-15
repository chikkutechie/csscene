
#include "rglutbinder.h"
#include "rview.h"
#include "rlog.h"
#include "rcontext.h"
#include "rcommandlineparser.h"

namespace chikkooos
{

RGlutBinder::RGlutBinder()
 : mWidth(chikkooos::WindowWidth),
   mHeight(chikkooos::WindowHeight),
   mX(chikkooos::WindowPositionX),
   mY(chikkooos::WindowPositionY),
   mTitle("chikkooos")
{}

RBinder & RBinder::instance()
{
	static RGlutBinder _instance;
    return _instance;
}

int RGlutBinder::exec()
{
    mLastTime.start();
    glutMainLoop();
    return 1;
}

bool RGlutBinder::initialize(int argc, char **argv)
{
	glutInit(&argc, argv);

    srand(time(0));

    try
    {
        RCommandLineParser parser;
        parser.addOption("gc", true);
        RCommandLineParser::Iterator iter = parser.begin(argc, (const char **)argv);
        for(; iter != parser.end(); ++iter) {
            if (iter->option.compare("--gc") == 0) {
                mGc = iter->argument;
                RContext::instance().setContext(mGc);
            }
        }
    } catch (RCommandLineParser::Exception const & e) {
        rLogE() << e.what() << std::endl;
    }

    return init();
}

bool RGlutBinder::initialize()
{
    int argc = 0;
    char *argv[] = {0};
	glutInit(&argc, argv);
    return init();
}

void RGlutBinder::destroy()
{}

void RGlutBinder::reshape(int w, int h)
{
    RGlutBinder::instance().renderer()->onReshape(w, h);
    ((RGlutBinder &)RGlutBinder::instance()).setSize(w, h);
}

void RGlutBinder::display()
{
    ((RGlutBinder &)RGlutBinder::instance()).draw();
    glutSwapBuffers();
}

void RGlutBinder::mouse(int button, int state, int x, int y)
{
    RGlutBinder::instance().mouseEvent(button, state, x, y);
}

void RGlutBinder::mouseMove(int x, int y)
{
    RGlutBinder::instance().mouseMove(x, y);
}

void RGlutBinder::menu(int id)
{
    if (RGlutBinder::instance().renderer()) {
        RGlutBinder::instance().renderer()->onMenuItemClicked(id);
    }
}

void RGlutBinder::timer(int)
{
    ((RGlutBinder &)RBinder::instance()).update();
    ((RGlutBinder &)RBinder::instance()).redraw();

    glutTimerFunc(TimerDelay, RGlutBinder::timer, 0);
}

//void RGlutBinder::addTimer(unsigned int delay)
//{
//	glutTimerFunc(delay, RGlutBinder::timer, 0);
//}

void RGlutBinder::redraw()
{
    glutPostRedisplay();
}

void RGlutBinder::keyboard(unsigned char key, int x, int y)
{
    RGlutBinder::instance().keyPress(key, x, y);
}

void RGlutBinder::draw()
{
    RBinder::draw();
}

void RGlutBinder::update()
{
    RBinder::update();
}

bool RGlutBinder::init()
{
    glutInitWindowPosition(mX, mY);
    glutInitWindowSize(mWidth, mHeight);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    glutCreateWindow(mTitle.c_str());

    glutReshapeFunc(RGlutBinder::reshape);
    glutDisplayFunc(RGlutBinder::display);
    glutMotionFunc(RGlutBinder::mouseMove);
    glutMouseFunc(RGlutBinder::mouse);
    glutKeyboardFunc(RGlutBinder::keyboard);
    glutTimerFunc(TimerDelay, RGlutBinder::timer, 0);

#if defined(WIN32) || defined(WIN64)
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        rLogE() << "Error in glew initialization : " << glewGetErrorString(err) << std::endl;
        return false;
    }
    rLogI() << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
#endif

    if (!renderer()->onInit()) {
    	rLogE() << "initialization failed" << std::endl;
    	return false;
    }

    rLogI() << "Depth Size(GLUT_WINDOW_DEPTH_SIZE) " << glutGet(GLUT_WINDOW_DEPTH_SIZE) << std::endl;
    rLogI() << "Depth Size(GLUT_GAME_MODE_PIXEL_DEPTH) " << glutGameModeGet(GLUT_GAME_MODE_PIXEL_DEPTH) << std::endl;

    return true;
}

}

