#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// ===== Terminal Modes =====
void enableRawMode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
}

void disableRawMode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
}

// ===== Draw Main Menu =====
void drawMenu(int selected) {
    const char *items[] = {
        "Option 1: Print Hello",
        "Option 2: Print Numbers",
        "Exit Program"
    };

    printf("\033[H\033[J"); // clear
    printf("Use ↑ ↓ and ENTER\n\n");

    for (int i = 0; i < 3; i++) {
        if (i == selected) printf(" > %s <\n", items[i]);
        else               printf("   %s\n", items[i]);
    }
}

// ===== Draw Submenu =====
void drawSubmenu(int selected, const char *message) {
    const char *items[] = {
        "Return to main menu",
        "Exit program"
    };

    printf("\033[H\033[J"); // clear screen

    // ---- Your custom text here ----
    printf("*** Submenu ***\n");
    printf("%s\n\n", message);   // <-- displayed text

    printf("Use ↑ ↓ and ENTER\n\n");

    // ---- Menu items ----
    for (int i = 0; i < 2; i++) {
        if (i == selected) printf(" > %s <\n", items[i]);
        else               printf("   %s\n", items[i]);
    }
}

// ===== Submenu Logic (arrow navigation) =====
int submenu(const char *msg) {
    int selected = 0;
    int ch;

    while (1) {
        drawSubmenu(selected, msg);
        ch = getchar();

        if (ch == 27) {
            ch = getchar();
            if (ch == '[') {
                ch = getchar();
                if (ch == 'A' && selected > 0) selected--;
                if (ch == 'B' && selected < 1) selected++;
            }
        }
        else if (ch == '\n') {
            return selected;
        }
    }
}

// ===== MAIN PROGRAM =====
int main() {
    enableRawMode();
    atexit(disableRawMode);

    int selected = 0;
    int ch;
    int running = 1;

    while (running) {

        // ===== MAIN MENU =====
        while (1) {
            drawMenu(selected);
            ch = getchar();
            
            printf("Made by Infy\n");

            if (ch == 27) {
                ch = getchar();
                if (ch == '[') {
                    ch = getchar();
                    if (ch == 'A' && selected > 0) selected--; // Up
                    if (ch == 'B' && selected < 2) selected++; // Down
                }
            }
            else if (ch == '\n') break; // option chosen
        }

        // ===== PROCESS SELECTED OPTION =====
        printf("\033[H\033[J");

        if (selected == 0) {
            printf("Hello!\n\n");
        }
        else if (selected == 1) {
            printf("Numbers: 1 2 3 4 5\n\n");
        }
        else if (selected == 2) {
            printf("Exiting...\n");
            break;
        }

        // ===== SUBMENU (ARROW NAVIGATION) =====
        int sub = submenu("Press ENTER to continue");
        if (sub == 1) running = 0;   // 1 = "Exit program"
        // 0 = return → loop continues
    }

    printf("Goodbye!\n");
    return 0;
}