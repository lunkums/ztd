#include "ztd/posix.h"

#include <errno.h>
#include <stdlib.h>
#include <time.h>

namespace ztd { namespace posix {
    Result<> getrandom(Slice<u8> buffer) {
        std::srand(time(ZTD_NULL));
        for (usize i = 0; i < buffer.len; ++i) {
            buffer[i] = std::rand() % 256;
        }
        return Ok();
    }

    Error unexpected_error(Error err) {
        if (unexpected_error_tracing) {
            //debug::print("unexpected errno: {d}\n", . {e});
            //debug::dump_current_stack_trace(null);
        }
        return Error("unexpected");
    }

    Result<usize> write(fd_t fd, Slice<const char> bytes) {
        if (bytes.len == 0) return 0;
        while (true) {
            const int rc = ::write(fd, bytes.ptr, bytes.len);
            switch (errno) {
                case 0:
                    return static_cast<usize>(rc);
                case EINVAL:
                    return Error("invalid argument");
                case EFAULT:
                    throw 1;
                case ENOENT:
                    return Error("process not found");
                case EAGAIN:
                    return Error("would block");
                case EBADF:
                    return Error("not open for writing"); // can be a race conditioncase E
                case EDESTADDRREQ:
                    throw 1;
                // case EDQUOT:
                //     return Error("DiskQuota");
                case EFBIG:
                    return Error("file too big");
                case EIO:
                    return Error("input output");
                case ENOSPC:
                    return Error("no space left");
                case EACCES:
                    return Error("access denied");
                case EPERM:
                    return Error("access denied");
                case EPIPE:
                    return Error("broken pipe");
                case ECONNRESET:
                    return Error("connection reset by peer");
                case EBUSY:
                    return Error("device busy");
                case ENXIO:
                    return Error("no device");
                default:
                    return unexpected_error(Error());
            }
        }
    }
}}
