// Messages are the scrolling messages within the UI.
// This file contains update and retrieval functions.

#include "7drltypes.h"

#define MAX_MSG_SIZE   ( 80 )

static int oldest_message = ( MAX_MESSAGES - 1 );

char messages[ MAX_MESSAGES ][ MAX_MSG_SIZE ];

void init_messages( void )
{
   bzero( messages, ( size_t ) sizeof( messages ) );

   return;
}

void add_message( char *message )
{


}

char *get_message( int pos )
{
   return NULL;

}

