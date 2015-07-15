
#ifndef RIMAGEHANDLERCREATOR_H
#define RIMAGEHANDLERCREATOR_H

#include <string>

namespace chikkooos
{

class RImageHandler;

class RImageHandlerCreator
{
public:
    static RImageHandler * createHandler(std::string const & filename);

private:
    RImageHandlerCreator();
    RImageHandlerCreator(RImageHandlerCreator const &);
    RImageHandlerCreator operator=(RImageHandlerCreator const &);
};

}

#endif

