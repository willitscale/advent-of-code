bool hasPattern(char * s);
bool isPattern(char * s, size_t mod);

bool hasPattern(char * s)
{
    ssize_t len = strlen(s);

    for(size_t j = 1; j <= len / 2; j++) {
        if (isPattern(s, j)) {
            return true;
        }
    }
    return false;
}

bool isPattern(char * s, size_t mod)
{
    size_t len = strlen(s);
    
    if (len % mod != 0) {
        return false;
    }

    for(size_t i = 0; i < mod; i++) {
        for(size_t j = i+mod; j < len; j+=mod) {
            if (s[i] != s[j]) {
                return false;
            }
        }
    }

    return true;
}