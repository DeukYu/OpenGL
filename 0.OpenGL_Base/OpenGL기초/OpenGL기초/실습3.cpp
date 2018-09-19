#include <gl\freeglut.h>
#include <time.h>

struct fPoint
{
	float x;
	float y;
};

void drawScene(void);
void reshape(int w, int h);

POINT Window_Pos = { 100,100 };
POINT Window_Size = { 800,600 };

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(Window_Pos.x, Window_Pos.y); // ������ ��ġ ���� - ���� ��� �𼭸� ��ġ ����
	glutInitWindowSize(Window_Size.x, Window_Size.y); // ������ ��ġ ���� - ��ġ ��ȯ
	glutCreateWindow("Example1");// ������ ���� �� glutDestroyWindow(int Win); - ������ �ı�
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop(); // GLUT �̺�Ʈ ���μ��� ���� ����
}

void drawScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ������
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü ĥ�ϱ�
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.33f, 1.0f);
	glVertex2f(-0.33f, -1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0.33f, 1.0f);
	glVertex2f(0.33f, -1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(1.0f, -0.33f);
	glVertex2f(-1.0f, -0.33f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(1.0f, 0.33f);
	glVertex2f(-1.0f, 0.33f);
	glEnd();

	fPoint fPos[9] = { {-0.65f,0.65f},{0.0f,0.65f},{0.65f,0.65f}
		, {-0.65f,0.0f }, { 0.0f,0.0f }, { 0.65f,0.0f }
		,{-0.65f,-0.65f},{0.0f,-0.65f},{0.65f,-0.65f} };

	srand((unsigned int)time(0));
	int iShape = ((rand() % 4) + 2);
	bool bReverse = false;

	for (int i = 0; i < 9; ++i)
	{
		if (2 == iShape) // ��
		{
			glBegin(GL_LINES);
			glVertex2f(fPos[i].x - 0.1f, fPos[i].y + 0.1f);
			glVertex2f(fPos[i].x + 0.1f, fPos[i].y - 0.1f);
			glEnd();
			if (bReverse == true)
				bReverse = false;
			++iShape;
		}
		else if (3 == iShape)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(fPos[i].x, fPos[i].y + 0.1f,0.0f);
			glVertex3f(fPos[i].x - 0.1f, fPos[i].y - 0.1f, 0.0f);
			glVertex3f(fPos[i].x + 0.1f, fPos[i].y - 0.1f, 0.0f);
			glEnd();
			if (bReverse == true)
				--iShape;
			else
				++iShape;
		}
		else if (4 == iShape)
		{
			glRectf(fPos[i].x - 0.1f, fPos[i].y + 0.1f, fPos[i].x + 0.1f, fPos[i].y - 0.1f);
			if (bReverse == true)
				--iShape;
			else
				++iShape;
		}
		else if (5 == iShape)
		{
			glBegin(GL_POLYGON);
			glVertex2f(fPos[i].x, fPos[i].y + 0.2f);
			glVertex2f(fPos[i].x - 0.2f, fPos[i].y);
			glVertex2f(fPos[i].x - 0.1f, fPos[i].y - 0.2f);
			glVertex2f(fPos[i].x + 0.1f, fPos[i].y - 0.2f);
			glVertex2f(fPos[i].x + 0.2f, fPos[i].y);
			glEnd();
			bReverse = true;
			--iShape;
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ�
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(-500, -500, -700, -700, -1.0, -1.0);
}