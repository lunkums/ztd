#include <ztd.h>

int main() {
    ztd::fs::File::Writer std_out = ztd::io::get_std_out().writer();
    ZTD_TRY(std_out.print("hello, world!\n"));
}
