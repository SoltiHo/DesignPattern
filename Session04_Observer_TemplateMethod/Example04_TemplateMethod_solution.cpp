namespace templateMethod {

class Game {
protected:
        uint movesCount;
public:
        Game() : movesCount(0) {}
        virtual ~Game() {}
protected:
        virtual void initializeGame()=0;
        virtual void move(uint move, uint turn)=0;
        virtual uint playsPerMove() { return 2; }
        virtual bool endOfGame()=0;
        virtual void printScore()=0;
public:
        void play() { // Template method.
                initializeGame();
                uint turn = 0;
                while(!endOfGame()) {
                        if(turn == 0) ++movesCount;
                        turn = (turn+1) % playsPerMove();
                        move(movesCount, turn);
                }
                printScore();
        }
};
class Go : public Game {
public:
        Go() {}
        virtual ~Go() { cout << "  ~Go\n"; }
public:
        void initializeGame() {
                cout << "  Setup Go board, 9-stone handicap.\n";
                cout << "     Black  White\n";
        }
        void move(uint move, uint turn) {
                if(turn%2 == 1) cout << "  " << movesCount << ": place";
                else                    cout << "  place\n";
        }
        bool endOfGame() {
                return(movesCount==4);
        }
        void printScore() {
                cout << "\n  Black won.\n";
        }
};
class Chess : public Game {
public:
        Chess() {}
        virtual ~Chess() { cout << "  ~Chess\n"; }
public:
        void initializeGame() {
                cout << "  Setup Chess board.\n";
                cout << "    White   Black\n";
        }
        void move(uint move, uint turn) {
                if(turn%2 == 1) cout << "  " << movesCount << ": move";
                else                    cout << "  capture\n";
        }
        bool endOfGame() {
                return(movesCount==4);
        }
        void printScore() {
                cout << "\n  White won.\n";
        }
};
class Checkers : public Game {
public:
        Checkers() {}
        virtual ~Checkers() { cout << "  ~Checkers\n"; }
public:
        void initializeGame() {
                cout << "  Setup Checker board.\n";
                cout << "     Red   Black\n";
        }
        void move(uint move, uint turn) {
                if(turn%2 == 1) cout << "  " << movesCount << ": move";
                else                    cout << "  jump\n";
        }
        bool endOfGame() {
                return(movesCount==4);
        }
        void printScore() {
                cout << "\n  Red won.\n";
        }
};
class QuantumTicTacToe : public Game {
public:
        QuantumTicTacToe() {}
        virtual ~QuantumTicTacToe() { cout << "  ~QuantumTicTacToe\n"; }
public:
        void initializeGame() {
                cout << "  Clear Quantum Tic-Tac-Toe board.\n";
                cout << "      X        O\n";
        }
        void move(uint move, uint turn) {
                cout << "  " << move << ": " << move << "-" << (move)%9 + 1;
                if(move%2 == 0) cout << "\n";
                else                    cout << "  ";
        }
        uint playsPerMove() {
                return 1;
        }
        bool endOfGame() {
                return(movesCount==9);
        }
        void printScore() {
                cout << "\n  X won.\n";
        }
};

void demo() {
        cout << "<< Template Method solution >>\n";

        Game* games[] = { new Go, new Chess, new Checkers, new QuantumTicTacToe };

        for(size_t i=0; i<sizeof(games)/sizeof(Game*); i++) {
                cout << endl;
                games[i]->play();
        }

        cout << endl;
        for(size_t i=0; i<sizeof(games)/sizeof(Game*); i++) {
                delete games[i];
        }
}

}
