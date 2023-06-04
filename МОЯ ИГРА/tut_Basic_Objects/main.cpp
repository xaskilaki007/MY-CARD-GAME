/*
Описание игры: в данной игре происходит анимация раздачи карт из колоды, присутствует 3d эффект, 
а также случайная выдача карт двум сторонам. Есть подпись. Есть музыка.
В случае, если вам не попались все персонажи, перезапустите игру, так как в ней 3 персонажа.


ВАЖНО! Чтобы заработала музыка потаскайте окно по экрану.
*/

#include <windows.h>
#include "GL/bass.h"
#include "GL/freeglut.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
struct Position {
	GLfloat x, y;
};
struct Figure {
	Position pos;
	bool isRight;
};
array<Position, 100> graph;
void plotGraph();
void renderScene(void);
void CardTable();

void Myhp();
void Myhp1();
void Enyhp();
void Enyhp1();

void ArchmansCard(double t, double x, double y, Figure* f);
void RiderCard(double t, double x, double y, Figure* f);
void SwordsmansCard(double t, double x, double y, Figure* f);

void Cards();
void proccessKey(unsigned char key, int x, int y);
Figure hero = { {0.0},false };

//Глобальные переменные
double Alfa = 0; double T0 = 3000; double DT = 100; double Y0 = 0.6; double Cx = -0.45, Cy = 0;
const int nFig = 6;
double moveT[nFig];
int figType[nFig];
double X[nFig], Y[nFig];

