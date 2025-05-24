#include <ztd.h>

int main() {
    ztd::io::writer stdout = ztd::io::get_std_out().writer();
    ZTD_TRY(stdout.print("hello, world!\n"));
}
