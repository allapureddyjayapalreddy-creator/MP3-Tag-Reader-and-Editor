#include <stdio.h>
#include "types.h"
#include "edit.h"
#include <string.h>
#include <stdlib.h>


Status read_and_validate_for_edit(char *file,char *tag){
    if(strcmp(tag,"-t")==0||strcmp(tag,"-T")==0||strcmp(tag,"-A")==0||strcmp(tag,"-y")==0||strcmp(tag,"-m")==0||strcmp(tag,"-c")==0){
            if(strstr(file, ".mp3") == NULL){
            return e_failure;   //Here we can check the .mp3 file or not
        }else{
            if(strcmp(strstr(file, ".mp3"),".mp3")){
                return e_failure;
            }
        }
    }else{
       return e_failure;
    }
    return e_success;
}

Status copy_head(FILE *fptr,FILE *ptr){
    char buffer[10];
    fread(buffer,1,10,fptr);   //Here we can read the data of header 10 bytes from the song.mp3 
    fwrite(buffer,1,10,ptr);  //Here we can we write the data of header of 10 bytes from temp.mp3
    long size=ftell(fptr);

}

Status read_tag(char* selected_tag,char *tag){
                
            if (strcmp(tag, "-a") == 0 ){
            strcpy(selected_tag, "TPE1");

            }else if (strcmp(tag, "-t") == 0){
            strcpy(selected_tag, "TIT2");

            }else if (strcmp(tag, "-A") == 0){
            strcpy(selected_tag, "TALB");

            }else if (strcmp(tag, "-y") == 0){
            strcpy(selected_tag, "TYER");

            }else if (strcmp(tag, "-c") == 0){
            strcpy(selected_tag, "COMM");

            }else if (strcmp(tag, "-C") == 0){
            strcpy(selected_tag, "TCON");
            }
            //selected_tag[4]='\0';
        return e_success;
}
Status content_data( FILE *ptr,int size,char * data){
    // fread(buffer,1,size,data);
    fwrite(data, 1, size, ptr);

}
Status read_e_size(int *size,FILE *fptr){
    char buffer[4];   //Here we take one buffer of4 bytes of size
    for(int i=3;i>=0;i--){   //we reading the reverse and convert in big to little
        buffer[i]=fgetc(fptr);//character by character buffer store it 4 bytes
    }
    // printf("%s\n",buffer);
    for(int i=0;i<4;i++){    //buffer size times we are running
        for(int j=7; j>=0;j--){  //it will store one byte = 8bits
            if(buffer[i] & (1<<j)){   //buffer[0] is there each bit will get from msb to lsb
                *size = (*size) | 1<<(8*i + j);   //we are set the msb to lsb
            }
        }
    }    
    return e_success;
}
Status compare_tag(FILE *fptr, FILE *ptr, char *selected_tag, char *new_data){
    char frame_id[5];
    int frame_size = 0;
    char flags[3];

    fread(frame_id, 1, 4, fptr);
    frame_id[4] = '\0';

    read_e_size(&frame_size, fptr);

    fread(flags, 1, 3, fptr);

    fwrite(frame_id, 1, 4, ptr);

    if (strcmp(frame_id, selected_tag) == 0){
        int data_size = strlen(new_data) + 1;

        unsigned char size_buf[4];
        size_buf[0] = (data_size >> 24) & 0xFF;
        size_buf[1] = (data_size >> 16) & 0xFF;
        size_buf[2] = (data_size >> 8)  & 0xFF;
        size_buf[3] = data_size & 0xFF;

        fwrite(size_buf, 1, 4, ptr);

        fwrite(flags, 1, 3, ptr);

        fwrite(new_data, 1, data_size-1, ptr);

        fseek(fptr, frame_size - 1, SEEK_CUR);
        
        return e_success;
    }else{
        
        unsigned char size_buf[4];
        size_buf[0] = (frame_size >> 24) & 0xFF;
        size_buf[1] = (frame_size >> 16) & 0xFF;
        size_buf[2] = (frame_size >> 8)  & 0xFF;
        size_buf[3] = frame_size & 0xFF;

        fwrite(size_buf, 1, 4, ptr);
       
        fwrite(flags, 1, 3, ptr);

        char *buffer = malloc(frame_size - 1);

        fread(buffer, 1, frame_size - 1, fptr);
        fwrite(buffer, 1, frame_size - 1, ptr);

    }
    return e_success;
}

Status copy_remain_data(FILE *fptr,FILE *ptr){
    char ch;
    while((ch=fgetc(fptr))!=EOF){
        fputc(ch,ptr);
    }
    return e_success;
}

Status do_edit(char *tag,char *data){
    FILE *fptr = fopen("song.mp3", "r+");
    FILE *ptr  = fopen("temp.mp3", "w+");

    if(copy_head( fptr, ptr)==e_failure){
        return e_failure;
    }

    char selected_tag[4];       //Here add the data 4 bytes

    if(read_tag(selected_tag,tag)==e_failure){
        return e_failure;
    }

        for(int i=0;i<6;i++){
    if(compare_tag(fptr,ptr,selected_tag,data)==e_failure){
        return e_failure;
    }
    }
    if(copy_remain_data(fptr,ptr)==e_failure){
        return e_failure;
    }
    printf("Edited Successfully in temporary file!\n");
    
    int ch;
    fseek(fptr,0,SEEK_SET);
    fseek(ptr,0,SEEK_SET);
        while ((ch = fgetc(ptr)) != EOF)
        {
            fputc(ch, fptr);
        }

        fclose(ptr);
        fclose(fptr);
        printf("Temporary file data should be copied successfully in the Orginal file Successfully!\n");
    return e_success;
}