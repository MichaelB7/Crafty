#include <stdio.h>
#include <math.h>
#define Abs(a)    (((a) > 0) ? (a) : -(a))
#define Max(a,b)  (((a) > (b)) ? (a) : (b))
#define Min(a,b)  (((a) < (b)) ? (a) : (b))
#define Sign(a)   ((a) < 0 ? -1 : +1)

int LMR[64][64];
int LMR_remaining_depth = 1;    /* leave 1 full ply after reductions    */
int LMR_min_reduction = 1;      /* minimum reduction 1 ply              */
int LMR_max_reduction = 7;      /* maximum reduction 7 plies            */
                                  /* next 3 values, 100 = 1.0, 200 = 2.0  */
int LMR_depth_bias = 200;       /* depth is 2x as important as          */
int LMR_moves_bias = 100;       /* moves in the formula.                */
int LMR_scale = 252;            /* smaller numbers increase reductions. */

void InitializeReductions() {
  int depth, moves;

  for (depth = 3; depth < 32; ++depth)
    for (moves = 2; moves < 64; ++moves)
      LMR[depth][moves] =
          Max(Min(log((double) depth * LMR_depth_bias / 100.0) *
              log((double) moves * LMR_moves_bias / 100.0) / (LMR_scale /
                  100.0), LMR_max_reduction), LMR_min_reduction);
}

void main() {
  int i, j;
  InitializeReductions();
  for (i = 0; i < 32; i++) {
    printf("%2d:", i);
    for (j = 0; j < 64; j++)
      printf("%2d", LMR[i][j]);
    printf("\n");
  }
}
