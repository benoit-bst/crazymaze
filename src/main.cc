#include "main.h"

Choice handle_menu()
{
    WINDOW *menu_win;
    uint highlight = 1;
    int choice = 0;
    int c;

    initscr();
    curs_set(0);
    clear();
    noecho();
    cbreak(); // Line buffering disabled. pass on everything

    // color
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    utils::init_color();

    // Title
    attron(COLOR_PAIR(2));
    printw("%s\n", title.c_str());

    // How to
    printw("\n\n Use arrow keys to go up and down,\n");
    printw(" Press enter to select a choice\n");
    attroff(COLOR_PAIR(2));
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
                if (c == 27)
                    endwin();
                    exit(1);
                refresh();
                break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0) // User did a choice come out of the infinite loop
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, menu[choice - 1]);
    clrtoeol();
    refresh();
    endwin();

    return utils::convert_choice(choice);
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
    cbreak(); // Line buffering disabled. pass on everything

    // How to
    attron(COLOR_PAIR(9));
    printw("\n Welcome to demo\n");
    attroff(COLOR_PAIR(9));
    refresh();
    usleep(400000);
    printw("\n Choose your maze size,\n");
    printw(" and find your path little rat...\n");
    printw(" Move:\n");
    printw("             Arrow UP\n");
    printw(" Arrow LEFT            Arrow RIGHT >\n");
    printw("            Arrow DOWN\n");

    const uint width = 51;
    const uint height = 21;
    maze my_maze(width, height);

    my_maze.random_maze(maze::dig_maze_algorithm::DFS);
    my_maze.find_path();
    auto mat = my_maze.matrix();
    for (uint i = 0; i < mat.size(); ++i) {
        if (i % width == 0)
            printw("\n ");
        utils::convert_char(mat[i]);
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
    cbreak(); //  Line buffering disabled. pass on everything

    attron(COLOR_PAIR(2));
    printw("%s ", bye_little_rat.c_str());
    refresh();
    for (uint i = 0; i < 20; ++i) {
        printw(".");
        refresh();
        usleep(50000);
    }
    attroff(COLOR_PAIR(2));
    endwin();
}

int main()
{
    setlocale(LC_ALL, "");

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
                return EXIT_SUCCESS;
                break;
            default:
                return EXIT_SUCCESS;

        }
    }
    return EXIT_SUCCESS;
}

