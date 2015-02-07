#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
typedef unsigned int uint;

/* Consider a company that has written a number of games, and plans more.
* All of their games involve players taking turns.
* Below is troubled code that 'represents' the historical development of their products.
* Rewrite it using the Template Method design pattern to eliminate duplication.
* Removing the structural duplication will facilitate faster development of new games.
* Part of the challenge of design patterns is spotting when one is applicable.
* This exercise has been deliberately designed to muddy the waters.
* It is therefore more like what you will find in the wild versus the classroom.
* Hint #1: you may want to review Stepanov's concept of uplift.
* Hint #2: refactoring is your friend.
*/

namespace duplicated_skelaton {

    void playGo() {
        std::cout << "  Setup Go board, 9-stone handicap.\n";
        std::cout << "     Black  White\n";

        short int turns = 0;
        unsigned short count = 0;
        while(count < 4) {
            if(turns == 0) ++count;
            turns = (turns+1) % 2;
            if(turns%2 == 1) {
                std::cout << "  " << count << ": place";
            }
            else {
                std::cout << "  place\n";
            }
        }

        std::cout << "\n  Black won.\n";
        std::cout << std::endl;
    }

#define TWO 2

    void playChess() {
        std::cout << "  Setup Chess board.\n";
        std::cout << "    White   Black\n";

        int play = 0;
        int n = 0;
        while(n < 4) {
            if(play == 0) ++n;
            play = (play+1) % TWO;
            if(play%TWO == 1)
                std::cout << "  " << n << ": move";
            else {
                std::cout << "  capture\n";
            }
        }

        std::cout << "\n  White won.\n";
        std::cout << std::endl;
    }

#define PLAYERS 2

    void playCheckers() {
        std::cout << "  Setup Checker board.\n";
        std::cout << "     Red   Black\n";

        uint side = 0;
        uint moves = 0;
        while(moves < 4) {
            if(side == 0) ++moves;
            side = (side+1) % PLAYERS;
            if(side%PLAYERS == 1) {
                std::cout << "  " << moves << ": move";
            }
            else
                std::cout << "  jump\n";
        }

        std::cout << "\n  Red won.\n";
        std::cout << std::endl;
    }

    void playQuantumTicTacToe() {
        std::cout << "  Clear Quantum Tic-Tac-Toe board.\n";
        std::cout << "      X        O\n";

        short move = 0;
        while(move < 9) {
            ++move;
            std::cout << "  " << move << ": " << move << "-" << (move)%9 + 1;
            if(move%2 == 0)
                std::cout << "\n";
            else
                std::cout << "  ";
        }

        std::cout << "\n  X won.\n";
        std::cout << std::endl;
    }

    void demo() {
        std::cout << "<< Template Method problem >>\n";

        playGo();
        playChess();
        playCheckers();
        playQuantumTicTacToe();
    }

}

#define COLUMN_WIDTH 10
namespace Solti {
    // assuming 
    //     1. # players can be 2 or more
    //     2. operation of the players may differ
    //     3. ending criteria could be different
    //     4. turns can be skipped

    class Player{
    public:
        Player() : _name(""){
        }
        Player(std::string player_name) : _name(player_name){
        }
        std::string _name;
    };

    class GameSkeleton{
    public: 
        GameSkeleton() : _playerCount(0){};
        virtual void setupTheGame() = 0;
        void RunTheGame();
        // Return NULL if enough players or something wrong.  
        // no way to tell them apart.  Skip the implementation for simplicity
        virtual Player* generatePlayer() = 0;
        
        // collect players at framework level and Print out players
        void enumeratePlayers();

        // main game flow control
        virtual void play();

        // where players take actions
        // return true if the round is over, return false if more players to move
        // Output parameters: pRoundMessage
        virtual bool operatePlayer(const unsigned int round, std::string* pRoundMessage) = 0;

        // check if the next turns needed
        virtual bool gameOver(const unsigned int round) = 0;
        
        // print out the winner
        virtual void anounceTheWinner() = 0;
    protected:
        std::vector<Player> _players;
        unsigned int _playerCount;
    };

