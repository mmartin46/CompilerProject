// Cody Digby and Mitchell Martin
// CS 4301
// Stage 0

#include <string>
#include <iomanip>
#include <stage0.h>
#include <stdexcept>


void Compiler::parser()
{
	nextChar();
	nextToken();
	if (token != "program")
	{
		processError("keyword \"program\" expected");
	}
	prog();
}

/* OTHER ROUTINES */
void Compiler::processError(string err)
{
	listingFile << endl;
	listingFile << "Error: Line " << lineNo << ": " << err << endl << endl;
	++errorCount;
	// Error count needs to be a zero or a one.
	if (errorCount > 0)
	{
		createListingTrailer();
		exit(1);			
	}
	createListingTrailer();
	exit(1);	
}

string Compiler::genInternalName(storeTypes stype) const
{
    static int intIndex = 0;
		static int boolIndex = 0;
		
    string internalName;
    
    switch (stype)
    {
    	case INTEGER:
		{
			internalName = "I" + to_string(intIndex);
			++intIndex;
			break;
		}
		case BOOLEAN:
		{
			internalName = "B" + to_string(boolIndex);
			++boolIndex;
			break;
		}
		default:
		{}
    
    }
    
    return internalName;
}


/* HELPER FUNCTIONS */
// ---------- Found on page 1 ---------------- //
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415552?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=RGxTUQ6Q%2Bu6G3dQUIF9uosjfgmT6ghjTIQ8%2Fojc8eKg%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27LanguageDefinitionAndGrammar.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFQaCXVzLWVhc3QtMSJGMEQCIF3NK48ts%2FeM9TMQxIyZyBFx4C%2Fv7HhGdlP%2F8M3VtadzAiAwjER2DH49ER5zMq15sTkRLJNS7ariJibbLuxBZtLXriq0BQh9EAMaDDYzNTU2NzkyNDE4MyIMBkyW5Yd7EkMMmfplKpEFB6%2Bzi%2FrAQmrRJQpRuNhKA0SumZm%2BvS8IfpqetIALwPNcKqvgPdpW%2FNpQw%2F1b8vfREH%2FDuVFVPn7sID5UJYNCjy%2BnOVtOo33N55%2FJ6%2Bgqx6yo2i7RIz1Wmw8lYkPnH%2B%2BAvIdjErzXQeXuEy1e2cAM%2BdetAHe6XLAccgBTupBgE49gWPc6JGYmR3P1CAX%2FwidBgCa9hyvEG%2FLV9SFWJQeMV16c7gte37TKsu36Ry5jrAMPTfIdbxv5zxqS%2FH6wZntvfeHiS43E%2F1Q%2BFF7pfAKoCVz2ggD7kjijFXvAbvvn%2FawPMA%2Bhl0%2B2%2B%2FuyMhdHS%2Bfzm%2BjADoXzYo68gmhx67QWFLRMazUPpL8zg%2BJ30wkphq2o3w5cmTWk%2B4T%2Bfk9PD5Ujp2joqu7uimu4F3E3TNU5EPisqLBEWtqSbsM5GdVRPKIk4rqHOF0J4%2BO9pFGFUCwblm6p9zYaQZDiMox%2BsqcewKDmTZhjUKXLs6ydBVudH50IvBtyq1ShWKCZ8%2F4F9a4YScnC7u%2FcPyB1woTErpOYyKK37uQH1ORk55sLzP4k1urHTTpDLOrYB7f6c0JglBHdpPbAvnJqHcp4iwCT4faqEL%2BbJ%2FeTP%2BxOx%2FF8XEoYXkcXXvr%2FHzXYD%2FuBOb8zPmZoWqEKZ%2B%2BdzoFMiJwZzTZpo5sMSZRtpC1d%2BtzJ5yf6iCoHXBHBlxedltPPoNnkoGw5XQvbd5gBtQO2vQkMj0YZ7BONo7LfhZp92gfGj9AcENzOXbmeOBdj%2FIQZsr9t7iwuEdNGo%2BK3FNrESkh%2FQI3ORRTKzMCtgRbJSef%2FAF9YgLPETIVMRjBuepVw6jMFo4oOCxt6dGALxu%2Bgvobk8P9%2ByILDwr%2FtLhPSQA%2FTBiALLxCOMO%2BA66kGOrIBullz4kuGAl0u4%2Fha%2F7MfFYMIHT8zsjY%2FOi4JcO7f%2F033dPw9pn75lhKpgW8ZyhpsEBAUZd3VA6BrLouZQ1dsI0xiA4rOE3fmh8mUihFxH4wst63jtjrUXJb5731yLaeza0z1Zyl0nztqRwSJclBUuOo7Vr%2B2kALIxY7WnWgx03FJXR2uG5Absw1NXQts0HK4MVguqlqpgEVtMDl2Qzp7GUF5rhIHUFdNPIJtKeR3C%2FAEsw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLXR24LND3%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=1673ba84c2fd9e47e6160f2f3911f670f08cbb0198278e7859739f4129cd9eed
// Look at 2.
bool Compiler::isKeyword(string s) const// determines if s is a keyword
{
	// List of legal keywords
	string keyWords[] = { "program", "const", "var", "integer", "boolean", "begin",
	"end", "true", "false", "not" };

	// Check if there is a match.
	bool keyFound = false;
	
	for (const auto &keyword : keyWords) 
	{
		if (keyword == s)
		{
			keyFound = true;
		}
	}
	return keyFound;
}

