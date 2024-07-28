#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

class Game {
public:
    virtual void play() = 0;
    virtual ~Game() {}
};

class RockPaperScissors : public Game {
public:
    int score=0;
    void play() override {
        while (true) {
            cout << "Enter your choice (rock, paper, scissors, or exit): ";
            string userChoice;
            cin >> userChoice;
            if(userChoice == "exit"){ break; }
            string computerChoice = generateComputerChoice();
            cout << "Computer's choice: " << computerChoice << endl;
            score += determineWinner(userChoice, computerChoice);
        }
    }

private:
 
    std::string generateComputerChoice() {
        const std::string choices[] = {"rock", "paper", "scissors"};
        return choices[rand() % 3];
    }

    int determineWinner(const std::string& user, const std::string& computer) {
        if (user == computer) {
            std::cout << "It's a tie!\n";
            return 1;
        } else if ((user == "rock" && computer == "scissors") ||
                   (user == "paper" && computer == "rock") ||
                   (user == "scissors" && computer == "paper")) {
            std::cout << "You win!\n";
            return 0;
        } else {
            std::cout << "Computer wins!\n";
            return -1;
        }
    }

};


class TicTacToe :public Game {
public:
    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

    void play() {
        while (!isGameOver()) {
            printBoard();
            makeMove();
            switchPlayer();
        }

        printResult();
    }

private:
    //int score_p; 
    std::vector<std::vector<char>> board;
    char currentPlayer;

    void printBoard() const {
        std::cout << "-------------\n";
        for (const auto& row : board) {
            std::cout << "| ";
            for (char cell : row) {
                std::cout << cell << " | ";
            }
            std::cout << "\n-------------\n";
        }
    }

    void makeMove() {
        int row, col;
        do {
            std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            std::cin >> row >> col;
        } while (!isValidMove(row, col));

        board[row - 1][col - 1] = currentPlayer;
    }

    bool isValidMove(int row, int col) const {
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            std::cout << "Invalid move. Try again.\n";
            return false;
        }
        return true;
    }

    bool isGameOver() const {
        return checkWin() || isBoardFull();
    }

    bool checkWin() const {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
                return true;
            }
        }

        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
            return true;
        }

        return false;
    }

    bool isBoardFull() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void printResult() const {
        printBoard();
        if (checkWin()) {
            std::cout << "Player " << currentPlayer << " wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    //public: score=score_p;
};

class SnakeGame : public Game {
public:
    int score;
    SnakeGame() : gameOver(false), score(0), width(20), height(10), snakeX(0), snakeY(0), fruitX(0), fruitY(0), direction('R') {
        // Initialize the snake and fruit positions
        snake.push_back({snakeX, snakeY});
        generateFruit();
    }

    void play() {
        while (!gameOver) {
            display();
            input();
            move();
            checkCollision();
            checkFruit();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Adjust speed of the game
        }

        std::cout << "Game Over! Your score is: " << score << std::endl;
    }

private:
    bool gameOver;
    //int score;
    int width;
    int height;
    int snakeX, snakeY;
    int fruitX, fruitY;
    char direction;
    std::vector<std::pair<int, int>> snake;

    void generateFruit() {
        srand(time(nullptr));
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    void display() {
        system("cls");  // Clear console

        for (int i = 0; i < width + 2; ++i)
            std::cout << "#";
        std::cout << std::endl;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (j == 0)
                    std::cout << "#";  // Left wall

                if (i == snakeY && j == snakeX)
                    std::cout << "O";  // Snake head
                else if (i == fruitY && j == fruitX)
                    std::cout << "F";  // Fruit
                else {
                    bool printSnakeBody = false;
                    for (auto &segment : snake) {
                        if (segment.first == j && segment.second == i) {
                            std::cout << "o";  // Snake body
                            printSnakeBody = true;
                        }
                    }
                    if (!printSnakeBody)
                        std::cout << " ";
                }

                if (j == width - 1)
                    std::cout << "#";  // Right wall
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width + 2; ++i)
            std::cout << "#";
        std::cout << std::endl;

        std::cout << "Score:" << score << std::endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    direction = 'L';
                    break;
                case 'd':
                    direction = 'R';
                    break;
                case 'w':
                    direction = 'U';
                    break;
                case 's':
                    direction = 'D';
                    break;
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }

    void move() {
        int prevX = snake[0].first;
        int prevY = snake[0].second;
        int tempX, tempY;
        snake[0].first = snakeX;
        snake[0].second = snakeY;

        for (int i = 1; i < snake.size(); ++i) {
            tempX = snake[i].first;
            tempY = snake[i].second;
            snake[i].first = prevX;
            snake[i].second = prevY;
            prevX = tempX;
            prevY = tempY;
        }

        switch (direction) {
            case 'L':
                --snakeX;
                break;
            case 'R':
                ++snakeX;
                break;
            case 'U':
                --snakeY;
                break;
            case 'D':
                ++snakeY;
                break;
        }
    }

    void checkCollision() {
        if (snakeX < 0 || snakeY < 0 || snakeX >= width || snakeY >= height)
            gameOver = true;

        for (auto &segment : snake) {
            if (segment.first == snakeX && segment.second == snakeY)
                gameOver = true;
        }qw w
    }

    void checkFruit() {
        if (snakeX == fruitX && snakeY == fruitY) {
            score += 10;
            snake.push_back({-1, -1});  // Add a new segment outside the visible area
            generateFruit();
        }
    }
};

void displayFileContent() {
    ifstream inputFile("gamingHub.txt");

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    int choice=0;
    int score1=0;
    int score2=0;
    int score3=0;


    cout<<"Welcome to gamingHub"<<endl;
    cout<<"Enter your choice (1:RockPaperScissor,2:snakegame,3:Tic Tac Toe,4:check previous scores)";
    cin>>choice;

    switch(choice){
        case 1:{
        RockPaperScissors rpsGame;
        rpsGame.play();
        score1=rpsGame.score;
        break;}

        case 2:{
        SnakeGame snakeGame;
        snakeGame.play();
        score2=snakeGame.score;
        break;}

        case 3:
        {TicTacToe game;
        game.play();
        break;}

        case 4:
            displayFileContent( );
            break;

        default:
            cout << "Invalid choice" << endl;
            break;

    }

    // Get the current time point
    auto currentTime = chrono::system_clock::now();
    // Convert the time point to a time_t object
    time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);
    // Convert the time_t object to a tm structure (for local time)
    tm* localTime = localtime(&currentTime_t);

    ofstream outputFile("gamingHub.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Date and Time: " <<asctime(localTime)<< endl;
        outputFile << "RockPaperScissor score: " <<score1<< endl;
        outputFile << "snake game score: " <<score2<< endl;
        outputFile << "SnakeGame score: " <<score3<< endl;
        outputFile.close();
    } else {
        cerr << "Unable to open file for appending." << endl;
    }

    return 0;
}
