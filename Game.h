//
// Created by Abdallah on 11-Mar-25.
//
#include<iostream>
#include <vector>

using namespace std;
#ifndef RPS_GAME_H
#define RPS_GAME_H


enum class moves {
    rock = 1, paper = 2, scissors = 3
};

struct g_data {
    int round;
    string p1_move;
    string p2_move;
    string winner;
};

//----------------------------------------------------------------
// User Class Definition
//----------------------------------------------------------------

class user {
private:
    string name;
    string type;
    int score;
    vector<moves> total_moves;
    moves user_move;

public:
    user(string name, string type);

    void add_score();

    string get_name();

    void set_move(moves move);

    string get_move();

    void take_user_selection();

    string move_to_string();

    friend class gameplay;
};



//----------------------------------------------------------------

// Game Mesasges Class Definition

//----------------------------------------------------------------


class game_messages {
public:
    game_messages();

    void start_game_message();

    void rules_message();

    void typing_message();

    void round_start_message(int round);

    void round_winner_message(string winner);

    void round_tie_message();

    void sudden_death_message();

    void winner_message(string winner);

    void game_over_message();

    void display_scoreboard(vector<g_data > all_moves, vector<user> players);
};

//----------------------------------------------------------------
// Gameplay Class Definition
//----------------------------------------------------------------
class game_messages;

class gameplay {
private:
    int rounds;
    int initial_value;
    vector<user> players;
    vector<pair<int, int> > all_moves;
    vector<g_data> game_data;
    string current_round_winner;
    game_messages msg;
public:
    gameplay();

    gameplay(int rounds, vector<user> players);

    ~gameplay();

    void game_info();

    void set_current_round_winner(string name);

    string get_current_round_winner();

    void set_rounds_count();

    void play_rounds();

    void get_score();

    void referee();

    void set_game_data(g_data &gd);

    void final_decision();

    void sudden_death();

    void start_game();

    friend class game_messages;
};

#endif //RPS_GAME_H
