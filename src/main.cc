#include <ncurses.h>
#include <iostream>
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
    //[> WINDOW* boite; <]
    initscr(); // Init WINDOW struct

    int N = COLS;
    int M = LINES;
    if (N  % 2 == 0)
        N--;
    if (M % 2 == 0)
        M--;


    //cout << "COLS " << COLS << endl;
    //cout << "LINES " << LINES << endl;
    //cout << "N " << N << endl;
    //cout << "M " << M << endl;
    //printw("COLS %d\n", COLS);
    //printw("LINES %d\n", LINES);
    //printw("N %d\n", N);
    //printw("M %d\n", M);

    maze my_maze(N,M);

    //my_maze.random_maze();
    // Print with ascii characters

    my_maze.random_maze();
    my_maze.find_path();
    auto mat = my_maze.matrix();
    for (uint i = 0; i < mat.size();  ++i) {
        for (uint j = 0; j < mat[i].size();  ++j) {
            printw("%c", mat[i][j]);
        }
        printw("\n");
    }
    refresh();
    getch();
    endwin();

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

    //cbreak();
    //noecho();
    //nodelay(stdscr, TRUE);

    //scrollok(stdscr, TRUE);
    //while (1) {
        //if (kbhit()) {
            //printw("Key pressed! It was: %d\n", getch());
            //refresh();
        //} else {
             //printw("No key pressed yet...\n");
            //refresh();
            //usleep(100);
        //}
    //}
    return 0;
}

