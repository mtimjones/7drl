// astar.c -- A* Implementation

#include "7drltypes.h"

// Reused this code from my published book "AI Application Programming, 2nd Edition"

struct node_s;

typedef struct node_s
{
   struct node_s *parent;
   double g;
   double h;
   double f;
   int y;
   int x;
} node_t;

#define MAX_LIST     50

typedef struct {
   int numElems;
   node_t *elem[ MAX_LIST ];
} list_t;

#define Y_MAX   MAP_NLINES
#define X_MAX   MAP_NCOLS

#define MIN_COST  ( ( double ) 1.0 )
#define ALPHA     ( ( double ) 0.5 )

node_t *start_node_p;

list_t openList_p;
list_t closedList_p;

void listInit( list_t *list_p )
{
   int i;

   list_p->numElems = 0;

   for ( i = 0 ; i < MAX_LIST ; i++ )
   {
      list_p->elem[ i ] = ( node_t * ) NULL;
   }

   return;
}

int listEmpty( list_t *list_p )
{
   if ( list_p->numElems == 0 ) return 1;
   else return 0;
}

node_t *listFindBest( list_t *list_p )
{
   int i;
   int best = -1;

   for ( i = 0 ; i < MAX_LIST ; i++ )
   {
      if ( list_p->elem[i] != 0 ) 
      {
         best = i++;
         break;
      }
   }

   for ( ; i < MAX_LIST ; i++ )
   {
      if ( list_p->elem[i] != 0 )
      {
         if ( list_p->elem[i]->f < list_p->elem[best]->f )
         {
            best = i;
         }
      }
   }

   return list_p->elem[ best ];
}

int listPresent( list_t *list_p, int y, int x )
{
   int i;

   for ( i = 0 ; i < MAX_LIST ; i++ )
   {
      if ( list_p->elem[i] )
      {
         if ( ( list_p->elem[i]->y == y ) && ( list_p->elem[i]->x == x ) )
         {
            return 1;
         }
      }
   }

   return 0;
}

void listAdd( list_t *list_p, node_t *elem_p )
{
   int i;

   for ( i = 0 ; i < MAX_LIST ; i++ ) 
   {
      if ( list_p->elem[i] == ( node_t *)NULL )
      {
         list_p->elem[i] = elem_p;
         list_p->numElems++;
         break;
      }
   }

   return;
}

node_t *listGet( list_t *list_p, int y, int x, int remove )
{
   int i;
   node_t *node = ( node_t * )NULL;

   for ( i = 0 ; i < MAX_LIST ; i++ )
   {
      if ( list_p->elem[i] )
      {
         if ( ( list_p->elem[i]->y == y ) && ( list_p->elem[i]->x == x ) )
         {
            node = list_p->elem[i];
            if ( remove )
            {
               list_p->elem[i] = (node_t *)NULL;
               list_p->numElems--;
            }
            break;
         }
      }
   }

   return node;
}

node_t *allocateNode( int y, int x )
{
   node_t *node_p;

   node_p = malloc( sizeof( node_t ) );

   node_p->g = node_p->h = node_p->f = ( double )0.0;
   node_p->parent = ( node_t *) NULL;

   node_p->y = y; node_p->x = x;

   return node_p;
}

const struct {
   int y;
   int x;
} succ[4] = { { -1, 0}, { 1, 0 }, { 0, 1 }, { 0, -1 } };

node_t *findSuccessorNode( node_t *curNode_p, int i )
{
   node_t *successor_p = ( node_t *)NULL;
   int y, x;
   char item;

   y = curNode_p->y + succ[i].y;
   x = curNode_p->x + succ[i].x;

   item = map_get_item( y, x );
   if ( ( item == SPACE_ICON ) || ( item == PLAYER_ICON ) )
   {
      successor_p = allocateNode( y, x );
   }

   return successor_p;
}

double calc_h( node_t *node_p, int goal_y, int goal_x )
{
   double h;

   h = (double)( MIN_COST *
                  ( abs( ( double ) node_p->y - ( double ) goal_y ) +
                    abs( ( double ) node_p->x - ( double ) goal_x ) ) );

   return h;
}

double calc_g( node_t *node_p )
{
   double g;

   g = 1.0 + ALPHA * ( node_p->g - 1.0 );

   return g;
}

void cleanup( void )
{
   int i;

   for ( i = 0 ; i < MAX_LIST ; i++ )
   {
      if ( openList_p.elem[ i ] ) free( openList_p.elem[ i ] );
      if ( closedList_p.elem[ i ] ) free( closedList_p.elem[ i ] );
   }

   return;
}

void getBestNextStep( node_t *walker, int *Y, int *X )
{
   walker = ( node_t * )walker->parent;

   while ( walker->parent )
   {
      *Y = walker->y; *X = walker->x;
      walker = ( node_t * ) walker->parent;
   }

   return;
}


void MoveTowardsPlayer( int start_y, int start_x, int goal_y, int goal_x, int *Y, int *X )
{
   node_t *curNode_p;

   // If we don't find a path, just remain calm...
   *Y = *X = 0;

   listInit( &openList_p );
   listInit( &closedList_p );

   start_node_p = allocateNode(start_y, start_x);

   /* Begin with our start node as the initial node */
   listAdd( &openList_p, start_node_p );

   while ( !listEmpty(&openList_p) ) {

     curNode_p = listFindBest( &openList_p );
     (void)listGet( &openList_p, curNode_p->y, curNode_p->x, 1 );
     listAdd( &closedList_p, curNode_p );

     if ((curNode_p->y == goal_y) && (curNode_p->x == goal_x)) 
     {
//       getBestNextStep( curNode_p, Y, X );
       *Y = start_y - *Y;
       *X = start_x - *X;

       cleanup();

       return;
     } else {

       int i;
       node_t *successor_p;
       node_t *temp;

       for (i = 0 ; i < 4 ; i++) {

         successor_p = findSuccessorNode( curNode_p, i );

         if (successor_p != (node_t *)NULL) {

           successor_p->h = calc_h( successor_p, goal_y, goal_x );
           successor_p->g = curNode_p->g + calc_g( curNode_p );
           successor_p->f = successor_p->g + successor_p->h;

           if (listPresent(&openList_p, successor_p->y, successor_p->x)) {
          
             temp = listGet( &openList_p, successor_p->y, successor_p->x, 0 );

             if (temp->f < successor_p->f) {

               free( successor_p );
               continue;

             }

           }

           if (listPresent(&closedList_p, successor_p->y, successor_p->x)) {
          
             temp = listGet( &closedList_p, successor_p->y, successor_p->x, 0 );

             if (temp->f < successor_p->f) {

               free( successor_p );
               continue;

             }

           }

           temp = listGet( &openList_p, 
                            successor_p->y, successor_p->x, 1 );
           if (temp) free(temp);

           temp = listGet( &closedList_p, 
                            successor_p->y, successor_p->x, 1 );
           if (temp) free(temp);

           successor_p->parent = (node_t *)curNode_p;
           listAdd( &openList_p, successor_p );

         }

       }

     }

   }

   // Solution not found...
  
   cleanup();

   return;
}
