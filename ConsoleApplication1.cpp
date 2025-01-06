#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int EGG_SIZE = 30;
const int PAN_WIDTH = 210;
const int PAN_HEIGHT = 170;
const int EASY_MODE_DURATION = 15;
const int MODERATE_MODE_DURATION = 30;
const int MAX_EGGS = 100;
enum EggType { GOOD, ROTTEN, GOLDEN };
struct Egg {
    CircleShape shape;
    EggType type = GOOD;
    bool active = false;};
void drawScore(RenderWindow& window, Font& font, int score, float time_passed, const string& difficulty) {
    Text score_text;
    score_text.setFont(font);
    score_text.setString("Score: " + to_string(score));
    score_text.setCharacterSize(24);
    score_text.setFillColor(Color::White);
    score_text.setPosition(10, 10);
    window.draw(score_text);
    Text time;
    time.setFont(font);
    time.setString("Time: " + std::to_string(static_cast<int>(time_passed)) + "s");
    time.setCharacterSize(24);
    time.setFillColor(Color::White);
    time.setPosition(10, 40);
    window.draw(time);
    Text difficulty_text;
    difficulty_text.setFont(font);
    difficulty_text.setString("Difficulty: " + difficulty);
    difficulty_text.setCharacterSize(24);
    difficulty_text.setFillColor(Color::White);
    difficulty_text.setPosition(10, 70);
    window.draw(difficulty_text);}
int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Portfolio Project: Egg Blitz");
    window.setFramerateLimit(60);
    Texture backgroundTexture, gameBackgroundTexture, panTexture;
    if (!backgroundTexture.loadFromFile("sfml_img.png") || !gameBackgroundTexture.loadFromFile("rose-petals.png") || !panTexture.loadFromFile("pan.png")) {
        std::cerr << "Could not load images" << std::endl;
        return -1;}
    SoundBuffer panSoundBuffer, splashSoundBuffer, backgroundSoundBuffer;
    if (!panSoundBuffer.loadFromFile("pansound.mp3") || !splashSoundBuffer.loadFromFile("splash.mp3") || !backgroundSoundBuffer.loadFromFile("bgg.mp3")) {
        std::cerr << "Could not load sounds" << std::endl;
        return -1;}
    Sound panSound(panSoundBuffer);
    Sound splashSound(splashSoundBuffer);
    Sound backgroundSound(backgroundSoundBuffer);
    backgroundSound.setLoop(true);
    backgroundSound.play();
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x, static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y);
    Font font;
    if (!font.loadFromFile("cccc.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;}
    RectangleShape button(Vector2f(250.0f, 100.0f));
    button.setFillColor(Color(100, 100, 255));
    button.setPosition(835.0f, 490.0f);
    Text button_text("Start", font, 40);
    button_text.setFillColor(Color::White);
    button_text.setPosition(885.0f, 510.0f);
    RectangleShape pan(Vector2f(PAN_WIDTH, PAN_HEIGHT));
    pan.setTexture(&panTexture);
    pan.setPosition(WINDOW_WIDTH / 2 - PAN_WIDTH / 2, WINDOW_HEIGHT - PAN_HEIGHT - 10);
    Egg eggs[MAX_EGGS];
    int score = 0;
    Clock gameClock, frameClock;
    bool gameStarted = false, gameOver = false;
    float eggSpeed = 150.0f;
    string difficulty = "Easy";
    srand(static_cast<unsigned int>(time(0)));
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && !gameStarted) {
                if (button.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                    gameStarted = true;
                    backgroundSound.stop();
                    backgroundSprite.setTexture(gameBackgroundTexture);
                    gameClock.restart();}}}
        if (gameStarted && !gameOver) {
            float elapsedTime = gameClock.getElapsedTime().asSeconds();
            if (elapsedTime > EASY_MODE_DURATION) {
                eggSpeed = 150.0f;
                difficulty = "Moderate"; }
            if (elapsedTime > MODERATE_MODE_DURATION) {
                eggSpeed = 200.0f;
                difficulty = "Hard";}
            if (Keyboard::isKeyPressed(Keyboard::Left) && pan.getPosition().x > 0) {
                pan.move(-10.0f, 0.0f);}
            if (Keyboard::isKeyPressed(Keyboard::Right) && pan.getPosition().x + PAN_WIDTH < WINDOW_WIDTH) {
                pan.move(10.0f, 0.0f);}
            if (rand() % 100 < 2) {
                for (int i = 0; i < MAX_EGGS; ++i) {
                    if (!eggs[i].active) {
                        eggs[i].shape.setRadius(EGG_SIZE / 2);
                        eggs[i].shape.setPosition(static_cast<float>(rand() % (WINDOW_WIDTH - EGG_SIZE)), 0.0f);
                        eggs[i].active = true;
                        int eggType = rand() % 3;
                        if (eggType == 0) {
                            eggs[i].shape.setFillColor(Color::Green);
                            eggs[i].type = GOOD; }
                        else if (eggType == 1) {
                            eggs[i].shape.setFillColor(Color::Red);
                            eggs[i].type = ROTTEN;}
                        else {
                            eggs[i].shape.setFillColor(Color::Yellow);
                            eggs[i].type = GOLDEN;}
                        break;} } }
            float deltaTime = frameClock.restart().asSeconds();
            for (int i = 0; i < MAX_EGGS; ++i) {
                if (eggs[i].active) {
                    eggs[i].shape.move(0, eggSpeed * deltaTime);
                    if (eggs[i].shape.getGlobalBounds().intersects(pan.getGlobalBounds())) {
                        if (eggs[i].type == GOOD) {
                            panSound.play();
                            score++;}
                        else if (eggs[i].type == ROTTEN) {
                            splashSound.play();
                            gameOver = true;}
                        else if (eggs[i].type == GOLDEN) {
                            panSound.play();}
                        eggs[i].active = false;}
                    else if (eggs[i].shape.getPosition().y > WINDOW_HEIGHT) {
                        eggs[i].active = false;}}}}
        window.clear();
        window.draw(backgroundSprite);
        if (!gameStarted) {
            window.draw(button);
            window.draw(button_text);}
        else {
            for (int i = 0; i < MAX_EGGS; ++i) {
                if (eggs[i].active) {
                    window.draw(eggs[i].shape);} }
            drawScore(window, font, score, gameClock.getElapsedTime().asSeconds(), difficulty);
            window.draw(pan);}
        if (gameOver) {
            Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over");
            gameOverText.setCharacterSize(48);
            gameOverText.setFillColor(Color::Yellow);
            gameOverText.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50);
            window.draw(gameOverText);
            window.draw(pan);}
        window.display();}
    return EXIT_SUCCESS;}