// ---------- Found on page 1 ---------------- //
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415552?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=RGxTUQ6Q%2Bu6G3dQUIF9uosjfgmT6ghjTIQ8%2Fojc8eKg%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27LanguageDefinitionAndGrammar.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFQaCXVzLWVhc3QtMSJGMEQCIF3NK48ts%2FeM9TMQxIyZyBFx4C%2Fv7HhGdlP%2F8M3VtadzAiAwjER2DH49ER5zMq15sTkRLJNS7ariJibbLuxBZtLXriq0BQh9EAMaDDYzNTU2NzkyNDE4MyIMBkyW5Yd7EkMMmfplKpEFB6%2Bzi%2FrAQmrRJQpRuNhKA0SumZm%2BvS8IfpqetIALwPNcKqvgPdpW%2FNpQw%2F1b8vfREH%2FDuVFVPn7sID5UJYNCjy%2BnOVtOo33N55%2FJ6%2Bgqx6yo2i7RIz1Wmw8lYkPnH%2B%2BAvIdjErzXQeXuEy1e2cAM%2BdetAHe6XLAccgBTupBgE49gWPc6JGYmR3P1CAX%2FwidBgCa9hyvEG%2FLV9SFWJQeMV16c7gte37TKsu36Ry5jrAMPTfIdbxv5zxqS%2FH6wZntvfeHiS43E%2F1Q%2BFF7pfAKoCVz2ggD7kjijFXvAbvvn%2FawPMA%2Bhl0%2B2%2B%2FuyMhdHS%2Bfzm%2BjADoXzYo68gmhx67QWFLRMazUPpL8zg%2BJ30wkphq2o3w5cmTWk%2B4T%2Bfk9PD5Ujp2joqu7uimu4F3E3TNU5EPisqLBEWtqSbsM5GdVRPKIk4rqHOF0J4%2BO9pFGFUCwblm6p9zYaQZDiMox%2BsqcewKDmTZhjUKXLs6ydBVudH50IvBtyq1ShWKCZ8%2F4F9a4YScnC7u%2FcPyB1woTErpOYyKK37uQH1ORk55sLzP4k1urHTTpDLOrYB7f6c0JglBHdpPbAvnJqHcp4iwCT4faqEL%2BbJ%2FeTP%2BxOx%2FF8XEoYXkcXXvr%2FHzXYD%2FuBOb8zPmZoWqEKZ%2B%2BdzoFMiJwZzTZpo5sMSZRtpC1d%2BtzJ5yf6iCoHXBHBlxedltPPoNnkoGw5XQvbd5gBtQO2vQkMj0YZ7BONo7LfhZp92gfGj9AcENzOXbmeOBdj%2FIQZsr9t7iwuEdNGo%2BK3FNrESkh%2FQI3ORRTKzMCtgRbJSef%2FAF9YgLPETIVMRjBuepVw6jMFo4oOCxt6dGALxu%2Bgvobk8P9%2ByILDwr%2FtLhPSQA%2FTBiALLxCOMO%2BA66kGOrIBullz4kuGAl0u4%2Fha%2F7MfFYMIHT8zsjY%2FOi4JcO7f%2F033dPw9pn75lhKpgW8ZyhpsEBAUZd3VA6BrLouZQ1dsI0xiA4rOE3fmh8mUihFxH4wst63jtjrUXJb5731yLaeza0z1Zyl0nztqRwSJclBUuOo7Vr%2B2kALIxY7WnWgx03FJXR2uG5Absw1NXQts0HK4MVguqlqpgEVtMDl2Qzp7GUF5rhIHUFdNPIJtKeR3C%2FAEsw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLXR24LND3%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=1673ba84c2fd9e47e6160f2f3911f670f08cbb0198278e7859739f4129cd9eed
// Look at 4.
bool Compiler::isSpecialSymbol(char c) const
{
	// List of special symbols.
	char specialSymbols[] = { ':', ',', ';', '=', '+', '-', '.' };
	
	// Check for a match
	bool symFound = false;
	
	for (const auto &symbol : specialSymbols)
	{
		if (symbol == c)
		{	
			symFound = true;
		}
	}
	return symFound;
}

