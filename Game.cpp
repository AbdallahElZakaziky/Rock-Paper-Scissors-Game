//
// Created by Abdallah on 11-Mar-25.
//
#include<iostream>
#include "Game.h"
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;

//----------------------------------------------------------------

// User Class Implementation

//----------------------------------------------------------------
user::user(string name, string type) {
    this->name = name;
    this->type = type;
    score = 0;
}

void user::add_score() {
    score++;
}

string user::get_name() {
    return name;
}

string user::move_to_string() {
    switch (user_move) {
        case moves::rock: {
            return "Rock";
            break;
        }
        case moves::paper: {
            return "Paper";
            break;
        }
        case moves::scissors: {
            return "Scissors";
            break;
        }
    }
}

string user::get_move() {
    switch (user_move) {
        case moves::rock: {
            return name + " Chose Rock ! \n";
            break;
        }
        case moves::paper: {
            return name + " Chose Paper ! \n";
            break;
        }
        case moves::scissors: {
            return name + " Chose Scissors ! \n";
            break;
        }
    }
}

void user::set_move(moves move) {
    this->user_move = move;
    total_moves.push_back(move);
}

void user::take_user_selection() {
    int selection;
    while (true) {
        if (type == "Human") {
            cin >> selection;
            cin.ignore();
        } else {
            random_device rd;
            mt19937 gen(rd()); // Mersenne Twister PRNG
            uniform_int_distribution<int> dist(1, 3); // Range [1, 3]

            selection = dist(gen);
        }
        switch (selection) {
            case 1: {
                set_move(moves::rock);
                cout << get_move();
                cout << "===================================================\n";
                break;
            }
            case 2: {
                set_move(moves::paper);
                cout << get_move();
                cout << "===================================================\n";
                break;
            }
            case 3: {
                set_move(moves::scissors);
                cout << get_move();
                cout << "===================================================\n";

                break;
            }
            default: {
                cout << "Hey " << name << " Enter a valid value (1 - 2 - 3) \n";
                continue;
            }
        }
        break;
    }
}


//----------------------------------------------------------------

// Game Message Classs definitions

//----------------------------------------------------------------

game_messages::game_messages() {
}

void game_messages::start_game_message() {
    cout << "================================================================\n";
    cout << "========== Welcome to Rock Paper Scissors Game =================\n";
}

void game_messages::rules_message() {
    cout << "================================================================\n";
    cout << "The rules are simple, you chose only one move either Rock, Paper, or Scissors\n";
    cout << "and the winner is determined by the following rules: \n";
    cout << "Rock crushes Scissors \n";
    cout << "Scissors cuts Paper \n";
    cout << "Paper covers Rock \n";
    cout << "If all players choose the same move, it's a tie \n";
    cout << "================================================================\n";
}

void game_messages::typing_message() {
    int speed = 250;
    string message = "Walter is thinking...";
    for (char c: message) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
    cout << endl;
}

void game_messages::game_over_message() {
    cout << "Game Over! \n";
}

void game_messages::display_scoreboard(vector<g_data> all_moves, vector<user> players) {
    // Header
    cout << "\n====================== Scoreboard =============================\n";
    cout << "===============================================================\n";
    cout << "| " << setw(6) << left << "Round"
            << " | " << setw(15) << left << players[0].get_name()
            << " | " << setw(15) << left << players[1].get_name()
            << " | " << setw(15) << left << "Round Winner" << " |\n";
    cout << "===============================================================\n";

    // Data Rows
    for (const auto &move: all_moves) {
        cout << "| " << setw(6) << left << move.round
                << " | " << setw(15) << left << move.p1_move
                << " | " << setw(15) << left << move.p2_move
                << " | " << setw(15) << left << move.winner << " |\n";
    }

    // Footer
    cout << "===============================================================\n";
}

void game_messages::round_start_message(int round) {
    cout << "===================================================\n";
    cout << "Round " << round << " Started \n";
    cout << "===================================================\n";
}

void game_messages::round_winner_message(string winner) {
    cout << "===================================================\n";
    cout << winner << " wins this round! \n";
    cout << "===================================================\n";
}

void game_messages::round_tie_message() {
    cout << "===================================================\n";
    cout << "This round ends with a tie ! \n";
    cout << "===================================================\n";
}

void game_messages::sudden_death_message() {
    cout << "===================================================\n";
    cout << "Sudden death !\n" <<
            "The game now is a tie\nyou'll be playing another round to decide the winner\n";
}

void game_messages::winner_message(string winner) {
    cout << "===================================================\n";
    cout << winner << " is the winner of the game wohoooooooo ! \n";
    cout << "Congratulations " << winner << "\n";
}


//----------------------------------------------------------------

// Gameplay Class Implementation

//----------------------------------------------------------------


gameplay::gameplay(int rounds, vector<user> player) {
    this->rounds = rounds;
    players = player;
}

gameplay::gameplay() {
}

gameplay::~gameplay() {
}

