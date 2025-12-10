
void buildLargestValue(char * line, char * result, size_t numbers, size_t offset, size_t idx);

void buildLargestValue(char * l, char * r, size_t n, size_t o, size_t idx)
{
    if (n == 0) {
        return;
    }
    size_t len = strlen(l);
    len -= (l[len-1] == '\n' ? 1 : 0);
    for (size_t i = o; i < len; i++) {
        if (l[i] > r[idx] && len - i >= n) {
            r[idx] = l[i];
            o = i+1;
        }
    }
    buildLargestValue(l, r, n - 1, o, idx + 1);
}
