/// @file libx.c  @date 05/10/2015
/// @author i@BlahGeek.com

/* old foo */
__asm__(".symver foo_1, foo@libX_1.0");
int foo_1() {
   return 1;
}

/* new foo */
__asm__(".symver foo_2, foo@@libX_2.0");
int foo_2() {
   return 2;
}

__asm__(".symver bar_1, bar@@libX_1.0");
int bar_1() {
    return -1;
}