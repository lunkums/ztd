#include <ztd.h>

int main() {
    ztd::io::Writer stdout = ztd::io::get_std_out().writer();
    ztd::usize i = 1;
    while (i <= 16) {
        if (i % 15 == 0) {
            ZTD_TRY(stdout.write_all("fizzbuzz\n"));
        } else if (i % 3 == 0) {
            ZTD_TRY(stdout.write_all("fizz\n"));
        } else if (i % 5 == 0) {
            ZTD_TRY(stdout.write_all("buzz\n"));
        } else {
            ZTD_TRY(stdout.print("{d}\n", i));
        }
        i += 1;
    }
    return 0;
}
