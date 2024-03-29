#include <iostream>
//#include <unistd.h>
#include <time.h>
#include <math.h>

// Apple Specific Compatibility Issues
#ifdef __APPLE__
	#include "GLUT/glut.h"
#else
	#include <glut.h>
#endif

// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;

// Function to Create Delay
void delay(float secs) {
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

// Function to Print Text
void print(char *string,
	GLfloat r, GLfloat g, GLfloat b,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize) {
	glPushMatrix();

	glColor3f(r, g, b);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);

	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();

	glLineWidth(1);
	glPointSize(1);
}

// Function to Draw Circle
void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius) {
		glPushMatrix();

		glTranslatef(x, y, 0);
		glScalef(sx, sy, 0);

    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = 0; i < 360; i += 5)
        glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
    glEnd();

		glPopMatrix();
}

// Function to Draw Circle
void drawSemiCircle(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat radius,
	GLfloat start_angle, GLfloat end_angle) {
		glPushMatrix();

		glTranslatef(tx, ty, 0);
		glScalef(sx, sy, 0);

    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = start_angle; i < end_angle; i += 5)
        glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
    glEnd();

		glPopMatrix();
}

// Function to Draw Arc
void drawArc(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3ub(r, g, b);
  for ( GLfloat i = 90; i < 270; i++)
    glVertex2f(15 * sin(i * PI / 180), 15 * cos(i * PI / 180));
  glEnd();
	glPointSize(1);

	glPopMatrix();
}

