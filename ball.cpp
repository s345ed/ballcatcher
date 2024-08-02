#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
const int screenWidth = 640;
const int screenHeight = 480;
const int paddleWidth = 100;
const int paddleHeight = 10;
const int paddleSpeed = 20;
const int ballRadius = 10;
int ballSpeed = 5;
void drawPaddle(int x);
void drawBall(int x, int y);
void displayScore(int score, int level);
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int paddleX = screenWidth / 2 - paddleWidth / 2;
    int ballX = rand() % (screenWidth - 2 * ballRadius) + ballRadius;
    int ballY = ballRadius;
    int ballDirectionX = 1;
    int score = 0;
    int level = 1;
    int consecutiveHits = 0;
    char ch;
    srand(time(0));
    while (true) {
        cleardevice();
        drawPaddle(paddleX);
        drawBall(ballX, ballY);
        displayScore(score, level);
        ballY += ballSpeed;
        ballX += ballDirectionX * ballSpeed;
        if (ballY + ballRadius >= screenHeight - paddleHeight &&
            ballX >= paddleX && ballX <= paddleX + paddleWidth) {
            ballY = ballRadius;
            ballX = rand() % (screenWidth - 2 * ballRadius) + ballRadius;
            score += 1 + consecutiveHits;
            consecutiveHits++;
            if (score % 10 == 0) {
                level++;
                ballSpeed += 2; 
            }
        } else if (ballY - ballRadius > screenHeight) {
            outtextxy(screenWidth / 2 - 50, screenHeight / 2, "Game Over!");
            getch();
            break;
        }
        if (ballX - ballRadius <= 0 || ballX + ballRadius >= screenWidth) {
            ballDirectionX *= -1;
        }
        if (kbhit()) {
            ch = getch();
            if (ch == 75) { 
                paddleX -= paddleSpeed;
                if (paddleX < 0) paddleX = 0;
            }
            if (ch == 77) { 
                paddleX += paddleSpeed;
                if (paddleX > screenWidth - paddleWidth) paddleX = screenWidth - paddleWidth;
            }
        }
        delay(30);
    }
    closegraph();
    return 0;
}
void drawPaddle(int x)
{
    setfillstyle(SOLID_FILL, BLUE);
    bar(x, screenHeight - paddleHeight, x + paddleWidth, screenHeight);
}
void drawBall(int x, int y)
{
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y, ballRadius, ballRadius);
}
void displayScore(int score, int level)
{
    char scoreText[30];
    sprintf(scoreText, "Score: %d  Level: %d", score, level);
    outtextxy(10, 10, scoreText);
}
