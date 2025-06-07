#include <ztd.h>

int main() {
    ztd::fs::File::Writer std_out = ztd::io::get_std_out().writer();
    ztd::usize i = 1;
    while (i <= 16) {
        if (i % 15 == 0) {
            ZTD_TRY(std_out.write_all("fizzbuzz\n"));
        } else if (i % 3 == 0) {
            ZTD_TRY(std_out.write_all("fizz\n"));
        } else if (i % 5 == 0) {
            ZTD_TRY(std_out.write_all("buzz\n"));
        } else {
            ZTD_TRY(std_out.print("{d}\n", i));
        }
        i += 1;
    }
    return 0;
}
