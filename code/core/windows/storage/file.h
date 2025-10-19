#ifndef PAX_WINDOWS_STORAGE_FILE_H
#define PAX_WINDOWS_STORAGE_FILE_H

#include "./import.h"

typedef struct Pax_Windows_File Pax_Windows_File;

/* Defaults */

Pax_Windows_File*
pax_windows_default_input(Pax_Arena* arena);

Pax_Windows_File*
pax_windows_default_output(Pax_Arena* arena);

Pax_Windows_File*
pax_windows_default_error(Pax_Arena* arena);

/* File */

Pax_Windows_File*
pax_windows_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Windows_File*
pax_windows_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Windows_File*
pax_windows_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

void
pax_windows_file_close(Pax_Windows_File* self);

paxb8
pax_windows_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name);

paxiword
pax_windows_file_write(Pax_Windows_File* self, paxu8* memory, paxiword length);

paxiword
pax_windows_file_read(Pax_Windows_File* self, paxu8* memory, paxiword length);

#endif // PAX_WINDOWS_STORAGE_FILE_H
