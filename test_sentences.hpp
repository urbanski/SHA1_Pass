#include <vector>


// Test sentences. SHA1, then b64 and hex encode and compare to OpenSSL output.
const static wxString test_numbers			= wxT( "0123456789" );
const static wxString test_lower				= wxT( "abcdefghijklmnopqrstuvwxyz" );
const static wxString test_upper				= wxT( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
const static wxString test_special				= wxT( "~`!@#$%^&*()_+-={}|[]\\;':\",./<> ?" );
const static wxString test_normal				= wxT( "A normal sentence." );
const static wxString test_unicode			= wxT( "\x00AE\x00A9\x2622" );
const static wxString test_spanish			= wxT( "\x00c1\x00c9\x00cd\x00d3\x00da\x00d1\x00dc\x00e1\x00e9\x00ed\x00f3\x00fa\x00f1\x00fc\x00bf" );
const static wxString test_german			= wxT( "\x00c4\x00e4\x00d6\x00f6\x00dc\x00fc\x00df\x20AC" );
const static wxString test_blank				= wxT( "" );
const static wxString test_all					= test_numbers + test_lower + test_upper + test_special + test_normal + test_unicode + test_spanish + test_german + test_blank;

static std::vector<wxString> test_sentences;
