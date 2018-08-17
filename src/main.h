#pragma once

#include <unistd.h>  // only for sleep()
#include <locale.h>
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
// Main page
//-----------------------------
static constexpr uint main_menu_size = 3;
static const array<string, main_menu_size> main_menu = {"Demo", "Play", "Exit"};

static constexpr uint main_width   = 13;
static constexpr uint main_height  = 9;
static constexpr uint main_start_x = 0;
static constexpr uint main_start_y = 12;

MainChoice main_page();

//------------------------------
// Demo
//-----------------------------
void demo();

//------------------------------
// play
//-----------------------------
static constexpr uint maze_menu_size = 5;
static const array<string, maze_menu_size> maze_menu = {"Small", "Medium", "Large", "Extra Large", "Exit"};

static constexpr uint maze_width   = 13;
static constexpr uint maze_height  = 9;
static constexpr uint maze_start_x = 0;
static constexpr uint maze_start_y = 2;

void play();

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

