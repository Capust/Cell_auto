#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glut.h>

#define FRAME_W 5///512
#define FRAME_H 5///128
#define PH 400
#define PE 1
#define PD 500
                                              
typedef unsigned char byte;

byte Frame[FRAME_H][FRAME_W][3], *F1, *F2;

void FieldDraw( byte *F );
void NewGeneration( byte *F1, byte *F2 );
void SetCell( byte *F, int x, int y, int value );
int GetCell( byte *F, int x, int y );
int GetNeighbours( byte *F, int x, int y );
void PutPixel( int x, int y, byte b, byte g, byte r );
void FieldInit( byte *F );
int random_gen( int p );
int Print_file( byte *F );
void Claster_lab( byte *F1, int *labels );
///void uni( int x, int y, int *labels );
int find(int n, int x, int y, int *labels );
void Copy_of_F( byte *Copy, byte *F );



