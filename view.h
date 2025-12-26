#ifndef VIEW_H
#define VIEW_H
#include <stdio.h>
#include "types.h"


typedef struct {
char * tag_name;  //Here we can store the Tag names of the file
char * tag_info;  //Here we can store the Tag Information of the file
}Info;

/*read_and_validate_for_view*/
Status read_and_validate_for_view(char *argv,char *file_store,Info *data);

/*To do_view skip_header*/
Status skip_header(FILE *fptr);

/*To do_view  read_tags*/
Status read_tags(FILE *fptr,Info *data);

/*To do_view read_size*/
Status read_size(int *size,FILE *fptr,Info *data);

/*To do_view read_content */
Status read_content(FILE *fptr,int size,Info *data);

/*To do_view*/
Status do_view(Info *data,char *file_store);


#endif