#include <gl\freeglut.h>
#include <time.h>
#include <iostream>

using namespace std;

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
	srand((unsigned)time(0));
	int H = (rand() % 30) + 1;
	int W = (rand() % 30) + 1;
	int a = 600 / H;
	int b = 600 / W;
	float RGB[3] = { (1.0f / 255.0f)*(rand() % 256),(1.0f / 255.0f)*(rand() % 256) ,(1.0f / 255.0f)*(rand() % 256) };
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체 칠하기
	cout << H << endl;
	cout << W << endl;
	cout << a << endl;
	cout << b << endl;
	for (int i = 0; i < H; ++i)
	{
		RGB[0] += 0.01f;
		RGB[1] += 0.01f;
		RGB[2] += 0.01f;
		for (int j = 0; j < W; ++j)
		{
			RGB[0] += 0.01f;
			RGB[1] += 0.01f;
			RGB[2] += 0.01f;
			glColor3f(RGB[0], RGB[1], RGB[2]);
			glRectf(-300 + (i * a), -300 + (j + 1) * b, -300 + ((i+1) * a),-300 + j * b);
		}
	}
	glFlush(); // 화면에 출력하기
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -1.0, 1.0);
}