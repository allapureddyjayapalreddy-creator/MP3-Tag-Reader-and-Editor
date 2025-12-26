#include <stdio.h>
#include "types.h"
#include <string.h>
#include "view.h"
#include <stdlib.h>

Status read_and_validate_for_view(char *file,char *file_store,Info *data){
    if(strstr(file, ".mp3") == NULL){
         return v_failure;   //Here we can check the .mp3 file or not
    }else{
        if(strcmp(strstr(file, ".mp3"),".mp3")){
            return v_failure;
        }
    }
    strcpy(file_store,file); //Here the file extension will be store
    // file_store = file;
    return v_success;
}


Status skip_header(FILE *fptr){
    fseek(fptr,10,SEEK_SET);   //Here in the .mp3 file header section will be skip
    return v_success;
}


Status read_tags(FILE *fptr,Info *data){
    char buffer[5];      //Here the local variable will be take that have 4 bytes of character and 1 byte will be store null value
    fread(buffer,1,4,fptr);  //Here we can read data of 4 bytes from th file
    buffer[4] = '\0';
    if(strcmp(buffer,"TPE1") ==0){
        data->tag_name="Artist name";    //Here we can compare that read data and it will be stote in one structure variable
    }else if(strcmp(buffer,"TIT2")==0){
        data->tag_name="Song name";
    }else if(strcmp(buffer,"TALB")==0){
        data->tag_name="Album";
    }else if(strcmp(buffer,"TYER")==0){
        data->tag_name="Year";  
    }else if(strcmp(buffer,"COMM")==0){
        data->tag_name="Content type";   
    }else if(strcmp(buffer,"TCON")==0){
        data->tag_name="Composer"; 
    }
    return v_success;
}      

Status read_size(int *size,FILE *fptr,Info *data){
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
    // printf("%d\n",*(size));
    return v_success;
}


Status read_content(FILE *fptr,int size,Info *data){
    char buffer[size-1];   //Here the data can read size-1 times
    fread(buffer, 1, size-1, fptr);   //data will be read the size-1 times 
    data->tag_info=buffer;     //that read data will be store in the one structure variable
    printf("%-18s\t\n", data->tag_info);  //Then we can print the data using that variable 
    //The read_tags,read_size,read_content  These will run 6 times in the loop because we have 6 names to fetch data 1 by 1
}



Status do_view(Info *data,char *file_store){
   FILE *fptr =fopen(file_store,"r");

    if(skip_header(fptr)==v_failure){
        return v_failure;
    }
    printf("------------------------------------------------------------------\n");
    printf("               MP3 Tag Reader and Editor for ID3v2 \n");
    printf("------------------------------------------------------------------\n");
    for(int i=0;i<6;i++){
        if(read_tags(fptr,data)==v_failure){
            return v_failure;
        }
       printf("%-18s:\t", data->tag_name);
    //    printf(tag_name);

        int size=0;
        if(read_size(&size,fptr,data)==v_failure){
            return v_failure;
        }
        fseek(fptr,3,SEEK_CUR); //Here we are skip the 3 bytes of data 2 bytes is flag and 1 byte is null character
        if(read_content(fptr,size,data)==v_failure){
            return v_failure;
        }
    }   
    printf("-----------------------------------------------------------------------\n");
}