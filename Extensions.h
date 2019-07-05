#if !defined( WGLX_EXTENSIONS_H_INCLUDED )
#define WGLX_EXTENSIONS_H_INCLUDED

#pragma once

/** @file *//********************************************************************************************************

                                                     Extensions.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/Extensions.h#3 $

	$NoKeywords: $

 ********************************************************************************************************************/


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


/********************************************************************************************************************/
#define WGL_ARB_extensions_string			1
/********************************************************************************************************************/

/* char const * wglGetExtensionsStringARB( HDC hdc ); */

typedef char const * ( APIENTRY * PFNWGLGETEXTENSIONSSTRINGARB )( HDC hdc );



#define WGLX_BIND_EXTENSION( fn, name, type )			( fn = ( type )WGlx::GetExtensionFunction( #fn, #name ) )
#define WGLX_BIND_WGL_EXTENSION( hDC, fn, name, type )	( fn = ( type )WGlx::GetWGLExtensionFunction( hDC, #fn, #name ) )

namespace WGlx
{

/// Returns @c true if the WGL extension is supported
bool ExtensionIsSupported( HDC hDC, char const * pExtensionName );

/// Returns a pointer an OpenGL extension's function
PROC GetExtensionFunction( char const * fName, char const * eName );

/// Returns a pointer a WGL extension's function
PROC GetWGLExtensionFunction( HDC hDC, char const * fName, char const * eName );

} // namespace WGlx


#endif // !defined( WGLX_EXTENSIONS_H_INCLUDED )
