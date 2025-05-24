#include <ztd.h>

int main() {
    ztd::io::writer stdout = ztd::io::get_std_out().writer();
    stdout.print("hello, world!\n");
}
