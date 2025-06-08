#ifndef ZTA_FS_FILE_H
#define ZTA_FS_FILE_H

#include "zta/io/writer.h"
#include "zta/posix.h"

namespace zta { namespace fs {
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

        Result<usize> read(Slice<u8> buffer) {
            return posix::read(handle, buffer);
        }

        Result<usize> read_all(Slice<u8> buffer) {
            usize index = 0;
            while (index != buffer.len) {
                Result<usize> result = read(buffer);
                if (result.is_error()) {
                    return result.error();
                }
                const usize amt = *result;
                if (amt == 0) break;
                index += amt;
            }
            return index;
        }
    };
}}

#endif