bool Compiler::isNonKeyId(string s) const
{
	size_t sLength = s.length();
	// Check if it's a keyword obviously.
	if (isKeyword(s))
	{
		return false;
	}
	
	// Defintions found in 9-10
	// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415552?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698354000000&X-Blackboard-Signature=07hLtQS5MseGUxbACX0NdjbnrNDG7Xlf9LHHrh8at5U%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27LanguageDefinitionAndGrammar.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFEaCXVzLWVhc3QtMSJIMEYCIQDNixLw7uh5rgLDTo4lZxlJPXQjxBXUxoXDX9Ma%2BOOj5QIhAKPWP8u9rbxVXwsTtsGbah7RY4PCDEj5X8nagAH%2ByN8hKrMFCHoQAxoMNjM1NTY3OTI0MTgzIgxUBTxoTkI0SNlskXUqkAWn1CVwY%2F0zzTnmAn8hTVrlDzxk7k3G0U2Jr4Nu4G0frmEbV04b5x%2BJYINu4iEcixqIYnWE32azcow%2BXkfg6xPxCK2VAN9oAHi3si6HhZ9TGw6sT%2BXQDq91PwTM5cMtJjQKWerl1VeuPvgQF4%2FrEY94aaawduhGPCX%2F9%2F0k1NcGjEMzBNv4Rbbw9rADkStVoSZ0o7zlsQVPdNlmlTIBtEZnsnDv6lZuFBPaBLv82FgcyMQx8OrkOpANi01%2BjFTHgvtTqNqu4KniNqIsbIptHbZMc0ZR9vEklh6Fgr3UPKKV7vhuIFzqT8i0caLHNizcqQh%2FUMFdIz1G8%2FZzOfALa9jsuBkvvOoorGe0MgErgNd3oBbt57B%2F1TNzC2hdAve4xM5egibICEK7%2Bb0aTrCHZk8I3Mmb4fY5l7VDHHWcZGu2oNaf5YSNjv%2B%2FN5pxhsLhPwzCrtSP6ROoqvj%2BoF5GzOYB%2B0cn8oPwVanaax2JDCG%2FSeQhez6yAxrn%2BuzE45q3StTYqomBOGYIbIThzF4QnSHVpoV1R1mBYE6ECYTJs7ClItTgOX3pWTHGFtLlVv2Bxd4Dnkb5H%2BCwEzeil2ZQ1jSFGlExKQjY4eqaIDm%2BaQH0JsGcpGVnu%2BNDFOja5lQ45T0QSfVHTR5x32CQuJLnjQwvKR%2B2jBItNr1rHQJTvypp17vLlCjqymA1Ym1GMTTPJqTm6%2BY6vfLtnmYmdJ1VK%2FW%2BvUVYdiqqyzUZRl5mSrT6gWDwADt2m7g%2B9tg6D6L0cyRWhxy%2Bze6nQBzEBPSLhKYNoxC6H82S0abzbR4cRMFJV0cmBAeRefjHZj4KfdZUpcQm7rwL0eZmUPOS5ND%2FIxeeREQ9NcfH0qkhTwOSP1aaAzC0suqpBjqwAYzs5XLa4enCLihgwWGpgT4Fhy71p6UJiJ5T7KmpudMd48fk2q0fo37x93n%2B7hNfXn965BAPgjYoUw9kGMWBOewCWeYAIQolg6%2FZdQTsISdocD7nav%2BAIL%2BoH4Cvm5PseNwkOLbD767ShrhO2eJLCJfKjpFDN47JZB6eXNpy7VH5eem1W5qKeLrSbHYNzNmT0Qx0faB76VXRiwKn8ku%2B4s2uIti%2FB5gGw67221KrSpCf&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL2AH7V2MG%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=1069f4ce646ef4b5ca64fe7222a94fcb9859937463307af11429737c6ea957d6
	// ALPHA ALPHANUMS
	// ALPHA (lowercase letters) | NUM (0-9)
	
	// Must start with an ALPHA.
	if (!isalpha(s[0]) || !islower(s[0]))
	{
		return false;
	}
	
	if (isdigit(s[0]))
	{
		return false;
	}
	
	if (s[0] == '_')
	{
		return false;
	}
	
	for (size_t i = 1; i < sLength; ++i)
	{
		if (isSpecialSymbol(s[i]))
		{
			if (s[i] != '_')
			{
				return false;
			}
		}
		// All lowercase
		if (isalpha(s[i]) && !islower(s[i]))
		{
		    return false;
		}
		
		// For 049.dat
		if (s[i] == '_')
		{
			if (s[i-1] == '_')
			{
				return false;
			}
		}
	}
	
	// The last character cannot be a '_' or an empty string.
	// ('_' | e) (alpha | num)
	if (s[sLength - 1] == '_')
	{
		return false;
	}
		
	return true;
}

// Found on page 2
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415551?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=nAUd5XqCXhQY3xwXK0beddFQbVtNqnh8TBlRP7KrMTM%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27SyntaxChart.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFIaCXVzLWVhc3QtMSJHMEUCIFqgdAl4uU%2F1uUNq6QMNE0g4%2FVfGI0P51oU7y%2By5Uaa3AiEAyMW2W813CltCinm9Ox71WMAJ%2BwBBvPKTSifrPCHvKi4qtAUIexADGgw2MzU1Njc5MjQxODMiDAF6TpIF5%2FRnbExGHiqRBTXxXIFLqOEB4aFyb2onHIilmYFZVaSo93XoVPOCFMqlUJQRA6peFtI7AGVfpjV7NPY%2B%2FoZQUmfcGLJzB5Mju3fSCF55un%2BFw%2BHYlmc%2Bgl9g2DuQpD%2BwxJrHu70wz2WeQNNVbNx9lhzusrqOQbmfiDWGNljFrB3ITe%2FnscozbBLUVUnr%2F05F%2BRybX43YPwOSxrCxLJWgILu7nPEEAwS0zpedC9Ccr%2F2AQC94bOERL4pOPXL1h%2B3zXOlq0VlTdLNFl6iGZchS4f4QqL%2F6z77OzWR%2FKbTCYvEoxJ8z5qIRYM5Gwd8uvM1CNhQq1WAI31AVFr%2BJQW1QtHb%2BnTa0hTrVay8tz%2FWi7Z%2BxWYvUz5lWVAGYR0GCkqL0tJLx6w5UiZifqdwjSdzQe5MfwIi0yFdj61lhwj%2FAUmSej50gHTAR81d0vLtWvKWFxVk5ImSJ6vG%2FhDdrQbbpo3%2FA7VUQUTMQnkvOMyHHwm3mDCH1UGVTUfMx1dX%2FP1%2F4RH5lnIZ31bBFznnFFwe94%2FyG%2Bho3HJPLh9QeuW%2BTH3D0BTCjAjgyMLRCNB%2FSdBlfJAaKUVHbhKWRzuaXdaSZB6sjMbN5BsoZD1%2Bdl65yaqNj3UFe1Y0HjOXbxkTcSVxFwEDfWlf0xIbiHxSqfUXJIl%2FXskFQtVCLuo3MW8vWZjGH8%2FLOC2%2FqH5dkjTskZGR9TFuFMj1drUsCw415dbNVoNb%2BS%2B52KqTf9gWvaGtof9jzCezghyIXX8nxC3ohssa3%2B7CyHdyKd5Tvk%2BwJQOSQuO6E38iiuEkkYi59Ku4%2B5r00FciYCSsLN%2Fvmc%2B2borvnmMXOfu%2FOoerNUCvlaKJ8GbWXkaBXCIYu3M93HX0FLpUSOS46zZPvJwcF3jDMyOqpBjqxAdW%2BXgpz36Tq3BVoXYamIZEOIaKO9xY0wVBxM5EWF9doSsvEeA344u5GIFTr2mBNiNoxXBkIPxu031lfIj6HAU5Lneq2Dr9KcirTg8KFcxXLKaVrBbIdTkr%2Bn4u0tO2ef8ht9gizdO5xH12f2pt9DIrwdgmNOGQ5SD%2BUsdKu1LHR55%2B23QOrPheOdY0BP5K7rEqC9shTHBBU7%2BjQQu77QPY4CR4rAKD36uoRB2lZ30Ai%2BQ%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL2GZD5TKV%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=eeffa7a4d06c6b1863ea5aafc25d57f5a496008b6121d1a9addade9737114de8
bool Compiler::isBoolean(string s) const // determines if s is a boolean
{
	return ((s == "true") || (s == "false") || (s == "boolean"));
}

