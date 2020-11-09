
#define NUM_ARG 0
#define DUP_LINE 1
#define WRONG_DATA 2
#define INVALID_LINE 3
#define INVALID_RGB 4
#define INVALID_PATH 5
#define NON_NEGATIVE 6
#define RESOLUTION 7
#define TEXTURE 8
#define MAP_FILE 9

char *(micub_err[]) =
{
	"Unexpected number of arguments, ",
 	"Duplicate line, ",
	"Must contain only integers, ",
	"Incorrect Line, ",
	"RGB format not correct, ",
	"Open image failed. path is not correct, ",
	"Width and Height must be non-negative, ",
	"Resolution",
	"Texture path",
	" map file"
};
