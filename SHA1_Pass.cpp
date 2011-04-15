// Copyright (C) 2010-2011 "16 Systems" ® legal@16systems.com. All Rights Reserved.

// Pick One
#define Linux
//#define Microsoft
//#define Mac


#ifdef Linux

	// wx Includes
	#include </home/brad/Downloads/wxWidgets-2.8.12/include/wx/wx.h>
	#include </home/brad/Downloads/wxWidgets-2.8.12/include/wx/clipbrd.h>
	#include </home/brad/Downloads/wxWidgets-2.8.12/include/wx/aboutdlg.h>
	#include </home/brad/Downloads/wxWidgets-2.8.12/include/wx/textfile.h>

	// Crypto++
	#include <cryptopp/sha.h>
	#include <cryptopp/hex.h>
	#include <cryptopp/hmac.h>
	#include <cryptopp/base64.h>
#endif

#ifdef Microsoft

	// wx Includes
	#include "/wxwidgets-2.8.12/include/wx/wx.h"
	#include "/wxwidgets-2.8.12/include/wx/clipbrd.h"
	#include "/wxwidgets-2.8.12/include/wx/aboutdlg.h"
	#include "/wxwidgets-2.8.12/include/wx/textfile.h"

	#define CRYPTOPP_DEFAULT_NO_DLL
	#include <dll.h>
	#include <default.h>

	USING_NAMESPACE(CryptoPP)
	USING_NAMESPACE(std)

	#include <sha.h>
	#include <hex.h>
	#include <hmac.h>
	#include <base64.h>
#endif

#ifdef Mac

	// wx Includes
	#include </Users/dan/Downloads/wxWidgets-2.8.12/include/wx/wx.h>
	#include </Users/dan/Downloads/wxWidgets-2.8.12/include/wx/clipbrd.h>
	#include </Users/dan/Downloads/wxWidgets-2.8.12/include/wx/aboutdlg.h>
	#include </Users/dan/Downloads/wxWidgets-2.8.12/include/wx/textfile.h>

	// Crypto++
	#include <cryptopp/sha.h>
	#include <cryptopp/hex.h>
	#include <cryptopp/hmac.h>
	#include <cryptopp/base64.h>
#endif


// Local Includes
#include "../input_validation/valid_strings.hpp"
#include "test_sentences.hpp"


// Language Packs. Pick One. Only English implemented. Translations welcomed.
// http://16s.us/sha1_pass/downloads/Language_Packs/readme.txt
#include "english.hpp"
//#include "french.hpp"
//#include "german.hpp"
//#include "spanish.hpp"
//#include "simplified_chinese.hpp"


// Set to true for debugging/test builds
const static bool SPDEBUG = false;
const static bool SPTEST = false;


// HMAC_SHA1
bool HMAC_SHA1 = false;
const static std::string HMAC_MSG = "SHA1_Pass";


// std::string to wxString
inline wxString std2wx( std::string s )
{
	return wxString( s.c_str(), wxConvUTF8 ); // May use wxConvLibc or wxConvLocal or wxConvUTF8 here.
}


// wxString to std::string (unused)
inline std::string wx2std( wxString s )
{
	return std::string( s.mb_str( wxConvUTF8 ) );
} 