// Function to Draw a Woman
void drawWoman(GLfloat tx, GLfloat ty, GLfloat sx, GLfloat sy,
	GLfloat hair_r, GLfloat hair_g, GLfloat hair_b,
	GLfloat top_r, GLfloat top_g, GLfloat top_b,
	GLfloat ribbon_r, GLfloat ribbon_g, GLfloat ribbon_b,
	GLfloat skirt_r, GLfloat skirt_g, GLfloat skirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Neck
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(203, 166, 108); // Darker Skin
	glVertex2f(507, 380);
	glVertex2f(507, 360);
	glVertex2f(513, 380);
	glVertex2f(513, 360);
	glEnd();
	glLineWidth(1);

	// Face
	drawCircle(510, 407,
		232, 190, 123, // Lighter Skin
		1, 1,
		30);

	// Hair
	drawSemiCircle(510, 420, 1, .6,
		hair_r, hair_g, hair_b,
		35, -90, 90);

	drawSemiCircle(485, 400, .4, 1,
		hair_r, hair_g, hair_b,
		35, -180, 0);

	// Left Eye
	drawCircle(505, 410,
		250, 250, 250,
		1, 1,
		5);

	drawCircle(508, 408,
		10, 10, 10,
		1, 1,
		2.5);

	// Right Eye
	drawCircle(530, 410,
		250, 250, 250,
		1, 1,
		5);

	drawCircle(532, 408,
		10, 10, 10,
		1, 1,
		2.5);

	// Smile
	drawArc(514, 388, .5, .3,
		20, 20, 20);

	// Nose
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(518, 405);
	glVertex2f(522, 398);
	glVertex2f(522, 398);
	glVertex2f(518, 395);
	glEnd();
	glLineWidth(1);

	// Arms
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
	glVertex2f(470, 340);
	glVertex2f(470, 240);
	glVertex2f(475, 340);
	glVertex2f(475, 240);
	glVertex2f(480, 340);
	glVertex2f(480, 240);

	glVertex2f(540, 340);
	glVertex2f(540, 240);
	glVertex2f(545, 340);
	glVertex2f(545, 240);
	glVertex2f(550, 340);
	glVertex2f(550, 240);
	glEnd();
	glLineWidth(1);

	// Top
	glBegin(GL_POLYGON);
	glColor3ub(top_r, top_g, top_b);
	glVertex2f(460, 370);
	glVertex2f(560, 370);
	glVertex2f(540, 300);
	glVertex2f(480, 300);
	glEnd();

	// Skirt
	glBegin(GL_POLYGON);
	glColor3ub(skirt_r, skirt_g, skirt_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glVertex2f(560, 180);
	glVertex2f(460, 180);
	glEnd();

	// Ribbon
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(ribbon_r, ribbon_g, ribbon_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glEnd();
	glLineWidth(1);

	// Legs
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
	glVertex2f(490, 180);
	glVertex2f(490, 150);
	glVertex2f(495, 180);
	glVertex2f(495, 150);

	glVertex2f(525, 180);
	glVertex2f(525, 150);
	glVertex2f(530, 180);
	glVertex2f(530, 150);
	glEnd();
	glLineWidth(1);

	glPopMatrix();
}

void drawKidsShirtAndTrousers(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Bottom Shirt
	glColor3ub(shirt_r, shirt_g, shirt_b);
	glBegin(GL_POLYGON);
	glVertex2f(0, 20);
	glVertex2f(100, 20);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glEnd();

	// Top Shirt
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(135, 105);
	glVertex2f(120, 175);
	glVertex2f(100, 200);
	glVertex2f(50, 180);
	glVertex2f(0, 200);
	glVertex2f(-20, 175);
	glVertex2f(-35, 105);
	glVertex2f(0, 100);
	glEnd();

	// Left Trouser
	glColor3ub(37, 107, 202);
	glBegin(GL_POLYGON);
	glVertex2f(0, 25);
	glVertex2f(0, -100);
	glVertex2f(35, -100);
	glVertex2f(65, 25);
	glEnd();

	// Right Trouser
	glBegin(GL_POLYGON);
	glVertex2f(35, 25);
	glVertex2f(65, -100);
	glVertex2f(100, -100);
	glVertex2f(100, 25);
	glEnd();

	glPopMatrix();
}

void drawKid(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Neck
	drawSemiCircle(-1, -35, .6, 1,
		203, 166, 108,
		20, -90, 90);

	// Face
  drawCircle(0, 0,
		232, 190, 123,
		1, 1,
		24);

	// Left Eye
	drawCircle(-8, 0,
		250, 250, 250,
		1, 1,
		4);
	drawCircle(-6, 0,
		10, 10, 10,
		1, 1,
		2);

	// Right Eye
	drawCircle(8, 0,
		250, 250, 250,
		1, 1,
		4);
	drawCircle(10, 0,
		10, 10, 10,
		1, 1,
		2);

	// Cap
	drawSemiCircle(0, 10, 1, 1,
		37, 107, 202,
		24, -90, 90);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(20, 14);
	glVertex2f(40, 16);
	glEnd();
	glLineWidth(1);

	// Hands
	drawCircle(-42, -82,
		232, 190, 123,
		1, 1,
		10);
	drawCircle(38, -82,
		232, 190, 123,
		1, 1,
		10);

	// Shirt and Trousers
	drawKidsShirtAndTrousers(-32, -125,
		.6, .5,
		shirt_r, shirt_g, shirt_b);

	// Left Shoe
	drawSemiCircle(-21, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	// Right Shoe
	drawSemiCircle(18, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	glPopMatrix();
}


/*
* Scene 0 - Introduction Screen
*/
void introduction() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("The Classroom",
		1, 1, 1,280,380, .3, .3, 2);

	print("by Your name		.",
		1, 1, 1, 790, 345, .15, .15, 1);
	print("(Your USN)",
		1, 1, 1, 840, 320, .1, .1, 1);

	print("Press N to continue...",
		1, 1, 1, 560, 10, .09, .09, 1);
}

/*
* Scene 1 - Summary Screen
*/
void summary() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("Summary",
		1, 1, 1, 75, 650, .3, .3, 1.5);

	// Summary Text
	print("As children we start learning.",
		1, 1, 1, 75, 575, .125, .125, 1.25);
	print("We are taught to by heart and understand.",
		1, 1, 1,  75, 550, .125, .125, 1.25);

	print("When we grow we choosing",
		1, 1, 1,  75, 475, .125, .125, 1.25);
	print("to be a Doctor or an Engineer, and the rest` of the options are at bleak focus. ",
		1, 1, 1,  75, 450, .125, .125, 1.25);

	print("Choosing to be a doctor is a rich man's dream.",
		1, 1, 1,  75, 375, .125, .125, 1.25);
	print("Ending up as an engineer has become a curse. ",
		1, 1, 1,  75, 350, .125, .125, 1.25);

	print("Engineering is a field to invent and innovate, not to follow orders from higher officials.",
		1, 1, 1,  75, 275, .125, .125, 1.25);
	print("We might as well study the lives of Hitler's Soldiers if we were to do so",
		1, 1, 1,  75, 250, .125, .125, 1.25);
	print("for the rest of out lives.",
		1, 1, 1,  75, 225, .125, .125, 1.25);

	print("Press N to move on...",
		1, 1, 1, 580, 10, .09, .09, 1);
}

// Function to Draw Ceiling
void KG_drawCeiling() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 800);
	glEnd();
	glLineWidth(1);

	glFlush();
}

