#include <gl\freeglut.h>
#include <iostream>
#include <list>
#include <time.h>
#include <math.h>

#define PI 3.14159f

using namespace std;

void Mouse(int button, int state, int x, int y);
void Circle_Move(int value);

typedef struct  tag_Tornado
{
	float x, y;
	float fAngle;
	float r;
}TORNADO,*PTORNADO;

typedef struct _tagCircle
{
	TORNADO tTornado[110];
	float start_x, start_y;
	int	  iCount;
	int	  iDir; // 0 ���������� 1 ��������
}CIRCLE, *PCIRCLE;

list<CIRCLE> g_CircleList;
//list<CIRCLE>::iterator iter;

void drawScene(void);
void reshape(int w, int h);

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };

int Num_Count = 0;

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

	glColor3f(1.f,1.f,1.f);
	glPointSize(5.f);
	glBegin(GL_POINTS);
	for (iter = g_CircleList.begin(); iter != iterEnd; ++iter)
	{
		for(int i=0;i<(*iter).iCount;++i)
			glVertex2f((*iter).tTornado[i].x, (*iter).tTornado[i].y);
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

	y = Window_Size.y - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (10 > Num_Count)
		{
			CIRCLE tCircle;
			tCircle.iCount = 0;
			tCircle.start_x = (float)x;
			tCircle.start_y = (float)y;
			tCircle.tTornado[tCircle.iCount].x = (float)x;
			tCircle.tTornado[tCircle.iCount].y = (float)y;
			tCircle.tTornado[tCircle.iCount].fAngle = 0;
			tCircle.tTornado[tCircle.iCount].r = 0;
			tCircle.iDir = rand() % 2;
			++tCircle.iCount;
			g_CircleList.push_back(tCircle);
		}
		++Num_Count;
	}
}

void Circle_Move(int value)
{
	list<CIRCLE>::iterator iter;
	list<CIRCLE>::iterator iterEnd = g_CircleList.end();

	for (iter = g_CircleList.begin(); iter != iterEnd;)
	{
		if (0 == (*iter).iDir)
		{
			if ((*iter).iCount < 55)
			{

				(*iter).tTornado[(*iter).iCount].r = (float)((*iter).iCount * 1.0f);
				(*iter).tTornado[(*iter).iCount].fAngle = (float)((*iter).iCount * (PI / 9.f));
				(*iter).tTornado[(*iter).iCount].x = (*iter).start_x + (float)((*iter).tTornado[(*iter).iCount].r * cosf((*iter).tTornado[(*iter).iCount].fAngle));
				(*iter).tTornado[(*iter).iCount].y = (*iter).start_y + (float)((*iter).tTornado[(*iter).iCount].r * sinf((*iter).tTornado[(*iter).iCount].fAngle));
				++(*iter).iCount;
				if ((*iter).iCount == 55)
				{
					(*iter).start_x += 2 * (*iter).tTornado[54].r;
				}
			}
			else if (55 <= (*iter).iCount && (*iter).iCount < 110)
			{
				(*iter).tTornado[(*iter).iCount].r = (*iter).tTornado[54].r - ((*iter).iCount - 54);
				(*iter).tTornado[(*iter).iCount].fAngle = (float)((PI / 1.f)) - (float)(((*iter).iCount - 54) * (PI / 9.f));
				(*iter).tTornado[(*iter).iCount].x = (*iter).start_x + (float)((*iter).tTornado[(*iter).iCount].r * cosf((*iter).tTornado[(*iter).iCount].fAngle));
				(*iter).tTornado[(*iter).iCount].y = (*iter).start_y + (float)((*iter).tTornado[(*iter).iCount].r * sinf((*iter).tTornado[(*iter).iCount].fAngle));
				++(*iter).iCount;
			}
		}
		else if (1 == (*iter).iDir)
		{
			if ((*iter).iCount < 55)
			{

				(*iter).tTornado[(*iter).iCount].r = (float)((*iter).iCount * 1.0f);
				(*iter).tTornado[(*iter).iCount].fAngle = -(float)((*iter).iCount * (PI / 9.f));
				(*iter).tTornado[(*iter).iCount].x = (*iter).start_x - (float)((*iter).tTornado[(*iter).iCount].r * cosf((*iter).tTornado[(*iter).iCount].fAngle));
				(*iter).tTornado[(*iter).iCount].y = (*iter).start_y - (float)((*iter).tTornado[(*iter).iCount].r * sinf((*iter).tTornado[(*iter).iCount].fAngle));
				++(*iter).iCount;
				if ((*iter).iCount == 55)
				{
					(*iter).start_x -= 2 * (*iter).tTornado[54].r;
				}
			}
			else if (55 <= (*iter).iCount && (*iter).iCount < 110)
			{
				(*iter).tTornado[(*iter).iCount].r = (*iter).tTornado[54].r - ((*iter).iCount - 54);
				(*iter).tTornado[(*iter).iCount].fAngle = (PI / 1.f) + (float)(((*iter).iCount - 54) * (PI / 9.f));
				(*iter).tTornado[(*iter).iCount].x = (*iter).start_x - (float)((*iter).tTornado[(*iter).iCount].r * cosf((*iter).tTornado[(*iter).iCount].fAngle));
				(*iter).tTornado[(*iter).iCount].y = (*iter).start_y - (float)((*iter).tTornado[(*iter).iCount].r * sinf((*iter).tTornado[(*iter).iCount].fAngle));
				++(*iter).iCount;
			}
		}
		++iter;
	}
	glutPostRedisplay();
	glutTimerFunc(100, Circle_Move, 1);
}