// Generate hex password from user provided sentence.
const std::string hex_passwd( const std::string& sentence, const std::string& type )
{	
	// SHA1
	CryptoPP::SHA1 hash;
	char digest[ hash.DigestSize() ];	
	hash.Update((const byte*)sentence.c_str(), sentence.size());
	hash.Final( (byte*)digest );
	
	// SHA1 Encoding
	std::string hex;
	CryptoPP::HexEncoder hexencoder;
	hexencoder.Attach( new CryptoPP::StringSink( hex ) );
	hexencoder.Put( (byte*)digest, sizeof(digest) );
	hexencoder.MessageEnd();
	
	// Lowercase
	transform( hex.begin(), hex.end(), hex.begin(), (int(*)(int)) tolower );

	// HMAC (Sentence is the secret key, string constant "SHA1_Pass" is the message)
	CryptoPP::HMAC<CryptoPP::SHA1> mac;
	char hmac[ hash.DigestSize() ];
	mac.SetKey( (const byte*)sentence.c_str(), sentence.size() );
	mac.Update( (const byte*)HMAC_MSG.c_str(), HMAC_MSG.size() );
	mac.Final( (byte*)hmac );

	// HMAC Encoding
	std::string hmac_hex;
	CryptoPP::HexEncoder hmac_hexencoder;
	hmac_hexencoder.Attach( new CryptoPP::StringSink( hmac_hex ) );
	hmac_hexencoder.Put( (byte*)hmac, sizeof(hmac) );
	hmac_hexencoder.MessageEnd();
	
	// Lowercase
	transform( hmac_hex.begin(), hmac_hex.end(), hmac_hex.begin(), (int(*)(int)) tolower );
	
	if ( SPDEBUG == true )
	{
		//Show the SHA1 hash and the HMAC_SHA1 hash
		wxMessageBox( std2wx(hex), sha1_label, wxOK | wxICON_INFORMATION );
		wxMessageBox( std2wx(hmac_hex), hmac_label, wxOK | wxICON_INFORMATION );
	}
	
	if ( HMAC_SHA1 == true )	
	{
		if ( type == full )
			return hmac_hex;
		else
			return hmac_hex.substr( 0, 20 );
	}

	else
	{
		if ( type == full )
			return hex;
		else
			return hex.substr( 0, 20 );
	}
}


// Generate b64 password from user provided sentence.
const std::string b64_passwd( const std::string& sentence, const std::string& type )
{
	// SHA1
	CryptoPP::SHA1 hash;
	char digest[ hash.DigestSize() ];	
	hash.Update((const byte*)sentence.c_str(), sentence.size());
	hash.Final( (byte*)digest );
	
	// SHA1 Encoding
	std::string b64;
	CryptoPP::Base64Encoder b64encoder;
	b64encoder.Attach( new CryptoPP::StringSink( b64 ) );
	b64encoder.Put( (byte*)digest, sizeof(digest) );
	b64encoder.MessageEnd();
	
	// HMAC (Sentence is the secret key, string constant "SHA1_Pass" is the message)
	CryptoPP::HMAC<CryptoPP::SHA1> mac;
	char hmac[ hash.DigestSize() ];	
	mac.SetKey( (const byte*)sentence.c_str(), sentence.size() );
	mac.Update( (const byte*)HMAC_MSG.c_str(), HMAC_MSG.size() );
	mac.Final( (byte*)hmac );
	
	// HMAC Encoding
	std::string hmac_b64;
	CryptoPP::Base64Encoder hmac_b64encoder;
	hmac_b64encoder.Attach( new CryptoPP::StringSink( hmac_b64 ) );
	hmac_b64encoder.Put( (byte*)hmac, sizeof(hmac) );
	hmac_b64encoder.MessageEnd();
	
	if ( SPDEBUG == true )
	{
		//Show the SHA1 hash and the HMAC_SHA1 hash
		wxMessageBox( std2wx(b64), sha1_label, wxOK | wxICON_INFORMATION );
		wxMessageBox( std2wx(hmac_b64), hmac_label, wxOK | wxICON_INFORMATION );
	}
	
	if ( HMAC_SHA1 == true )
	{
		if ( type == full )
			return hmac_b64;
		else
			return hmac_b64.substr( 0, 14 );
	}

	else
	{
		if ( type == full )
			return b64;
		else
			return b64.substr( 0, 14 );
	}
}


// Run tests on test_sentences
void tests()
{
	test_sentences.push_back( test_numbers );		// 1
	test_sentences.push_back( test_lower );			// 2
	test_sentences.push_back( test_upper );			// 3
	test_sentences.push_back( test_special );			// 4
	test_sentences.push_back( test_normal );		// 5
	test_sentences.push_back( test_unicode );		// 6
	test_sentences.push_back( test_spanish );		// 7
	test_sentences.push_back( test_german );		// 8
	test_sentences.push_back( test_blank );			// 9
	test_sentences.push_back( test_all );			// 10
	
	std::vector<wxString>::const_iterator it;
	
	// Create test output file
	wxTextFile file( test_file );	
	file.Create();
	
	for ( it = test_sentences.begin(); it != test_sentences.end(); ++it )
	{
		// Convert the sentence to UTF8
		wxCharBuffer buffer = (*it).ToUTF8();
	
		// SHA1 and Encode, then return password
		const std::string hex_1 = hex_passwd( buffer.data(), full );
		const std::string b64_1 = b64_passwd( buffer.data(), full );
	
		// The password may only have trusted characters
		const std::string hex_clean = vs_remove( hex_1, trusted( only_hex ) );
		const std::string b64_clean = vs_remove( b64_1, trusted( only_base64 ) );
	
		// Convert to wxString
		wxString hex_password = std2wx( hex_clean );
		wxString b64_password = std2wx( b64_clean );
		
		file.AddLine( hex_password );
		file.AddLine( b64_password );
		
		file.Write();
	}
	
	file.Close();
}


