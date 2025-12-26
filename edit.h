#ifndef EDIT_H
#define EDIT_H
#include <stdio.h>
#include "types.h"

/*read_and_validate_for_edit*/
Status read_and_validate_for_edit(char *file,char *tag);

Status copy_head(FILE *fptr,FILE *ptr);

Status read_tag(char* selected_tag,char *tag);

Status content_data( FILE *ptr,int size,char * data);

Status compare_tag(FILE *fptr, FILE *ptr,char *selected_tag,char *data);

Status copy_remain_data(FILE *fptr,FILE *ptr);

Status do_edit(char *tag,char *data);

Status read_e_size(int *size,FILE *fptr);


#endif