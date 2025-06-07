#ifndef ZTD_FS_FILE_H
#define ZTD_FS_FILE_H

#include "ztd/io/writer.h"
#include "ztd/posix.h"

namespace ztd { namespace fs {
    struct File {
        typedef posix::fd_t Handle;

        Handle handle;

        File(Handle handle) : handle(handle) {}

        static Result<usize> write(File self, Slice<const char> bytes) {
            return self.write(bytes);
        }

        Result<usize> write(Slice<const char> bytes) {
            return posix::write(handle, bytes);
        }

        typedef io::GenericWriter<File, &File::write> Writer;

        Writer writer();
    };
}}

#endif