// Found on page 2
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415551?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=nAUd5XqCXhQY3xwXK0beddFQbVtNqnh8TBlRP7KrMTM%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27SyntaxChart.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFIaCXVzLWVhc3QtMSJHMEUCIFqgdAl4uU%2F1uUNq6QMNE0g4%2FVfGI0P51oU7y%2By5Uaa3AiEAyMW2W813CltCinm9Ox71WMAJ%2BwBBvPKTSifrPCHvKi4qtAUIexADGgw2MzU1Njc5MjQxODMiDAF6TpIF5%2FRnbExGHiqRBTXxXIFLqOEB4aFyb2onHIilmYFZVaSo93XoVPOCFMqlUJQRA6peFtI7AGVfpjV7NPY%2B%2FoZQUmfcGLJzB5Mju3fSCF55un%2BFw%2BHYlmc%2Bgl9g2DuQpD%2BwxJrHu70wz2WeQNNVbNx9lhzusrqOQbmfiDWGNljFrB3ITe%2FnscozbBLUVUnr%2F05F%2BRybX43YPwOSxrCxLJWgILu7nPEEAwS0zpedC9Ccr%2F2AQC94bOERL4pOPXL1h%2B3zXOlq0VlTdLNFl6iGZchS4f4QqL%2F6z77OzWR%2FKbTCYvEoxJ8z5qIRYM5Gwd8uvM1CNhQq1WAI31AVFr%2BJQW1QtHb%2BnTa0hTrVay8tz%2FWi7Z%2BxWYvUz5lWVAGYR0GCkqL0tJLx6w5UiZifqdwjSdzQe5MfwIi0yFdj61lhwj%2FAUmSej50gHTAR81d0vLtWvKWFxVk5ImSJ6vG%2FhDdrQbbpo3%2FA7VUQUTMQnkvOMyHHwm3mDCH1UGVTUfMx1dX%2FP1%2F4RH5lnIZ31bBFznnFFwe94%2FyG%2Bho3HJPLh9QeuW%2BTH3D0BTCjAjgyMLRCNB%2FSdBlfJAaKUVHbhKWRzuaXdaSZB6sjMbN5BsoZD1%2Bdl65yaqNj3UFe1Y0HjOXbxkTcSVxFwEDfWlf0xIbiHxSqfUXJIl%2FXskFQtVCLuo3MW8vWZjGH8%2FLOC2%2FqH5dkjTskZGR9TFuFMj1drUsCw415dbNVoNb%2BS%2B52KqTf9gWvaGtof9jzCezghyIXX8nxC3ohssa3%2B7CyHdyKd5Tvk%2BwJQOSQuO6E38iiuEkkYi59Ku4%2B5r00FciYCSsLN%2Fvmc%2B2borvnmMXOfu%2FOoerNUCvlaKJ8GbWXkaBXCIYu3M93HX0FLpUSOS46zZPvJwcF3jDMyOqpBjqxAdW%2BXgpz36Tq3BVoXYamIZEOIaKO9xY0wVBxM5EWF9doSsvEeA344u5GIFTr2mBNiNoxXBkIPxu031lfIj6HAU5Lneq2Dr9KcirTg8KFcxXLKaVrBbIdTkr%2Bn4u0tO2ef8ht9gizdO5xH12f2pt9DIrwdgmNOGQ5SD%2BUsdKu1LHR55%2B23QOrPheOdY0BP5K7rEqC9shTHBBU7%2BjQQu77QPY4CR4rAKD36uoRB2lZ30Ai%2BQ%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL2GZD5TKV%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=eeffa7a4d06c6b1863ea5aafc25d57f5a496008b6121d1a9addade9737114de8
bool Compiler::isInteger(string s) const  // determines if s is an integer
{	
	if (s == "integer")
	{
		return true;
	}
	size_t i = 0;
	// If there is a + or -.
	if (s.front() == '+' || s.front() == '-')
	{
		++i;
	}
	// Checks if the current element is a digit
	for (; i < s.length(); ++i)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}

	return true;
}

