__asm__(".symver foo_1, foo@@libX_1.0");
int foo_1() {
   return 1;
}

__asm__(".symver bar_1, bar@@libX_1.0");
int bar_1() {
    return -1;
}