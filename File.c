#include <unistd.h>

#define MAX_INPUT 1024

int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int is_hex_char(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

int hex_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1;
}

void encode_char(char c, char output[2]) {
    const char hex[] = "0123456789ABCDEF";
    output[0] = hex[(c >> 4) & 0xF];
    output[1] = hex[c & 0xF];
}

int decode_chars(const char input[2], char *output) {
    int high = hex_to_int(input[0]);
    int low = hex_to_int(input[1]);
    if (high == -1 || low == -1) return -1;
    *output = (high << 4) | low;
    return 0;
}

void encode_mode() {
    char buffer[MAX_INPUT];
    int pos = 0;
    char c;
    int first = 1;

    while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n') {
        if (is_space(c)) {
            if (pos > 0) {
                buffer[pos] = '\0';
                if (!first) write(STDOUT_FILENO, " ", 1);
                char encoded[2];
                encode_char(buffer[0], encoded);
                write(STDOUT_FILENO, encoded, 2);
                first = 0;
                pos = 0;
            }
        } else {
            if (pos == 0) buffer[pos++] = c;
        }
    }

    if (pos > 0) {
        if (!first) write(STDOUT_FILENO, " ", 1);
        char encoded[2];
        encode_char(buffer[0], encoded);
        write(STDOUT_FILENO, encoded, 2);
    }
    write(STDOUT_FILENO, "\n", 1);
}

void decode_mode() {
    char buffer[MAX_INPUT];
    int pos = 0;
    char c;
    int first = 1;

    while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n') {
        if (is_space(c)) {
            if (pos == 2) {
                buffer[pos] = '\0';
                if (!first) write(STDOUT_FILENO, " ", 1);
                char decoded;
                if (decode_chars(buffer, &decoded) == -1) {
                    write(STDOUT_FILENO, "n/a\n", 4);
                    return;
                }
                write(STDOUT_FILENO, &decoded, 1);
                first = 0;
            }
            pos = 0;
        } else {
            if (pos < 2 && is_hex_char(c)) buffer[pos++] = c;
        }
    }

    if (pos == 2) {
        if (!first) write(STDOUT_FILENO, " ", 1);
        char decoded;
        if (decode_chars(buffer, &decoded) {
            write(STDOUT_FILENO, "n/a\n", 4);
            return;
        }
        write(STDOUT_FILENO, &decoded, 1);
    }
    write(STDOUT_FILENO, "\n", 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDOUT_FILENO, "n/a\n", 4);
        return 1;
    }

    char *mode = argv[1];
    if (mode[0] == '0' && mode[1] == '\0') {
        encode_mode();
    } else if (mode[0] == '1' && mode[1] == '\0') {
        decode_mode();
    } else {
        write(STDOUT_FILENO, "n/a\n", 4);
        return 1;
    }

    return 0;
}
