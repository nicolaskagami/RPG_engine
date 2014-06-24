//Nicolas Silveira Kagami
//Input Output header

#define MAX_PARAMETERS      12
#define MAX_FILENAME        15
#define MAX_LINE_SIZE       30
class IO 
{
    public:
        FILE * input_file;
        int parameters[MAX_PARAMETERS];
        int numparam;
        bool file_confirm;
        char entrystr[MAX_LINE_SIZE];
        IO();
        int read();
        int open_file(char * filename);
    private:
        char * buffer;
};