//Рандомайзер координат раздачи карт
void init_game() { 
	srand(time(NULL));
	for (int i=0; i < nFig; i++) {
		moveT[i] = 0;
		figType[i] = rand() % 3;
	}
	X[0] = -0.6, Y[0] = Y0;
	X[1] = 0.2, Y[1] = Y0;
	X[2] = -0.4, Y[2] = Y0;
	X[3] = 0.4, Y[3] = Y0;
	X[4] = -0.2, Y[4] = Y0;
	X[5] = 0.6, Y[5] = Y0;
}
//Функция для анимации, нужна для плавной анимации
void animate(int value) {
	for (int i = 0; i < nFig; ++i) {
		moveT[i] += DT;
		if (moveT[i] < T0)
			break;
		else
			moveT[i] = T0;
	}

	glutPostRedisplay();
	glutTimerFunc(DT, animate, 0);
}
//МУЗЫКА
void Sound()
{
	PlaySound("1.wav", NULL, SND_ASYNC);
}
//МУЗЫКА
void track() {
	Sound();
}
//Главная функция
int main(int argc, char* argv[])
{
	init_game();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(777, 666);
	glutCreateWindow("Lesson - Time Interactive");
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(proccessKey);
	glutTimerFunc(DT, animate, 0);

	glutMainLoop();
	return 0;
}
//Функция для создания текста
void RenderString(float x, float y, void* font, const unsigned char* s)
{
	char* c;

	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);

	glutBitmapString(font, s);
}
//Главная функция отрисовки
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	Figure f = { {0,0},false };
	
	plotGraph();
	f.pos.x = 0;
	f.pos.y = 0;
	CardTable();
	Myhp();
	Myhp1();
	Enyhp();
	Enyhp1();
	//Для рандома
	for (int i = 0; i < nFig; i++) {
		auto t = figType[i];
		switch (t) {
		case 0:
			ArchmansCard(moveT[i], X[i], Y[i],0);
			break;
		case 1:
			RiderCard(moveT[i], X[i], Y[i],0);
			break;
		case 2:
			SwordsmansCard(moveT[i], X[i], Y[i], &hero);
			break;
		}
	}
	Cards();
	//Вывод текста
	RenderString(0.3f, 0.3f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Card Animation \n by Peter Shpakov");

	track();
	glPopMatrix();
	glutSwapBuffers();
}
//Голубой карточный стол
void CardTable() {	
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2f(-0.87838, 0.94661);	glVertex2f(0.85943, 0.94661);
	glVertex2f(0.85943, -0.45932);	glVertex2f(-0.87838, -0.45932);
	glColor3ub(0, 150, 140);//Голубой фон
	glVertex2f(-0.84838, 0.91661); glVertex2f(0.82943, 0.91661);
	glVertex2f(0.82943, -0.42932); glVertex2f(-0.84838, -0.42932);
	glColor3ub(0, 0, 0);//Линия по середине
	glVertex2f(-0.01895, 0.91661); glVertex2f(-0.017, 0.91661);
	glVertex2f(-0.017, -0.42932); glVertex2f(-0.01895, -0.42932);
	glEnd();
	glPopMatrix();
}
//Моё HP (фон черный)
void Myhp() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3ub(250, 250, 250);
	glVertex2f(-0.67189, -0.50046); glVertex2f(-0.33436, -0.50046);
	glVertex2f(-0.33436, -0.66055); glVertex2f(-0.67189, -0.66055);
	glColor3ub(0, 0, 0);
	glVertex2f(-0.65867, -0.51368); glVertex2f(-0.34494, -0.51368);
	glVertex2f(-0.34494, -0.64997); glVertex2f(-0.65867, -0.64997);
	glEnd();
	glPopMatrix();
}
//Моё HP (Красное)
void Myhp1() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3ub(250, 0, 0);
	glVertex2f(-0.63643, -0.53854); glVertex2f(-0.58922, -0.53855);
	glVertex2f(-0.58922, -0.62403); glVertex2f(-0.63643, -0.62403);
	glEnd();
	glPopMatrix();
}
//HP врага(чёрное)
void Enyhp() {
	glPushMatrix();
	glTranslated(-0.2, 0, 0);
	glBegin(GL_QUADS);
	glColor3ub(250, 250, 250);
	glVertex2f(0.53133, -0.50046); glVertex2f(0.86506, -0.50046);
	glVertex2f(0.86506, -0.66055); glVertex2f(0.53133, -0.66055);
	glColor3ub(0, 0, 0);
	glVertex2f(0.54133, -0.51368); glVertex2f(0.85506, -0.51368);
	glVertex2f(0.85506, -0.64997); glVertex2f(0.54133, -0.64997);
	glEnd();
	glPopMatrix();
}
//Врага HP (Красное)
void Enyhp1() {
	glPushMatrix();
	glTranslated(-0.2, 0, 0);
	glBegin(GL_QUADS);
	glColor3ub(250, 0, 0);
	glVertex2f(0.56357, -0.53854); glVertex2f(0.61078, -0.53855);
	glVertex2f(0.61078, -0.62403); glVertex2f(0.56357, -0.62403);
	glEnd();
	glPopMatrix();
}
//Карта мечника (SwordsmansCard)
void SwordsmansCard(double t, double x, double y, Figure* f) {
	glPushMatrix();
	glTranslatef(f->pos.x, f->pos.y, 0);//Это для передвижения клавиатурой
	

	
	double c = t / T0;
	
	glTranslated(Cx + c * (x - Cx), Cy + c * (y - Cy), 0);
	
	glRotated(180 * c + 180, 1, 0, 0);
	glScaled(0.6, 0.6, 0);//Это для уменьшения персонажа
	glTranslated((0.2754 + 0.02511) / 2, -(0.16478 + 0.85782) / 2, 0);//Начальное положение карты мечника 1,2
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);//карта фон
	glVertex2f(-0.2754, 0.85782); glVertex2f(-0.02511, 0.85782);
	glVertex2f(-0.02511, 0.16478); glVertex2f(-0.2754, 0.16478);
	glColor3ub(100, 100, 100);//карта фон
	glVertex2f(-0.26695, 0.85005); glVertex2f(-0.03494, 0.85005);
	glVertex2f(-0.03494, 0.17478); glVertex2f(-0.26695, 0.17478);

	if (c >= 0.5) {
	glColor3ub(0, 0, 0);//шлем
	glVertex2f(-0.20855, 0.78693); glVertex2f(-0.08262, 0.79864);
	glVertex2f(-0.10507, 0.66393); glVertex2f(-0.22319, 0.6649);
	glColor3ub(100, 100, 100);//Решетка на шлеме
	glVertex2f(-0.19744, 0.75847); glVertex2f(-0.18564, 0.75889);
	glVertex2f(-0.18607, 0.68897); glVertex2f(-0.20123, 0.68981);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.17048, 0.75889); glVertex2f(-0.16, 0.76);
	glVertex2f(-0.157, 0.68981); glVertex2f(-0.17216, 0.68981);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.14, 0.76); glVertex2f(-0.12541, 0.76058);
	glVertex2f(-0.12667, 0.68897); glVertex2f(-0.13847, 0.68981);
	glColor3ub(250, 200, 0);//Шея
	glVertex2f(-0.18805, 0.67173); glVertex2f(-0.16364, 0.67173);
	glVertex2f(-0.15974, 0.58583); glVertex2f(-0.19242, 0.5859);
	glColor3ub(0, 0, 0);//Туловище
	glVertex2f(-0.24875, 0.59899); glVertex2f(-0.09203, 0.59991);
	glVertex2f(-0.13734, 0.44689); glVertex2f(-0.21084, 0.44642);
	glColor3ub(250, 150, 0);//Руки: левая/правая плечо-предплечье-кулак-мечь
	glVertex2f(-0.09831, 0.59537); glVertex2f(-0.0759, 0.54387);
	glVertex2f(-0.08853, 0.53629); glVertex2f(-0.10423, 0.57464);
	glColor3ub(250, 150, 0);//Предплечье
	glVertex2f(-0.0759, 0.54387); glVertex2f(-0.06361, 0.5245);
	glVertex2f(-0.06705, 0.51787); glVertex2f(-0.08853, 0.53629);
	glColor3ub(250, 150, 0);//кулак
	glVertex2f(-0.07629, 0.52772); glVertex2f(-0.05595, 0.51852);
	glVertex2f(-0.05287, 0.49383); glVertex2f(-0.08122, 0.49563);
	glColor3ub(0, 0, 0);//рукоять
	glVertex2f(-0.05911, 0.53067); glVertex2f(-0.04836, 0.52376);
	glVertex2f(-0.06742, 0.50323); glVertex2f(-0.06814, 0.51221);
	glColor3ub(0, 0, 0);
	glVertex2f(-0.05896, 0.54576); glVertex2f(-0.0273, 0.50965);
	glVertex2f(-0.03573, 0.50263); glVertex2f(-0.06722, 0.53811);
	glColor3ub(0, 0, 0);//Клинок
	glVertex2f(-0.02014, 0.57182); glVertex2f(-0.00711, 0.56014);
	glVertex2f(-0.04306, 0.52067); glVertex2f(-0.05264, 0.53531);
	glColor3ub(0, 0, 0);
	glVertex2f(-0.02014, 0.57182); glVertex2f(0, 0.58);
	glVertex2f(-0.00711, 0.56014); glVertex2f(-0.02539, 0.55961);
	glColor3ub(250, 200, 0);//Левая рука
	glVertex2f(-0.22262, 0.59467); glVertex2f(-0.07595, 0.50663);
	glVertex2f(-0.08122, 0.49563); glVertex2f(-0.23716, 0.57261);
	glColor3ub(0, 0, 0);//левая нога сверху вниз
	glVertex2f(-0.20955, 0.46133); glVertex2f(-0.19193, 0.46207);
	glVertex2f(-0.19487, 0.36224); glVertex2f(-0.21322, 0.36297);
	glColor3ub(0, 0, 0);//1левая нога сверху вниз
	glVertex2f(-0.21925, 0.36656); glVertex2f(-0.18695, 0.37463);
	glVertex2f(-0.21072, 0.26742); glVertex2f(-0.22822, 0.26832);
	glColor3ub(0, 0, 0);//2левая нога сверху вниз
	glVertex2f(-0.21925, 0.36656); glVertex2f(-0.18695, 0.37463);
	glVertex2f(-0.21072, 0.26742); glVertex2f(-0.22822, 0.26832);
	glColor3ub(0, 0, 0);//3левая нога сверху вниз
	glVertex2f(-0.22158, 0.28484); glVertex2f(-0.22158, 0.28484);
	glVertex2f(-0.18759, 0.2352); glVertex2f(-0.25773, 0.23844);
	glColor3ub(0, 0, 0);//1правая нога сверху вниз
	glVertex2f(-0.16995, 0.46148); glVertex2f(-0.14249, 0.47136);
	glVertex2f(-0.14798, 0.36481); glVertex2f(-0.16995, 0.36371);
	glColor3ub(0, 0, 0);//2правая нога сверху вниз
	glVertex2f(-0.16995, 0.36371); glVertex2f(-0.14798, 0.36481);
	glVertex2f(-0.15958, 0.26742); glVertex2f(-0.14523, 0.26607);
	glColor3ub(0, 0, 0);//3правая нога сверху вниз
	glVertex2f(-0.15737, 0.28484); glVertex2f(-0.15737, 0.28484);
	glVertex2f(-0.12122, 0.23466); glVertex2f(-0.17518, 0.23574);
	}
	glEnd();
	glPopMatrix();
}
//Карта лучника (ArchmansCard)
void ArchmansCard(double t, double x, double y, Figure* f){
	glPushMatrix();
	
	
	double c = t / T0;

	glTranslated(Cx + c * (x - Cx), Cy + c * (y - Cy), 0);
	
	glRotated(180 * c + 180, 1, 0, 0);
	glScaled(0.6, 0.6, 0);//Это для уменьшения персонажа
	glTranslated(-(0.2046 + 0.45489) / 2, -(0.16478 + 0.85782) / 2, 0);//Начальное положение лучника 1, 2
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);//карта фон
	glVertex2f(0.2046, 0.85782); glVertex2f(0.45489, 0.85782);
	glVertex2f(0.45489, 0.16478); glVertex2f(0.2046, 0.16478);
	glColor3ub(100, 100, 100);//карта фон
	glVertex2f(0.21118, 0.85169); glVertex2f(0.44822, 0.85169);
	glVertex2f(0.44822, 0.17303); glVertex2f(0.21118, 0.17303);

	if(c>0.5){
	glColor3ub(50, 50, 50);//Голова с низу в верх
	glVertex2f(0.2114, 0.76245); glVertex2f(0.38314, 0.70384);
	glVertex2f(0.36191, 0.67236); glVertex2f(0.24188, 0.68274);

	glVertex2f(0.22787, 0.81654); glVertex2f(0.34932, 0.79241);
	glVertex2f(0.40984, 0.77284); glVertex2f(0.2114, 0.76245);
	glColor3ub(0, 0, 0);//Глаз
	glVertex2f(0.32781, 0.83481); glVertex2f(0.38907, 0.82263);
	glVertex2f(0.40984, 0.77284); glVertex2f(0.22787, 0.81654);
	glColor3ub(0, 0, 0);//Зубы
	glVertex2f(0.30437, 0.77916); glVertex2f(0.32801, 0.77113);
	glVertex2f(0.30704, 0.74704); glVertex2f(0.27001, 0.77292);

	glVertex2f(0.32623, 0.78452); glVertex2f(0.35121, 0.77247);
	glVertex2f(0.35835, 0.74302); glVertex2f(0.32087, 0.77292);

	glVertex2f(0.36683, 0.78006); glVertex2f(0.39404, 0.77292);
	glVertex2f(0.39628, 0.74615); glVertex2f(0.35121, 0.77247);

	glVertex2f(0.27224, 0.73187); glVertex2f(0.31329, 0.74079);
	glVertex2f(0.3066, 0.71938); glVertex2f(0.28, 0.72);

	glVertex2f(0.32623, 0.71849); glVertex2f(0.35166, 0.73589);
	glVertex2f(0.34229, 0.70644); glVertex2f(0.32087, 0.70912);

	glVertex2f(0.35924, 0.70599); glVertex2f(0.38869, 0.73142);
	glVertex2f(0.37486, 0.70153); glVertex2f(0.35701, 0.69618);
	glColor3ub(250, 200, 0);//Левая рука
	glVertex2f(0.30179, 0.59797); glVertex2f(0.3521, 0.63074);
	glVertex2f(0.35622, 0.6166); glVertex2f(0.30706, 0.58025);

	glVertex2f(0.3521, 0.63074); glVertex2f(0.45725, 0.62457);
	glVertex2f(0.45774, 0.61552); glVertex2f(0.35622, 0.6166);
	glColor3ub(0, 0, 0);//Тело
	glVertex2f(0.27505, 0.68454); glVertex2f(0.35318, 0.57692);
	glVertex2f(0.35387, 0.42665); glVertex2f(0.28388, 0.43626);
	glColor3ub(220, 200, 0);//Правая рука
	glVertex2f(0.30233, 0.61189); glVertex2f(0.39271, 0.61487);
	glVertex2f(0.40076, 0.58829); glVertex2f(0.29382, 0.59064);
	glColor3ub(250, 170, 0);//Правая нога
	glVertex2f(0.32233, 0.48189); glVertex2f(0.35233, 0.47989);
	glVertex2f(0.37233, 0.25989); glVertex2f(0.34233, 0.26189);
	glColor3ub(250, 170, 0);//Левая нога
	glVertex2f(0.28624, 0.48545); glVertex2f(0.31102, 0.48327);
	glVertex2f(0.31611, 0.25986); glVertex2f(0.2903, 0.26323);
	glColor3ub(0, 0, 0);//ЛУК
	glVertex2f(0.45194, 0.76071); glVertex2f(0.46356, 0.76071);
	glVertex2f(0.46568, 0.60312); glVertex2f(0.44932, 0.60503);
	glColor3ub(0, 0, 0);//ЛУК
	glVertex2f(0.44932, 0.60503); glVertex2f(0.46568, 0.60312);
	glVertex2f(0.41927, 0.44575); glVertex2f(0.40332, 0.45099);
	glColor3ub(0, 0, 0);//Тетева
	glVertex2f(0.45194, 0.76071); glVertex2f(0.46356, 0.76071);
	glVertex2f(0.40076, 0.58829); glVertex2f(0.39271, 0.61487);
	glColor3ub(0, 0, 0);//Тетева
	glVertex2f(0.39271, 0.61487); glVertex2f(0.40076, 0.58829);
	glVertex2f(0.41927, 0.44575); glVertex2f(0.40332, 0.45099);
	glColor3ub(0, 0, 200);//Стрела
	glVertex2f(0.39271, 0.61487); glVertex2f(0.47984, 0.60608);
	glVertex2f(0.4796, 0.60108); glVertex2f(0.40345, 0.61156);
	glColor3ub(250, 0, 200);//Наконечник
	glVertex2f(0.46568, 0.60312); glVertex2f(0.47984, 0.60608);
	glVertex2f(0.48824, 0.60297); glVertex2f(0.4796, 0.60108);
	glColor3ub(250, 0, 0);//Тяги бархатные левые
	glVertex2f(0.26907, 0.31575); glVertex2f(0.3214, 0.31255);
	glVertex2f(0.3198, 0.21856); glVertex2f(0.2632, 0.22497);
	glColor3ub(250, 0, 0);//Тяги бархатные левые
	glVertex2f(0.19751, 0.23992); glVertex2f(0.30966, 0.27303);
	glVertex2f(0.33155, 0.20682); glVertex2f(0.17242, 0.20735);
	glColor3ub(250, 0, 0);//Тяги бархатные правые
	glVertex2f(0.33102, 0.31255); glVertex2f(0.39349, 0.31736);
	glVertex2f(0.41485, 0.22657); glVertex2f(0.33956, 0.22284);
	glColor3ub(250, 0, 0);//Тяги бархатные правые
	glVertex2f(0.33796, 0.27463); glVertex2f(0.47039, 0.25488);
	glVertex2f(0.5, 0.2); glVertex2f(0.35, 0.2);
	}
	glEnd();
	glPopMatrix();
}
//Карта наездника (RiderCard)
void RiderCard(double t, double x, double y, Figure* f) {
	glPushMatrix();
	
	double c = t / T0;
	glTranslated(Cx + c * (x - Cx), Cy + c * (y - Cy), 0);
	
	glRotated(180 * c + 180, 1, 0, 0);
	glScaled(0.6, 0.6, 0);
	glTranslated((0.62316 + 0.36511) / 2, -(0.16478 + 0.85782) / 2, 0);//Начальное положение наездника 1, 2
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);//карта фон
	glVertex2f(-0.62316, 0.85782); glVertex2f(-0.36511, 0.85782);
	glVertex2f(-0.36511, 0.16478); glVertex2f(-0.62316, 0.16478);
	glColor3ub(100, 100, 100);//карта фон2
	glVertex2f(-0.61759, 0.85169); glVertex2f(-0.37423, 0.85169);
	glVertex2f(-0.37178, 0.17303); glVertex2f(-0.61759, 0.17303);
	if(c>0.5){
	glColor3ub(0, 0, 0);//морда лошади1
	glVertex2f(-0.66243, 0.77805); glVertex2f(-0.58634, 0.74737);
	glVertex2f(-0.6747, 0.69706); glVertex2f(-0.68575, 0.71669);
	glColor3ub(0, 0, 0);//морда лошади2
	glVertex2f(-0.56532, 0.8028); glVertex2f(-0.48325, 0.70319);
	glVertex2f(-0.58634, 0.74737); glVertex2f(-0.66243, 0.77805);
	glColor3ub(0, 0, 0);//шея лошади1
	glVertex2f(-0.58634, 0.74737); glVertex2f(-0.48325, 0.70319);
	glVertex2f(-0.59984, 0.55101); glVertex2f(-0.58634, 0.74737);
	glColor3ub(0, 0, 0);//шея лошади2
	glVertex2f(-0.48325, 0.70319); glVertex2f(-0.48939, 0.55347);
	glVertex2f(-0.5532, 0.48597); glVertex2f(-0.59984, 0.55101);
	glColor3ub(250, 250, 250);//правая передняя нога
	glVertex2f(-0.61579, 0.57433); glVertex2f(-0.5532, 0.53629);
	glVertex2f(-0.62684, 0.50438); glVertex2f(-0.65261, 0.52402);
	glColor3ub(0, 0, 0);//тело лошади
	glVertex2f(-0.48939, 0.55347); glVertex2f(-0.3853, 0.40145);
	glVertex2f(-0.45582, 0.3325); glVertex2f(-0.5532, 0.48597);
	glColor3ub(250, 250, 250);//левая нога лошади
	glVertex2f(-0.47449, 0.37529); glVertex2f(-0.43928, 0.35203);
	glVertex2f(-0.55433, 0.2244); glVertex2f(-0.56753, 0.24578);
	glColor3ub(250, 250, 250);//правая нога лошади1
	glVertex2f(-0.44385, 0.37325); glVertex2f(-0.39582, 0.40547);
	glVertex2f(-0.43319, 0.28476); glVertex2f(-0.44573, 0.28901);
	glColor3ub(250, 250, 250);//правая нога лошади2
	glVertex2f(-0.44573, 0.28901); glVertex2f(-0.43319, 0.28476);
	glVertex2f(-0.4427, 0.22692); glVertex2f(-0.4726, 0.22503);
	glColor3ub(250, 250, 250);//хвост лошади1
	glVertex2f(-0.41869, 0.43531); glVertex2f(-0.35712, 0.40344);
	glVertex2f(-0.38861, 0.37899); glVertex2f(-0.41258, 0.41368);
	glColor3ub(250, 250, 250);//хвост лошади1
	glVertex2f(-0.38861, 0.37899); glVertex2f(-0.35712, 0.40344);
	glVertex2f(-0.37392, 0.30498); glVertex2f(-0.39525, 0.32985);
	glColor3ub(250, 250, 250);//Грива лошади
	glVertex2f(-0.55468, 0.76962); glColor3ub(0, 0, 0); glVertex2f(-0.53148, 0.75619);
	glVertex2f(-0.52561, 0.71613); glVertex2f(-0.54857, 0.72444);
	glColor3ub(250, 250, 250);
	glVertex2f(-0.55, 0.75); glVertex2f(-0.51755, 0.72908);
	glVertex2f(-0.49815, 0.69042); glVertex2f(-0.53903, 0.70547);
	glColor3ub(250, 250, 250);
	glVertex2f(-0.52253, 0.69472); 	glVertex2f(-0.48678, 0.67999);
	glVertex2f(-0.47951, 0.63377); glVertex2f(-0.5, 0.65);
	glColor3ub(250, 250, 250);//левая передняя нога лошади1
	glVertex2f(-0.63911, 0.60256); glVertex2f(-0.55566, 0.58047);
	glVertex2f(-0.57529, 0.5412); glVertex2f(-0.65138, 0.54979);
	glColor3ub(250, 250, 250);//левая передняя нога лошади2
	glVertex2f(-0.70293, 0.57065); glVertex2f(-0.63911, 0.60256);
	glVertex2f(-0.65138, 0.54979); glVertex2f(-0.69188, 0.53261);
	glColor3ub(250, 0, 0);//голова всадника
	glVertex2f(-0.39805, 0.66606); glVertex2f(-0.37319, 0.67879);
	glVertex2f(-0.36409, 0.61815); glVertex2f(-0.39598, 0.62976);
	glColor3ub(250, 0, 0);//шея всадника
	glVertex2f(-0.38502, 0.62986); glVertex2f(-0.36797, 0.62538);
	glVertex2f(-0.38971, 0.60047); glVertex2f(-0.41464, 0.61102);
	glColor3ub(250, 0, 0);//тело всадника
	glVertex2f(-0.41624, 0.62874); glVertex2f(-0.36851, 0.59438);
	glVertex2f(-0.43342, 0.4827); glVertex2f(-0.47828, 0.52374);
	glColor3ub(250, 0, 0);//нога всадника
	glVertex2f(-0.57947, 0.46933); glVertex2f(-0.45, 0.55);
	glVertex2f(-0.44106, 0.51229); glVertex2f(-0.55656, 0.45215);
	glColor3ub(250, 0, 0);//рука всадника
	glVertex2f(-0.45, 0.65); glVertex2f(-0.38971, 0.60047);
	glVertex2f(-0.41433, 0.58961); glVertex2f(-0.47542, 0.62206);
	glColor3ub(0, 0, 0);//копьё всадника
	glVertex2f(-0.49931, 0.76065); glColor3ub(0, 0, 250); glVertex2f(-0.36453, 0.47128);
	glColor3ub(0, 0, 0); glVertex2f(-0.37175, 0.46333); glColor3ub(0, 0, 250); glVertex2f(-0.51508, 0.75398);
	glColor3ub(0, 0, 0);//наконечник копья всадника
	glVertex2f(-0.51932, 0.77581); glVertex2f(-0.49931, 0.76065);
	glVertex2f(-0.50113, 0.74306); glVertex2f(-0.51508, 0.75398);
	}
	glEnd();
	glPopMatrix();
}
//Колода карт
void Cards() {
	glPushMatrix();
	glTranslated(Cx-0.5*(-0.80631-0.60602), Cy-0.5*(0.02052 - 0.42252), -0.01);

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	//6 card
	glVertex2f(-0.80631, 0.02052); glVertex2f(-0.60602, 0.02052);
	glVertex2f(-0.60602, -0.42252); glVertex2f(-0.80631, -0.42252);
	//5 card
	glVertex2f(-0.79631, 0.03052); glVertex2f(-0.59602, 0.03052);
	glVertex2f(-0.59602, -0.42252); glVertex2f(-0.79631, -0.42252);
	//4 card
	glVertex2f(-0.79631, 0.03052); glVertex2f(-0.59602, 0.03052);
	glVertex2f(-0.59602, -0.42252); glVertex2f(-0.79631, -0.42252);
	//3 card
	glVertex2f(-0.79231, 0.06052); glVertex2f(-0.59602, 0.06052);
	glVertex2f(-0.59602, -0.42252); glVertex2f(-0.79231, -0.42252);
	//2 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.78631, 0.10052); glVertex2f(-0.57602, 0.10052);
	glVertex2f(-0.57602, -0.41252); glVertex2f(-0.78631, -0.41252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.77631, 0.09052); glVertex2f(-0.58602, 0.09052);
	glVertex2f(-0.58602, -0.40252); glVertex2f(-0.77631, -0.40252);

	//1.7 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.78631, 0.02052); glVertex2f(-0.58602, 0.02052);
	glVertex2f(-0.58602, -0.42252); glVertex2f(-0.78631, -0.42252);
	//1.6 card
	glVertex2f(-0.77631, 0.03052); glVertex2f(-0.57602, 0.03052);
	glVertex2f(-0.57602, -0.42252); glVertex2f(-0.77631, -0.42252);
	//1.5 card
	glVertex2f(-0.77631, 0.03052); glVertex2f(-0.57602, 0.03052);
	glVertex2f(-0.57602, -0.42252); glVertex2f(-0.77631, -0.42252);
	//1.4 card
	glVertex2f(-0.77231, 0.06052); glVertex2f(-0.57602, 0.06052);
	glVertex2f(-0.57602, -0.42252); glVertex2f(-0.77231, -0.42252);
	//1.3 card

	glVertex2f(-0.76631, 0.10052); glVertex2f(-0.55602, 0.10052);
	glVertex2f(-0.55602, -0.41252); glVertex2f(-0.76631, -0.41252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.75631, 0.09052); glVertex2f(-0.56602, 0.09052);
	glVertex2f(-0.56602, -0.40252); glVertex2f(-0.75631, -0.40252);

	//1.2 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.74231, 0.06052); glVertex2f(-0.54602, 0.00052);
	glVertex2f(-0.60602, -0.44252); glVertex2f(-0.80231, -0.38252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.75231, 0.05052); glVertex2f(-0.57602, -0.00948);
	glVertex2f(-0.63602, -0.43252); glVertex2f(-0.81231, -0.37252);
	//1.1 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.80231, 0.00052); glVertex2f(-0.60602, 0.06052);
	glVertex2f(-0.54602, -0.38252); glVertex2f(-0.74231, -0.44252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.78231, -0.00948); glVertex2f(-0.61602, 0.05052);
	glVertex2f(-0.55602, -0.37252); glVertex2f(-0.72231, -0.43252);

	//1 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.76231, 0.06052); glVertex2f(-0.56602, 0.00052);
	glVertex2f(-0.62602, -0.44252); glVertex2f(-0.82231, -0.38252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.75231, 0.05052); glVertex2f(-0.57602, -0.00948);
	glVertex2f(-0.63602, -0.43252); glVertex2f(-0.81231, -0.37252);
	//0.1 card
	glColor3ub(0, 0, 0);
	glVertex2f(-0.82231, 0.00052); glVertex2f(-0.62602, 0.06052);
	glVertex2f(-0.56602, -0.38252); glVertex2f(-0.76231, -0.44252);
	glColor3ub(100, 100, 100);
	glVertex2f(-0.80231, -0.00948); glVertex2f(-0.63602, 0.05052);
	glVertex2f(-0.57602, -0.37252); glVertex2f(-0.74231, -0.43252);



	glEnd();
	glPopMatrix();
}
//Для движения персонажа
void proccessKey(unsigned char key, int x, int y) {
	if (key == 'd') {
		hero.pos.x += 0.1;
		hero.isRight = true;

	}
	if (key == 'a') {
		hero.pos.x -= 0.1;
		hero.isRight = true;

	}
	if (key == 'w') {
		hero.pos.y += 0.1;
		hero.isRight = true;

	}
	if (key == 's') {
		hero.pos.y -= 0.1;
		hero.isRight = true;

	}
	glutPostRedisplay();
}
//Фон
void plotGraph() {
	glPushMatrix();
	glScalef(.25, .25, 1);
	glTranslatef(-3, 0, 0);


	glBegin(GL_QUADS);// ФОН
	glColor3ub(50, 75, 50);
	glVertex2f(7, 5); //1(PrVe)//Ground
	glVertex2f(7, -5); //2(PrNi)
	glVertex2f(-5, -5); //3(LeNi)
	glVertex2f(-5, 5); //4(LeVe)

	glEnd();
	glPopMatrix();
}