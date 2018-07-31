#include <ncurses.h>
#include <unistd.h>  /* only for sleep() */

#include <maze/maze.h>

using namespace std;
using namespace cm;

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    /* WINDOW* boite; */
    initscr(); // Init WINDOW struct

    /* int N = 0; */
    /* int M = 0; */
    /* if (COLS % 2 == 0) */
    /*     N = COLS - 1; */
    /* if (LINES % 2 == 0) */
    /*     M = LINES - 1; */
    /* const int val = M; */
    /* maze<100,val> my_maze; */

    /* my_maze.random_maze(); */
    /* // Print with ascii characters */
    /* my_maze.print_maze(); */


    /* printw("Term size x %d - y %d\n", LINES, COLS); */

    /* while(1) { */
    /*     printw("Le terminal actuel comporte %d lignes et %d colonnes\n", LINES, COLS); */
    /*     refresh();  // Rafraîchit la fenêtre par défaut (stdscr) afin d'afficher le message */
    /*     if(getch() != 410)  // 410 est le code de la touche générée lorsqu'on redimensionne le terminal */
    /*         printw("Le  %c\n", ); */
    /*         /1* break; *1/ */
    /*     } */

    /*     endwin(); */

    /*     free(boite); */

    /* return 0; */

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    scrollok(stdscr, TRUE);
    while (1) {
        if (kbhit()) {
            printw("Key pressed! It was: %d\n", getch());
            refresh();
        } else {
            /* printw("No key pressed yet...\n"); */
            refresh();
            usleep(100);
        }
    }
    endwin();
    return 0;
}