    void GameSkeleton::enumeratePlayers(){
        // get the players for the game
        Player* temp = NULL;
        std::vector<Player>::iterator it;
        unsigned int i = 0;
        while (temp = generatePlayer()){
            it = this->_players.end();
            this->_players.insert(it, *temp);
        }
        
        // print out the users
        std::cout << std::setw(COLUMN_WIDTH) << std::left << "";
        for(unsigned int i = 0; i < this->_players.size(); i++){
            std::cout << std::setw(COLUMN_WIDTH) << std::left << this->_players[i]._name;
        }
        std::cout << std::endl;
    }

    void GameSkeleton::play(){
        unsigned int round = 1;
        unsigned int playerIndex = 0;  // output parameter
        std::string roundMessage = "";  // output parameter
        while(!(this->gameOver(round))){
            std::ostringstream temp;
            temp << round << ": ";
            std::cout << std::setw(COLUMN_WIDTH) << std::right << temp.str();
            //while(this->operatePlayer(round, &operationMessage, &playerIndex)){
            //    std::cout << std::setw(COLUMN_WIDTH) << std::left << operationMessage;
            //}
            this->operatePlayer(round, &roundMessage);
            std::cout << std::setw(COLUMN_WIDTH) << std::left << roundMessage;
            // completed one round
            std::cout << std::endl;
            round++;
            roundMessage = "";
        }
    }
    void GameSkeleton::RunTheGame(){
        this->setupTheGame();
        this->enumeratePlayers();
        this->play();
        this->anounceTheWinner();
    }
    // --------------------------- Actual Game Implementation ---------------------------
    // ---------- PlayGo ----------
    class PlayGo : public GameSkeleton {
    public:
        virtual void setupTheGame();
        virtual Player* generatePlayer();
        //virtual bool enoughPlayers();
        virtual bool operatePlayer(const unsigned int round, std::string* pRoundMessage);
        virtual bool gameOver(const unsigned int round);
        virtual void anounceTheWinner();
    };

    void PlayGo::setupTheGame(){
        std::cout << "  Setup Go board, 9-stone handicap.\n";
    }
    Player* PlayGo::generatePlayer(){
        Player* temp = NULL;
        if(this->_playerCount == 0){
            temp = new Player("Black");
        }
        else if(this->_playerCount == 1){
            temp = new Player("White");
        }
        if(temp){
            // allocation succeeded
            this->_playerCount++;
        }
        return temp;
    }

    bool PlayGo::operatePlayer(const unsigned int round, std::string* pRoundMessage){
        std::ostringstream roundMessageBuffer;
        
        for(short int turns = 0; turns < 2; turns++){
            if(turns == 0) {
                // black
                roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "place";
            }
            else {
                // white
                if(round < 4){
                    roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "place";
                }
            }
        }
        *pRoundMessage = roundMessageBuffer.str();
        return true;
    }
    bool PlayGo::gameOver(const unsigned int round){
        if(round <= 4){
            return false;
        }
        else{
            return true;
        }
    }
    void PlayGo::anounceTheWinner(){
        std::cout << "  Black won." << std::endl << std::endl;
    }
    // ---------- PlayChess ----------
    class PlayChess : public GameSkeleton {
    public:
        virtual void setupTheGame();
        virtual Player* generatePlayer();
        //virtual bool enoughPlayers();
        virtual bool operatePlayer(const unsigned int round, std::string* pRoundMessage);
        virtual bool gameOver(const unsigned int round);
        virtual void anounceTheWinner();
    };

    void PlayChess::setupTheGame(){
        std::cout << "  Setup Chess board.\n";
    }
    Player* PlayChess::generatePlayer(){
        Player* temp = NULL;
        if(this->_playerCount == 0){
            temp = new Player("White");
        }
        else if(this->_playerCount == 1){
            temp = new Player("Black");
        }
        if(temp){
            // allocation succeeded
            this->_playerCount++;
        }
        return temp;
    }

    bool PlayChess::operatePlayer(const unsigned int round, std::string* pRoundMessage){
        std::ostringstream roundMessageBuffer;
        
        for(short int turns = 0; turns < 2; turns++){
            if(turns == 0) {
                // White
                roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "move";
            }
            else {
                // Black
                if(round < 4){
                    roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "capture";
                }
            }
        }
        *pRoundMessage = roundMessageBuffer.str();
        return true;
    }
    bool PlayChess::gameOver(const unsigned int round){
        if(round <= 4){
            return false;
        }
        else{
            return true;
        }
    }
    void PlayChess::anounceTheWinner(){
        std::cout << "  White won." << std::endl << std::endl;
    }