// Found on page 2
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415551?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=nAUd5XqCXhQY3xwXK0beddFQbVtNqnh8TBlRP7KrMTM%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27SyntaxChart.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFIaCXVzLWVhc3QtMSJHMEUCIFqgdAl4uU%2F1uUNq6QMNE0g4%2FVfGI0P51oU7y%2By5Uaa3AiEAyMW2W813CltCinm9Ox71WMAJ%2BwBBvPKTSifrPCHvKi4qtAUIexADGgw2MzU1Njc5MjQxODMiDAF6TpIF5%2FRnbExGHiqRBTXxXIFLqOEB4aFyb2onHIilmYFZVaSo93XoVPOCFMqlUJQRA6peFtI7AGVfpjV7NPY%2B%2FoZQUmfcGLJzB5Mju3fSCF55un%2BFw%2BHYlmc%2Bgl9g2DuQpD%2BwxJrHu70wz2WeQNNVbNx9lhzusrqOQbmfiDWGNljFrB3ITe%2FnscozbBLUVUnr%2F05F%2BRybX43YPwOSxrCxLJWgILu7nPEEAwS0zpedC9Ccr%2F2AQC94bOERL4pOPXL1h%2B3zXOlq0VlTdLNFl6iGZchS4f4QqL%2F6z77OzWR%2FKbTCYvEoxJ8z5qIRYM5Gwd8uvM1CNhQq1WAI31AVFr%2BJQW1QtHb%2BnTa0hTrVay8tz%2FWi7Z%2BxWYvUz5lWVAGYR0GCkqL0tJLx6w5UiZifqdwjSdzQe5MfwIi0yFdj61lhwj%2FAUmSej50gHTAR81d0vLtWvKWFxVk5ImSJ6vG%2FhDdrQbbpo3%2FA7VUQUTMQnkvOMyHHwm3mDCH1UGVTUfMx1dX%2FP1%2F4RH5lnIZ31bBFznnFFwe94%2FyG%2Bho3HJPLh9QeuW%2BTH3D0BTCjAjgyMLRCNB%2FSdBlfJAaKUVHbhKWRzuaXdaSZB6sjMbN5BsoZD1%2Bdl65yaqNj3UFe1Y0HjOXbxkTcSVxFwEDfWlf0xIbiHxSqfUXJIl%2FXskFQtVCLuo3MW8vWZjGH8%2FLOC2%2FqH5dkjTskZGR9TFuFMj1drUsCw415dbNVoNb%2BS%2B52KqTf9gWvaGtof9jzCezghyIXX8nxC3ohssa3%2B7CyHdyKd5Tvk%2BwJQOSQuO6E38iiuEkkYi59Ku4%2B5r00FciYCSsLN%2Fvmc%2B2borvnmMXOfu%2FOoerNUCvlaKJ8GbWXkaBXCIYu3M93HX0FLpUSOS46zZPvJwcF3jDMyOqpBjqxAdW%2BXgpz36Tq3BVoXYamIZEOIaKO9xY0wVBxM5EWF9doSsvEeA344u5GIFTr2mBNiNoxXBkIPxu031lfIj6HAU5Lneq2Dr9KcirTg8KFcxXLKaVrBbIdTkr%2Bn4u0tO2ef8ht9gizdO5xH12f2pt9DIrwdgmNOGQ5SD%2BUsdKu1LHR55%2B23QOrPheOdY0BP5K7rEqC9shTHBBU7%2BjQQu77QPY4CR4rAKD36uoRB2lZ30Ai%2BQ%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL2GZD5TKV%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=eeffa7a4d06c6b1863ea5aafc25d57f5a496008b6121d1a9addade9737114de8
bool Compiler::isLiteral(string s) const// determines if s is a literal
{
	if (isBoolean(s))
	{
		return true;
	}
	
	// Check if the literal contains "not "
	//if (s.substr(0, 4) == "not ")
	//{
	//	if (isBoolean(s.substr(4, -1)))
	//	{
	//		return true;
	//	}
	//}
	
	if (s.front() == '+' || s.front() == '-')
	{
		if (isInteger(s))
		{
			return true;
		}
	}
	if (isInteger(s))
	{
		return true;
	}
	return false;
}



/* COMPILER FUNCTIONS */
// Link: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8422333?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698354000000&X-Blackboard-Signature=tQ0ruO8r8%2FWDciGQ5eHqZ5zWNwCiTnVjT%2BtUFxWzB5s%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27OverallCompilerStructure%25282%2529.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFAaCXVzLWVhc3QtMSJHMEUCIQDOh79wpa%2FC24mCI27En3XIud1XA5N4gUiE3b3AUmyYDAIgQNUM3kR6rD6dhNoPrXZxhvukGsRXmh8U3ox5s%2FXUfPcqswUIeRADGgw2MzU1Njc5MjQxODMiDBrZjT2T5P7PJ7ff5iqQBQXJSiAQa6if%2B26hbfIHlnlidCVd3dsYmCz0sdt2%2FzrOL3umkC4Zl7TynlAtEOi8YhG2H6%2BSOptr7RdoVPa92FCX9dnOrHv2%2Brhf6NsGZ5UYsGDT%2BGRFOSQaGNKYRxzhVFbiRLRY3REIW2zTlLgCU5CCwe3T1Hd2lbxeKgcWNi4%2BN4U9zHPIfbsSoJic6tGyJnxsuyhX34ffUcFiPtPYWPQfelmkQIbl1q%2FxH0xBrK%2BfOxjy5GE6NN4L2U2gJW5wdr9lTv%2BCbTIMTEXcZ5vOCMS8%2BLEAd4sNp66cyLzVSSMhcySAVAc7ZcnX%2B2WdVHRx729TCsa9VqDi5s%2BCwCkdeeXgJHOMjp1QBy6n%2FbN%2BKzNBUpyCquY%2BtRscoE6AI%2BPGSYFwvwDOZ%2Fc2gb%2B51jFfX5cbUQSVX2IsogL4%2BubYx5o%2Bbs%2FW%2FkW1Vza8CMEvv0bnnOwuf0ruUqwQYrA8KuQ1xcHKpUjsIs%2FCYJtTMUM7DysgLVW%2Fz8Dn9tWq59mTtzuVDT2mQ9795%2FbLGSgGPTFqG9d%2BPiscieu3hdc%2F1Cwh6swFLVriuc7Fmni8HhLOA7uCt0NBMBmNh9FFUEmUM7embbw3djRx41ZcVtdJ65%2BqQHEz9WzJG1DxNzsm0t4yAC9GPiQ9vDqAohiBizfa0riIZpU%2F0pUOI5msPFR36mfGDRMET9RLGO15hP7jKiD2z2PcpT1IAsYew1UVmsT1c8bwwpINy%2BInH58mPrsMItsjhe7S3S%2BqNkw8gdFcvDuBmB1hhtImc4jgGeaoNE8x7Orl4HNe%2BT%2BDPfTCeo815z%2FfJhVQs4f6NLgaOACTEfjsMVPEVGKVmcHnbgLD4vBtJLwMbKTmlgWSc6%2F%2BMwSpI2ilNOk0MJ6W6qkGOrEBk5gOfsGy7%2FtDwIlT7p538%2FlvdwymUNN4hBp8db8aAF%2FlqL259wFfcfdWVK%2BZAHArcnvt0MZoUU6FtcdsSx6DxuOAyNVVFHuornCT8HMb%2Bm4JVm1nusJWIW86%2BShuz8mZdqCVoS2vAsjW%2Fq6SfF7RAa7CFZ5zYF6dhvDNOQu9vNgBckt3orAnc%2BXnhayf1EGtuILZUAqzibTiGmuva4KVVY6cI9OvdPFjeFceugJ65XZn&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL4MDLYE7C%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=d8e8b88cb7bc4daf837795f31e75dc0ed09de94a53cc5265b153f38a8efb120d
// Page 6 

