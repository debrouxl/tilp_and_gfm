// AddEntry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string.h>

#define FALSE	0
#define TRUE	(!FALSE)

#define AUTOEXEC	"C:\\Autoexec.bat"
#define MAXCHARS	1024
#define KEYWORD		"PANGO_WIN32_NO_UNISCRIBE"
#define LINE		"set PANGO_WIN32_NO_UNISCRIBE=\"anything\""

int main(int argc, char* argv[])
{
	FILE *f;
	int bEntry = FALSE;

	// Open file
	f = fopen(AUTOEXEC, "rt");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open %s in reading.\n", AUTOEXEC);
		return -1;
	}

	// Search for entry
	while(!feof(f))
	{
		char line[MAXCHARS];

		fgets(line, MAXCHARS, f);
		if(strstr(line, KEYWORD))
			bEntry = TRUE;
	}

	// Close file
	fclose(f);

	// Entry already exists ?
	if(bEntry == TRUE)
		return 0;

	// Reopen file
	f = fopen(AUTOEXEC, "at");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open %s in writing.\n", AUTOEXEC);
		return -1;
	}

	fprintf(f, "# Added by TiLP setup for speeding GTK+ 2.x rendering\n");
	fprintf(f, "%s", LINE);

	// Close file (again)
	fclose(f);
	
	
	return 0;
}

