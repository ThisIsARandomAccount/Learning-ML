#include "file_reader.h"

/// Reads file, storing and returning it as a character array. Newlines are ignored
/// - Parameter path: File to read
string reader(char* path){
    FILE* file = fopen(path,"r");
    if(file == NULL){
        perror("Failed to open file");
    }
    int character = fgetc(file);
    char* read_data = (char*)malloc(sizeof(char)*100);
    if(read_data == NULL){
        perror("Failed to allocate memory");
    }
    int size = 100;
    int count = 1;
    while(character != EOF){
        if(size <= count){
            read_data = (char*)realloc(read_data, (int)(sizeof(char)*size*1.2));
            if(read_data == NULL){
                perror("Failed to reallocate memory");
            }
        }
        read_data[count-1] = character;
        count++;
        character = fgetc(file);
    }
    read_data = (char*)realloc(read_data,sizeof(char)*count);
    read_data[count-1] = '\0';
    if(read_data == NULL){
        perror("Failed to reallocate memory");
    }
    if(ferror(file)){
        perror("Failed to read file");
    }
    if(feof(file)){
        fclose(file);
        string to_return = {read_data, count};
        return to_return;
    }
    fclose(file);
    return((string){NULL,0});
}
