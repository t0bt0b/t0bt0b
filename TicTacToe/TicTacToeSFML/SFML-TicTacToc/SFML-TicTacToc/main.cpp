#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class TTT {
private:
    sf::RenderWindow window;
    sf::Texture playfield, symbolX, symbolO;
    sf::Sprite addPlayfield, addX, addO, pieces[9];
    sf::Font font;
    sf::Text playerTurnMsg, playerWinMsg;
    sf::Event event;
    sf::IntRect squareFields[9];
    sf::Vector2i position[9];
    sf::SoundBuffer buffer;
    sf::Sound placeSound;
    char* placementList = (char*)malloc(sizeof(char) * 9);
    bool teste = false;

public:
    void loadGameWindow();
    bool loadGameFiles();
    bool loadFontFile();
    bool loadSoundFile();
    void setGameFiles();
    void whoseTurn();
    void updateWhoseTurn(int round);
    void rectCoord();
    void setRectCoord(sf::IntRect& fields, int left, int top, int width, int height);
    bool takeRound(int turn);
    bool isClicked(int fPos);
    void posPieces();
    void setPosPieces(sf::Vector2i &pos, int left, int top);
    void gameLoop();
    char winFunction(int round);
};

void TTT::loadGameWindow() {
    window.create(sf::VideoMode(700, 800), "TicTacToe", sf::Style::Close);
}

bool TTT::loadGameFiles() {
    return (playfield.loadFromFile("img/playfield.png") && symbolX.loadFromFile("img/X.png") && symbolO.loadFromFile("img/O.png"));
}

bool TTT::loadFontFile() {
    return font.loadFromFile("fonts/data-latin.ttf");
}

bool TTT::loadSoundFile() {
    return buffer.loadFromFile("sounds/placeSound.wav");
}

void TTT::setGameFiles() {
    addPlayfield.setTexture(playfield);
    addPlayfield.scale(1.f, 1.f);
    addPlayfield.setPosition(140.f, 240.f); //X Y
    
    addX.setTexture(symbolX);
    addO.setTexture(symbolO);
}

void TTT::whoseTurn() {
    playerTurnMsg.setString("Spieler 1");
    playerTurnMsg.setFont(font);
    playerTurnMsg.setCharacterSize(60);
    playerTurnMsg.setFillColor(sf::Color::Black);
    playerTurnMsg.move(225, 50);
    
    playerWinMsg.setFont(font);
    playerWinMsg.setCharacterSize(60);
    playerWinMsg.setFillColor(sf::Color::Black);
    playerWinMsg.move(165, 50);
}

void TTT::updateWhoseTurn(int round) {
    std::string message;
    message = round % 2 == 0 ? "Spieler 1" : "Spieler 2";
    playerTurnMsg.setString(message);
}

void TTT::setRectCoord(sf::IntRect& fields, int left, int top, int width, int height) {
    fields.left = left;
    fields.top = top;
    fields.width = width;
    fields.height = height;
}

void TTT::rectCoord() {
    setRectCoord(squareFields[0], 145, 245, 275, 375);
    setRectCoord(squareFields[1], 280, 245, 410, 375);
    setRectCoord(squareFields[2], 415, 245, 545, 375);

    setRectCoord(squareFields[3], 145, 380, 275, 510);
    setRectCoord(squareFields[4], 280, 380, 410, 510);
    setRectCoord(squareFields[5], 415, 380, 545, 510);

    setRectCoord(squareFields[6], 145, 515, 275, 645);
    setRectCoord(squareFields[7], 280, 515, 410, 645);
    setRectCoord(squareFields[8], 415, 515, 545, 645);
}

void TTT::setPosPieces(sf::Vector2i& pos, int left, int top) {
    pos.x = left;
    pos.y = top;
}

