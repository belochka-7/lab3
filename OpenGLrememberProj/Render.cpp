#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

void calcBezeir(double P[][3], double res[][3], int n)
{
	for (int i = 0; i < 3; ++i)
		res[0][i] = P[0][i];

	for (int i = 1; i < n-1; ++i)
	{
		double t = i * (1.0 / (n-2)), t2 = t * t, t3 = t2 * t;
		double tI = 1 - t, tI2 = tI*tI, tI3 = tI2*tI; 
		for (int j = 0; j < 3; ++j)
			res[i][j] = tI3*P[0][j] + 3*t*tI2*P[1][j] + 3*t2*tI*P[2][j] + t3*P[3][j];
	}

	for (int i = 0; i < 3; ++i)
		res[n-1][i] = P[3][i];
}

void calcHermite(double P[][3], double res[][3], int n)
{
	for (int i = 0; i < 3; ++i)
		res[0][i] = P[0][i];

	for (int i = 0; i < n; ++i)
	{
		double t = i * (1.0 / (n-2)), t2 = t * t, t3 = t2 * t;
		for (int j = 0; j < 3; ++j)
			res[i][j] = P[0][j]*(2*t3-3*t2+1) + P[1][j]*(-2*t3+3*t2) + P[2][j]*(t3-2*t2+t) + P[3][j]*(t3-t2);
	}

	for (int i = 0; i < 3; ++i)
		res[n - 1][i] = P[1][i];
}

void drawCurve(double P[][3], int n)
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; ++i)
		glVertex3dv(P[i]);
	glEnd();
}

void drawLines(double P[][3])
{
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; ++i)
		glVertex3dv(P[i]);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; ++i)
		glVertex3dv(P[i]);
	glEnd();
}

void drawVectors(double P[][3])
{
	glBegin(GL_LINES);
	for (int i = 0; i < 2; ++i)
	{
		glVertex3dv(P[i]);
		glVertex3d(P[i][0] + P[i+2][0], P[i][1] + P[i+2][1], P[i][2] + P[i+2][2]);
	}
	glEnd();
}

void drawBezeir(double P[][3], double curve[][3], int N, double r, double g, double b)
{
	calcBezeir(P, curve, N);
	glColor3d(r, g, b);
	glLineWidth(3);
	drawCurve(curve, N);
	glPointSize(10);
	glLineWidth(1);
	drawLines(P);
}

void drawHermite(double P[][3], double curve[][3], int N, double r, double g, double b)
{
	calcHermite(P, curve, N);
	glColor3d(r, g, b);
	glLineWidth(3);
	drawCurve(curve, N);
	glLineWidth(1);
	drawVectors(P);
}

void Render(double delta_time)
{
	double bezeir1[][3] = { { 0, 0, 0 },
							{ 3, 2, 2 },
							{ 2, 3, 4 },
							{ 3, 1, 2 } };
	double bezeir2[][3] = { { 0, 0, 0 },
							{ -2, 3, 2 },
							{ -4, 2, 5 },
							{ -2, 2, 5 } };
	double hermite1[][3] = { { 0, 0, 0 },
							 { 4, -3, 2 },
							 { 3, -4, 3 },
						     { 5, -5, 2 } };
	double hermite2[][3] = { { 0, 0, 0 },
							 { -2, -4, 1 },
							 { -1, -2, 2 },
							 { -4, -1, 1 } };
	double curve[50][3];
	drawBezeir(bezeir1, curve, 50, 0.75, 0.75, 0);
	drawBezeir(bezeir2, curve, 50, 0, 0.75, 0.75);
	drawHermite(hermite1, curve, 50, 0.75, 0, 0.75);
	drawHermite(hermite2, curve, 50, 0.75, 0.75, 0.75);
}