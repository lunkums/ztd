#include <ztd.h>
using namespace ztd;

#include <stdio.h>

int main() {
    fs::File::Writer writer = io::get_std_out().writer();
    Array<u8, 1024> buffer;
    heap::FixedBufferAllocator fba = heap::FixedBufferAllocator::init(buffer);
    mem::Allocator allocator = fba.allocator();

    u64 seed;
    posix::getrandom(mem::as_bytes(&seed));
    rand::DefaultPrng prng = rand::DefaultPrng::init(seed);
    Random random = prng.random();

    u8 target_number = random.int_range_at_most<u8>(1, 100);

    u8 max_guesses = 7;
    u8 guesses_made = 0;
    bool won = false;

    writer.write("Welcome to the Hi-Lo Guessing Game!\n");
    writer.write("I'm thinking of a number between 1 and 100.\n");
    writer.write("You have 7 guesses to find it!\n\n");
}