// Function to Draw Side Wall
void KG_drawSideWall() {
	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(200, 175);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);
}
// Function to Draw Center Wall
void KG_drawCenterWall() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glEnd();

	// Border for Center Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 175);
	glVertex2f(200, 175);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Ceiling
void KG_drawCeilingDark() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(128, 128, 128); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(105, 105, 105); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(105, 105, 105); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(128, 128, 128); // Dark Brown
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 800);
	glEnd();
	glLineWidth(1);

	glFlush();
}

// Function to Draw Side Wall
void KG_drawSideWallDark() {
	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(128, 128, 128);
	glVertex2f(0, 800);
	glColor3ub(105, 105, 105); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(105, 105, 105); // Light Brown
	glVertex2f(200, 175);
	glColor3ub(128, 128, 128); // Dark Brown
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(200, 175);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);
}
// Function to Draw Center Wall
void KG_drawCenterWallDark() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(105, 105, 105); // Light Brown
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glColor3ub(128, 128, 128); // Dark Brown
	glVertex2f(1400, 175);
	glVertex2f(200, 175);
	glEnd();

	// Border for Center Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 175);
	glVertex2f(200, 175);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Floor
void KG_drawFloor() {
	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();

	// Border for Floor
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Outside Background
void KG_drawOutside() {
	// Outside
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();
}

// Function to Draw Door
void KG_drawDoor() {
	// Door Hinges
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(180, 540);
	glVertex2f(30, 520);
	glVertex2f(30, 180);
	glVertex2f(180, 165);
	glEnd();

	// Door Knob
	drawCircle(45, 350,
		223, 189, 31, // Goldish Yellow
		1, 1,
		5);
}

// Function to Draw Kid's Head
void KG_drawKidsHead(GLfloat tx, GLfloat ty) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);

	// Kid's Face
	drawCircle(480, 110,
		232, 190, 123, // Lighter Skin
		1, 1,
		25);

	int hair_line;

	// Kid's Hair Strands
	hair_line = 400;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);

	glPopMatrix();
}


// Function to Draw TubeLight
void KG_drawTubelight() {
	// Blackboard
	glBegin(GL_POLYGON);
	glColor3ub(192, 192, 192); // Almost silver
	glVertex2f(650, 640);
	glVertex2f(900, 640);
	glVertex2f(900, 670);
	glVertex2f(650, 670);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 240); // Almost silver
	glVertex2f(660, 645);
	glVertex2f(890, 645);
	glVertex2f(890, 665);
	glVertex2f(660, 665);
	glEnd();
}

// Function to Draw TubeLight
void KG_drawTubelightDark() {
	// Blackboard
	glBegin(GL_POLYGON);
	glColor3ub(192, 192, 192); // Almost silver
	glVertex2f(650, 640);
	glVertex2f(900, 640);
	glVertex2f(900, 670);
	glVertex2f(650, 670);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(169, 169, 169); // Almost silver
	glVertex2f(660, 645);
	glVertex2f(890, 645);
	glVertex2f(890, 665);
	glVertex2f(660, 665);
	glEnd();
}

