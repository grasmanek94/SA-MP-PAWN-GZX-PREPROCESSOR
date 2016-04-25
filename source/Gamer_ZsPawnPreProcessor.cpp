// Gamer_ZsPawnPreProcessor.cpp : Defines the entry point for the console application.
// GZsPPP
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace std;

vector<wstring> Adders;
vector<long> AddersNum;

void AddIdentifier(wstring ONE,long TWO)
{
	Adders.push_back(ONE);
	AddersNum.push_back(TWO);
}

std::wstring exec(wchar_t* cmd) { 
	FILE* pipe = _wpopen(cmd, L"r"); 
	if (!pipe) return L"ERROR"; 
	wchar_t buffer[32000]; 
	std::wstring result = L""; 
	while(!feof(pipe)) { 
		if(fgetws(buffer, 32000, pipe) != NULL) 
				result += buffer; 
	} 
	_pclose(pipe); 
	return result; 
} 

wstring convertInt(long number)
{
   wstringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc == 4)
	{
		_TCHAR *myFile = argv[3];
		_TCHAR StrippedName[256];
		_TCHAR PawnCCdir[256];
		_TCHAR CommandToExecute[1024];
		_TCHAR *SourceFileFolder = new _TCHAR[256];
		_TCHAR * TemporaryFile = new _TCHAR[256];
		//
		int i = 0;
		for(; (unsigned)i < wcslen(myFile); ++i)
		{
			SourceFileFolder[i] = myFile[i];
			SourceFileFolder[i+1] = 0;
		}
		i = wcslen(SourceFileFolder)-1;
		for(; i > 0; --i)
		{
			if(SourceFileFolder[i] == '\\')
			{
				SourceFileFolder[i] = 0;
				break;
			}
		}
		for(int x = 0; x < 256; ++x)StrippedName[x] = 0;
		GetModuleFileName( NULL, PawnCCdir, 256 );
		i = wcslen(PawnCCdir);
		for(; i > 0; --i)
		{
			if(PawnCCdir[i] == '\\')
			{
				PawnCCdir[i] = 0;
				break;
			}
		}
		i = wcslen(myFile);
		int start = 0,end = i;
		for(; i > 0; --i)
		{
			if(myFile[i] == '\\')
			{
				start = i+1;
				break;
			}
			if(myFile[i] == '.' && 
				wcslen(myFile) == (unsigned)end)
			{
				end = i;
			}
		}
		for(i = 0; i < (end-start); ++i)
		{
			StrippedName[i] = myFile[start+i];
		}
		//
			for(int a = 0; a < 256; ++a)
			{
				TemporaryFile[a] = 0;
			}
			swprintf(TemporaryFile,256,L"\"%s\\%s.amx\"",SourceFileFolder,StrippedName);
			_wremove(TemporaryFile);
			for(int a = 0; a < 256; ++a)
			{
				TemporaryFile[a] = 0;
			}
			swprintf(TemporaryFile,256,L"%s.temp",myFile);
			//CopyFile(myFile,TemporaryFile,false);
			wfstream ReadFrom (myFile); 
			//remove(TemporaryFile);
			_wremove(TemporaryFile);
			//wcout << myFile << "|" << TemporaryFile << "\r\n";
			wofstream TempOpen (TemporaryFile); 
			wstring line;
//			bool InComment		= false;
//			bool InStringQuote	= false;
//			bool InStringToken	= false;
			unsigned long linenum = 0;
			//bool InMultiLine	= false;
			//cout << ReadFrom.is_open() << "|" << TempOpen.is_open() << "\r\n";
			if (ReadFrom.is_open() && TempOpen.is_open()) 
			{
				while ( getline(ReadFrom,line).good() )
				{   
					++linenum;
					//wcout << line;
					/*size_t foundComment;
					size_t foundStringQuote;
					size_t foundStringToken;
					size_t foundMultiLine;

					if(InComment == false)
					{
						foundStringQuote = line.find(L"\"");
						foundStringToken = line.find(L"'");
						foundComment = line.find(L"/*");
						if(foundStringQuote == string::npos)
						{
							if(foundStringToken == string::npos)
							{
								if(foundComment != string::npos)
								{
									InComment = true;
								}
							}
							else
							{
								if(foundComment < foundStringToken)
								{
									InComment = true;
								}
								else
								{
									bool InString = true;
									foundStringToken = line.find(L"'",foundStringToken+1);
									while(foundStringToken != string::npos)
									{
										if(InString == true)
										{	
											InString = false;
										}
										else
										{
											if(foundComment < foundStringToken)
											{
												break;
											}
											InString = true;
										}
										foundStringToken = line.find(L"'",foundStringToken+1);
									}
									if(InString = false)
									{

									}
								}
							}
						}
					}
					else
					{
						foundComment = line.find(L"/*");
					}*/
					//cout << "179\r\n";
					size_t foundReplacer = line.find(L"#adder");
					if(foundReplacer == string::npos)
					{
						//cout << "183\r\n";
						for(int v = 0; v < (int)Adders.size(); ++v)
						{
							size_t foundPlus;
							size_t foundMacro = line.find(Adders.at(v));

							//wcout << Adders.at(v) << "|" << AddersNum.at(v) << L"\r\n";
							//cout << "188\r\n";
							while(foundMacro != string::npos)
							{
								foundPlus = line.find(L"+",foundMacro);
								if(foundPlus == string::npos)
								{
									line.replace(foundMacro,Adders.at(v).length(),convertInt(AddersNum.at(v)));
								}
								else
								{
									int AmountOfChars[2] = {0,0};
									bool GotVal = false;
									char numer[256];
									//cout << "204\r\n";
									//_TCHAR *tmpws = new _TCHAR[256];
									//cout << "205\r\n";
									//[CRASH]swprintf(tmpws,256,L"%s",line.substr(foundMacro+foundPlus,wcslen(tmpws)-(foundMacro+foundPlus)));
									//cout << "206\r\n";
									for(int b = (int)(foundPlus); b < (int)line.length()/*(int)wcslen(tmpws)*/; ++b)
									{
										//if ( tmpws[b] >= '0' && tmpws[b] <= '9' ) {
										if ( line[b] >= '0' && line[b] <= '9' ) {
											GotVal = true;
											//numer.insert(numer.length(),tmpws[b],1);
											numer[(AmountOfChars[0])] = (char)line[b];
											++AmountOfChars[0];
											//wcout << "added: "<< line[b] << "\r\n";
										}
										else
										{
											if(GotVal == true)break;
											++AmountOfChars[1];
										}
										//cout << "219\r\n";
									}
									//cout << atoi(numer) << "-n\r\n";
									long Add = 0;
									long result = AddersNum.at(v);
									//cout << result << " -r\r\n";
									//cout << "223\r\n";
									if(AmountOfChars[0] > 0)
									{
										Add = atoi(numer);
										//cout << Add << "-a\r\n";
									}
									//cout << "228\r\n";
									result+= Add;
									_TCHAR xxx[32];
									swprintf(xxx,32,L"%d",result);
									//cout << "232\r\n";
									line.replace(foundMacro,((foundPlus-foundMacro)+AmountOfChars[1]+AmountOfChars[0]),xxx);
								}
								//cout << "235\r\n";
								foundMacro = line.find(Adders.at(v),foundMacro+1);
							}
							//cout << "238\r\n";
						}
						TempOpen << line << L"\n";
						//cout << "231\r\n";
					}
					else
					{
						//cout << "235\r\n";
						if(int(foundReplacer) != 0)
						{
							//cout << "238\r\n";
							wcout << "GZsPPP ("<<linenum<<") warning: found #adder but not at the beginning of the line! Ignoring this one and writing to output file! May cause pawnCC errors.\r\n";
							TempOpen << line << L"\n";
							//cout << "241\r\n";
						}
						else
						{
							//cout << "245\r\n";
							wstringstream Define[2];
							if(line[6] != 9 && line[6] != 32)
							{
								//wcout << L"Not an adder...|" << line[6] << "\r\n";
								continue; //not a #adder<space/tab><expression> directive. - ignore
							}
							bool Writing = false;
							int g = 0;
							for(g = 7; g < (int)line.length(); ++g)
							{
								if(line[g] == 9 || line[g] == 32)
								{
									if(Writing == false)
									{
										continue;
									}
									else
									{
										Writing = false;
										++g;
										break;
									}
								}
								if((line[g] >= 65 && line[g] <= 90) || (line[g] >= 97 && line[g] <= 122) || line[g] == 95)//A-Z,a-z,_
								{
									Writing = true;
									Define[0] << line[g];
								}
							}
							//cout << "275\r\n";
							for(;g < (int)line.length(); ++g)
							{
								if(line[g] == 9 || line[g] == 32 || line[g] == '(')
								{
									if(Writing == false)
									{
										continue;
									}
									else
									{
										break;
									}
								}
								if((line[g] >= '0' && line[g] <= '9'))
								{
									Writing = true;
									Define[1] << line[g];
								}
							}
							//cout << "295\r\n";
							long xxx;
							Define[1] >> xxx;
							//wcout << Define[1].str() << "-w " << xxx <<"\r\n";
							//wcout << _wtoi(Define[1]) << " - xxx atoi\r\n";
							AddIdentifier(Define[0].str(),xxx);
							TempOpen << L"\n";
						}
						//cout << "300\r\n";
					}    
				}
				//cout << "303\r\n";
				ReadFrom.close();
				TempOpen.close();
			}
			else
			{//
				cout << "Cannot process files, file access error\r\n";
				return 0;
			}
		
		//
		_TCHAR tempnamex[256];
		swprintf(tempnamex,256,L"%s.temp.x",myFile);
		_wrename(myFile,tempnamex);
		_wrename(TemporaryFile,myFile);
		//CopyFile(myFile,L"debug.pwn",false);//debugging
		swprintf(CommandToExecute,1024,L"cd \"%s\" && pawncco.exe -;+ -(+ \"%s\" && move /Y \"%s\\%s.amx\" \"%s\"",PawnCCdir,myFile,PawnCCdir,StrippedName,SourceFileFolder);
		wcout << exec(
			CommandToExecute
			)
			;
		_wremove(myFile);
		_wremove(TemporaryFile);
		Sleep(10);
		_wrename(tempnamex,myFile);
		cout << "\r\n---------------------------------------\r\nGamer_Zs Pawn #adder PreProcessor v0.1\r\nInfo: Please ignore \"moved x file(s)\".";
	}
	return 0;
}