    // ---------- PlayCheckers ----------
    class PlayCheckers : public GameSkeleton {
    public:
        virtual void setupTheGame();
        virtual Player* generatePlayer();
        //virtual bool enoughPlayers();
        virtual bool operatePlayer(const unsigned int round, std::string* pRoundMessage);
        virtual bool gameOver(const unsigned int round);
        virtual void anounceTheWinner();
    };

    void PlayCheckers::setupTheGame(){
        std::cout << "  Setup Checker board.\n";
    }
    Player* PlayCheckers::generatePlayer(){
        Player* temp = NULL;
        if(this->_playerCount == 0){
            temp = new Player("Red");
        }
        else if(this->_playerCount == 1){
            temp = new Player("Black");
        }
        if(temp){
            // allocation succeeded
            this->_playerCount++;
        }
        return temp;
    }

    bool PlayCheckers::operatePlayer(const unsigned int round, std::string* pRoundMessage){
        std::ostringstream roundMessageBuffer;
        
        for(short int turns = 0; turns < 2; turns++){
            if(turns == 0) {
                // Red
                roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "move";
            }
            else {
                // Black
                if(round < 4){
                    roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "jump";
                }
            }
        }
        *pRoundMessage = roundMessageBuffer.str();
        return true;
    }
    bool PlayCheckers::gameOver(const unsigned int round){
        if(round <= 4){
            return false;
        }
        else{
            return true;
        }
    }
    void PlayCheckers::anounceTheWinner(){
        std::cout << "  Red won." << std::endl << std::endl;
    }

    // ---------- PlayCheckers ----------
    class PlayQuantumTicTacToe : public GameSkeleton {
    public:
        virtual void setupTheGame();
        virtual Player* generatePlayer();
        //virtual bool enoughPlayers();
        virtual bool operatePlayer(const unsigned int round, std::string* pRoundMessage);
        virtual bool gameOver(const unsigned int round);
        virtual void anounceTheWinner();
    };

    void PlayQuantumTicTacToe::setupTheGame(){
        std::cout << "  Clear Quantum Tic-Tac-Toe board.\n";
    }
    Player* PlayQuantumTicTacToe::generatePlayer(){
        Player* temp = NULL;
        if(this->_playerCount == 0){
            temp = new Player("X");
        }
        else if(this->_playerCount == 1){
            temp = new Player("O");
        }
        if(temp){
            // allocation succeeded
            this->_playerCount++;
        }
        return temp;
    }

    bool PlayQuantumTicTacToe::operatePlayer(const unsigned int round, std::string* pRoundMessage){
        std::ostringstream roundMessageBuffer;

        if(round % 2){
            // X
            std::ostringstream temp;
            temp << round << "-" << ((round)%9 + 1);
            roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << temp.str();
        }
        else{
            // O
            std::ostringstream temp;
            temp << round << "-" << ((round)%9 + 1);
            roundMessageBuffer << std::setw(COLUMN_WIDTH) << std::left << "" << temp.str();
        }
        
        *pRoundMessage = roundMessageBuffer.str();
        return true;
    }
    bool PlayQuantumTicTacToe::gameOver(const unsigned int round){
        if(round <= 9){
            return false;
        }
        else{
            return true;
        }
    }
    void PlayQuantumTicTacToe::anounceTheWinner(){
        std::cout << "  X won." << std::endl << std::endl;
    }
}

int main(){
    duplicated_skelaton::demo();

    std::cout << std::endl << " ---------------------------- Template Method ----------------------------" << std::endl;
    Solti::GameSkeleton* game1 = new Solti::PlayGo;
    game1->RunTheGame();

    Solti::GameSkeleton* game2 = new Solti::PlayChess;
    game2->RunTheGame();

    Solti::GameSkeleton* game3 = new Solti::PlayCheckers;
    game3->RunTheGame();
    
    Solti::GameSkeleton* game4 = new Solti::PlayQuantumTicTacToe;
    game4->RunTheGame();

    return 0;
}
