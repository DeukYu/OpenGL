#include <gl\freeglut.h>
#include <time.h>
#include <iostream>

using namespace std;

struct Rect_Obj
{
	float left, top;
	float right, bottom;
	float fspeed;
	bool istate = false;
	float RGB[3] = {};
	int	isize_count = 0;
	int iDir = 0; // 0 ↗ 1 ↖ 2 ↙ 3 ↘
};
void drawScene(void);
void reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void MoveFunction(int value);
void Keyboard(unsigned char key, int x, int y);

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };

bool left_button = false;
Rect_Obj tRect[10] = {};
int iCount = 0;
int iSelect = -1;


void main(int argc, char** argv)
{
	srand((unsigned)time(0));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(Window_Pos.x, Window_Pos.y); // 윈도우 위치 설정 - 좌측 상단 모서리 위치 지정
	glutInitWindowSize(Window_Size.x, Window_Size.y); // 윈도우 위치 설정 - 위치 변환
	glutCreateWindow("Example1");// 윈도우 생성 ↔ glutDestroyWindow(int Win); - 윈도우 파괴
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(1000, TimerFunction, 1);
	glutTimerFunc(100, MoveFunction, 2);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // GLUT 이벤트 프로세싱 루프 실행
}

void drawScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체 칠하기
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 10; ++i)
	{
		glColor3f(tRect[i].RGB[0], tRect[i].RGB[1], tRect[i].RGB[2]);
		glRectf(tRect[i].left, tRect[i].top, tRect[i].right, tRect[i].bottom);
		if (iSelect == i && true == tRect[i].istate)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glLineWidth(5.0f);
			glBegin(GL_LINE_LOOP);
			glVertex2f(tRect[i].left, tRect[i].top);
			glVertex2f(tRect[i].right, tRect[i].top);
			glVertex2f(tRect[i].right, tRect[i].bottom);
			glVertex2f(tRect[i].left, tRect[i].bottom);
			glEnd();
		}
	}
	glFlush(); // 화면에 출력하기
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned)time(0));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		tRect[iCount].left = (float)x;
		tRect[iCount].top = (float)(Window_Size.y - y);
		tRect[iCount].right = (float)(tRect[iCount].left + ((rand() % 100) + 50));
		tRect[iCount].bottom = (float)(tRect[iCount].top - ((rand() % 100) + 50));
		tRect[iCount].istate = true;
		tRect[iCount].fspeed = (float)((rand() % 10) + 1);
		tRect[iCount].iDir = rand() % 4;

		for (int i = 0; i < 3; ++i)
		{
			tRect[iCount].RGB[i] = 1.0f / 255.0f * (rand() % 255);
		}
		++iCount;

		if (10 == iCount)
		{
			iCount = 0;
		}

		//left_button = true;
	}
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j) // 색
		{
			tRect[i].RGB[j] = 1.0f / 255.0f * (rand() % 255);
		}
		if (tRect[i].istate == true) // 크기
		{
			if (tRect[i].isize_count == 0 || tRect[i].isize_count == 1)
			{
				tRect[i].left -= 10;
				tRect[i].top += 10;
				tRect[i].right += 10;
				tRect[i].bottom -= 10;
				++tRect[i].isize_count;
			}
			else if (tRect[i].isize_count == 2 || tRect[i].isize_count == 3)
			{
				tRect[i].left += 10;
				tRect[i].top -= 10;
				tRect[i].right -= 10;
				tRect[i].bottom += 10;
				if (3 == tRect[i].isize_count)
				{
					tRect[i].isize_count = 0;
				}
				else
					++tRect[i].isize_count;
			}
		}
	}
	glutTimerFunc(1000, TimerFunction, 1);
}

void MoveFunction(int value)
{
	glutPostRedisplay();
	for (int i = 0; i < 10; ++i)
	{
		if (tRect[i].istate)
		{
			switch (tRect[i].iDir)
			{
			case 0://↗
				tRect[i].left += tRect[i].fspeed;
				tRect[i].top += tRect[i].fspeed;
				tRect[i].right += tRect[i].fspeed;
				tRect[i].bottom += tRect[i].fspeed;

				if (tRect[i].right > (float)Window_Size.x) // 오른쪽 충돌
				{
					tRect[i].iDir = 1; // ↖
				}
				else if (tRect[i].top > (float)Window_Size.y) // 위쪽 충돌
				{
					tRect[i].iDir = 3; // ↘
				}
				break;
			case 1:// ↖
				tRect[i].left -= tRect[i].fspeed;
				tRect[i].top += tRect[i].fspeed;
				tRect[i].right -= tRect[i].fspeed;
				tRect[i].bottom += tRect[i].fspeed;

				if (tRect[i].top > (float)Window_Size.y) // ↙
				{
					tRect[i].iDir = 2;
				}
				else if (tRect[i].left < (float)Window_Size.x - 800)//↗
				{
					tRect[i].iDir = 0;
				}
				break;
			case 2: // ↙
				tRect[i].left -= tRect[i].fspeed;
				tRect[i].top -= tRect[i].fspeed;
				tRect[i].right -= tRect[i].fspeed;
				tRect[i].bottom -= tRect[i].fspeed;

				if (tRect[i].left < (float)Window_Size.x - 800)
				{
					tRect[i].iDir = 3;
				}
				else if (tRect[i].bottom < (float)Window_Size.y - 600)
				{
					tRect[i].iDir = 0;
				}
				break;
			case 3:
				tRect[i].left += tRect[i].fspeed;
				tRect[i].top -= tRect[i].fspeed;
				tRect[i].right += tRect[i].fspeed;
				tRect[i].bottom -= tRect[i].fspeed;

				if (tRect[i].bottom < (float)Window_Size.y - 600)
				{
					tRect[i].iDir = 0;
				}
				else if (tRect[i].right > (float)Window_Size.y) // ↙
				{
					tRect[i].iDir = 2;
				}
				break;
			}
		}
	}
	glutTimerFunc(100, MoveFunction, 2);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		iSelect = 0;
		break;
	case '2':
		iSelect = 1;
		break;
	case '3':
		iSelect = 2;
		break;
	case '4':
		iSelect = 3;
		break;
	case '5':
		iSelect = 4;
		break;
	case '6':
		iSelect = 5;
		break;
	case '7':
		iSelect = 6;
		break;
	case '8':
		iSelect = 7;
		break;
	case '9':
		iSelect = 8;
		break;
	case '0':
		iSelect = 9;
		break;
	case '+':
		for (int i = 0; i < 10; ++i)
		{
			if(tRect[i].fspeed < 20)
			tRect[i].fspeed += 1.0f;
		}
		break;
	case '-':
		for (int i = 0; i < 10; ++i)
		{
			if (tRect[i].fspeed > 0)
				tRect[i].fspeed -= 1.0f;
		}
		break;
	}
}
