#include <stdio.h>

int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int is_hex_digit(char c) {
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

int decode_chars(const char input[2], char* output) {
    int high = hex_to_int(input[0]);
    int low = hex_to_int(input[1]);
    if (high == -1 || low == -1) return -1;
    *output = (high << 4) | low;
    return 0;
}

void encode_mode() {
    char c;
    int first = 1;
    
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') break;
        
        if (!is_space(c)) {
            if (!first) putchar(' ');
            char encoded[2];
            encode_char(c, encoded);
            putchar(encoded[0]);
            putchar(encoded[1]);
            first = 0;
            
            // Пропускаем остальные символы до следующего пробела или конца строки
            while (1) {
                c = getchar();
                if (c == EOF || c == '\n' || is_space(c)) break;
            }
        }
    }
    putchar('\n');
}

void decode_mode() {
    char c;
    int first = 1;
    char hex[2];
    int pos = 0;
    
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') break;
        
        if (!is_space(c)) {
            if (pos < 2 && is_hex_digit(c)) {
                hex[pos++] = c;
            } else {
                // Некорректный символ
                printf("n/a\n");
                return;
            }
        } else if (pos > 0) {
            if (pos != 2) {
                printf("n/a\n");
                return;
            }
            
            char decoded;
            if (decode_chars(hex, &decoded) == -1) {
                printf("n/a\n");
                return;
            }
            
            if (!first) putchar(' ');
            putchar(decoded);
            first = 0;
            pos = 0;
        }
    }
    
    // Обработка последнего символа
    if (pos > 0) {
        if (pos != 2) {
            printf("n/a\n");
            return;
        }
        
        char decoded;
        if (decode_chars(hex, &decoded) == -1) {
            printf("n/a\n");
            return;
        }
        
        if (!first) putchar(' ');
        putchar(decoded);
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("n/a\n");
        return 1;
    }

    char mode = argv[1][0];
    if (argv[1][1] != '\0') {
        printf("n/a\n");
        return 1;
    }

    if (mode == '0') {
        encode_mode();
    } else if (mode == '1') {
        decode_mode();
    } else {
        printf("n/a\n");
        return 1;
    }

    return 0;
}
