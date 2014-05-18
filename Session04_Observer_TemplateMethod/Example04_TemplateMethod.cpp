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
        cout << "  Setup Go board, 9-stone handicap.\n";
        cout << "     Black  White\n";

        short int turns = 0;
        unsigned short count = 0;
        while(count < 4) {
                if(turns == 0) ++count;
                turns = (turns+1) % 2;
                if(turns%2 == 1) {
                        cout << "  " << count << ": place";
                }
                else {
                        cout << "  place\n";
                }
        }

        cout << "\n  Black won.\n";
        cout << endl;
}

#define TWO 2

void playChess() {
        cout << "  Setup Chess board.\n";
        cout << "    White   Black\n";

        int play = 0;
        int n = 0;
        while(n < 4) {
                if(play == 0) ++n;
                play = (play+1) % TWO;
                if(play%TWO == 1)
                        cout << "  " << n << ": move";
                else {
                        cout << "  capture\n";
                }
        }

        cout << "\n  White won.\n";
        cout << endl;
}

#define PLAYERS 2

void playCheckers() {
        cout << "  Setup Checker board.\n";
        cout << "     Red   Black\n";

        uint side = 0;
        uint moves = 0;
        while(moves < 4) {
                if(side == 0) ++moves;
                side = (side+1) % PLAYERS;
                if(side%PLAYERS == 1) {
                        cout << "  " << moves << ": move";
                        }
                else
                        cout << "  jump\n";
        }

        cout << "\n  Red won.\n";
        cout << endl;
}

void playQuantumTicTacToe() {
        cout << "  Clear Quantum Tic-Tac-Toe board.\n";
        cout << "      X        O\n";

        short move = 0;
        while(move < 9) {
                ++move;
                cout << "  " << move << ": " << move << "-" << (move)%9 + 1;
                if(move%2 == 0)
                        cout << "\n";
                else
                        cout << "  ";
        }

        cout << "\n  X won.\n";
        cout << endl;
}

void demo() {
        cout << "<< Template Method problem >>\n";

        playGo();
        playChess();
        playCheckers();
        playQuantumTicTacToe();
}

}
