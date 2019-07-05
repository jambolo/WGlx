/** @file *//********************************************************************************************************

                                                    Extensions.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/Extensions.cpp#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "Extensions.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <cstdio>

#include "Glx/Extensions.h"

#include "Misc/Trace.h"


namespace WGlx
{


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

PROC GetExtensionFunction( char const * fName, char const * eName )
{
	PROC	address	= NULL;

	if ( Glx::Extension::IsSupported( eName ) )
	{
		address = wglGetProcAddress( fName );
		trace( "WGlx::GetExtensionFunction: %s::%s@0x%08x\n", eName, fName, address );
	}
	else
	{
		trace( "WGlx::GetExtensionFunction: %s is not supported\n", eName );
	}
		
	return address;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

PROC GetWGLExtensionFunction( HDC hDC, char const * fName, char const * eName )
{
	if ( ExtensionIsSupported( hDC, eName ) )
	{
		return wglGetProcAddress( fName );
	}
	else
	{
		return NULL;
	}
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

bool ExtensionIsSupported( HDC hDC, char const * pExtensionName )
{
	bool			isSupported			= false;

	// Get wglGetExtensionsStringARB. If it exists, then see if the extension
	// is supported. Otherwise, NO extensions are supported.

	PFNWGLGETEXTENSIONSSTRINGARB const	wglGetExtensionsStringARB	= ( PFNWGLGETEXTENSIONSSTRINGARB )wglGetProcAddress( "wglGetExtensionsStringARB" );

	if ( wglGetExtensionsStringARB )
	{
		int const		len					= strlen( pExtensionName );
		char const *	pExtensionString	= wglGetExtensionsStringARB( hDC );
		char const *	pMatch;
		char const *	pStart;

//		// Extension names should not have spaces.
//
//		pMatch = ( char * ) strchr( extension, ' ' );
//		if ( pMatch || *extension == '\0' )
//			return 0;

		// Search the extensions string for substrings matching the specified extension name

		for ( pStart = pExtensionString;
			  ( pMatch = ( char * ) strstr( ( char const * ) pStart, pExtensionName ) ) != 0;
			  pStart = pMatch + len )
		{
			// If this is not a substring of an extension then a match is found

			char const	terminator	= pMatch[ len ];

			if ( ( pMatch == pExtensionString || pMatch[ -1 ] == ' ' ) &&
				 ( terminator == ' ' || terminator == '\0' ) )
			{
				isSupported = true;
				break;
			}
		}
	}

	return isSupported;
}


} // namespace WGlx