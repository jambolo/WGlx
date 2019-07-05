/*****************************************************************************

                                   Font.cpp

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/Font.cpp#2 $

	$NoKeywords: $

*****************************************************************************/

#include "Font.h"

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

Font::Font( HDC hDC )
{
	// Reserve a contiguous range of display lists for the font. If a range
	// can't be found, then just abort

	m_DisplayListBase = glGenLists( NUM_GLYPHS );
	if ( m_DisplayListBase == 0 )
	{
		return;
	}

	// Create bitmaps for the device context font

	wglUseFontBitmaps( hDC, FIRST_GLYPH, NUM_GLYPHS, m_DisplayListBase );
};


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

Font::Font( HDC hDC, LOGFONT const & fontInfo )
{
	// Reserve a contiguous range of display lists for the font. If a range
	// can't be found, then just abort

	m_DisplayListBase = glGenLists( NUM_GLYPHS );
	if ( m_DisplayListBase == 0 )
	{
		return;
	}

	HFONT	hFont, hOldFont;
	
	// Create the font and select it into the DC

	hFont = CreateFontIndirect( &fontInfo );
	hOldFont = static_cast< HFONT >( SelectObject( hDC, hFont ) );

	// Create bitmaps for the device context font

	wglUseFontBitmaps( hDC, FIRST_GLYPH, NUM_GLYPHS, m_DisplayListBase );

	// Select the previous font and delete the created font now that it no
	// longer needed

	SelectObject( hDC, hOldFont );
	DeleteObject( hFont );
};


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

Font::~Font()
{
	if ( m_DisplayListBase == 0 )
	{
		return;
	}

	glDeleteLists( m_DisplayListBase, NUM_GLYPHS );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void Font::DrawString( char const * pText ) const
{
	if ( m_DisplayListBase == 0 )
	{
		return;
	}

	int const	len	= strlen( pText );

	if ( len > 0 )
	{
		glListBase( m_DisplayListBase - FIRST_GLYPH );
		glCallLists( len, GL_UNSIGNED_BYTE, pText );
	}
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void Font::DrawChar( unsigned int c ) const
{
	if ( m_DisplayListBase == 0 )
	{
		return;
	}

	glCallList( m_DisplayListBase + c - FIRST_GLYPH );
}


} // namespace WGlx