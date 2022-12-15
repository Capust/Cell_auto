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
        else if (GetCell(F, x, y) == 0)
          PutPixel(x, y, 255, 255, 255);
      }
    }
}

void NewGeneration( byte *F1, byte *F2 )
{
  int x, y, H = FRAME_H, W = FRAME_W, c[5], value = 0, i = 0, n, l = 0;
  
  for (y = 0; y < H; y += (H - 1))
  {
    for (x = 0; x < W; x += (W - 1))
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

  if (x < 0 || y < 0)
    return 0;
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
      if ((rand() % 2) == 1)
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
void Claster_lab( byte *F3, int *labels )
{
  int y, x;
  int largest_label = 0, i, left, below; 

  for (i = 0; i < FRAME_H * FRAME_W; i++)
    labels[i] = 0;

  for (y = 0; y < FRAME_H + 1; y++)
  {
    for (x = 0; x < FRAME_W + 1; x++)
    {
      if ((GetCell(F3, x, y) == 1) || (GetCell(F3, x, y) == 2))
      {
        left = GetCell(F3, x - 1, y);
        below = GetCell(F3, x, y - 1);
       /// printf("L %i| %i |B %i, x: %i, y: %i\n",  left,F3[x + y * (FRAME_W + 1)], below, x - 1, y - 1);
        if ((left == 0) && (below == 0))
        {
          largest_label = largest_label + 1;
          labels[x + y * FRAME_W] = largest_label;
        }
        else 
        {
          if ((left != 0) && (below == 0)) 
            labels[x + y * FRAME_W] = labels[(x - 1) + y * FRAME_W];
          else
          {
            if ((left == 0) && (below != 0))
              labels[x + y * FRAME_W] = labels[x + (y - 1) * FRAME_W];
            else        
            {
              labels[x + y * FRAME_W] = find(x + y * FRAME_W, labels[(x - 1) + y * FRAME_W], labels[x + (y - 1) * FRAME_W], labels);
            }
          }
        }
      } 
    }   
  }
}

int find(int n, int x, int y, int *labels )
{
  int i;

  for (i = 0; i < n; i++)
  {
    if (labels[i] = y)
      labels[i] = x;
  }
  return x;
}

/*
void Claster_lab( byte *F3, int *labels )
{
  int y, x, x1, y1;
  int largest_label = 0, i, left, below; 

  for (i = 0; i < FRAME_H*FRAME_W; i++)
    labels[i] = 0;

  for (y = 1; y < FRAME_H + 1; y++)
  {
    for (x = 1; x < FRAME_W + 1; x++)
    {
      x1 = x - 1;
      y1 = y - 1;
      if ((F3[x + y * (FRAME_W + 1)] == 1) || (F3[x + y * (FRAME_W + 1)] == 2))
      {
        left = F3[x1 + y * (FRAME_W + 1)];
        below = F3[x + y1 * (FRAME_W + 1)];
       /// printf("L %i| %i |B %i, x: %i, y: %i\n",  left,F3[x + y * (FRAME_W + 1)], below, x - 1, y - 1);
        if ((left == 0) && (below == 0))
        {
          largest_label = largest_label + 1;
          labels[x1 + y1 * FRAME_W] = largest_label;
        }
        else 
        {
          if ((left != 0) && (below == 0)) 
            labels[x1 + y1 * FRAME_W] = labels[(x1 - 1) + y1 * FRAME_W];
          else
          {
            if ((left == 0) && (below != 0))
              labels[x1 + y1 * FRAME_W] = labels[x1 + (y1 - 1) * FRAME_W];
            else        
            {
              labels[x1 + y1 * FRAME_W] = find(x1 + y1 * FRAME_W, labels[(x1 - 1) + y1 * FRAME_W], labels[x1 + (y1 - 1) * FRAME_W], labels);
            }
          }
        }
      } 
    }   
  }
  printf("\n");
}
/*void uni( int x, int y, int *labels )
{
  labels[find(x, labels)] = find(y, labels);
}*/
/*
int find(int n, int x, int y, int *labels )
{
  int i;

  for (i = 0; i < n; i++)
  {
    if (labels[i] = y)
      labels[i] = x;
  }
  return x;
}
void Copy_of_F( byte *Copy, byte *F )
{
  int i, k = 0;

  for (i = 0; i < FRAME_W + 1; i++)
    Copy[i] = 0;
  for (i = FRAME_W + 1; i < (FRAME_W + 1) * (FRAME_H + 1); i++)
  {
    if (i % (FRAME_W + 1) == 0)
    {
      Copy[i] = 0;
      k++;
    }
    else
      Copy[i] = F[i - FRAME_W - 1 - k];
  }
}*/