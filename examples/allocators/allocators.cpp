#include <zta.h>

int main() {
    zta::u8 buffer[] =
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    zta::Slice<zta::u8> slice(buffer);
    zta::heap::FixedBufferAllocator fba = zta::heap::FixedBufferAllocator::init(slice);
    zta::mem::Allocator a = fba.allocator();
    zta::Optional<zta::u8*> mem = a.raw_alloc(3, zta::mem::Alignment::two, 0);
    if (mem.has_value()) {
        zta::debug::print("%c\n", (*mem)[2]);
    }
}
