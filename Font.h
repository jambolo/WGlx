#if !defined( WGLX_FONT_H_INCLUDED )
#define WGLX_FONT_H_INCLUDED

#pragma once

/*****************************************************************************

                                    Font.h

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/Font.h#2 $

	$NoKeywords: $

*****************************************************************************/

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>


namespace WGlx
{


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class Font
{
public:

	enum
	{
		NUM_GLYPHS	= 256,
		FIRST_GLYPH	= 0
	};

	Font( HDC hDC );
	Font( HDC hDC, LOGFONT const & fontInfo );

	virtual ~Font();

	// Draw a string
	void DrawString( char const * pText ) const;

	// Draw a single character
	void DrawChar( unsigned int c ) const;

private:
	GLuint	m_DisplayListBase;
};


} // namespace WGlx

#endif // !defined( WGLX_FONT_H_INCLUDED )
