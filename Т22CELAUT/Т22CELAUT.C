#include <stdio.h>

#include "CELAUT.H"

int num = 0;
void Display( void )
{
  int K1[FRAME_H*FRAME_W];
  int i;

  for (i = 0; i < FRAME_H*FRAME_W; i++)
    K1[i] = 0;

  glClear(GL_COLOR_BUFFER_BIT);

  FieldDraw(F1);

   for (i = 0; i < FRAME_H*FRAME_W; i++)
  {
    if (i % FRAME_W == 0)
      printf("\n");
    printf("%d", F1[i]);
  }
  printf("\n");
 /*
 for (i = 0; i < (FRAME_H + 1)*(FRAME_W + 1); i++)
  {
    if (i % (FRAME_W + 1)== 0)
      printf("\n");
    printf("%d", F3[i]);
  }                   */
  Claster_lab(F1, K1);
  for (i = 0; i < FRAME_H*FRAME_W; i++)
    {                      
    if (i % (FRAME_W) == 0)
      printf("\n");
    printf("%d", K1[i]);
  } 
   
  NewGeneration(F1, F2);
  memcpy(F1, F2, FRAME_W * FRAME_H);
  glPixelZoom(8, 8);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
 /// printf("%i\n", Print_file(F1));
  printf("\n+1 iteration ");
  printf("%i\n", num);
  num++;
  if (num == 13)
  {
    Claster_lab(F1, K1);
    
  }
  getchar();
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
  
 /* F3 = malloc(FRAME_W * FRAME_H);
  if (F3 == NULL)
  {
    printf("Error: Not enough memory!\n");
    return;
  } */

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