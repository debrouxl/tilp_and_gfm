/*  ti_link - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* David Kuder has provided to me a converter module that I have corrected
 * due to some errors and has written below:
 */
/*
 *  This module converts GTKTILINK files to TIGL files
 *  going the other direction should be farily simple
 *  Parts taken from XLink85  Copyright (c) 1996 Jani Halme
 */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

int ti86_gtl_to_tigl_other_files(char *filename_src, char *filename_dst);
int ti86_gtl_to_tigl_group_files(char *filename_src, char *filename_dst);
int ti86_gtl_to_tigl_backup_files(char *filename_src, char *filename_dst);

/* ------------------------------------ */
/* tilp files to TIGraphLink files */
/* ------------------------------------ */

int ti86_gtl_to_tigl(char *filename_src, char *filename_dst)
{
  FILE *in;
  char varname[9];
  char svartype[5];
  
  /* Open the file */
  //printf("-->src<%s>\n", filename_src);
  in=fopen(filename_src, "rb");
  if(in == NULL)
  { 
	  return 0;
  }
  /* Retrieve some internal informations */
  fscanf(in, "%s\n", varname);
  if(!strcmp(varname, "TI86_PAK"))
  {
	/* We have a PAK file -> .86g */
	ti86_gtl_to_tigl_group_files(filename_src, filename_dst);
	fclose(in);
  }
  else
  {
	rewind(in);
	fscanf(in, "%s\n", varname);
	if(strcmp(varname, "TI86")) return 26;
	fscanf(in, "%s\n", varname);
	while(fgetc(in) != '\n');
	fscanf(in, "%s\n", svartype);
	if(!strcmp(svartype, "BACKUP"))
	{
	  /* We have a backup file -> .92 */
	  ti86_gtl_to_tigl_backup_files(filename_src, filename_dst);
	}
	else
	{
	  /* We have a normal file -> .86? */
	  ti86_gtl_to_tigl_other_files(filename_src, filename_dst);
	}
	fclose(in);
  }

  return 0;
}

int ti86_gtl_to_tigl_group_files(char *filename_src, char *filename_dst)
{
  char desc[43]="Group file received by tilp";
  FILE *in, *out;
  word sum=0;
  char varname[9];
  byte vartype;
  longword varsize;
  longword nvar;
  char svartype[5];
  char svarlock[4];
  int i;
  int c;
  int n;
  char buffer[256];
  long offset;
  longword size=0;
  
  /* Open the file */
  //printf("-->src<%s>\n", filename_src);
  in=fopen(filename_src, "rb");
  if(in == NULL)
  {
	  return 37;
  }
  /* Recreate the right extension */
  strcpy(filename_dst, filename_src);
  for(i=strlen(filename_dst); filename_dst[i] != '.'; i--)
  {
	filename_dst[i]='\0';
  }
  filename_dst[i]='\0';
  strcat(filename_dst, ".");
  strcat(filename_dst, "86g");
  /* Open a new file */
  //printf("-->dst<%s>\n", filename_dst);
  out=fopen(filename_dst, "wb");
  if(out == NULL)
  {
	  return 38;
  }
  /* The group file header */
  rewind(in);
  fscanf(in, "%s\n", buffer);
  if(strcmp(buffer, "TI86_PAK")) return 26;
  fscanf(in, "%08X\n", &nvar);
  printf("Number of vars: %i\n", nvar);
  fprintf(out, "**TI86**");
  fprintf(out, "%c%c%c", 0x1A, 0x0A, 0x00);
  for(i=0; i<42; i++) fprintf(out, "%c", desc[i]);
  offset=ftell(out);
  fprintf(out, "XX");

  for(n=0; n<nvar; n++)
  {
	/* Retrieve some informations */
	fscanf(in, "%s\n", varname);
	if(strcmp(varname, "TI86")) return 26;
	fscanf(in, "%s\n", varname);
	while(fgetc(in) != '\n');
	fscanf(in, "%s\n", svartype);
	vartype=ti_calc.type2byte(svartype);
	fscanf(in, "%08X\n", &varsize);
	size+=varsize+15;
	fgets(svarlock, 4, in);
	/* and write it */
	fprintf(out, "%c%c", 0x0B, 0x00);
    sum+=0x0B;
	fprintf(out, "%c%c", LSW(varsize), MSW(varsize));
	sum=sum+LSW(varsize)+MSW(varsize);
	fprintf(out, "%c", vartype);
	sum+=vartype;
	for(i=0; i<8; i++)
	{
		if(i < strlen(varname))
		{
		fprintf(out, "%c", varname[i]);
		sum+=varname[i];
		}
		else
		fprintf(out, "%c", '\0');
	}
	fprintf(out, "%c%c", LSW(varsize), MSW(varsize));
	sum=sum+LSW(varsize)+MSW(varsize);
	for(i=0; i<varsize; i++)
	{	
		c=fgetc(in);
		sum+=c;
		fputc(c, out);
	}
	fgetc(in);
  }
  fprintf(out, "%c%c", LSW(sum), MSW(sum));
  fseek(out, offset, SEEK_SET);
  fprintf(out, "%c%c", LSW(size), MSW(size));
  fseek(out, 0L, SEEK_END);

  fclose(in);
  fclose(out);	

  return 0;
}

