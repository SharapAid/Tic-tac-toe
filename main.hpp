#pragma once
#include <iostream>
#include <string>
using namespace std;

enum state{
    MENU,
    PLAY,
    EXIT
};

class Player{
private:
    string m_player;
    char m_simbol;
    static short m_cout;
    short m_index;
public:
    Player(){
        m_player = " ";
        m_simbol = ' ';
        m_cout ++;
        m_index = m_cout;
    }

    void SetPlayer(){
        string player;
        cout<<"Enter name of player: ";
        cin>>player;
        m_player = player;
    }

    string GetName(){
        return m_player;
    }

    short GetPlayerIndex(){
        return m_index;
    }

    char GetSimbol(){
        if(this->GetPlayerIndex() == 1){
            m_simbol = '*';  
        }
        else if(this->GetPlayerIndex() == 2){
            m_simbol = 'o';
        }
        return m_simbol;
    }
};
short Player::m_cout = 0;



class Board{
private:
    char m_board[3][3]{};
    short m_position_x;
    short m_position_y;
    short m_winner;
public:
    Board(){
        for(short i = 0; i < 3; i++){
            for(short j = 0; j < 3; j++){
                m_board[i][j] = ' ';
            }
        }
        m_position_x = 0;
        m_position_y = 0; 
        m_winner = 0;
    }

    void SetPositionSimbol(Player& player){
        do{
            cout<<"Where do you want to set simbol?";
            cin>>m_position_y>>m_position_x;
        }
        while((m_position_y < 0 or m_position_y > 2) || (m_position_x < 0 or m_position_x > 2));
        m_board[m_position_y][m_position_x] = player.GetSimbol();
    }

    void draw(){
        cout<<"------"<<endl;
        for(short i = 0; i < 3; i++){
            for(short j = 0; j < 3; j++){
                cout<<m_board[i][j]<<"|";
            }
            cout<<endl<<"------"<<endl;
        }
    }

    short GetWinner(Player& player){
        if(player.GetPlayerIndex() == 2){
            if(m_board[0][0] == 'o' and m_board[0][1] == 'o' and m_board[0][2] == 'o'){
                m_winner = 2;
            }
            if(m_board[1][0] == 'o' and m_board[1][1] == 'o' and m_board[1][2] == 'o'){
                m_winner = 2;
            }
            if(m_board[2][0] == 'o' and m_board[2][1] == 'o' and m_board[2][2] == 'o'){
                m_winner = 2;
            }
            if(m_board[0][0] == 'o' and m_board[1][1] == 'o' and m_board[2][2] == 'o'){
                m_winner = 2;
            }
            if(m_board[0][2] == 'o' and m_board[1][1] == 'o' and m_board[2][0] == 'o'){
                m_winner = 2;
            }
            if(m_board[0][0] == 'o' and m_board[1][0] == 'o' and m_board[2][0] == 'o'){
                m_winner = 2;
            }
            if(m_board[0][1] == 'o' and m_board[1][1] == 'o' and m_board[2][1] == 'o'){
                m_winner = 2;
            }
            if(m_board[0][2] == 'o' and m_board[1][2] == 'o' and m_board[2][2] == 'o'){
                m_winner = 2;
            }
        }
        else if(player.GetPlayerIndex() == 1){
            if(m_board[0][0] == '*' and m_board[0][1] == '*' and m_board[0][2] == '*'){
                m_winner = 1;
            }
            if(m_board[1][0] == '*' and m_board[1][1] == '*' and m_board[1][2] == '*'){
                m_winner = 1;
            }
            if(m_board[2][0] == '*' and m_board[2][1] == '*' and m_board[2][2] == '*'){
                m_winner = 1;
            }
            if(m_board[0][0] == '*' and m_board[1][1] == '*' and m_board[2][2] == '*'){
                m_winner = 1;
            }
            if(m_board[0][2] == '*' and m_board[1][1] == '*' and m_board[2][0] == '*'){
                m_winner = 1;
            }
            if(m_board[0][0] == '*' and m_board[1][0] == '*' and m_board[2][0] == '*'){
                m_winner = 1;
            }
            if(m_board[0][1] == '*' and m_board[1][1] == '*' and m_board[2][1] == '*'){
                m_winner = 1;
            }
            if(m_board[0][2] == '*' and m_board[1][2] == '*' and m_board[2][2] == '*'){
                m_winner = 1;
            }
        }
        return m_winner;
    }
};





class Game{
private:
    short m_cout;
    state m_state;
public:
    Game(){
        m_state = state::MENU;
        m_cout = 0;
    }

    void WriteRuls(){
        cout<<"Play two person, player shood enter position of simbol."<<endl;
        cout<<"In default first player is 'o', the second is '*'"<<endl;
        cout<<"You shuod enter coords of simbol"<<endl<<"(y , x)"<<endl;
    }

    void SetState(state states){
        m_state = states;
    }

    int GetState(){
        return m_state;
    }

    void ChangeState(){
        while(this->GetState() != state::EXIT){
            if(this->GetState() ==  state::MENU){
                cout<<"What you want to do?"<<endl;
                do{
                    cout<<"play - 1, exit - 0: ";
                    cin>>m_cout;
                }
                while(m_cout < 0 or m_cout > 1);
                if(m_cout == 1){
                    this->SetState(state::PLAY);
                }
                else{
                    this->SetState(state::EXIT);
                }
            }
            Player player1;
            Player player2;
            Board board;
            if(this->GetState() == state::PLAY){      
                player1.SetPlayer();
                player2.SetPlayer();
                short game_pass = 0;
                bool is_ween = false;
                short winner_is = 0;
                board.draw();
                do{
                    cout<<"Player "<<player1.GetName()<<" play."<<endl;
                    board.SetPositionSimbol(player1);
                    board.draw();
                    game_pass ++;
                    if(game_pass > 4){
                        winner_is = board.GetWinner(player1);
                        if(winner_is > 0){
                            is_ween = true;
                            break;
                        }
                    }
                    cout<<"Player "<<player2.GetName()<<" play."<<endl;
                    board.SetPositionSimbol(player2);
                    board.draw();
                    game_pass ++;
                    if(game_pass > 4){
                        winner_is = board.GetWinner(player2);
                        if(winner_is > 0){
                            is_ween = true;
                            break;
                        }
                    }
                }
                while(is_ween == false or game_pass < 9);
                if(winner_is == 1){
                    cout<<"Player "<<player1.GetName()<<" is winner!!!"<<endl;
                    this->SetState(state::MENU);
                }
                else if(winner_is == 2){
                    cout<<"Player "<<player2.GetName()<<" is winner!!!"<<endl;
                    this->SetState(state::MENU);
                }
                else{
                    cout<<"Draw"<<endl;
                    this->SetState(state::MENU);
                }
            }
        }
        if(this->GetState() == state::EXIT){
            cout<<"Do you reale want to exit?"<<endl;
            cout<<"0 - yes, 1 - no: ";
            cin>>m_cout;
            if(m_cout == 1){
                this->SetState(state::MENU);
            }
        }
    }
};
