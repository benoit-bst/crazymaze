#pragma once

#include <unistd.h>  // only for sleep()
#include <locale.h>  // only for sleep()
#include <iostream>

#include <ncurses.h> // graphic lib for term

#include <maze/maze.h> // maze core lib

using namespace std;
using namespace cm;

static constexpr char D_value = 68;
static constexpr char d_value = 100;
static constexpr char N_value = 78;
static constexpr char n_value = 110;
static constexpr char Q_value = 81;
static constexpr char q_value = 113;

void convert_char(const char simple_char);

//------------------------------
// Main title
//-----------------------------
static const string title=R"(
              Welcome to
  __ _ _ __ _ ____  _   _ __  __ _ ______
 / _| '_/ _` |_ / || | | '  \/ _` |_ / -_)
 \__|_| \__,_/__|\_, | |_|_|_\__,_/__\___|
                 |__/

                 game)";

//------------------------------
// Menu Handling
//-----------------------------
static const array<string, 3> menu = {"Demo", "Play", "Exit"};
enum class Choice {
    demo,
    play,
    exit
};

static constexpr uint menu_width   = 13;
static constexpr uint menu_height  = 9;
static constexpr uint menu_start_x = 0;
static constexpr uint menu_start_y = 12;

Choice handle_menu();
void print_menu(WINDOW *menu_win, const uint highlight);

//------------------------------
// Demo
//-----------------------------
void demo();

//------------------------------
// Bye
//-----------------------------
static const string bye_little_rat=R"(

                 _..----.._    _
               .'  .--.    "-.(0)_
   '-.__.-'"'=:|   ,  _)_ \__ . c\'-..
                '''------'---''---'-"

   Bye little Rat)";
void bye();