int ti86_gtl_to_tigl_backup_files(char *filename_src, char *filename_dst)
{
  char desc[43]="Backup file received by tilp";
  FILE *in, *out;
  word sum;
  char varname[9];
  byte vartype;
  longword varsize;
  longword size;
  char svartype[5];
  char svarlock[4];
  int i, j;
  int c;
  long offset;
	
  /* Open the file */
  //printf("-->src<%s>\n", filename_src);
  in=fopen(filename_src, "rb");
  if(in == NULL) return 37;
  /* Retrieve some internal informations */
  fscanf(in, "%s\n", varname);
  if(strcmp(varname, "TI86")) return 26;
  fscanf(in, "%s\n", varname);
  while(fgetc(in) != '\n');
  fscanf(in, "%s\n", svartype);
  vartype=ti_calc.type2byte(svartype);
  fscanf(in, "%08X\n", &varsize);
  fgets(svarlock, 4, in);
  // Recreate the right extension
  strcpy(filename_dst, filename_src);
  for(i=strlen(filename_dst); filename_dst[i] != '.'; i--)
  {
	filename_dst[i]='\0';
  }
  filename_dst[i]='\0';
  strcat(filename_dst, ".86g");
  /* Open a new file */
  //printf("-->dst<%s>\n", filename_dst);
  out=fopen(filename_dst, "wb");
  if(out == NULL) return 38;
  /* The file header */
  fprintf(out, "**TI86**");
  fprintf(out, "%c%c%c", 0x1A, 0x0A, 0x00);
  for(i=0; i<42; i++) fprintf(out, "%c", desc[i]);
  offset=ftell(out);
  fprintf(out, "XX");
  size=0;
  fprintf(out, "%c%c", 0x09, 0x00);
  sum=0x09;
  fscanf(in, "%02X", &c);
  fscanf(in, "%02X", &c);
  for(i=0; i<9; i++)
  {
	fscanf(in, "%02X", &c);
	sum+=c;
	fprintf(out, "%c", c);
  }
  fgetc(in);
  for(j=0; j<3; j++)
  {
	fgetc(in);
	fscanf(in, "%02X", &c);
	sum+=c;
	varsize=(c << 8);
	fprintf(out, "%c", c);
	fscanf(in, "%02X", &c);
	sum+=c;
	varsize+=c;
	fprintf(out, "%c", c);
	fgetc(in);
	fgetc(in);
	size+=varsize;
	printf("%08X = %i\n", varsize, varsize);
	for(i=0; i<varsize; i++)
	{
	  c=fgetc(in);
	  sum+=c;
	  fputc(c, out);
	}
	fgetc(in);
  }
  fprintf(out, "%c%c", LSW(sum), MSW(sum));
  size+=2;
  fseek(out, offset, SEEK_SET);
  fprintf(out, "%c%c", LSW(size+15), MSW(size+15));
  fseek(out, 0L, SEEK_END);

  fclose(in);
  fclose(out);

  return 0;
}

int ti86_gtl_to_tigl_other_files(char *filename_src, char *filename_dst)
{
  char desc[43]="File received by tilp";
  FILE *in, *out;
  word sum;
  char varname[9];
  byte vartype;
  longword varsize;
  char svartype[5];
  char svarlock[4];
  int i;
  int c;
  
  /* Open the file */
  //printf("-->src<%s>\n", filename_src);
  in=fopen(filename_src, "rb");
  if(in == NULL)
  {
	  return 37;
  }
  /* Retrieve some internal informations */
  fscanf(in, "%s\n", varname);
  if(strcmp(varname, "TI86")) return 26;
  fscanf(in, "%s\n", varname);
  while(fgetc(in) != '\n');
  fscanf(in, "%s\n", svartype);
  if(!strcmp(svartype, "BACKUP")) return 21;
  vartype=ti_calc.type2byte(svartype);
  fscanf(in, "%08X\n", &varsize);
  fgets(svarlock, 4, in);
  /* Recreate the right extension */
  strcpy(filename_dst, filename_src);
  for(i=strlen(filename_dst); filename_dst[i] != '.'; i--)
  {
	filename_dst[i]='\0';
  }
  filename_dst[i]='\0';
  strcat(filename_dst, ".");
  strcat(filename_dst, ti_calc.byte2fext(vartype));
  /* Open a new file */
  //printf("-->dst<%s>\n", filename_dst);
  out=fopen(filename_dst, "wb");
  if(out == NULL)
  {
	  return 38;
  }
  /* The file header */
  fprintf(out, "**TI86**");
  fprintf(out, "%c%c%c", 0x1A, 0x0A, 0x00);
  for(i=0; i<42; i++) fprintf(out, "%c", desc[i]);

  fprintf(out, "%c%c", LSW(varsize+15), MSW(varsize+15));
  fprintf(out, "%c%c", 0x0B, 0x00);
  sum=0x0B;
  fprintf(out, "%c%c", LSW(varsize), MSW(varsize));
  sum=sum+LSW(varsize)+MSW(varsize);
  fprintf(out, "%c", vartype);
  sum+=vartype;
  for(i=0; i<8; i++)
  {
	if(i < strlen(varname))
	{
	  fprintf(out, "%c", varname[i]);
	  sum+=varname[i];
	}
	else
	fprintf(out, "%c", '\0');
  }
  fprintf(out, "%c%c", LSW(varsize), MSW(varsize));
  sum=sum+LSW(varsize)+MSW(varsize);
  for(i=0; i<varsize; i++)
  {
	c=fgetc(in);
	sum+=c;
	fputc(c, out);

  }
  fprintf(out, "%c%c", LSW(sum), MSW(sum));

  fclose(in);
  fclose(out);

  return 0;
}

