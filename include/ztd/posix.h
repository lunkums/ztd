#ifndef ZTD_POSIX_H
#define ZTD_POSIX_H

#include "ztd/result.h"
#include "ztd/types.h"

#include <unistd.h>

namespace ztd { namespace posix {
    typedef int fd_t;

    const fd_t stdout_fileno = STDOUT_FILENO;
    const fd_t stdin_fileno = STDIN_FILENO;

    Result<> getrandom(Slice<u8> buffer);

    /// Whether or not `error.Unexpected` will print its value and a stack trace.
    ///
    /// If this happens the fix is to add the error code to the corresponding
    /// switch expression, possibly introduce a new error in the error set, and
    /// send a patch to Zig.
    const bool unexpected_error_tracing =
        false; //builtin.zig_backend ==.stage2_llvm and builtin.mode ==.Debug;

    Error unexpected_errno(Error err);

    Result<usize> read(fd_t fd, Slice<u8> buf);

    Result<usize> write(fd_t fd, Slice<const char> bytes);
}}

#endif
