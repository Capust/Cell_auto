#include "CELAUT.H"

int random_gen( int p )
{
  if ((rand() % 10000) >= (p - 1))   /// P+ => 1
    return 0;
  else 
    return 1;
  
}
void FieldDraw( byte *F )
{
  int x, y, H = FRAME_H, W = FRAME_W;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      if (GetCell(F, x, y) == 1)
        PutPixel(x, y, 30, 12, 122);
      else 
      {
        if(GetCell(F, x, y) == 2)                       
          PutPixel(x, y, 122, 12, 30);
        else
          PutPixel(x, y, 255, 255, 255);
      }
    }
}

void NewGeneration( byte *F1, byte *F2 )
{
  int x, y, H = FRAME_H, W = FRAME_W, c[5], value = 0, i, n, m;

  for (y = 0; y < H; y++)                                    
    for (x = 0; x < W; x++)
    { 
      n = 0;
      c[0] = GetCell(F1, x, y - 1);
      c[1] = GetCell(F1, x - 1, y);
      c[2] = GetCell(F1, x + 1, y);
      c[3] = GetCell(F1, x, y + 1);
      c[4] = GetCell(F1, x, y);
      if (c[4] == 1 || c[4] == 2)                          
      {
        for (i = 0; i < 4; i++)
          n += (c[i] ? 0 : 1);  ///number of inactive cells   2 -> -1
        if (n == 0)
          SetCell(F2, x, y, (rand() % 2 + 1));
        else
        {
          for (; n > 0; n--)
            value += random_gen(PD);    ///pd->0.05
          if (value)
            SetCell(F2, x, y, 0);
          else 
            SetCell(F2, x, y, (rand() % 2 + 1));
        }
      }
      else
      {
        n = 0;
        if (random_gen(PE)) 
          SetCell(F2, x, y, (rand() % 2) + 1);
        else///independent spin change pe        
        {
          for (i = 0; i < 4; i++)
            n += (c[i] ? 0 : 1); ///n -> inactive
          if (n != 4)            ///have active cells at the neighbours 
          {
            value = 0;
            for (m = 4 - n; m > 0; m--)
              value += random_gen(PH) ? 1 : 0;    
            if (value)
              SetCell(F2, x, y, (rand() % 2 + 1));
            else 
              SetCell(F2, x, y, 0);
          }
          else
            SetCell(F2, x, y, 0);
        }
      }
    }
}
/*c = GetCell(F1, x, y);
      n = GetNeighbours(F1, x, y);
      if (c && (n < 2 || n > 3))
        c = 0;
      else if (!c && n == 3)
        c = 1;
      SetCell(F2, x, y, c);*/
void SetCell( byte *F, int x, int y, int value )    
{
  int W = FRAME_W, H = FRAME_H;

  x = (x + W) % W;
  y = (y + H) % H;
  F[y * W + x] = value;
}

int GetCell( byte *F, int x, int y )  
{
  int W = FRAME_W, H = FRAME_H;

  x = (x + W) % W;   ///donut
  y = (y + H) % H;
  return F[y * W + x];   ///012
}

void PutPixel( int x, int y, byte b, byte g, byte r )
{
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

void FieldInit( byte *F )       ///+problem: reduction in the population of active 
{
  int x, y, H = FRAME_H, W = FRAME_W;

  for (y = 0; y < H; y++)
  {
    for (x = 0; x < W; x++)
    {
      if ((rand() % 20) == 1)
        F[y * W + x] = ((rand() % 3));     ///-> +-1/0
      else
        F[y * W + x] = 0;
    }
  }
}

