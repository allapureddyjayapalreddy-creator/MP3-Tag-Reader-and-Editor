/*Name   : A.Jayapal Reddy
  Date   : 18-12-205
  Description : The project is MP3 tag Reader and Editor.
                The description is take one song file and that we can read and edit using this project
  sampel Input : Here the Input ./a.out -v song.mp3 we can read the file data
                while come to edit ./a.out -e -y 2025 song.mp3 it will read and change the year tag inr MP3 file
Sampele Ouput :              
Song name         :     Sunny Sunny - Yo Yo Honey Singh - [SongsPk.CC]
Artist name       :     Yo Yo Honey Singh - [SongsPk.CC]@u��|
Album             :     hello
Year              :     2025
Composer          :     Bollywood Music - [SongsPk.CC]
Content type      :     eng*/


#include "view.h"
#include "edit.h"
#include <stdio.h>
#include <string.h>
#include "types.h"


OperationType check_operation_type(char *);

int main(int argc, char *argv[])
{
    if(strcmp(argv[1],"--help")==0){
printf("-a Modifies Artist name\n"
    "-A Modifies Album\n"
    "-t Modifies Title\n"
    "-y Modifies year\n"
    "-c Modifies content type\n"
    "-C Modifies comment\n");
    }
    
        if((argc==3) &&(check_operation_type(argv[1])==e_view)){//Here argc are 3 or not check first then 1 is -v to check
            Info data;                //This is structure datatype and variable
            char file_store[15];    //This variable  will be store the file extension in view.c
            if(read_and_validate_for_view(argv[2],file_store, &data)== v_success){  //Validate the .mp3 or not contain in cml
                        if(do_view(&data, file_store)==v_failure){//then do_view function will be work and get and set the information
                            return 0;
                        }
            }
        } else if(argc==5 &&(check_operation_type(argv[1])==e_edit)){
            // Info data;
            char *ch=argv[2];
            if(read_and_validate_for_edit(argv[4],ch)== e_success){
                        if(do_edit(ch,argv[3])==e_failure){
                            return 0;
                        }
            }
        }else {
             printf("Unsupported file\n");
        }    

}    


OperationType check_operation_type(char *symbol)
{
    // Step 1 : Check whether the symbol is -e or not true - > return e_view false -> Step 2
    if (strcmp(symbol, "-v") == 0)
        return e_view;

    if (strcmp(symbol, "-e") == 0)
        return e_edit;


    return e_unsupported;
    // Step 2 : Check whether the symbol is -d or not true - > return e_edit false -> return e_unsupported
}
