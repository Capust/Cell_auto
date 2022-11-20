#include <string.h>
#include <stdlib.h>
#include <glut.h>

#define FRAME_W 512
#define FRAME_H 128
#define ph 485

                                              
typedef unsigned char byte;

byte Frame[FRAME_H][FRAME_W][3], *F1, *F2;

void FieldDraw( byte *F );
void NewGeneration( byte *F1, byte *F2 );
void SetCell( byte *F, int x, int y, int value );
int GetCell( byte *F, int x, int y );
int GetNeighbours( byte *F, int x, int y );
void PutPixel( int x, int y, byte b, byte g, byte r );
void FieldInit( byte *F );
void BlockSpawn( byte *F, int x, int y );
void BlinkerSpawn( byte *F, int x, int y );