#include <gl\freeglut.h>
#include <time.h>

void drawScene(void);
void reshape(int w, int h);

POINT Window_Pos = {100,100};
POINT Window_Size = {800,600};

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
	glutMainLoop(); // GLUT 이벤트 프로세싱 루프 실행
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체 칠하기
	glBegin(GL_LINES);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
	glColor3f(1.0f/255.0f * (rand()%255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // 그리기 색을 'green'으로 지정
	glRectf(-1.0f, 1.0f, -0.7f, 0.7f); // 사각형 그리기 - 왼쪽 위
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // 그리기 색을 'green'으로 지정
	glRectf(-1.0f, -1.0f, -0.7f, -0.7f); // 사각형 그리기 - 왼쪽 아래
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // 그리기 색을 'green'으로 지정
	glRectf(1.0f, 1.0f, 0.7f, 0.7f); // 사각형 그리기 - 오른쪽 위
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // 그리기 색을 'green'으로 지정
	glRectf(0.7f, -0.7f, 1.0f, -1.0f); // 사각형 그리기 - 오른쪽 아래
	glColor3f(1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255), 1.0f / 255.0f * (rand() % 255)); // 그리기 색을 'green'으로 지정
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0.0f);
	glVertex3f(0.2f, -0.2f, 0.0f);
	glEnd();
	glFlush(); // 화면에 출력하기
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}