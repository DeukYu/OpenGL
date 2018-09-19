#include <gl\freeglut.h>
#include <iostream>
#include <list>
#include <time.h>
#include <math.h>

#define PI 3.14159f

using namespace std;

void Mouse(int button, int state, int x, int y);
void Circle_Move(int value);

typedef struct struct_tagPos
{
	float x, y;
}POS, *PPOS;

typedef struct _tagCircle
{
	POS	tPos;
	POS tStart;
	float fDist;
	float fLimitDist;
	float fAngle;
	float RGB[3];
	bool bRandom;
}CIRCLE, *PCIRCLE;

list<CIRCLE> g_CircleList;

void drawScene(void);
void reshape(int w, int h);

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };
float RGB[3] = {};

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(Window_Pos.x, Window_Pos.y); // ������ ��ġ ���� - ���� ��� �𼭸� ��ġ ����
	glutInitWindowSize(Window_Size.x, Window_Size.y); // ������ ��ġ ���� - ��ġ ��ȯ
	glutCreateWindow("Example1");// ������ ���� �� glutDestroyWindow(int Win); - ������ �ı�
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Circle_Move, 1);
	glutMainLoop(); // GLUT �̺�Ʈ ���μ��� ���� ����
}

void drawScene(void)
{
	list<CIRCLE>::iterator iter;
	list<CIRCLE>::iterator iterEnd = g_CircleList.end();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // ������
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü ĥ�ϱ�

	for (iter = g_CircleList.begin(); iter != iterEnd; ++iter)
	{
		glColor3f((*iter).RGB[0], (*iter).RGB[1], (*iter).RGB[2]);
		glBegin(GL_POINTS);
			glVertex2f((*iter).tPos.x, (*iter).tPos.y);

	}
	glEnd();
	glFlush(); // ȭ�鿡 ����ϱ�
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(0));
	bool Random = rand() % 2;
	float RGB[3] = { 1.0f / 255.0f * (rand() % 255) ,1.0f / 255.0f * (rand() % 255) ,1.0f / 255.0f * (rand() % 255) };
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float fAngle = 0.f;

		for (int i = 0; i < 360; ++i)
		{
			CIRCLE tCircle;

			tCircle.tPos.x = (float)x;
			tCircle.tPos.y = (float)(Window_Size.y - y);
			tCircle.tStart.x = (float)x;
			tCircle.tStart.y = (float)(Window_Size.y - y);
			tCircle.fDist = 0.f;
			tCircle.fLimitDist = 150.f;
			tCircle.fAngle = fAngle;
			tCircle.bRandom = Random;
			if (tCircle.bRandom == true)
			{
				for (int j = 0; j < 3; ++j)
				{
					tCircle.RGB[j] = 1.f;
				}
			}
			else
			{
				for (int j = 0; j < 3; ++j)
				{
					tCircle.RGB[j] = RGB[j];
				}
			}

			g_CircleList.push_back(tCircle);
			fAngle += PI / 180.f;
		}
	}
}

void Circle_Move(int value)
{
	list<CIRCLE>::iterator iter;
	list<CIRCLE>::iterator iterEnd = g_CircleList.end();

	float RGB[3] = { 1.0f / 255.0f * (rand() % 255) ,1.0f / 255.0f * (rand() % 255) ,1.0f / 255.0f * (rand() % 255) };


	for (iter = g_CircleList.begin(); iter != iterEnd;)
	{
		(*iter).tPos.x += 10.f * cosf((*iter).fAngle);
		(*iter).tPos.y += 10.f * sinf((*iter).fAngle);

		(*iter).fDist += 10.f;

		if ((*iter).fDist >= (*iter).fLimitDist && (*iter).bRandom == true)
		{
			(*iter).tPos.x = (*iter).tStart.x;
			(*iter).tPos.y = (*iter).tStart.y;
			(*iter).fDist = 0.f;
			//iter = g_CircleList.erase(iter);
			//iterEnd = g_CircleList.end();
		}
		else if ((*iter).fDist >= (*iter).fLimitDist && (*iter).bRandom == false)
		{
			for (int j = 0; j < 3; ++j)
			{
				(*iter).RGB[j] = RGB[j];
			}
			++iter;
		}
		else
		{
			++iter;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, Circle_Move, 1);
}