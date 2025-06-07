#include "ztd/fs/file.h"

namespace ztd { namespace fs {
    io::Writer File::writer() {
        return io::Writer();
    }
}}