Compiler::Compiler(char **argv)
{

	sourceFile.open(argv[1]);
	listingFile.open(argv[2]);
	objectFile.open(argv[3]);
}

Compiler::~Compiler()
{
	sourceFile.close();
	listingFile.close();
	objectFile.close();
}

void Compiler::createListingHeader()
{
	// Time variable.
	time_t now = time(NULL);
	
	string names = "CODY DIGBY, MITCHELL MARTIN";
	
	// The following needs to be sent to the listing file.";
	listingFile << "STAGE0:" << "  " << names << "      " << ctime(&now)<< endl; 
	listingFile << "LINE NO." << "              " << "SOURCE STATEMENT" << "\n";
	listingFile << "\n";
}

void Compiler::createListingTrailer()
{
	listingFile << "COMPILATION TERMINATED";
	if (errorCount == 1)
	{
		listingFile << "      " << errorCount << " ERROR ENCOUNTERED" << endl;
	}
	else
	{
		listingFile << "      " << errorCount << " ERRORS ENCOUNTERED" << endl;
	}
}









/* ASSEMBLY FUNCTIONS */
storeTypes Compiler::whichType(string name) //tells which data type a name has
{
  storeTypes dataType;
  map<string, SymbolTableEntry>::iterator iter = symbolTable.find(name);
  
  if (isLiteral(name))
  {
  	if (isBoolean(name))
    {
    	dataType = BOOLEAN;
    }
    else
    {
    	dataType = INTEGER;
    }
  }
  else
  {
  	// if symbolTable[name] is defined 
  	if (symbolTable.count(name) > 0)
    {
    	dataType = iter->second.getDataType();
    }
    else
    {
		// Grabs '-big' and 'not'
    	processError("reference to undefined constant");
    }
  }
  return dataType;
}


string Compiler::whichValue(string name) //tells which value a name has
{
	string value;
	map<string, SymbolTableEntry>::iterator iter = symbolTable.find(name);
  
	if (isLiteral(name))
	{
		value = name;
	}
  	else 
  	{
  		// IS DEFINED AND HAS A VALUE
		
  		if ((symbolTable.count(name) > 0) && (iter->second.getValue() != ""))
    	{
    		value = iter->second.getValue();
		}
    	else
    	{
			processError("reference to undefined constant" );
    	}
  	}
	return value;
}


void Compiler::code(string op, string operand1, string operand2)
{
 	if (op == "program")
  {
  	emitPrologue(operand1);
  }
  else if (op == "end")
  {
  	emitEpilogue();
  }
  else
  {
  	processError("compiler error since function code should not be called with illegal arguments");
  }
}


void Compiler::emit(string label, string instruction, string operands,
            string comment)
{
	// Sets how the content is position,
	// written in the psuedocode.
	objectFile << left << setw(8) << label;
	objectFile << left << setw(8) << instruction;
	objectFile << left << setw(24) << operands;
	objectFile << left << comment << endl;
}

void Compiler::emitPrologue(string progName, string operand2)
{
	time_t currTime = time(NULL);
	string names = "CODY DIGBY, MITCHELL MARTIN";
	string along1 = "%INCLUDE \"Along32.inc\"";
	string along2 = "%INCLUDE \"Macros_Along.inc\"";
	
	// Writes the names, includes, and time to the object file.
	objectFile << "; " << names;
	objectFile << "       " << ctime(&currTime);
	objectFile << along1 << endl;
	objectFile << along2 << endl << endl;
	
	emit("SECTION", ".text");
	emit("global", "_start", "", "; program " + progName);
	objectFile << endl;
	emit("_start:");
	
/*
	; CODY DIGBY, MITCHELL MARTIN 		Mon Oct 19 17:19:53 2020
	%INCLUDE "Along32.inc"
	%INCLUDE "Macros_Along.inc"
	SECTION .text
	global _start ; program stage0no001
*/
}

void Compiler::emitEpilogue(string operand1, string operand2)
{
	emit("","Exit", "{0}");
	objectFile << "\n";
	emitStorage();
}

