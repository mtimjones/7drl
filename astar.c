// astar.c -- A* Implementation

#include "7drltypes.h"

// Reused this code from my published book "AI Application Programming, 2nd Edition"

//FILE *ofp;

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

#define MAX_LIST     500

typedef struct {
   int numElems;
   node_t *elem[ MAX_LIST ];
} list_t;

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
      if ( list_p->elem[i] ) 
      {
         best = i++;
         break;
      }
   }

   for ( ; i < MAX_LIST ; i++ )
   {
      if ( list_p->elem[i] )
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
   int x;
   int y;
} succ[4] = { { 0, -1}, { 0, 1 }, { 1, 0 }, { -1, 0 } };

node_t *getNeighborNode( node_t *curNode_p, int i )
{
   node_t *successor_p = ( node_t *)NULL;
   int y, x;
   char item;

   y = curNode_p->y + succ[i].y;
   x = curNode_p->x + succ[i].x;

   item = map_get_item( y, x );
   if ( ( item == SPACE_ICON ) || ( item == PROTECTOR_ICON ) )
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

//   fclose( ofp );

   return;
}

void getBestNextStep( node_t *walker, int *Y, int *X )
{
   walker = ( node_t * )walker->parent;

   if ( walker )
   {
      *Y = walker->y, *X = walker->x;
   } 
   else
   {
      *Y = *X = 0;
   }

if ( 0 ) {
   char line[80];
   sprintf( line, "getBestNextStep %d, %d", *Y, *X );
   add_message( line );
}

   return;
}


void MoveTowardsPlayer( int start_y, int start_x, int goal_y, int goal_x, int *Y, int *X )
{
   node_t *current;

//   ofp = fopen( "trace.astar", "w" );

   // If we don't find a path, just remain calm...
   *Y = *X = 0;

   // Initialize the open (frontier) and closed lists.
   listInit( &openList_p );
   listInit( &closedList_p );

   // Allocate our initial node (from the starting point) and add to the open list
   start_node_p = allocateNode( start_y, start_x );
   start_node_p->f = calc_h( start_node_p, start_y, start_x );
   listAdd( &openList_p, start_node_p );

//   fprintf( ofp, "Start node at %d, %d\n", start_y, start_x );
//   fprintf( ofp, "Goal node is %d, %d\n", goal_y, goal_x );

   while ( !listEmpty(&openList_p) )
   {
      // Find the best node on the frontier
      current = listFindBest( &openList_p );

      // Remove it from the open list
      (void)listGet( &openList_p, current->y, current->x, 1 );

      // Push it to the closed list
      listAdd( &closedList_p, current );

      // Have we reached the goal?
      if ((current->y == goal_y) && (current->x == goal_x)) 
      {
         getBestNextStep( current, Y, X );

         *Y = *Y - goal_y;
         *X = *X - goal_x;

         cleanup();

         return;

      } else {

         // Find each of the four conway neighbors
         for ( int i = 0 ; i < 4 ; i++ ) 
         {
            node_t *neighbor;
            node_t *stored_neighbor;
            double tentative_Gscore = 0.0;

            neighbor = getNeighborNode( current, i );

            // If this position is not legal, skip it.
            if ( !neighbor ) continue;

            // If this node is on the close list, ignore it and move on.
            if ( listPresent( &closedList_p, neighbor->y, neighbor->x ) )
            {
               free( neighbor );
               continue;
            }

            // Calculate this neighbors gscore
            tentative_Gscore = current->g + 1.0;

            // If we're searching too far, just terminate early.
            if ( tentative_Gscore > 20 )
            {
//               fprintf( ofp, "Early termination... %g\n", tentative_Gscore );
               free( neighbor );
               cleanup( );
               return;
            }

            stored_neighbor = listGet( &openList_p, neighbor->y, neighbor->x, 0 );

            // Do we have a node on the open list already?
            if ( stored_neighbor )
            {
               // Yes, but the score is lower, so leave it as is.
               if ( tentative_Gscore >= stored_neighbor->g )
               {
                  free( neighbor );
                  continue;
               }
               else
               {
                  // Remove the currently stored neighbor node at this position.
                  listGet( &openList_p, neighbor->y, neighbor->x, 1 );
                  
                  // Add the new node here which is a better path.
                  listAdd( &openList_p, neighbor );
               }
            }
            else
            {
               // No node for this position, so add to the open list
               listAdd( &openList_p, neighbor );
            }

            // Score this new neighbor.
            neighbor->parent = current;
            neighbor->g = tentative_Gscore;
            neighbor->f = tentative_Gscore + calc_h( neighbor, goal_y, goal_x );

//            fprintf(ofp, "better %d, %d g%g f%g\n", neighbor->y, neighbor->x, neighbor->g, neighbor->f );
         }
      }
   }

   // We failed to find a solution.
   
   cleanup();

   return;
}
