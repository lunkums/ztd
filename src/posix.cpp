#include "zta/posix.h"

#include "zta/builtin.h"

#include <errno.h>
#include <stdlib.h>
#include <time.h>

namespace zta { namespace posix {
    Result<> getrandom(Slice<u8> buffer) {
        std::srand(time(ZTA_NULL));
        for (usize i = 0; i < buffer.len; ++i) {
            buffer[i] = std::rand() % 256;
        }
        return Ok();
    }

    Error unexpected_errno(Error err) {
        if (unexpected_error_tracing) {
            //debug::print("unexpected errno: {d}\n", . {e});
            //debug::dump_current_stack_trace(null);
        }
        return Error("unexpected");
    }

    Result<usize> read(fd_t fd, Slice<u8> buf) {
        if (buf.len == 0) return 0;

        // Prevents EINVAL.
        // const max_count = switch (native_os) {
        //     .linux = > 0x7ffff000,
        //     .macos,
        //     .ios,
        //     .watchos,
        //     .tvos,
        //     .visionos = > maxInt(i32),
        //     else = > maxInt(isize),
        // };
        const usize max_count = 0x7ffff000;
        while (true) {
            const int rc = ::read(fd, buf.ptr, builtin::min(buf.len, max_count));
            switch (errno) {
                case 0: // SUCCESS
                    return static_cast<usize>(rc);
                case EINTR:
                    continue;
                case EINVAL:
                    throw 1;
                case EFAULT:
                    throw 1;
                case ENOENT:
                    return Error("EProcessNotFound");
                case EAGAIN:
                    return Error("EWouldBlock");
                case ECANCELED:
                    return Error("ECanceled");
                case EBADF:
                    return Error("ENotOpenForReading");
                case EIO:
                    return Error("EInputOutput");
                case EISDIR:
                    return Error("EIsDir");
                case ENOBUFS:
                    return Error("ESystemResources");
                case ENOMEM:
                    return Error("ESystemResources");
                case ENOTCONN:
                    return Error("ESocketNotConnected");
                case ECONNRESET:
                    return Error("EConnectionResetByPeer");
                case ETIMEDOUT:
                    return Error("ConnectionTimedOut");
                default:
                    return unexpected_errno(Error());
            }
        }
    }

    Result<usize> write(fd_t fd, Slice<const char> bytes) {
        if (bytes.len == 0) return 0;

        //      const max_count = switch (native_os) {
        //     .linux => 0x7ffff000,
        //     .macos, .ios, .watchos, .tvos, .visionos => maxInt(i32),
        //     else => maxInt(isize),
        // };
        const usize max_count = 0x7ffff000;
        while (true) {
            const int rc = ::write(fd, bytes.ptr, builtin::min(bytes.len, max_count));
            switch (errno) {
                case 0: // SUCCESS
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
                    return unexpected_errno(Error());
            }
        }
    }
}}
