void kernel_main() {
    char* video = (char*) 0xB8000;
    video[0] = 'H';
    video[1] = 0x0F;
    video[2] = 'i';
    video[3] = 0x0F;
    video[4] = '!';
    video[5] = 0x0F;
}
