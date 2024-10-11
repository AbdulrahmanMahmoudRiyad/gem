#include <stdio.h>
#include <assert.h>
#include "nob.h"
#include "raylib.h"

void test_mkdir() {
    const char *test_dir = "test_dir";
    assert(nob_mkdir_if_not_exists(test_dir) == true);
    printf("Test passed: nob_mkdir_if_not_exists\n");
}

void test_load_font() {
    Font font = LoadFont("assets/fonts/alagard.png");
    assert(font.texture.id != 0);
    printf("Test passed: LoadFont\n");
    UnloadFont(font);
}

void test_load_image() {
    Image image = LoadImage("assets/images/test.png");
    assert(image.width > 0 && image.height > 0);
    printf("Test passed: LoadImage\n");
    UnloadImage(image);
}

int main() {
    InitWindow(800, 600, "Test Window");

    test_mkdir();
    test_load_font();
    test_load_image();

    CloseWindow();
    return 0;
}

