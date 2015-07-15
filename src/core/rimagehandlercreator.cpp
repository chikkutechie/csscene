
#include "rcommon.h"
#include "rimagehandlercreator.h"
#include "rbmpimagehandler.h"
#include "rpngimagehandler.h"

namespace chikkooos
{

RImageHandler * RImageHandlerCreator::createHandler(std::string const & filename)
{
    std::string ext;
    int index = filename.length() - 3;
    if (index >= 0) {
        ext = filename.substr(index, 3);
    }

    if (ext.compare("png") == 0) {
        return new RPNGImageHandler();
    } else if (ext.compare("bmp") == 0) {
        return new RBMPImageHandler();
    }

    return 0;
}

}

