#include <gl\freeglut.h>
#include <time.h>
#include <iostream>

using namespace std;

struct rect_state
{
	float x1, y1;
	float x2, y2;
	bool	state = false;
	float RGB[3] = {};
	int	size_count = 0;
};
void drawScene(void);
void reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };

bool left_button = false;
rect_state tRect[10] = {};
int iCount = 0;


void main(int argc, char** argv)
{
	srand((unsigned)time(0));

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(Window_Pos.x, Window_Pos.y); // ������ ��ġ ���� - ���� ��� �𼭸� ��ġ ����
	glutInitWindowSize(Window_Size.x, Window_Size.y); // ������ ��ġ ���� - ��ġ ��ȯ
	glutCreateWindow("Example1");// ������ ���� �� glutDestroyWindow(int Win); - ������ �ı�
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(1000, TimerFunction, 1);
	glutMainLoop(); // GLUT �̺�Ʈ ���μ��� ���� ����
}

void drawScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ������
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü ĥ�ϱ�
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 10; ++i)
	{
		glColor3f(tRect[i].RGB[0], tRect[i].RGB[1], tRect[i].RGB[2]);
		glRectf(tRect[i].x1,tRect[i].y1,tRect[i].x2,tRect[i].y2);
	}
	glFlush(); // ȭ�鿡 ����ϱ�
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
		cout << x << " " << y << endl;
		tRect[iCount].x1 = (float)x;
		tRect[iCount].y1 = (float)(Window_Size.y - y);
		tRect[iCount].x2 = (float)(tRect[iCount].x1 + ((rand() % 100) + 50));
		tRect[iCount].y2 = (float)(tRect[iCount].y1 - ((rand() % 100) + 50));
		tRect[iCount].state = true;
		for (int i = 0; i < 3; ++i)
		{
			tRect[iCount].RGB[i] = 1.0f / 255.0f * (rand() % 255);
		}
		++iCount;
		if (10 == iCount)
		{
			iCount = 0;
		}

		left_button = true;
	}
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
		tRect[i].RGB[j] = 1.0f / 255.0f * (rand() % 255);
		}
		if (tRect[i].state == true)
		{
			if (tRect[i].size_count == 0 || tRect[i].size_count == 1)
			{
				tRect[i].x1 -= 10;
				tRect[i].y1 += 10;
				tRect[i].x2 += 10;
				tRect[i].y2 -= 10;
				++tRect[i].size_count;
			}
			else if (tRect[i].size_count == 2 || tRect[i].size_count == 3)
			{
				tRect[i].x1 += 10;
				tRect[i].y1 -= 10;
				tRect[i].x2 -= 10;
				tRect[i].y2 += 10;
				if (3 == tRect[i].size_count)
				{
					tRect[i].size_count = 0;
				}
				else
					++tRect[i].size_count;
			}
		}
	}
	glutTimerFunc(1000, TimerFunction, 1);
}