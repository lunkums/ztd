#include "ztd/fs/file.h"

namespace ztd { namespace fs {
    File::Writer File::writer() {
        return File::Writer(*this);
    }
}}