class MyApp: public wxApp
{
	virtual bool OnInit();
};


class MyFrame: public wxFrame
{
	public:

		MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size, long style );

		void OnQuit( wxCommandEvent& event );
		void OnBase64( wxCommandEvent& event );
		void OnBase64Half( wxCommandEvent& event );
		void OnHex( wxCommandEvent& event );
		void OnHexHalf( wxCommandEvent& event );
		void OnViewSentence( wxCommandEvent& event );
		void OnSecureMode( wxCommandEvent& event );
		void OnHMAC( wxCommandEvent& event );
		void OnHelp( wxCommandEvent& event );
		void rbt_clear_cb();
		void rbt_clear_s();
	
		// The panel pointer (pointer rather than reference because the parent may be null)
		wxPanel *panel;
	
		// TextCtrls
		wxTextCtrl *textctrl;
		wxTextCtrl partial_pass;	// This is read-only
	
		// Static Text
		wxStaticText sentence;
	
		// Check boxes
		wxCheckBox view_sentence;
		wxCheckBox secure_mode;
		wxCheckBox hmac;
	
		// Buttons
		wxButton help;
		wxButton B64;
		wxButton B64H;
		wxButton HEX;
		wxButton HEXH;
		
		// About/Help Info
		wxAboutDialogInfo info;		

		DECLARE_EVENT_TABLE()
};


enum
{
	ID_Quit = 1,
	ID_About,
	ID_Base64,
	ID_Base64Half,
	ID_Hex,
	ID_HexHalf,
	ID_ViewSentence,
	ID_SecureMode,
	ID_HMAC,
	ID_Help
	
};


BEGIN_EVENT_TABLE( MyFrame, wxFrame )
EVT_MENU( ID_Quit, MyFrame::OnQuit )
EVT_MENU( ID_Base64, MyFrame::OnBase64 )
EVT_MENU( ID_Base64Half, MyFrame::OnBase64Half )
EVT_MENU( ID_Hex, MyFrame::OnHex )
EVT_MENU( ID_HexHalf, MyFrame::OnHexHalf )
EVT_MENU( ID_ViewSentence, MyFrame::OnViewSentence )
EVT_MENU( ID_SecureMode, MyFrame::OnSecureMode )
EVT_MENU( ID_SecureMode, MyFrame::OnHMAC )
EVT_MENU( ID_Help, MyFrame::OnHelp )
END_EVENT_TABLE()


IMPLEMENT_APP( MyApp )


bool MyApp::OnInit()
{
	// The frame is the main window. 
	
	MyFrame *frame = new MyFrame( title, wxPoint( 50, 50 ), wxSize( 436,150 ), wxSYSTEM_MENU|wxMINIMIZE_BOX|wxCLOSE_BOX|wxCAPTION );
	frame->Center( wxBOTH );
	frame->Show( true );
	SetTopWindow( frame );
	
	// Disable shrinking window too small. minW, minH, maxW, maxH, incH
	frame->SetSizeHints( 436,150, 436,150, 0 );
	
	// Run tests
	if ( SPTEST == true )
	{
		tests();
	}
	
	return true;
} 