void gameplay::game_info() {
    char choice;
    string username;
    vector<user> player;
    cout << "Enter Your Information" << endl;
    cout << "Enter your name : ";
    getline(cin, username);
    user user_1(username, "Human");
    player.push_back(user_1);
    cout << "Do you wish to play with a friend or against a bot ?" << endl
            << "Friends F - Bot B" << endl;
    while (true) {
        cin >> choice;
        cin.ignore();
        if (choice == 'F' || choice == 'f') {
            cout << "Please enter your name : ";
            getline(cin, username);
            user user_2(username, "Human");
            player.push_back(user_2);
            break;
        } else if (choice == 'B' || choice == 'b') {
            cout << "You will be playing against Walter the bot\n";
            user user_2("Walter the bot", "Bot");
            player.push_back(user_2);
            break;
        } else {
            cout << "Invalid choice. Please enter 'F' for friends or 'B' for bot. \n" << endl;
        }
    }
    set_rounds_count();
    this->players = player;
}

void gameplay::set_current_round_winner(string name) {
    current_round_winner = name;
}

string gameplay::get_current_round_winner() {
    return current_round_winner;
}

void gameplay::set_rounds_count() {
    int rounds_num;
    cout << "How many rounds do you wish to play? \n( 3 - 5 - 7 ) \n";
    while (true) {
        cin >> rounds_num;
        cin.ignore();
        switch (rounds_num) {
            case 3:
                cout << "Number of rounds is 3 \n";
                break;
            case 5:
                cout << "Number of rounds is 5 \n";
                break;
            case 7:
                cout << "Number of rounds is 7 \n";
                break;
            default: {
                cout << "Please enter a valid round number ( 3 - 5 - 7 ) \n";
                continue;
            }
        }
        break;
    }
    this->rounds = rounds_num;
    this->initial_value = 1;
}

void gameplay::play_rounds() {
    for (int i = initial_value; i <= rounds; ++i) {
        msg.round_start_message(i);
        for (int j = 0; j < 2; ++j) {
            if (players[j].type == "Human") {
                cout << players[j].name << " please enter your move \n";
                cout << "1 - Rock \n2 - Paper \n3 - Scissors\n";
            } else {
                msg.typing_message();
            }
            players[j].take_user_selection();
        }
        referee();
        g_data gd = {
            i,
            players[0].move_to_string(),
            players[1].move_to_string(),
            this->current_round_winner
        };
        game_data.push_back(gd);
        get_score();
    }
}

void gameplay::get_score() {
    cout << "Current score : \n" + players[0].name + " : " + to_string(players[0].score) << "\n"
            << players[1].name + " : " + to_string(players[1].score) << "\n";
    cout << "===================================================\n";
}

void gameplay::referee() {
    if (players[0].user_move == moves::rock) {
        if (players[1].user_move == moves::paper) {
            players[1].add_score();
            msg.round_winner_message(players[1].name);
            set_current_round_winner(players[1].name);
        } else if (players[1].user_move == moves::scissors) {
            players[0].add_score();
            msg.round_winner_message(players[0].name);
            set_current_round_winner(players[0].name);
        } else {
            msg.round_tie_message();
            set_current_round_winner("Tie");
        }
    } else if (players[0].user_move == moves::paper) {
        if (players[1].user_move == moves::scissors) {
            players[1].add_score();
            msg.round_winner_message(players[1].name);
            set_current_round_winner(players[1].name);
        } else if (players[1].user_move == moves::rock) {
            players[0].add_score();
            msg.round_winner_message(players[0].name);
            set_current_round_winner(players[0].name);
        } else {
            msg.round_tie_message();
            set_current_round_winner("Tie");
        }
    } else {
        if (players[1].user_move == moves::rock) {
            players[1].add_score();
            msg.round_winner_message(players[1].name);
            set_current_round_winner(players[1].name);
        } else if (players[1].user_move == moves::paper) {
            players[0].add_score();
            msg.round_winner_message(players[0].name);
            set_current_round_winner(players[0].name);
        } else {
            msg.round_tie_message();
            set_current_round_winner("Tie");
        }
    }
}

void gameplay::set_game_data(g_data &gd) {
    game_data.push_back(gd);
}

void gameplay::final_decision() {
    if (players[0].score > players[1].score) {
        msg.game_over_message();
        msg.winner_message(players[0].name);
        msg.display_scoreboard(this->game_data, this->players);
    } else if (players[1].score > players[0].score) {
        msg.game_over_message();
        msg.winner_message(players[1].name);
        msg.display_scoreboard(this->game_data, this->players);
    } else
        sudden_death();
}

void gameplay::sudden_death() {
    msg.sudden_death_message();
    this->initial_value = rounds + 1;
    this->rounds += 1;
    play_rounds();
    final_decision();
}

void gameplay::start_game() {
    msg.start_game_message();
    msg.rules_message();
    game_info();
    play_rounds();
    final_decision();
}
