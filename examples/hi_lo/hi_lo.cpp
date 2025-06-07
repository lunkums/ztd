#include <ztd.h>
using namespace ztd;

#include <stdio.h>

int main() {
    io::writer writer = io::get_std_out().writer();
    array<u8, 1024> buffer;
    heap::fixed_buffer_allocator fba = heap::fixed_buffer_allocator::init(buffer);
    mem::allocator allocator = fba.allocator();

    u64 seed;
    posix::getrandom(mem::as_bytes(&seed));
    rand::default_prng prng = rand::default_prng::init(seed);
    random random = prng.random();

    u8 target_number = random.int_range_at_most<u8>(1, 100);

    u8 max_guesses = 7;
    u8 guesses_made = 0;
    bool won = false;

    writer.write("Welcome to the Hi-Lo Guessing Game!\n");
    writer.write("I'm thinking of a number between 1 and 100.\n");
    writer.write("You have 7 guesses to find it!\n\n");
}
