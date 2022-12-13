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
  int x, y, H = FRAME_H, W = FRAME_W, c[5], value = 0, i = 0, n, l = 0;
  
  for (y = 0; y < H; y += (H - 1))
  {
    for (x = 0; x < H; x += (H - 1))
    {
      n = 0;
      switch (l)
      {
      case 0: 
        {
          c[0] = GetCell(F1, x, y + 1);
          c[1] = GetCell(F1, x + 1, y);
          c[2] = GetCell(F1, x, y);
          l++;
          break;
        }
      case 1: 
        {
          c[0] = GetCell(F1, x, y + 1);
          c[1] = GetCell(F1, x - 1, y);
          c[2] = GetCell(F1, x, y);
          l++;
          break;
        }
      case 2: 
        {
          c[0] = GetCell(F1, x, y - 1);
          c[1] = GetCell(F1, x + 1, y);
          c[2] = GetCell(F1, x, y);
          l++;
          break;
        }
      case 3: 
        {
          c[0] = GetCell(F1, x, y - 1);
          c[1] = GetCell(F1, x - 1, y);
          c[2] = GetCell(F1, x, y);
          break;
        }
      }
      if (c[2] == 1 || c[2] == 2)                          
      {
        for (i = 0; i < 2; i++)
          n += (c[i] ? 0 : 1);  ///number of inactive cells   2 -> -1
        if (n == 0)
          SetCell(F2, x, y, (rand() % 2 + 1));
        else
        {
          value = 0;
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
          for (i = 0; i < 2; i++)
            n += (c[i] ? 0 : 1); ///n -> inactive
          if (n != 2)            ///have active cells at the neighbours 
          {
            value = 0;
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

  for (y = 0, l = 0; y < H; y += (H - 1), l++)
  {
    for (x = 1; x < W - 1; x++)
    {
      n = 0;
      switch (l)
      {
      case 0: 
        {
          c[0] = GetCell(F1, x, y + 1);
          c[1] = GetCell(F1, x + 1, y);
          c[2] = GetCell(F1, x - 1, y);
          c[3] = GetCell(F1, x, y);
          break;
        }
      case 1: 
        {
          c[0] = GetCell(F1, x, y - 1);
          c[1] = GetCell(F1, x - 1, y);
          c[2] = GetCell(F1, x + 1, y);
          c[3] = GetCell(F1, x, y);
          break;
        }
      }
      if (c[3] == 1 || c[3] == 2)                          
      {
        for (i = 0; i < 3; i++)
          n += (c[i] ? 0 : 1);  ///number of inactive cells   2 -> -1
        if (n == 0)
          SetCell(F2, x, y, (rand() % 2 + 1));
        else
        {
          value = 0;
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
          for (i = 0; i < 3; i++)
            n += (c[i] ? 0 : 1); ///n -> inactive
          if (n != 3)            ///have active cells at the neighbours 
          {
            value = 0;
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
  
  for (y = 1, l = 0; y < H - 1; y++)
  {
    for (x = 0; x < W; x += W - 1, l++)
    {
      n = 0;
      switch (l)
      {
      case 0: 
        {
          c[0] = GetCell(F1, x, y + 1);
          c[1] = GetCell(F1, x + 1, y);
          c[2] = GetCell(F1, x, y - 1);
          c[3] = GetCell(F1, x, y);
          break;
        }
      case 1: 
        {
          c[0] = GetCell(F1, x, y - 1);
          c[1] = GetCell(F1, x - 1, y);
          c[2] = GetCell(F1, x, y + 1);
          c[3] = GetCell(F1, x, y);
          l = 0;
          break;
        }
      }
      if (c[3] == 1 || c[3] == 2)                          
      {
        for (i = 0; i < 3; i++)
          n += (c[i] ? 0 : 1);  ///number of inactive cells   2 -> -1
        if (n == 0)
          SetCell(F2, x, y, (rand() % 2 + 1));
        else
        {
          value = 0;
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
          for (i = 0; i < 3; i++)
            n += (c[i] ? 0 : 1); ///n -> inactive
          if (n != 3)            ///have active cells at the neighbours 
          {
            value = 0;
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


  for (y = 1; y < H; y++)                                    
    for (x = 1; x < W; x++)
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
          value = 0;
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

 /// x = (x + W) % W;   ///donut
 /// y = (y + H) % H;
  return F[y * W + x];   ///012
}

void PutPixel( int x, int y, byte b, byte g, byte r )
{
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

void FieldInit( byte *F )     
{
  int x, y, H = FRAME_H, W = FRAME_W;

  for (y = 0; y < H; y++)
  {
    for (x = 0; x < W; x++)
    {
      if ((rand() % 40) == 1)
        F[y * W + x] = ((rand() % 3));  
      else
        F[y * W + x] = 0;
    }
  }
}

int Print_file( byte *F )
{
  int active = 0, inactive = 0, x, y;
  FILE *filename;

  if ((filename = fopen("text.txt", "a")) == NULL)
  {
    printf("File is not found\n");
    return 0;
  }
  for (y = 0; y < FRAME_H; y++)
  {
    for (x = 0; x < FRAME_W; x++)
    {
      if (GetCell(F1, x, y) == 0)
        inactive++;
      else
        active++;
    }
  }
  ///printf("a: %i, ina: %i", active, inactive); 
  fprintf(filename, "%i \n", active);
  fclose(filename);
  return 1;
}

void Clacter_lab( byte *F1, int *F2 )
{
  int y, x;
  int largest_label = 0, labels[FRAME_W * FRAME_H], i, left, below; 

  for (i = 0; i < FRAME_W * FRAME_H; i++)
  {
    labels[i] = 0;
  }

  for (y = 1; y < FRAME_H; y++)
  {
    for (x = 1; x < FRAME_W; x++)
    {
      if ((GetCell(F1, x, y) == 1) || (GetCell(F1, x, y) == 2))
      {
        left = GetCell(F1, x - 1, y);
        below = GetCell(F1, x, y - 1);

        if ((left == 0) || (below == 0))
        {
          largest_label = largest_label + 1;
          F2[x + y * FRAME_H] = largest_label;
        }
        else 
        {
          if ((left != 0) && (below == 0)) 
            F2[x + y * FRAME_H] = find(left, labels);
          else
          {
            if ((left == 0) && (below != 0))
              F2[x + y * FRAME_H] = find(below, labels);
            else        
            {
              uni(left, below, labels);
              F2[x + y * FRAME_H] = find(left, labels);
            }
          }
        }
      }
    }
  } 
}
void uni( int x, int y, int *labels )
{
  labels[find(x, labels)] = find(y, labels);
}

int find( int x, int *labels )
{
  int y = x;

  while (labels[y] != y)
    y = labels[y];
  while (labels[x] != x)
  {
    int z = labels[x];
    
    labels[x] = y;
    x = z;
  }
  return y;
}