MyFrame::MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( NULL, -1, title, pos, size, style )
{
	// The panel is within the frame
	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// These controls are within the panel	
	textctrl = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxPoint( 69, 5 ), wxSize( 330, 25 ), wxTE_PASSWORD, wxDefaultValidator );
	
	sentence.Create( panel, wxID_ANY, u_sentence, wxPoint( 3, 8 ), wxDefaultSize, 0 );
	
	view_sentence.Create( panel, 3, vs, wxPoint( 69, 35 ), wxDefaultSize, 0, wxDefaultValidator );	
	Connect( 3, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame::OnViewSentence ) );
	
	secure_mode.Create( panel, 4, sm, wxPoint( 194, 35 ), wxDefaultSize, 0, wxDefaultValidator );	
	Connect( 4, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame::OnSecureMode ) );

	hmac.Create( panel, 5, hm, wxPoint( 270, 35 ), wxDefaultSize, 0, wxDefaultValidator );	
	Connect( 5, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame::OnHMAC ) );
	
	partial_pass.Create( panel, 6, wxEmptyString, wxPoint( 349, 33 ), wxSize( 50, 25 ), wxTE_READONLY, wxDefaultValidator );

	HEX.Create( panel, 7, hex_label, wxPoint( 69, 62 ),  wxSize( 80, 25 ), wxBU_EXACTFIT, wxDefaultValidator );	
	Connect( 7, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::OnHex ) );
	
	HEXH.Create( panel, 8, hex_half_label, wxPoint( 153, 62 ),  wxSize( 80, 25 ), wxBU_EXACTFIT, wxDefaultValidator );	
	Connect( 8, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::OnHexHalf ) );
	
	B64.Create( panel, 9, b64_label, wxPoint( 235, 62 ),  wxSize( 80, 25 ), wxBU_EXACTFIT, wxDefaultValidator );	
	Connect( 9, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::OnBase64 ) );
	
	B64H.Create( panel, 10, b64_half_label, wxPoint( 317, 62 ),  wxSize( 80, 25 ), wxBU_EXACTFIT, wxDefaultValidator );	
	Connect( 10, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::OnBase64Half ) );
	
	help.Create( panel, 11, help_label, wxPoint( 403, 5 ), wxSize( 25, 25), wxBU_EXACTFIT, wxDefaultValidator );	
	Connect( 11, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::OnHelp ) );
	
	// On start-up, set partial_pass value
	partial_pass.SetValue( pass_peek );
	
	// On start-up, do not View Sentence
	view_sentence.SetValue( false );
	
	// On start-up, do not use Secure Mode
	secure_mode.SetValue( false );

	// On start-up, do not use HMAC
	hmac.SetValue( false );
	
	// The 1 means only create one status field within the statusbar
	CreateStatusBar( 1, wxFULL_REPAINT_ON_RESIZE, wxID_ANY );
	SetStatusText( title );
	
	// Set Tool Tips
	textctrl->SetToolTip( type_sentence_tip );
	sentence.SetToolTip( type_sentence_tip );	
	partial_pass.SetToolTip( pass_peek_tip );
	HEX.SetToolTip( a_40_char_tip );
	HEXH.SetToolTip( a_20_char_tip );
	B64.SetToolTip( a_28_char_tip );
	B64H.SetToolTip( a_14_char_tip );
	view_sentence.SetToolTip( vs_tip );
	secure_mode.SetToolTip( sm_tip );
	hmac.SetToolTip( hmac_tip );
	help.SetToolTip( help_tip );
	
	//Populate About Information
	info.SetName( title );
	info.SetDescription( description );
	info.SetCopyright( copyright );
	info.SetWebSite( url, url_label );
} 


void MyFrame::rbt_clear_cb()
{
	// Clear the clip board.
	wxTheClipboard->Clear();
}


void MyFrame::rbt_clear_s()
{
	// Clear the sentence.
	textctrl->Clear();
	
	// Clear the viewable partial pass.
	partial_pass.Clear();
}


void MyFrame::OnQuit( wxCommandEvent& WXUNUSED( event ) )
{
	// Call rbt_clear_s()
	rbt_clear_s();
	
	// Call rbt_clear_cb()
	rbt_clear_cb();

	// Close the app.
	Close( true );
}


void MyFrame::OnHelp( wxCommandEvent& WXUNUSED( event ) )
{
	// Show the About/Help Information
	wxAboutBox( info );
}


