// Cody Digby and Mitchell Martin
// CS 4301
// Stage 0
#include <string>
#include <iomanip>
#include <stage0.h>
#include <stdexcept>


// https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5fb6991aeccdc/8415551?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1698364800000&X-Blackboard-Signature=nAUd5XqCXhQY3xwXK0beddFQbVtNqnh8TBlRP7KrMTM%3D&X-Blackboard-Client-Id=100963&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27SyntaxChart.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEFIaCXVzLWVhc3QtMSJHMEUCIFqgdAl4uU%2F1uUNq6QMNE0g4%2FVfGI0P51oU7y%2By5Uaa3AiEAyMW2W813CltCinm9Ox71WMAJ%2BwBBvPKTSifrPCHvKi4qtAUIexADGgw2MzU1Njc5MjQxODMiDAF6TpIF5%2FRnbExGHiqRBTXxXIFLqOEB4aFyb2onHIilmYFZVaSo93XoVPOCFMqlUJQRA6peFtI7AGVfpjV7NPY%2B%2FoZQUmfcGLJzB5Mju3fSCF55un%2BFw%2BHYlmc%2Bgl9g2DuQpD%2BwxJrHu70wz2WeQNNVbNx9lhzusrqOQbmfiDWGNljFrB3ITe%2FnscozbBLUVUnr%2F05F%2BRybX43YPwOSxrCxLJWgILu7nPEEAwS0zpedC9Ccr%2F2AQC94bOERL4pOPXL1h%2B3zXOlq0VlTdLNFl6iGZchS4f4QqL%2F6z77OzWR%2FKbTCYvEoxJ8z5qIRYM5Gwd8uvM1CNhQq1WAI31AVFr%2BJQW1QtHb%2BnTa0hTrVay8tz%2FWi7Z%2BxWYvUz5lWVAGYR0GCkqL0tJLx6w5UiZifqdwjSdzQe5MfwIi0yFdj61lhwj%2FAUmSej50gHTAR81d0vLtWvKWFxVk5ImSJ6vG%2FhDdrQbbpo3%2FA7VUQUTMQnkvOMyHHwm3mDCH1UGVTUfMx1dX%2FP1%2F4RH5lnIZ31bBFznnFFwe94%2FyG%2Bho3HJPLh9QeuW%2BTH3D0BTCjAjgyMLRCNB%2FSdBlfJAaKUVHbhKWRzuaXdaSZB6sjMbN5BsoZD1%2Bdl65yaqNj3UFe1Y0HjOXbxkTcSVxFwEDfWlf0xIbiHxSqfUXJIl%2FXskFQtVCLuo3MW8vWZjGH8%2FLOC2%2FqH5dkjTskZGR9TFuFMj1drUsCw415dbNVoNb%2BS%2B52KqTf9gWvaGtof9jzCezghyIXX8nxC3ohssa3%2B7CyHdyKd5Tvk%2BwJQOSQuO6E38iiuEkkYi59Ku4%2B5r00FciYCSsLN%2Fvmc%2B2borvnmMXOfu%2FOoerNUCvlaKJ8GbWXkaBXCIYu3M93HX0FLpUSOS46zZPvJwcF3jDMyOqpBjqxAdW%2BXgpz36Tq3BVoXYamIZEOIaKO9xY0wVBxM5EWF9doSsvEeA344u5GIFTr2mBNiNoxXBkIPxu031lfIj6HAU5Lneq2Dr9KcirTg8KFcxXLKaVrBbIdTkr%2Bn4u0tO2ef8ht9gizdO5xH12f2pt9DIrwdgmNOGQ5SD%2BUsdKu1LHR55%2B23QOrPheOdY0BP5K7rEqC9shTHBBU7%2BjQQu77QPY4CR4rAKD36uoRB2lZ30Ai%2BQ%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231026T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL2GZD5TKV%2F20231026%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=eeffa7a4d06c6b1863ea5aafc25d57f5a496008b6121d1a9addade9737114de8

/* HELPER FUNCTIONS */
bool isBoolean(string s)  // determines if s is a boolean
{
	return ((s == "true") || (s == "false"));
}


bool isInteger(string s)   // determines if s is an integer
{
	try
	{
		// Converts a string to an integer
		stoi(s);
	}
	catch (const invalid_argument &e) 
	{
		return false;
	}
	return true;
}


bool isLiteral(string s) // determines if s is a literal
{
	if (isBoolean(s) || !isBoolean(s))
	{
		return true;
	}
	if (s.front() == '+' || s.front() == '-')
	{
		return true;
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

	sourceFile.open(argv[0]);
	listingFile.open(argv[1]);
	objectFile.open(argv[2]);
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
	listingFile << "STAGE0:" << setw(2) << names << setw(6) << ctime(&now)<< endl; 
	listingFile << "LINE NO:" << setw(9) << "SOURCE STATEMENT" << "\r\n";
}


