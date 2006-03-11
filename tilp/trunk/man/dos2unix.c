#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Remove the '\r' characters specifics to DOS */
int convert(char *filename)
{
  FILE *in;
  FILE *tmp;
  FILE *out;
  int c;

  /* Open the input file and process it into a temp file */
  printf("Processing file <%s>... ", filename);  
  in=fopen(filename, "rt");
  if(in == NULL)
    {
      printf("Unable to open this file: <%s>.\n", filename);
      return -1;
    }
  tmp=fopen("dos2unix.tmp", "wt");
  if(tmp == NULL)
    {
      printf("Unable to open temporary file.\n");
      return -1;
    }

  while(!feof(in))
    {
      c=fgetc(in);
      if(feof(in)) break;
      if(c == 13) continue;
      fputc(c, tmp);
    }

  fclose(in);
  fclose(tmp);

  /* Copy the temp file into the input file */
  tmp=fopen("dos2unix.tmp", "rt");
  if(tmp == NULL)
    {
      printf("Unable to open this file: <%s>.\n", filename);
      return -1;
    }
  out=fopen(filename, "wt");
  if(out == NULL)
    {
      printf("Unable to open temporary file.\n");
      return -1;
    }

  while(!feof(tmp))
    {
      c=fgetc(tmp);
      if(feof(tmp)) break;
      fputc(c, out);
    }

  fclose(tmp);
  fclose(out);
  printf("Done.\n");
  unlink("dos2unix.tmp");

  return 0;
}

/* Return the filename or its extension if it has one */
char *file_extension(char *filename)
{
  int i;
  char *p;
  
  for(i=strlen(filename); i > 0; i--)
    {
      if(filename[i] == '.') break;
    }
  p=filename+i;

return p;
}

/* Used by scandir to select files to sort */
int select_file(const struct dirent *d)
{
  const char *files[]={ "Makefile", "Makefile.in", ".c", ".h", ".txt" , NULL};
  int i=0;
  
  while(files[i] != NULL)
    {
      if(!strcmp(file_extension((char *)d->d_name), files[i])) break;
      i++;
    }
  //printf("<%i: %s>\n", i, files[i]);
  if(files[i] == NULL)
    return 0;
  else
    return 1;
  
  return 0;
}

int main(int argc, char *argv[], char **arge)
{
  char filename[256];
  struct dirent **namelist;
  int n;


  if(argc > 1)
    {
      strcpy(filename, argv[1]);
      if(convert(filename))
	{
	  printf("Error !!!\n");
	}
    }
  else
    {
      n = scandir(".", &namelist, select_file, alphasort);
      if (n < 0)
	perror("scandir");
      else
	while(n--) 
	  {
	    //printf("<%s>\n", namelist[n]->d_name);
	    convert(namelist[n]->d_name);
	    chmod(namelist[n]->d_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	  }
    }
  
  return 0;
}