void MyFrame::OnBase64( wxCommandEvent& WXUNUSED( event ) )
{
	// Get the sentence. Depending on the platform, this will have different Unicode encodings.
	wxString the_sentence = textctrl->GetValue();
	
	// Convert the sentence to UTF8
	wxCharBuffer buffer = the_sentence.ToUTF8();
	
	// SHA1 the sentence.
	const std::string temp_password = b64_passwd( buffer.data(), full );
	
	// The password may only have base64 characters in it
	const std::string clean_password = vs_remove( temp_password, trusted( only_base64 ) );
	
	// Convert clean_password to wxString
	wxString the_password = std2wx( clean_password );
	
	// Display partial pass (first 4 chars of password)
	partial_pass.SetValue( the_password.SubString( 0, 3 ) );
	
	// Copy the password to the clipboard.
	if ( wxTheClipboard->Open() )
	{
		wxTheClipboard->SetData( new wxTextDataObject( the_password ) );
		wxTheClipboard->Close();
	}
	
	// Set status bar text
	SetStatusText( b64_password_copied );
	
	if ( SPDEBUG == true )
	{
		wxMessageBox( the_sentence, u_sentence, wxOK | wxICON_INFORMATION, this);
		wxMessageBox( the_password, password, wxOK | wxICON_INFORMATION, this);
		
		// Log password		
		wxTextFile file( debug_b64 );		
		file.Create();
		file.AddLine( the_password );
		file.Write();		
		file.Close();
		
		if ( the_password.Len() != 28 )
			wxMessageBox( wxString::Format( wxT("%i"),the_password.Len() ), length_label, wxOK | wxICON_ERROR, this);
	}
}


void MyFrame::OnBase64Half( wxCommandEvent& WXUNUSED( event ) )
{
	// Get the sentence. Depending on the platform, this will have different Unicode encodings.
	wxString the_sentence = textctrl->GetValue();
	
	// Convert the sentence to UTF8
	wxCharBuffer buffer = the_sentence.ToUTF8();
	
	// SHA1 the sentence.
	const std::string temp_password = b64_passwd( buffer.data(), half );
	
	// The password may only have base64 characters in it
	const std::string clean_password = vs_remove( temp_password, trusted( only_base64 ) );
	
	// Convert clean_password to wxString
	wxString the_password = std2wx( clean_password );
	
	// Display partial pass (first 4 chars of password)
	partial_pass.SetValue( the_password.SubString( 0, 3 ) );
	
	// Copy the password to the clipboard.
	if ( wxTheClipboard->Open() )
	{
		wxTheClipboard->SetData( new wxTextDataObject( the_password ) );
		wxTheClipboard->Close();
	}
	
	// Set status bar text
	SetStatusText( b64_h_password_copied );
	
	if ( SPDEBUG == true )
	{
		wxMessageBox( the_sentence, u_sentence, wxOK | wxICON_INFORMATION, this);
		wxMessageBox( the_password, password, wxOK | wxICON_INFORMATION, this);
		
		// Log password		
		wxTextFile file( debug_b64_h );		
		file.Create();
		file.AddLine( the_password );
		file.Write();		
		file.Close();
		
		if ( the_password.Len() != 14 )
			wxMessageBox( wxString::Format( wxT("%i"),the_password.Len() ), length_label, wxOK | wxICON_ERROR, this);
	}
}


void MyFrame::OnHex( wxCommandEvent& WXUNUSED( event ) )
{
	// Get the sentence. Depending on the platform, this will have different Unicode encodings.
	wxString the_sentence = textctrl->GetValue();
	
	// Convert the sentence to UTF8
	wxCharBuffer buffer = the_sentence.ToUTF8();
	
	// SHA1 the sentence.
	const std::string temp_password = hex_passwd( buffer.data(), full );
	
	// The password may only have hex characters in it
	const std::string clean_password = vs_remove( temp_password, trusted( only_hex ) );
	
	// Convert clean_password to wxString
	wxString the_password = std2wx( clean_password );
	
	// Display partial pass (first 4 chars of password)
	partial_pass.SetValue( the_password.SubString( 0, 3 ) );
	
	// Copy the password to the clipboard.
	if ( wxTheClipboard->Open() )
	{
		wxTheClipboard->SetData( new wxTextDataObject( the_password ) );
		wxTheClipboard->Close();
	}
	
	// Set status bar text
	SetStatusText( hex_password_copied );
	
	if ( SPDEBUG == true )
	{
		wxMessageBox( the_sentence, u_sentence, wxOK | wxICON_INFORMATION, this);
		wxMessageBox( the_password, password, wxOK | wxICON_INFORMATION, this);
		
		// Log password		
		wxTextFile file( debug_hex );		
		file.Create();
		file.AddLine( the_password );
		file.Write();		
		file.Close();
		
		if ( the_password.Len() != 40 )
			wxMessageBox( wxString::Format( wxT("%i"),the_password.Len() ), length_label, wxOK | wxICON_ERROR, this);
	}
}