/* ------------------------------------ */
/* TIGraphLink files to tilp files */
/* ------------------------------------ */

int ti86_tigl_to_gtl(char *filename_src, char *filename_dst)
{
  FILE *in;
  FILE *out=NULL;
  char varname[9];
  byte vartype;
  longword varsize;
  int i, j;
  char buffer[MAXCHARS];
  char file_extension[MAXCHARS];
  char c;

  /* Open the file */
  //printf("-->src<%s>\n", filename_src);
  in=fopen(filename_src, "rb");
  if(in == NULL) return 37;
  fgets(buffer, 9, in);
  if(strcmp(buffer, "**TI86**")) return 26;
  fgetc(in);
  fgetc(in);
  fgetc(in);
  for(i=0; i<42; i++) fgetc(in);
  varsize=fgetc(in);
  varsize+=fgetc(in) << 8;

  /* Recreate the right extension */
  strcpy(filename_dst, filename_src);
  for(i=strlen(filename_dst); filename_dst[i] != '.'; i--) {}
  strcpy(file_extension, filename_dst+i+1);
  filename_dst[i]='\0';
  strcat(filename_dst, ".");
  //printf("Filename: <%s> | Extension: <%s>\n", filename_dst, file_extension);
  printf("<<%c>>\n", file_extension[2]);
  switch(file_extension[2])
  {
	  /* Group file */
  case 'g':
  case 'G':
	  break;
	/* Backup file */
  case 'b':
  case 'B':
	/* Open a new file */
	strcat(filename_dst, "BACKUP");
	printf("-->dst<%s>\n", filename_dst);
	out=fopen(filename_dst, "wb");
	if(out == NULL) return 38;	
	/* Write the new file */
	fprintf(out, "TI86\n");
	fprintf(out, "0.00\n");
	fprintf(out, "main\\backup\n");
	fprintf(out, "BACKUP\n");
	fprintf(out, "00000000\n");
	fprintf(out, "00\n");
	c=fgetc(in);
	fprintf(out, "%02X", fgetc(in));
	fprintf(out, "%02X", c);
    for(i=0; i<9; i++)
	{
		fprintf(out, "%02X", fgetc(in));
	}
	fprintf(out, "\n");
	for(i=0; i<3; i++)
	{
		varsize=fgetc(in);
		varsize+=fgetc(in) << 8;
		fprintf(out, "<%02X%02X>\n", MSW(varsize), LSW(varsize));
		printf("<%04X>\n", varsize);
		for(j=0; j<varsize; j++)
		{
		  fputc(fgetc(in), out);
		}
		fprintf(out, "\n");
	}
	  break;
	/* Normal file */
  default:
	fgetc(in);
	fgetc(in);
	varsize=fgetc(in);
	varsize+=fgetc(in) << 8;
	vartype=fgetc(in);
	for(i=0; i<8; i++) varname[i]=fgetc(in);
	varname[i]='\0';
	/* Open a new file */
	strcat(filename_dst, ti_calc.byte2type(vartype));
	//printf("-->dst<%s>\n", filename_dst);
	out=fopen(filename_dst, "wb");
	if(out == NULL) return 38;	
	  /* Write the new file */
	fprintf(out, "TI86\n");
	fprintf(out, "%s\n", varname);
	fprintf(out, "%s\n", varname);
	fprintf(out, "%s\n", ti_calc.byte2type(vartype));
	fprintf(out, "%08X\n", varsize);
	fprintf(out, "00\n");
	fgetc(in);
	fgetc(in);
	for(i=0; i<varsize; i++)
	{
		fputc(fgetc(in), out);
	}
		break;
  }

  fclose(in);
  fclose(out);

  return 0;
}
