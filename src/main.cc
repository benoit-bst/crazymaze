#include "main.h"

MainChoice main_page()
{
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
    const uint choice = utils::handle_menu<main_menu_size, MainChoice>(main_menu, main_height, main_width, main_start_y, main_start_x);
    return utils::convert_main_choice(choice);
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
    printw("                 Arrow UP or k\n");
    printw(" Arrow LEFT or h                 Arrow RIGHT or l\n");
    printw("                 Arrow DOWN or j\n");

    const uint width = 47;
    const uint height = 17;
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

void play()
{
    initscr();
    clear();
    noecho();
    cbreak(); // Line buffering disabled. pass on everything

    // How to
    attron(COLOR_PAIR(9));
    printw("\n Select a size\n");
    attroff(COLOR_PAIR(9));
    refresh();

    // Menu
    pair<int, int> maze_size;
    while (1) {
        const uint choice = utils::handle_menu<maze_menu_size, MazeChoice>(maze_menu, maze_height, maze_width, maze_start_y, maze_start_x);
        MazeChoice maze_choice = utils::convert_maze_choice(choice);
        if (maze_choice == MazeChoice::exit) {
            endwin();
            return;
        }
        maze_size = utils::convert_maze_size(maze_choice);
        if ((maze_size.first <= COLS - 1) &&  (maze_size.second <= LINES - 1)) {
            break;
        } else {
            mvprintw(11, 1, "Your terminal is too small for this size...");
            mvprintw(12, 1, "Please select a smaller size or resize terminal.");
            refresh();
        }
    };

    clear();
    maze my_maze(maze_size.first, maze_size.second);
    my_maze.random_maze(maze::dig_maze_algorithm::DFS);
    auto mat = my_maze.matrix();
    for (uint i = 0; i < mat.size(); ++i) {
        if (i % maze_size.first == 0)
            printw("\n ");
        utils::convert_char(mat[i]);
    }
    refresh();

    // move cursor
    utils::move_cursor(my_maze);

    clrtoeol();
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
        MainChoice action = main_page();

        switch (action) {
            case MainChoice::demo:
                demo();
                break;
            case MainChoice::play:
                play();
                break;
            case MainChoice::exit:
                bye();
                return EXIT_SUCCESS;
                break;
            default:
                return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