void TTT::posPieces() {
    setPosPieces(position[0], 145, 245);
    setPosPieces(position[1], 280, 245);
    setPosPieces(position[2], 415, 245); 

    setPosPieces(position[3], 145, 380);
    setPosPieces(position[4], 280, 380);
    setPosPieces(position[5], 415, 380);

    setPosPieces(position[6], 145, 515);
    setPosPieces(position[7], 280, 515);
    setPosPieces(position[8], 415, 515);

}

bool TTT::isClicked(int fPos) {
    return (event.mouseButton.x >= squareFields[fPos].left
        && event.mouseButton.x <= squareFields[fPos].width
        && event.mouseButton.y >= squareFields[fPos].top
        && event.mouseButton.y <= squareFields[fPos].height);

}

char TTT::winFunction(int round) {
    short xCount = 0, oCount = 0;

    //first row
    for (int i = 0; i <= 2; i++) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
    //second row
    for (int i = 3; i <= 5; i++) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
    //third row
    for (int i = 6; i <= 8; i++) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;

    //first column
    for (int i = 0; i <= 6; i+=3) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
    //second column
    for (int i = 1; i <= 7; i += 3) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
    //third column
    for (int i = 2; i <= 8; i += 3) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;

    //diagonal \ 
    for (int i = 0; i <= 8; i += 4) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
    //diagonal /
    for (int i = 2; i <= 6; i += 2) {
        if (placementList[i] == 'X') {
            xCount++;
            oCount = 0;
        }
        else if (placementList[i] == 'O') {
            oCount++;
            xCount = 0;
        }
        if (xCount == 3) return 'X';
        else if (oCount == 3)return 'O';
    }
    xCount = 0, oCount = 0;
}

bool TTT::takeRound(int round) {
    for (int fPos = 0; fPos < 9; fPos++) {
        if (isClicked(fPos)) {
            //std::cout << fPos << std::endl;
            if (squareFields[fPos].left != -500) {
                placeSound.play();
                pieces[round] = round % 2 == 0 ? addX : addO;
                pieces[round].move((float)position[fPos].x, (float)position[fPos].y);
                squareFields[fPos].left = -500;
                placementList[fPos] = round % 2 == 0 ? 'X' : 'O';
                std::cout << "placementList pos: " << fPos << " " << placementList[fPos] << std::endl;
                updateWhoseTurn(round);
                return true;
            }
            else {
                updateWhoseTurn(round);
                return false;
            }
        }
    }
    return false;
}

void TTT::gameLoop() {
    int round = 0;
    char proof;
    bool winnerFound = true;
    whoseTurn();
    rectCoord();
    posPieces();
    placeSound.setBuffer(buffer);
    sf::Mouse mouse;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && round < 9 && winnerFound) {
            if(takeRound(round)) {
                proof = winFunction(round);
                if (proof == 'X' || proof == 'O')winnerFound = false;
                else round++;
            }
        }
        if (winnerFound == false) {
            round % 2 == 0 ? playerWinMsg.setString("  Spieler 1\n   gewinnt") : playerWinMsg.setString("  Spieler 2\n   gewinnt");
        }
        else if (round == 9) {
            playerWinMsg.setString("Unentschieden");
            round++;
        }

        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(addPlayfield);
        winnerFound == true && round < 9 ? window.draw(playerTurnMsg) : window.draw(playerWinMsg);
        for (int i = 0; i < 9; i++) {
            window.draw(pieces[i]);
        }
        window.display();
    }
}

int main() {
    TTT game;
    game.loadGameWindow();

    if (!game.loadGameFiles()) {
        std::cout << "Fehler game.loadGameFiles()" << std::endl;
        return EXIT_FAILURE;
    }
    game.setGameFiles();

    if (!game.loadFontFile()) {
        std::cout << "Fehler game.loadFontFile()" << std::endl;
        return EXIT_FAILURE;
    }

    if (!game.loadSoundFile()) {
        std::cout << "Fehler game.loadSoundFile()" << std::endl;
        return EXIT_FAILURE;
    }

    game.gameLoop();

    return EXIT_SUCCESS;
}
