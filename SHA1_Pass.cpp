// Copyright (C) 2007-2011 "16 Systems" ® legal@16systems.com. All Rights Reserved.

// Standard C++ Includes
#include <cstdlib>
#include <vector>

// FLTK Includes
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Window.H>

// Local Includes
#include "../input_validation/valid_strings.hpp"

// Pick One (Unix is Linux, Mac OS X and BSDs)
//~ #define Unix
#define Microsoft

// Crypto++
#ifdef Unix
	#include <cryptopp/sha.h>
	#include <cryptopp/hex.h>
	#include <cryptopp/base64.h>
#endif

#ifdef Microsoft
	#define CRYPTOPP_DEFAULT_NO_DLL
	#include <dll.h>
	#include <default.h>

	USING_NAMESPACE(CryptoPP)
	USING_NAMESPACE(std)

	#include <sha.h>
	#include <hex.h>
	#include <base64.h>
#endif


// Change Log

// 1.0 - Initial release.
// 1.1 - Make copy occur as soon as user clicks encoding button. Put version number in title bar.
// 1.2 - Make sentence field hidden to prevent shoulder surfing. Add button so user can see sentence when needed.
// 1.3 - Clean up sentence, display buffers and clipboard on exit or clear_all. Implement secure_mode for secure visual usage in meetings, etc.
// 1.4 - Make editing sentences easier. Toggle back and forth from viewable to hidden sentence


Fl_Window win ( 500, 232, "SHA1_Pass v1.4 - 16 Systems" );

Fl_Input *sentence = new Fl_Secret_Input( 85, 0, 415, 30, "Sentence  " );

Fl_Button h_full ( 2, 40, 80, 30, "&Hex" );
Fl_Button h_half ( 2, 80, 80, 30, "He&x Half" );
Fl_Button b64 ( 2, 120, 80, 30, "&B64" );
Fl_Button b_half ( 2, 160, 80, 30, "B6&4 Half" );

Fl_Check_Button secure ( 28, 200, 120, 30, "Secure Mode" );
Fl_Check_Button show_s ( 158, 200, 120, 30, "View Sentence" );
Fl_Button clear_s ( 288, 200, 120, 30, "Clear &Sentence" );
Fl_Button clear_a ( 418, 200, 80, 30, "&Clear All" );

Fl_Text_Display disp0 ( 85, 40, 415, 30 );
Fl_Text_Display disp1 ( 85, 80, 415, 30 );
Fl_Text_Display disp2 ( 85, 120, 415, 30 );
Fl_Text_Display disp3 ( 85, 160, 415, 30 );

Fl_Text_Buffer *buff0 = new Fl_Text_Buffer();
Fl_Text_Buffer *buff1 = new Fl_Text_Buffer();
Fl_Text_Buffer *buff2 = new Fl_Text_Buffer();
Fl_Text_Buffer *buff3 = new Fl_Text_Buffer();

Fl_Button kill ( 0, 0, 0, 0, "&q" );

std::vector<Fl_Text_Buffer*> buffers;

bool SECURE = false;


// Generate hex password from user provided sentence.
const std::string hex_passwd( const std::string& sentence )
{
	CryptoPP::SHA1 hash;
	char digest[ hash.DigestSize() ];
	
	hash.Update((const byte*)sentence.c_str(), sentence.size());
	hash.Final( (byte*)digest );
	
	std::string hex;
	CryptoPP::HexEncoder hexencoder;
	hexencoder.Attach( new CryptoPP::StringSink( hex ) );
	hexencoder.Put( (byte*)digest, sizeof(digest) );
	hexencoder.MessageEnd();
	
	transform( hex.begin(), hex.end(), hex.begin(), (int(*)(int)) tolower );
	
	return hex;
}


// Generate b64 password from user provided sentence.
const std::string b64_passwd( const std::string& sentence )
{
	CryptoPP::SHA1 hash;
	char digest[ hash.DigestSize() ];
	
	hash.Update((const byte*)sentence.c_str(), sentence.size());
	hash.Final( (byte*)digest );
	
	std::string b64;
	CryptoPP::Base64Encoder b64encoder;
	b64encoder.Attach( new CryptoPP::StringSink( b64 ) );
	b64encoder.Put( (byte*)digest, sizeof(digest) );
	b64encoder.MessageEnd();
	
	return b64;
}


// Display hex
inline void gen_hex( Fl_Widget* w, void* buff )
{
	if ( SECURE == false )
	{
		disp0.textcolor(0);
	}
	
	else
	{
		disp0.textcolor(255);
	}
	
	Fl_Text_Buffer *b = ( Fl_Text_Buffer* )buff;
	const std::string password = hex_passwd( sentence->value() );
	b->text( password.c_str() );	
		
	// Copy password to clipboard so user only has to paste
	Fl::copy( password.c_str(), password.size(), 1);
}