void Compiler::emitStorage()
{
  emit("SECTION", ".data", "", "");
  map<string, SymbolTableEntry>::iterator iter = symbolTable.begin();
  for (iter = symbolTable.begin(); iter != symbolTable.end(); ++iter)
  {
  	if ((iter->second.getAlloc()) == YES && (iter->second.getMode() == CONSTANT))
    {
		// True = -1
		// False = 0
		// Look at Lecture (Week 10, Day 2, 30 Minute mark.
		string value = iter->second.getValue();
		if (iter->second.getValue() == "false")
		{
			value = "0";
		}
		else if (iter->second.getValue() == "true")
		{
			value = "-1";
		}
    	emit(iter->second.getInternalName(), "dd", value, "; " + iter->first);
    }
  }
  
  objectFile << "\n";
  emit("SECTION", ".bss");
  for (iter = symbolTable.begin(); iter != symbolTable.end(); ++iter)
  {
  	if ((iter->second.getAlloc()) == YES && (iter->second.getMode() == VARIABLE))
    {
    	emit(iter->second.getInternalName(), "resd", "1", "; " + iter->first);
    }
  }
  
}

void Compiler::insert(string externalName, storeTypes inType, modes inMode,
              string inValue, allocation inAlloc, int inUnits)
{
	string name;
	
	string::iterator str_itr = externalName.begin();
	
	
	while (str_itr < externalName.end())
	{
		// GRABBING EACH NAME.
		name = "";
		
		// The CONTENTS of the ITERATOR
		// *str_itr - contents (the actual variable)
		// str_itr - iterator itself
		
		// 
		while ((*str_itr != ',') && (str_itr < externalName.end()))
		{
			name += *str_itr;
			++str_itr;	// Incrementing the iterator, not the contents.
		}
		
		// Already defined.
		if (name.size() != 0)
		{
			if (symbolTable.count(name) > 0)
			{
				processError("symbol " + name + " is multiply defined");
			}
			else if (isKeyword(name))
			{
				processError("illegal use of keyword");
			}
			else
			{
				if (isupper(name[0]))
				{
					// Take only the 15 characters.
					string limitName = name.substr(0, 15);
					symbolTable.insert( { limitName, SymbolTableEntry(limitName, inType, inMode, inValue, inAlloc, inUnits)} );
				}
				else
				{
					// Take only the 15 characters.
					string limitName = name.substr(0, 15);
					symbolTable.insert( { limitName, SymbolTableEntry(genInternalName(inType), inType, inMode, inValue, inAlloc, inUnits)} );        
				}
			}
			// The symbol table will hold up to 256 entries.
			if (symbolTable.size() > 256)
			{
				processError("cannot hold over 256 entries");
			}
		}
		
		if (str_itr == externalName.end())
		{
			break;
		}
		else
		{	
			++str_itr;
		}
	}
}











/* LEXICAL FUNCTIONS */


// Basically implementing the psuedocode.
string Compiler::nextToken()
{
	token = "";
	while (token == "")
	{
		if (ch == '{')
		{
			while ((nextChar() != END_OF_FILE) &&
					(ch != '}'))
			{
				// Empty one
			}
			
			if (ch == END_OF_FILE)
			{
				processError("unexpected end of file");
			}
			else
			{
				nextChar();
			}
		}
		else if (ch == '}')
		{
			processError("'}' cannot begin token");
		}
		else if (isspace(ch))
		{
			nextChar();
		}
		else if (isSpecialSymbol(ch))
		{
			token = ch;
			nextChar();
		}
		else if (islower(ch))
		{
			token = ch;
			while ((isalpha(nextChar()) ||
				   isdigit(ch) ||
				   (ch == '_')) &&
				   (ch != END_OF_FILE))
			{
				token += ch;
			}
			
			if (ch == END_OF_FILE)
			{
				processError("unexpected end of file");
			}
		}
		else if (isdigit(ch))
		{
			token = ch;
			while (isdigit(nextChar()) && (ch != END_OF_FILE))
			{
				token += ch;
			}
			if (ch == END_OF_FILE)
			{
				processError("unexpected end of file");
			}
		}
		else if (ch == END_OF_FILE)
		{
			token = ch;
		}
		else
		{
			processError("illegal symbol");
		}
	}
	
	// Get the first 15 characters.
	token = token.substr(0, 15);
	
	return token;
}

char Compiler::nextChar()
{
	// Gets the next character and stores it in ch.
	static char prevCh = '\n';
	sourceFile.get(ch);
	
	// If the end of the file has been reached.
	if (sourceFile.eof())
	{
		ch = END_OF_FILE;
	}
	
	// If the ch isn't at the end of file.
	if (ch != END_OF_FILE)
	{
		if (prevCh == '\n')
		{
			lineNo++;
			// Insert line number in the listing gile.
			listingFile << setw(5) << right << lineNo << "|";
		}
		// Put the ch inside the listing file.
		listingFile << ch;	
	}
	else
	{
		// Keeps the bottom line.
		listingFile << endl;
	}
	
	prevCh = ch;
	return ch;
}






/* GRAMMAR RULES */
void Compiler::prog()
{
	if (token != "program")
	{
		processError("keyword \"program\" expected");
	}
	progStmt();
	if (token == "const")
	{
		consts();
	}
	if (token == "var")
	{
		vars();
	}
	if (token != "begin")
	{
		processError("keyword \"begin\" expected");
	}
	beginEndStmt();
	if (token != "$")
	{
		processError("no text may follow \"end\"");
	}
}

