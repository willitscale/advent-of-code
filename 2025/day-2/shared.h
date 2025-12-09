char hasPattern(char * s);
char isPattern(char * s, size_t mod);

char hasPattern(char * s)
{
    ssize_t len = strlen(s);

    for(size_t j = 1; j <= len / 2; j++) {
        if (isPattern(s, j)) {
            return 1;
        }
    }
    return 0;
}

char isPattern(char * s, size_t mod)
{
    size_t len = strlen(s);
    
    if (len % mod != 0) {
        return 0;
    }

    for(size_t i = 0; i < mod; i++) {
        for(size_t j = i+mod; j < len; j+=mod) {
            if (s[i] != s[j]) {
                return 0;
            }
        }
    }

    return 1;
}