// Display half_hex
inline void gen_half_hex( Fl_Widget* w, void* buff )
{
	if ( SECURE == false )
	{
		disp1.textcolor(0);
	}
	
	else
	{
		disp1.textcolor(255);
	}
	
	Fl_Text_Buffer *b = ( Fl_Text_Buffer* )buff;
	const std::string temp = hex_passwd( sentence->value() );
	const std::string password( temp, 0, 20 );
	b->text( password.c_str() );	
	
	// Copy password to clipboard so user only has to paste
	Fl::copy( password.c_str(), password.size(), 1);
}


// Display b64
inline void gen_b64( Fl_Widget* w, void* buff )
{
	if ( SECURE == false )
	{
		disp2.textcolor(0);
	}
	
	else
	{
		disp2.textcolor(255);
	}
	
	Fl_Text_Buffer *b = ( Fl_Text_Buffer* )buff;
	const std::string temp = b64_passwd( sentence->value() );
	const std::string password = Remove( temp, everything_but_spaces );
	b->text( password.c_str() );	
	
	// Copy password to clipboard so user only has to paste
	Fl::copy( password.c_str(), password.size(), 1);
}


// Display half_b64
inline void gen_half_b64( Fl_Widget* w, void* buff )
{
	if ( SECURE == false )
	{
		disp3.textcolor(0);
	}
	
	else
	{
		disp3.textcolor(255);
	}
	
	Fl_Text_Buffer *b = ( Fl_Text_Buffer* )buff;
	const std::string temp = b64_passwd( sentence->value() );
	const std::string password( temp, 0, temp.size()/2 );
	b->text( password.c_str() );	
	
	// Copy password to clipboard so user only has to paste
	Fl::copy( password.c_str(), password.size(), 1);
}


// Clear Display Buffers
inline void wipe_buffers()
{
	std::vector<Fl_Text_Buffer*>::const_iterator bit;
	
	for ( bit = buffers.begin(); bit != buffers.end(); ++bit )
	{
		(*bit)->text( "" );	
	}
}


// Clear Clipboards
inline void wipe_clipboards()
{
	Fl::copy( "", 0, 1);
	Fl::copy( "", 0, 0);
}


// Clear Sentence
inline void wipe_sentence()
{
	sentence->value( "" );
}


// Clear Sentence
inline void clear_sentence( Fl_Widget* w )
{
	wipe_sentence();
}


// Clean up and close the program when the user clicks X or presses the left Alt+Q keys
inline void rbt_quit( Fl_Widget* w )
{
	wipe_sentence();
	wipe_buffers();
	wipe_clipboards();
	exit( 0 );
}


// Show the sentence field to the user (Does not work in secure_mode)
inline void show_sentence( Fl_Widget* w )
{
	// Show the sentence
	if ( show_s.value() == 1 )
	{
		sentence->type( 0 );	
		Fl::redraw();
	}
	
	// Hide the sentence
	else
	{
		sentence->type( 5 );	
		Fl::redraw();
	}
}


// Secure Mode
inline void secure_mode( Fl_Widget* w )
{
	// Enter Secure Mode
	if ( secure.value() == 1 )
	{
		// Uncheck and deactivate "View Sentence"
		show_s.value( 0 );
		show_s.deactivate();
		
		// Hide sentence
		sentence->type( 5 );	
		Fl::redraw();
		
		SECURE = true;
		
		wipe_clipboards();
		wipe_buffers();
	}
	
	// Leave Secure Mode
	else
	{
		show_s.activate();
		SECURE = false;
		
		wipe_sentence();
		wipe_clipboards();
		wipe_buffers();
	}
}


// Clear All Fields
inline void clear_all( Fl_Widget* w )
{
	wipe_sentence();
	wipe_clipboards();
	wipe_buffers();
}


// main
int main()
{	
	// Push the buffers into buffers vector
	buffers.push_back( buff0 );
	buffers.push_back( buff1 );
	buffers.push_back( buff2 );
	buffers.push_back( buff3 );
	
	// Default to non-visually secure
	secure.value( 0 );
	show_s.value( 0 );
	
	win.show();
	
	win.callback(rbt_quit);
	kill.callback(rbt_quit);
	
	h_full.callback( gen_hex, (void*)buff0 );	
	h_half.callback( gen_half_hex, (void*)buff1 );		
	b64.callback( gen_b64, (void*)buff2 );	
	b_half.callback( gen_half_b64, (void*)buff3 );		
	
	secure.callback( secure_mode );
	show_s.callback( show_sentence );
	clear_s.callback( clear_sentence );	
	clear_a.callback( clear_all );	
	
	disp0.buffer( buff0 );
	disp1.buffer( buff1 );
	disp2.buffer( buff2 );
	disp3.buffer( buff3 );

	return Fl::run();
}