void Compiler::progStmt()
{
	string x;
	if (token != "program")
	{
		processError("keyword \"program\" expected");
	}
	x = nextToken();
	if (!isNonKeyId(token))
	{
		processError("program name expected");
	}
	if (nextToken() != ";")
	{
		processError("semicolon expected");
	}
	nextToken();
	code("program", x);
	insert(x, PROG_NAME, CONSTANT, x, NO, 0);
}

// Basically the psuedocode
void Compiler::consts()
{
	if (token != "const")
	{
		processError("keyword \"const\" expected");
	}
	if (!isNonKeyId(nextToken()))
	{
		processError("non-keyword identifier must follow \"const\"");
	}
	constStmts();
}

// Basically the psuedocode
void Compiler::vars()
{
	if (token != "var")
	{
		processError("keyword \"var\" expected");
	}
	if (!isNonKeyId(nextToken()))
	{
		processError("non-keyword identifier must follow \"var\"");
	}
	varStmts();
}

// Basically the psuedocode.
void Compiler::beginEndStmt()
{
	if (token != "begin")
	{
		processError("keyword \"begin\" expected");
	}
	if (nextToken() != "end")
	{
		processError("keyword \"end\" expected");
	}
	if (nextToken() != ".")
	{
		processError("period expected");
	}
	nextToken();
	code("end", ".");
}


void Compiler::constStmts() //token should be NON_KEY_ID
{
  string x, y;
  if (!isNonKeyId(token))
  {
  	processError("non-keyword identifier expected");
  }
  x = token;
  if (nextToken() != "=")
  {
  	processError("\"=\" expected");
  }
  y = nextToken();
  
  if ( (y != "+") && (y != "-") && (y != "not") && (!isNonKeyId(y)) && (whichType(y) != BOOLEAN) && (whichType(y) != INTEGER) )
  {
  	processError("token to the right of \"=\" illegal");
  }
  if ((y == "+") || (y == "-"))
  {
	// 042.dat
	// whichType() looks it up but it doesn't exist.
	if (!isInteger(nextToken()))
	{
    	processError("integer expected after sign");
    }
    y += token;
  }
  if (y == "not")
  {
	// .052.dat (CHECKS THE if the non_key_id exists after "not"
  	if (whichType(nextToken()) != BOOLEAN)
    {
		// Look up in the table
		string savedToken = token;
		auto isItFound = symbolTable.find(savedToken);

		// Fetch the value
		if (isItFound != symbolTable.end())
		{
			string value = isItFound->second.getValue();
			if (value == "true")
			{
				y = "false";
			}
			else if (value == "false")
			{
				y = "true";
			}
			else
			{
				// 043.dat
				processError("boolean expected after \"not\"");
			}
		}
		else
		{
			processError("boolean expected after \"not\"");
		}
	}
    if (token == "true")
    {
    	y = "false";
    }
    else if (token == "false")
    {
    	y = "true";
    }
	else
	{
		// .052.dat (CHECKS THE if the non_key_id exists after "not"
		// Look up in the table
		string savedToken = token;
		auto isItFound = symbolTable.find(savedToken);

		// Fetch the value
		if (isItFound != symbolTable.end())
		{
			string value = isItFound->second.getValue();
			if (value == "true")
			{
				y = "false";
			}
			else if (value == "false")
			{
				y = "true";
			}
			else
			{
				processError("boolean expected after \"not\"");	
			}
		}
		else
		{
			processError("boolean expected after \"not\"");
		}
	}
  }  
  

 
  if (nextToken() != ";")
  {
  	processError("semicolon expected");
  }
  if ((whichType(y) != INTEGER) && (whichType(y) != BOOLEAN))
  {
	processError("data type of token on the right-hand side must be INTEGER or BOOLEAN");
  }
  insert(x, whichType(y), CONSTANT, whichValue(y), YES, 1);
  x = nextToken();
  if ((x != "begin") && (x != "var") && (!isNonKeyId(x)))
  {
	processError("non-keyword identifier, \"begin\", or \"var\" expected");
  }
  if (isNonKeyId(x))
  {
	constStmts();  
  }
}

void Compiler::varStmts() //token should be NON_KEY_ID
{ /*
   if (token is not a NON_KEY_ID)
   processError(non-keyword identifier expected)
   x = ids()
   if (token != ":")
   processError(":" expected)
   if (nextToken() is not one of "integer","boolean")
   processError(illegal type follows ":")
  y = token
   if (nextToken() != ";")
   processError(semicolon expected)
   insert(x,y,VARIABLE,"",YES,1)
   if (nextToken() is not one of "begin",NON_KEY_ID)
   processError(non-keyword identifier or "begin" expected)
   if (token is a NON_KEY_ID)
   varStmts()
   */
   
  string x, y;

	if (!isNonKeyId(token))
    {
			processError("non-keyword identifier expected");
	}

	x = ids();

	if (token != ":")
    {
			processError("\":\" expected");
	}
    
	nextToken();
	if ((token != "integer") && (token != "boolean"))
    {
			processError("illegal type follows \":\"");
	}

	y = token;

	if (nextToken() != ";")
    {
			processError("semicolon expected");
	}

	insert(x, whichType(y), VARIABLE, "", YES, 1);
  
	nextToken();
	if ((token != "begin") && (!isNonKeyId(token)))
    {
			processError("non-keyword identifier or begin expected");
	}
  
	if (isNonKeyId(token))
	{
			varStmts();
	}
}


string Compiler::ids() //token should be NON_KEY_ID
{
   string temp, tempString;
   if (!isNonKeyId(token))
   {
   		processError("non-keyword identifier expected");
   }
   tempString = token;
   temp = token;
   if (nextToken() == ",")
   {
   		if (!isNonKeyId(nextToken()))
      {
      		processError("non-keyword identifier expected");
      }
      tempString = temp + "," + ids();
   }
   return tempString;
}
// ::
