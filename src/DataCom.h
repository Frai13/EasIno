#ifndef DATACOM_H
#define DATACOM_H

#ifdef TESTING
#define ARRAY_LENGTH 5
#define ARG_LENGTH 20
#else
#define ARRAY_LENGTH 5
#define ARG_LENGTH 15
#endif

#define HEAD_LENGTH 6
#define TAIL_LENGTH 5
#define FULL_LENGTH                                                                           \
    (HEAD_LENGTH * sizeof(char) + ARRAY_LENGTH * (ARG_LENGTH + sizeof(char)) * sizeof(char) + \
     TAIL_LENGTH * sizeof(char))

#define MAX_POS_VALUE(P)                \
    ({                                  \
        int pos;                        \
        if (P < 0) {                    \
            pos = 0;                    \
        } else if (P >= ARRAY_LENGTH) { \
            pos = ARRAY_LENGTH - 1;     \
        } else {                        \
            pos = P;                    \
        }                               \
        pos;                            \
    })

class DataCom {
   public:
    const static char *head;
    const static char *tail;
    const static char separator;
    char operation[ARG_LENGTH];
    char args[ARRAY_LENGTH][ARG_LENGTH];
    const static int array_length = ARRAY_LENGTH;
    const static int arg_length = ARG_LENGTH;

    DataCom();
    DataCom(const char *line);
    DataCom(const DataCom &);
    ~DataCom();
    DataCom &operator=(const DataCom &);
    void builder(const char *line, char separator);
    void setOperation(int arg);
    void setOperation(unsigned int arg);
    void setOperation(long arg);
    void setOperation(unsigned long arg);
    void setOperation(bool arg);
    void setOperation(double arg, unsigned int n_decimals);
    void setOperation(float arg, unsigned int n_decimals);
    void setOperation(char arg);
    void setOperation(const char *arg);
    void setArgument(int position, int arg);
    void setArgument(int position, unsigned int arg);
    void setArgument(int position, long arg);
    void setArgument(int position, unsigned long arg);
    void setArgument(int position, bool arg);
    void setArgument(int position, double arg, unsigned int n_decimals);
    void setArgument(int position, float arg, unsigned int n_decimals);
    void setArgument(int position, char arg);
    void setArgument(int position, const char *arg);
    void toString(char *line);
    char **splitString(const char *value, char split, int length);
    int indexOfChar(const char *value, char c, int start_index);
    int indexOfCharArray(const char *value, const char *str, int start_index);
    void subStr(const char *value, int start, int length, char *result);
};

#endif  // DATACOM_H