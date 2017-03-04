// Messages are the scrolling messages within the UI.
// This file contains update and retrieval functions.

#include "7drltypes.h"

#define MAX_MSG_SIZE   ( NCOLS - 2 )

static int write_ptr = 0;

char messages[ MAX_MESSAGES ][ MAX_MSG_SIZE ];

void init_messages( void )
{
   bzero( messages, sizeof( messages ) );
   return;
}

void add_message( char *msg )
{
   int i = 0;
   size_t len = strlen( msg );

   // Copy the message into the buffer and pad with spaces
   while ( i < ( MAX_MSG_SIZE - 1 ) )
   {
      if ( i < len ) messages[ write_ptr ][ i ] = msg[ i ];
      else messages[ write_ptr ][ i ] = ' ';
      i++;
   }

   // Null terminate
   messages[ write_ptr ][ ( MAX_MSG_SIZE - 1 ) ] = 0;

   if ( ++write_ptr >= MAX_MESSAGES  )
   {
      write_ptr = 0;
   }

   return;
}

char *get_message( int pos )
{
   int read_ptr;

   read_ptr = write_ptr + pos;

   if (read_ptr >= MAX_MESSAGES )
   {
      read_ptr -= MAX_MESSAGES;
   }

   return &messages[ read_ptr ][ 0 ];
}

