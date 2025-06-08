#include <zta.h>

int main() {
    zta::fs::File::Writer std_out = zta::io::get_std_out().writer();
    ZTA_TRY(std_out.print("hello, world!\n"));
}
