#include <zta.h>

int main() {
    zta::fs::File::Writer std_out = zta::io::get_std_out().writer();
    zta::usize i = 1;
    while (i <= 16) {
        if (i % 15 == 0) {
            ZTA_TRY(std_out.write_all("fizzbuzz\n"));
        } else if (i % 3 == 0) {
            ZTA_TRY(std_out.write_all("fizz\n"));
        } else if (i % 5 == 0) {
            ZTA_TRY(std_out.write_all("buzz\n"));
        } else {
            ZTA_TRY(std_out.print("{d}\n", i));
        }
        i += 1;
    }
    return 0;
}
