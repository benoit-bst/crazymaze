#include "main.h"

Choice handle_menu()
{
    WINDOW *menu_win;
    uint highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */

    // Title
    printw("%s\n", title.c_str());

    // How to
    printw("\n\n Use arrow keys to go up and down,\n");
    printw(" Press enter to select a choice\n");
    refresh();

    // Menu
    menu_win = newwin(menu_height, menu_width, menu_start_y, menu_start_x);
    keypad(menu_win, TRUE);
    print_menu(menu_win, highlight);

    // main loop
    while(1) {
        c = wgetch(menu_win);
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = menu.size();
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == menu.size())
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                mvprintw(24, 0, "Please select and press enter");
                //mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, menu[choice - 1]);
    clrtoeol();
    refresh();
    endwin();

    switch (choice) {
        case 1:
            return Choice::demo;
            break;
        case 2:
            return Choice::play;
            break;
        case 3:
            return Choice::exit;
            break;
        default:
            return Choice::exit;
            break;
    }
}

void print_menu(WINDOW *menu_win, const uint highlight)
{
    int x, y;

    x = 1;
    y = 1;
    //box(menu_win, 0, 0);
    for(uint i = 0; i < menu.size(); ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", menu[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", menu[i].c_str());
        ++y;
    }
    wrefresh(menu_win);
}


void demo()
{
    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */

    // How to
    printw("\n Welcome to demo\n");
    refresh();

    const uint width = 51;
    const uint height = 21;
    maze my_maze(width, height);

    my_maze.random_maze(maze::dig_maze_algorithm::DFS);
    my_maze.find_path();
    auto mat = my_maze.matrix();
    for (uint i = 0; i < mat.size(); ++i) {
        if (i % width == 0)
            printw("\n");
        printw("%c", mat[i]);
    }
    refresh();
    getch();
    endwin();
}

void bye()
{
    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */

    printw("%s ", bye_little_rat.c_str());
    refresh();
    for (uint i = 0; i < 20; ++i) {
        printw(".");
        refresh();
        usleep(79000);
    }
    endwin();
}

int main()
{
    while(1) {

        // Menu
        Choice action = handle_menu();

        switch (action) {
            case Choice::demo:
                demo();
                break;
            case Choice::play:

                break;
            case Choice::exit:
                bye();
                return 0;
                break;
            default:
                return 0;

        }
    }
    return 0;
}














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


// main(void)
// {
//     //[> WINDOW* boite; <]
//     initscr(); // Init WINDOW struct

//     // title
//     printw("%s\n", title.c_str());

//     // menu
//     printw("\n%s\n", menu.c_str());

//     while(1) {

//         getch();
//         if ( (getch() == Q_value) || (getch() == q_value) )
//             break;
//     }


//     int N = COLS - 1;
//     int M = LINES - 1;
//     if (N  % 2 == 0)
//         N--;
//     if (M % 2 == 0)
//         M--;

//     //cout << "COLS " << COLS << endl;
//     //cout << "LINES " << LINES << endl;
//     //cout << "N " << N << endl;
//     //cout << "M " << M << endl;
//     //printw("COLS %d\n", COLS);
//     //printw("LINES %d\n", LINES);
//     //printw("N %d\n", N);
//     //printw("M %d\n", M);

//     //maze my_maze(N,M);

//     //my_maze.random_maze(maze::dig_maze_algorithm::DFS);
//     //my_maze.find_path();
//     //auto mat = my_maze.matrix();
//     //for (uint i = 0; i < mat.size(); ++i) {
//         //if (i % N == 0)
//             //printw("\n");
//         //printw("%c", mat[i]);
//     //}
//     refresh();
//     getch();
//     endwin();

//     /* printw("Term size x %d - y %d\n", LINES, COLS); */

//     /* while(1) { */
//     /*     printw("Le terminal actuel comporte %d lignes et %d colonnes\n", LINES, COLS); */
//     /*     refresh();  // Rafraîchit la fenêtre par défaut (stdscr) afin d'afficher le message */
//     /*     if(getch() != 410)  // 410 est le code de la touche générée lorsqu'on redimensionne le terminal */
//     /*         printw("Le  %c\n", ); */
//     /*         /1* break; *1/ */
//     /*     } */

//     /*     endwin(); */

//     /*     free(boite); */

//     /* return 0; */

//     //cbreak();
//     //noecho();
//     //nodelay(stdscr, TRUE);

//     //scrollok(stdscr, TRUE);
//     //while (1) {
//         //if (kbhit()) {
//             //printw("Key pressed! It was: %d\n", getch());
//             //refresh();
//         //} else {
//              //printw("No key pressed yet...\n");
//             //refresh();
//             //usleep(100);
//         //}
//     //}
//     return 0;
// }

