#include<bangtal.h>
#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>

TimerID timer1;
SceneID room;
ObjectID startButton, endButton;
ObjectID picture[10];
int N, M, n, m, z;
int X[9] = { 0,300,600,0,300,600,0,300,600 };
int Y[9] = { 600,600,600,300,300,300,0,0,0 };

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool show) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (show) {
		showObject(object);
	}
	return object;
}

void endGame(bool success) {
	if (success == true) {
		showMessage("성공~~~");
	}
	else {
		showMessage("헉,실패!!!");
	}

	setObjectImage(startButton, "restart.png");
	showObject(startButton);
	showObject(endButton);

	stopTimer(timer1);
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		endGame(false);
	}
}

void go(int x) {
	int b = x + 1;
	char filename[10];
	sprintf_s(filename, "%d.png", b);
	if (x != 8) {
		picture[x] = createObject(filename, room, N, M, true);
		picture[8] = createObject("9.png", room, X[x], Y[x], true);
		n = N, m = M;
		N = X[x], M = Y[x];
		X[x] = n, Y[x] = m;
	}

}



bool end() {
	bool end = false;
	if (X[0] == 0 && Y[0] == 600) {
		if (X[1] == 300 && Y[1] == 600) {
			if (X[2] == 600 && Y[2] == 600) {
				if (X[3] == 0 && Y[3] == 300) {
					if (X[4] == 300 && Y[4] == 300) {
						if (X[5] == 600 && Y[5] == 300) {
							if (X[6] == 0 && Y[6] == 0) {
								if (X[7] == 300 && Y[7] == 0) {
									if (X[8] == 600 && Y[8] == 0) {
										end = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return end;
}

bool movable(int v) {
	int a, b, c, d;
	a = N + 300, b = N - 300;
	c = M - 300, d = M + 300;
	if (X[v] == a && Y[v] == M)return true;
	if (X[v] == b && Y[v] == M)return true;
	if (X[v] == N && Y[v] == c)return true;
	if (X[v] == N && Y[v] == d) return true;
	return false;
}

void startGame() {
	hideObject(endButton);
	hideObject(startButton);
	N = 600, M = 0;
	go(rand() % 8);
	go(0);
	go(rand() % 8);
	go(4);
	end();
	setTimer(timer1, 300.f);
	startTimer(timer1);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		startGame();
	}
	else if (object == endButton) {
		endGame();
	}
	else if (object == picture[0]) {

		if (movable(0)) {
			picture[0] = createObject("1.png", room, N, M, true);
			go(0);
			end();
		}

	}
	else if (object == picture[1]) {

		if (movable(1)) {
			picture[1] = createObject("2.png", room, N, M, true);
			go(1);
			end();
		}
	}
	else if (object == picture[2]) {

		if (movable(2)) {
			picture[2] = createObject("3.png", room, N, M, true);
			go(2);
			end();
		}
	}
	else if (object == picture[3]) {
		if (movable(3)) {
			picture[3] = createObject("4.png", room, N, M, true);
			go(3);
			end();
		}
	}
	else if (object == picture[4]) {
		if (movable(4)) {
			picture[4] = createObject("5.png", room, N, M, true);
			go(4);
			end();
		}
	}
	else if (object == picture[5]) {
		if (movable(5)) {
			picture[5] = createObject("6.png", room, N, M, true);
			go(5);
			end();
		}
	}
	else if (object == picture[6]) {
		if (movable(6)) {
			picture[6] = createObject("7.png", room, N, M, true);
			go(6);
			end();
		}
	}
	else if (object == picture[7]) {
		if (movable(7)) {
			picture[7] = createObject("8.png", room, N, M, true);
			go(7);
			end();
		}
	}
	else if (object == picture[8]) {
		if (movable(8)) {
			picture[8] = createObject("9.png", room, N, M, true);
			go(8);
			end();
		}
	}
	if (end() == true) {
		stopTimer(timer1);
		endGame(end());
		startButton = createObject("restart.png", room, 410, 750, true);
		endButton = createObject("end.png", room, 410, 700, true);
	}
}



int main() {
	setMouseCallback(mouseCallback);
	room = createScene("room", "배경.png");

	picture[0] = createObject("1.png", room, 0, 600, true);
	picture[1] = createObject("2.png", room, 300, 600, true);
	picture[2] = createObject("3.png", room, 600, 600, true);
	picture[3] = createObject("4.png", room, 0, 300, true);
	picture[4] = createObject("5.png", room, 300, 300, true);
	picture[5] = createObject("6.png", room, 600, 300, true);
	picture[6] = createObject("7.png", room, 0, 0, true);
	picture[7] = createObject("8.png", room, 300, 0, true);
	picture[8] = createObject("9.png", room, 600, 0, true);

	startButton = createObject("start.png", room, 410, 750, true);
	endButton = createObject("end.png", room, 410, 700, false);

	timer1 = createTimer(300.f);

	showTimer(timer1);
	startGame(room);
}
