#include "ztd/io.h"

#include <unistd.h>

namespace ztd { namespace io {
    fs::file get_std_out() {
        return fs::file(STDOUT_FILENO);
    }
}}
