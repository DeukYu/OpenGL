#include <gl\freeglut.h>
#include <time.h>

void drawScene(void);
void reshape(int w, int h);

POINT Window_Pos = {100,100};
POINT Window_Size = {800,600};

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
	glutMainLoop(); // GLUT �̺�Ʈ ���μ��� ���� ����
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ������
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü ĥ�ϱ�
	glBegin(GL_LINES);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
	glColor3f(1.0f/255.0f * (rand()%255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // �׸��� ���� 'green'���� ����
	glRectf(-1.0f, 1.0f, -0.7f, 0.7f); // �簢�� �׸��� - ���� ��
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // �׸��� ���� 'green'���� ����
	glRectf(-1.0f, -1.0f, -0.7f, -0.7f); // �簢�� �׸��� - ���� �Ʒ�
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // �׸��� ���� 'green'���� ����
	glRectf(1.0f, 1.0f, 0.7f, 0.7f); // �簢�� �׸��� - ������ ��
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // �׸��� ���� 'green'���� ����
	glRectf(0.7f, -0.7f, 1.0f, -1.0f); // �簢�� �׸��� - ������ �Ʒ�
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // �׸��� ���� 'green'���� ����
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0.0f);
	glVertex3f(0.2f, -0.2f, 0.0f);
	glEnd();
	glFlush(); // ȭ�鿡 ����ϱ�
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}