void MyFrame::OnHexHalf( wxCommandEvent& WXUNUSED( event ) )
{
	// Get the sentence. Depending on the platform, this will have different Unicode encodings.
	wxString the_sentence = textctrl->GetValue();
	
	// Convert the sentence to UTF8
	wxCharBuffer buffer = the_sentence.ToUTF8();
	
	// SHA1 the sentence.
	const std::string temp_password = hex_passwd( buffer.data(), half );
	
	// The password may only have hex characters in it
	const std::string clean_password = vs_remove( temp_password, trusted( only_hex ) );
	
	// Convert clean_password to wxString
	wxString the_password = std2wx( clean_password );

	// Display partial pass (first 4 chars of password)
	partial_pass.SetValue( the_password.SubString( 0, 3 ) );
	
	// Copy the password to the clipboard.
	if ( wxTheClipboard->Open() )
	{
		wxTheClipboard->SetData( new wxTextDataObject( the_password ) );
		wxTheClipboard->Close();
	}
	
	// Set status bar text
	SetStatusText( hex_h_password_copied );
	
	if ( SPDEBUG == true )
	{
		wxMessageBox( the_sentence, u_sentence, wxOK | wxICON_INFORMATION, this);
		wxMessageBox( the_password, password, wxOK | wxICON_INFORMATION, this);
		
		// Log password
		wxTextFile file( debug_hex_h );
		file.Create();
		file.AddLine( the_password );
		file.Write();
		file.Close();
		
		if ( the_password.Len() != 20 )
			wxMessageBox( wxString::Format( wxT("%i"),the_password.Len() ), length_label, wxOK | wxICON_ERROR, this);
	}
}


void MyFrame::OnViewSentence( wxCommandEvent& WXUNUSED( event ) )
{	
	const wxString the_sentence = textctrl->GetValue();
	
	// View Sentence has been checked.
	if ( view_sentence.IsChecked() )
	{
		// Set to plaintext style
		delete textctrl;
		textctrl = new wxTextCtrl( panel, -1, the_sentence, wxPoint( 69, 5 ), wxSize( 330, 25 ), wxTE_LEFT, wxDefaultValidator );
		
		// Recreate tool tip
		textctrl->SetToolTip( type_sentence_tip );
		
		// Set status bar text
		SetStatusText( vs_on );
	}
	
	// View Sentence has been unchecked.
	else
	{
		// Set to password style
		delete textctrl;
		textctrl = new wxTextCtrl( panel, -1, the_sentence, wxPoint( 69, 5 ), wxSize( 330, 25 ), wxTE_PASSWORD, wxDefaultValidator );
		
		// Recreate tool tip
		textctrl->SetToolTip( type_sentence_tip );
		
		// Set status bar text
		SetStatusText( vs_off );
	}
}


void MyFrame::OnSecureMode( wxCommandEvent& WXUNUSED( event ) )
{	
	// Get the sentence.
	const wxString the_sentence = textctrl->GetValue();
	
	// Uncheck view_sentence.
	view_sentence.SetValue( false );
	
	// Secure Mode has been checked.
	if ( secure_mode.IsChecked() )
	{		
		// Set to password style.
		delete textctrl;
		textctrl = new wxTextCtrl( panel, -1, the_sentence, wxPoint( 69, 5 ), wxSize( 330, 25 ), wxTE_PASSWORD, wxDefaultValidator );
		
		// Recreate tool tip
		textctrl->SetToolTip( type_sentence_tip );

		// Disable view_sentence.
		view_sentence.Disable();
		
		// Set status bar text
		SetStatusText( sm_on );
	}
	
	// Secure Mode has been unchecked.
	else
	{
		// Call rbt_clear_s()
		rbt_clear_s();
		
		// Call rbt_clear_cb()
		rbt_clear_cb();
		
		// Enable view_sentence button.
		view_sentence.Enable();
		
		// Set status bar text
		SetStatusText( sm_off );

		// Reset partial_pass
		partial_pass.SetValue( pass_peek );
	}
}


void MyFrame::OnHMAC( wxCommandEvent& WXUNUSED( event ) )
{
	// HMAC has been checked.
	if ( hmac.IsChecked() )
	{
		SetStatusText( hmac_on );
		HMAC_SHA1 = true;
	}

	// HMAC has been unchecked.
	else
	{
		SetStatusText( hmac_off );
		HMAC_SHA1 = false;
	}
}

