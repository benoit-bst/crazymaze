#pragma once

#include <unistd.h>  // only for sleep()
#include <locale.h>  // only for sleep()
#include <iostream>

#include "utils.h"

using namespace std;

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

