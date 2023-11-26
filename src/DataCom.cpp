#include "DataCom.h"

#ifdef CPP_STD
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#else
#include <Arduino.h>
#include <math.h>
#endif

const char *DataCom::head = "EINO::";
const char *DataCom::tail = "::END";
const char DataCom::separator = ';';

DataCom::DataCom() {
    operation[0] = '\0';
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        args[i][0] = '\0';
    }
}

DataCom::~DataCom() {}

DataCom::DataCom(const char *line) : DataCom() {
    int head_index = indexOfCharArray(line, DataCom::head, 0);
    int tail_index = indexOfCharArray(line, DataCom::tail, 0);
    if (head_index == -1 || tail_index == -1) {
        return;
    }
    char line_mod[FULL_LENGTH];
    line_mod[0] = '\0';
    subStr(line, head_index + strlen(DataCom::head),
           tail_index - (head_index + strlen(DataCom::head)), line_mod);

    if (line_mod) {
        char **aux = splitString(line_mod, DataCom::separator, ARRAY_LENGTH + 1);

        memcpy(operation, aux[0], strlen(aux[0]) + 1);
        free(aux[0]);

        for (int i = 0; i < ARRAY_LENGTH; i++) {
            memcpy(args[i], aux[i + 1], strlen(aux[i + 1]) + 1);
            free(aux[i + 1]);
        }
        free(aux);
    }
}

DataCom::DataCom(const DataCom &other) : DataCom() {
    if (this != &other) {
        memcpy(operation, other.operation, strlen(other.operation) + 1);
        for (int i = 0; i < ARRAY_LENGTH; i++) {
            memcpy(args[i], other.args[i], strlen(other.args[i]) + 1);
        }
    }
}

DataCom &DataCom::operator=(const DataCom &other) {
    if (this != &other) {
        memcpy(operation, other.operation, strlen(other.operation) + 1);
        for (int i = 0; i < ARRAY_LENGTH; i++) {
            memcpy(args[i], other.args[i], strlen(other.args[i]) + 1);
        }
    }

    return *this;
}

void DataCom::toString(char *line) {
    memcpy(line, DataCom::head, strlen(DataCom::head) + 1);
    strncat(line, operation, strlen(operation));
    strncat(line, &DataCom::separator, sizeof(DataCom::separator));
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        strncat(line, args[i], strlen(args[i]));
        strncat(line, &DataCom::separator, sizeof(DataCom::separator));
    }
    strncat(line, DataCom::tail, strlen(DataCom::tail));
    return;
}

void DataCom::builder(const char *line, char separator) {
    char **aux = splitString(line, separator, ARRAY_LENGTH + 1);
    memcpy(operation, aux[0], strlen(aux[0]) + 1);
    free(aux[0]);
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        memcpy(args[i], aux[i + 1], strlen(aux[i + 1]) + 1);
        free(aux[i + 1]);
    }
    free(aux);
}

void DataCom::setOperation(int op) { snprintf(operation, ARG_LENGTH, "%d", op); }

void DataCom::setOperation(unsigned int op) { snprintf(operation, ARG_LENGTH, "%u", op); }

void DataCom::setOperation(long op) { snprintf(operation, ARG_LENGTH, "%ld", op); }

void DataCom::setOperation(unsigned long op) { snprintf(operation, ARG_LENGTH, "%lu", op); }

void DataCom::setOperation(bool op) { snprintf(operation, ARG_LENGTH, "%d", op); }

void DataCom::setOperation(double op, unsigned int n_decimals) {
#ifndef CPP_STD
    // This algorithm should be improved, since it is a bit hardcoded
    int new_n_dec = n_decimals > ARG_LENGTH ? ARG_LENGTH : n_decimals;
    char aux[50];  // enough size to include max amount of decimals and a large int part
    dtostrf(op, 0, new_n_dec, aux);
    snprintf(operation, ARG_LENGTH, "%s", aux);
#endif
}

void DataCom::setOperation(float op, unsigned int n_decimals) {
#ifndef CPP_STD
    // This algorithm should be improved, since it is a bit hardcoded
    int new_n_dec = n_decimals > ARG_LENGTH ? ARG_LENGTH : n_decimals;
    char aux[50];  // enough size to include max amount of decimals and a large int part
    dtostrf(op, 0, new_n_dec, aux);
    snprintf(operation, ARG_LENGTH, "%s", aux);
#endif
}

void DataCom::setOperation(char op) { snprintf(operation, ARG_LENGTH, "%c", op); }

void DataCom::setOperation(const char *op) {
    memcpy(operation, op, strlen(op) + 1);
    int length = strlen(op) + 1;
    if (length > ARG_LENGTH - 1) {
        length = ARG_LENGTH - 1;
    }
    memcpy(operation, op, length);
    operation[length] = '\0';
}

