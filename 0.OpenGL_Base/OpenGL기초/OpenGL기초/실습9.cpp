#include <gl\freeglut.h>
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

void drawScene(void);
void reshape(int w, int h);
void Mouse_Input(int button, int state, int x, int y);
void Mouse_Motion(int x, int y);
void Eraser(int value);

struct fRect
{
	float left, top, right, bottom;
	float	RGB[3];
};

struct Mouse_Pos
{
	float x, y;
};

list<fRect> g_fRectList;

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };

bool bStart = true;
bool bLeft_Button = false;
bool bCreation = true;
fRect fRect_Mouse;
Mouse_Pos tMouse_Pos;

void main(int argc, char** argv)
{
	srand((unsigned int)time(0));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(Window_Pos.x, Window_Pos.y); // 윈도우 위치 설정 - 좌측 상단 모서리 위치 지정
	glutInitWindowSize(Window_Size.x, Window_Size.y); // 윈도우 위치 설정 - 위치 변환
	glutCreateWindow("Example1");// 윈도우 생성 ↔ glutDestroyWindow(int Win); - 윈도우 파괴
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse_Input);
	glutMotionFunc(Mouse_Motion);
	glutTimerFunc(10, Eraser, 1);
	glutMainLoop(); // GLUT 이벤트 프로세싱 루프 실행
}

void drawScene(void)
{
	list<fRect>::iterator iter;
	list<fRect>::iterator iterEnd = g_fRectList.end();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체 칠하기

	if (bStart)
	{
		for (int i = 0; i < 100; ++i)
		{
			fRect tfRect;

			tfRect.left = (float)(rand() % Window_Size.x);
			tfRect.top = (float)(rand() % Window_Size.y);
			tfRect.right = tfRect.left + 30.f;
			tfRect.bottom = tfRect.top + 30.f;
			for (float& d : tfRect.RGB)
				d = 1.f / 255.f * (rand() % 255);

			g_fRectList.push_back(tfRect);
		}
		bStart = false;
	}

	for (iter = g_fRectList.begin(); iter != iterEnd; ++iter)
	{
		glColor3f((*iter).RGB[0], (*iter).RGB[1], (*iter).RGB[2]);
		glRectf((*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}
	if (bLeft_Button)
	{
		glColor3f(fRect_Mouse.RGB[0], fRect_Mouse.RGB[1], fRect_Mouse.RGB[2]);
		glRectf(fRect_Mouse.left, fRect_Mouse.top, fRect_Mouse.right, fRect_Mouse.bottom);
	}
	glFlush(); // 화면에 출력하기
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
}

void Mouse_Input(int button, int state, int x, int y)
{
	y = Window_Size.y - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		tMouse_Pos.x = (float)x;
		tMouse_Pos.y = (float)y;
		fRect_Mouse.left = (float)(x - 30.f);
		fRect_Mouse.top = (float)(y + 30.f);
		fRect_Mouse.right = (float)(x + 30.f);
		fRect_Mouse.bottom = (float)(y - 30.f);
		bLeft_Button = true;
	}
	else
		bLeft_Button = false;
}

void Mouse_Motion(int x, int y)
{
	y = Window_Size.y - y;

	if (bLeft_Button)
	{
		tMouse_Pos.x = (float)x;
		tMouse_Pos.y = (float)y;
		fRect_Mouse.left = (float)(x - 30.f);
		fRect_Mouse.top = (float)(y + 30.f);
		fRect_Mouse.right = (float)(x + 30.f);
		fRect_Mouse.bottom = (float)(y - 30.f);
	}
}

void Eraser(int value)
{
	list<fRect>::iterator iter;
	list<fRect>::iterator iterend = g_fRectList.end();

	if (bLeft_Button)
	{
		fRect_Mouse.left = (float)(tMouse_Pos.x - 30.f);
		fRect_Mouse.top = (float)(tMouse_Pos.y + 30.f);
		fRect_Mouse.right = (float)(tMouse_Pos.x + 30.f);
		fRect_Mouse.bottom = (float)(tMouse_Pos.y - 30.f);
		for (iter = g_fRectList.begin(); iter != iterend; )
		{
			if ((fRect_Mouse.left < (*iter).right) && (fRect_Mouse.top > (*iter).bottom) &&
				(fRect_Mouse.right >(*iter).left) && (fRect_Mouse.bottom < (*iter).top))
			{
				iter = g_fRectList.erase(iter);
				iterend = g_fRectList.end();
			}
			else
				++iter;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Eraser, 1);
}