// Function to Draw Blackboard
void KG_drawBlackboard() {
	// Blackboard
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();

	// Blackboard Border
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Teacher's Table
void KG_drawTeachersTable() {
	// Teacher's Table
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(510, 260);
	glVertex2f(470, 200);
	glVertex2f(1080, 200);
	glVertex2f(1040, 260);
	glEnd();

	// Teacher's Table Edge
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(470, 200);
	glVertex2f(470, 190);
	glVertex2f(1080, 190);
	glVertex2f(1080, 200);
	glEnd();

	// Left Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(530, 190);
	glVertex2f(540, 190);
	glVertex2f(540, 130);
	glVertex2f(530, 130);
	glEnd();

	// Right Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(1020, 190);
	glVertex2f(1010, 190);
	glVertex2f(1010, 130);
	glVertex2f(1020, 130);
	glEnd();
}

// Function to Draw Children's Desks
void KG_drawChildrensDesks() {
	// Left Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(400, 150);
	glVertex2f(700, 150);
	glVertex2f(730, 120);
	glVertex2f(370, 120);
	glEnd();

	// Left Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(370, 120);
	glVertex2f(370, 115);
	glVertex2f(730, 115);
	glVertex2f(730, 120);
	glEnd();

	// Right Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(850, 150);
	glVertex2f(1150, 150);
	glVertex2f(1180, 120);
	glVertex2f(820, 120);
	glEnd();

	// Right Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(820, 120);
	glVertex2f(820, 115);
	glVertex2f(1180, 115);
	glVertex2f(1180, 120);
	glEnd();
}

/*
* Scene 3 - Kindergarten
*/
void kindergarten() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	KG_drawCeiling();
	KG_drawSideWall();
	KG_drawCenterWall();
	KG_drawFloor();

	KG_drawOutside();

	KG_drawDoor();

	KG_drawBlackboard();

	KG_drawTubelight();

	// Teacher
	drawWoman(0, 0, 1, 1,
		60, 60, 60,
		229, 49, 49, // top
		37, 107, 202, // ribbon
		229, 49, 49 // skirt
	);

	KG_drawTeachersTable();

	KG_drawChildrensDesks();

	KG_drawKidsHead(0, 0);
	KG_drawKidsHead(140, 0);
	KG_drawKidsHead(460, 0);
	KG_drawKidsHead(600, 0);

	print("A",
		1, 1, 1, 600, 440, .3, .3, 3);

	print("- Apple",
		1, 1, 1,  655, 445, .2, .2, 1);

	print("B",
		1, 1, 1,600, 380, .3, .3, 3);

	print("- Ball",
		1, 1, 1, 655, 385, .2, .2, 1);

	print("... and so on",
		1, 1, 1,  560, 220, .2, .2, 1.5);

	print("This is where our educational journey begins...",
		1, 1, 1, 380, 30, .14, .14, 1);
}

/*
* Scene 3 - Kindergarten
*/
void kindergartenDark() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	KG_drawCeilingDark();
	KG_drawSideWallDark();
	KG_drawCenterWallDark();
	KG_drawFloor();

	KG_drawOutside();

	KG_drawDoor();

	KG_drawBlackboard();

	KG_drawTubelightDark();

	// Teacher
	drawWoman(0, 0, 1, 1,
		60, 60, 60,
		229, 49, 49, // top
		37, 107, 202, // ribbon
		229, 49, 49 // skirt
	);

	KG_drawTeachersTable();

	KG_drawChildrensDesks();

	KG_drawKidsHead(0, 0);
	KG_drawKidsHead(140, 0);
	KG_drawKidsHead(460, 0);
	KG_drawKidsHead(600, 0);

	print("A",
		1, 1, 1, 600, 440, .3, .3, 3);

	print("- Apple",
		1, 1, 1,  655, 445, .2, .2, 1);

	print("B",
		1, 1, 1,600, 380, .3, .3, 3);

	print("- Ball",
		1, 1, 1, 655, 385, .2, .2, 1);

	print("... and so on",
		1, 1, 1,  560, 220, .2, .2, 1.5);

	print("This is where our educational journey begins...",
		1, 1, 1, 380, 30, .14, .14, 1);
}



// Function to Render Scene
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		introduction();
		break;
	case 1:
		summary();
		break;
	case 2:
		kindergarten();
		break;
	case 3:
		kindergartenDark();
		break;
	default:
		break;
	}
	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
	// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
	// Go to Next Scene
	case 'n':
	case 'N':
		if (SCENE_ID == 15)
			break;
		SCENE_ID++;
		break;
	case 'r':
	case 'R':
		if (SCENE_ID == 2){
		SCENE_ID++;
		break;}
		else if(SCENE_ID == 3){
			SCENE_ID--;
			break;}
	// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("The Classroom");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	// Timer Function
	// every 25 milliseconds, update function is called
	//glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}