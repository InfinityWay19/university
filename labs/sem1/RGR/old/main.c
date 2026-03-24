#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <termios.h>
#include <unistd.h>

// Turn off terminal buffering (so we read keypresses immediately)
void enableRawMode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);  // disable canonical mode and echo
    tcsetattr(0, TCSANOW, &term);
}

// Restore terminal mode when exiting
void disableRawMode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
}

// Draw menu
void drawMenu(int selected) {
    const char *items[] = {
        "Option 1: Print Hello",
        "Option 2: Print Numbers",
        "Option 3: Exit"
    };

    int count = 3;

    printf("\033[H\033[J"); // clear screen

    printf("Use ↑ ↓ arrows and ENTER\nИспользуйте ↑ ↓ стрелки и ENTER\n");

    for (int i = 0; i < count; i++) {
        if (i == selected)
            printf(" > %s <\n", items[i]);  // highlight
        else
            printf("   %s\n", items[i]);
    }
}

int main() {
    enableRawMode();
    atexit(disableRawMode);  // ensure restore on exit
    setlocale(LC_ALL, "Russian");

    int selected = 0;
    int ch;

    while (1) {
        drawMenu(selected);

        ch = getchar();

        if (ch == 27) { // ESC
            ch = getchar();
            if (ch == '[') {
                ch = getchar();
                if (ch == 'A') {        // up arrow
                    if (selected > 0) selected--;
                } else if (ch == 'B') { // down arrow
                    if (selected < 2) selected++;
                }
            }
        }
        else if (ch == '\n') { // ENTER
            break;
        }
    }

    printf("\nYou selected: %d\nВы выбрали: %d\n", selected + 1);

    if (selected == 0) printf("Hello!\nПривет!\n");
    if (selected == 1) {
        for (int i = 1; i <= 5; i++) printf("%d ", i);
        printf("\n");
    }
    if (selected == 2) printf("Goodbye!\nДо встречи!\n");

    return 0;
}
