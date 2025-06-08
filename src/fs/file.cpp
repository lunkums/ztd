#include "zta/fs/file.h"

namespace zta { namespace fs {
    File::Writer File::writer() {
        return File::Writer(*this);
    }
}}