void DataCom::setArgument(int position, int arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%d", arg);
}

void DataCom::setArgument(int position, unsigned int arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%u", arg);
}

void DataCom::setArgument(int position, long arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%ld", arg);
}

void DataCom::setArgument(int position, unsigned long arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%lu", arg);
}

void DataCom::setArgument(int position, bool arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%d", arg);
}

void DataCom::setArgument(int position, double arg, unsigned int n_decimals) {
    int new_pos = MAX_POS_VALUE(position);
#ifndef CPP_STD
    // This algorithm should be improved, since it is a bit hardcoded
    int new_n_dec = n_decimals > ARG_LENGTH ? ARG_LENGTH : n_decimals;
    char aux[50];  // enough size to include max amount of decimals and a large int part
    dtostrf(arg, 0, new_n_dec, aux);
    snprintf(args[new_pos], ARG_LENGTH, "%s", aux);
#endif
}

void DataCom::setArgument(int position, float arg, unsigned int n_decimals) {
    int new_pos = MAX_POS_VALUE(position);
#ifndef CPP_STD
    // This algorithm should be improved, since it is a bit hardcoded
    int new_n_dec = n_decimals > ARG_LENGTH ? ARG_LENGTH : n_decimals;
    char aux[50];  // enough size to include max amount of decimals and a large int part
    dtostrf(arg, 0, new_n_dec, aux);
    snprintf(args[new_pos], ARG_LENGTH, "%s", aux);
#endif
}

void DataCom::setArgument(int position, char arg) {
    int new_pos = MAX_POS_VALUE(position);
    snprintf(args[new_pos], ARG_LENGTH, "%c", arg);
}

void DataCom::setArgument(int position, const char *arg) {
    int new_pos = MAX_POS_VALUE(position);
    int length = strlen(arg) + 1;
    if (length > ARG_LENGTH - 1) {
        length = ARG_LENGTH - 1;
    }
    memcpy(args[new_pos], arg, length);
    args[new_pos][length] = '\0';
}

char **DataCom::splitString(const char *input, char split, int length) {
    char **output;

    output = (char **)malloc((length) * sizeof(char *));
    for (int j = 0; j < length; j++) {
        output[j] = (char *)malloc(ARG_LENGTH * sizeof(char));
        memcpy(output[j], "", 1);
    }

    int i = 0;
    int indexStart = 0;
    int indexEnd = indexOfChar(input, split, 0);
    while (true) {
        if (i >= length) {
            break;
        } else if (indexEnd != -1) {
            int sub_str_length = indexEnd - indexStart;
            if (sub_str_length > ARG_LENGTH - 1) {
                sub_str_length = ARG_LENGTH - 1;
            }
            memcpy(output[i], input + indexStart, sub_str_length);
            output[i][sub_str_length] = '\0';
            i++;
            indexStart = indexEnd + 1;
        } else {
            int sub_str_length = strlen(input) - indexStart;
            if (sub_str_length > ARG_LENGTH - 1) {
                sub_str_length = ARG_LENGTH - 1;
            }
            memcpy(output[i], input + indexStart, sub_str_length);
            output[i][sub_str_length] = '\0';
            i++;
            break;
        }
        indexEnd = indexOfChar(input, split, indexStart);
    }
    return output;
}

int DataCom::indexOfChar(const char *value, char c, int start_index) {
    if (start_index < 0) {
        start_index = 0;
    }

    if (start_index > strlen(value)) {
        return -1;
    }

    const char *ptr = strchr(value + start_index, c);
    if (ptr) {
        return ptr - value;
    }
    return -1;
}
int DataCom::indexOfCharArray(const char *value, const char *str, int start_index) {
    if (start_index < 0) {
        start_index = 0;
    }

    if (start_index > strlen(value)) {
        return -1;
    }

    int i = indexOfChar(value, str[0], start_index);
    while (i >= 0) {
        int c = 1;
        int j = i + c;
        for (; i + c < strlen(value); c++) {
            j = indexOfChar(value, str[c], i + c);
            if (j != i + c) {
                break;
            } else if (c + 1 == strlen(str)) {
                return i;
            }
        }
        i = indexOfChar(value, str[0], i + 1);
    }
    return -1;
}

void DataCom::subStr(const char *value, int start, int length, char *result) {
    result[0] = '\0';

    if (start < 0) {
        start = 0;
    } else if (start > strlen(value)) {
        return;
    }

    if (length < 0) {
        length = 0;
    } else if (length > FULL_LENGTH) {
        length = FULL_LENGTH - start - 1;
    } else if (length + start > strlen(value)) {
        length = strlen(value) - start - 1;
    }

    if (length < 0) {
        length = 0;
    }

    memcpy(result, &value[start], length);
    result[length] = '\0';

    return;
}
