#include <ztd.h>
using namespace ztd;

#include <stdio.h>

int main() {
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

    fs::File::Writer writer = io::get_std_out().writer();
    writer.write("Welcome to the Hi-Lo Guessing Game!\n");
    writer.write("I'm thinking of a number between 1 and 100.\n");
    writer.write("You have 7 guesses to find it!\n\n");

    fs::File std_in = io::get_std_in();
    Array<u8, 10> buf;

    while (guesses_made < max_guesses and !won) {
        writer.write("Next guess: ");

        Result<usize> result = std_in.read(buf);
        if (result.is_error()) {
            continue;
        }
        usize bytes_read = *result;
        if (bytes_read > 0) {
            // Remove newline character
            Slice<u8> input_str = buf(0, bytes_read - 1);

            Result<u8> guess_result = fmt::parse_int<u8>(input_str, 10);
            if (guess_result.is_error()) {
                writer.write("Please enter a valid number between 1 and 100!\n\n");
                continue;
            }
            u8 guess = *guess_result;

            if (guess < 1 or guess > 100) {
                writer.write("Please enter a number between 1 and 100!\n\n");
                continue;
            }

            guesses_made += 1;

            if (guess == target_number) {
                won = true;
                writer.write("Congratulations! You won!\n");
            } else if (guess < target_number) {
                writer.write("Too low! Try higher.\n\n");
            } else {
                writer.write("Too high! Try lower.\n\n");
            }
        }
    }

    if (!won) {
        writer.write("You lost! Better luck next time.\n");
    }
}
