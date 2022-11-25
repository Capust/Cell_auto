#include <stdio.h>

#include "CELAUT.H"

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  FieldDraw(F1);
  NewGeneration(F1, F2);

  memcpy(F1, F2, FRAME_W * FRAME_H);
  glPixelZoom(4, 4);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
  printf("+1 iteration\n");
}

void Keyboard( byte Key, int x, int y )
{
  if (Key == 27)
    exit(30);
}

void main( int argc, char *argv[] )
{
  F1 = malloc(FRAME_W * FRAME_H);
  if (F1 == NULL)
  {
    printf("Error: Not enough memory!\n");
    return;
  }
  F2 = malloc(FRAME_W * FRAME_H);
  if (F2 == NULL)
  {
    printf("Error: Not enough memory!\n");
    return;
  }
  FieldInit(F1);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("cellauto");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
}