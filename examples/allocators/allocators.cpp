#include <ztd.h>

int main() {
    ztd::u8 buffer[] =
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    ztd::slice<ztd::u8> slice(buffer);
    ztd::heap::fixed_buffer_allocator fba = ztd::heap::fixed_buffer_allocator::init(slice);
    ztd::mem::allocator a = fba.allocator();
    ztd::optional<ztd::u8*> mem = a.raw_alloc(3, ztd::mem::alignment::two, 0);
    if (mem.has_value()) {
        ztd::debug::print("%c\n", (*mem)[2]);
    }
}
