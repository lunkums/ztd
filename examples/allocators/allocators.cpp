#include <ztd.h>

int main() {
    ztd::u8 buffer[] =
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    ztd::Slice<ztd::u8> slice(buffer);
    ztd::heap::FixedBufferAllocator fba = ztd::heap::FixedBufferAllocator::init(slice);
    ztd::mem::Allocator a = fba.allocator();
    ztd::Optional<ztd::u8*> mem = a.raw_alloc(3, ztd::mem::Alignment::two, 0);
    if (mem.has_value()) {
        ztd::debug::print("%c\n", (*mem)[2]);
    }
}
