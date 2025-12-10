LPoint * getRange(char *, LinkedList *);
char pointInRanges(LinkedList *, size_t);
char pointInRange(LPoint *, size_t);

LPoint * getRange(char * s, LinkedList * ll)
{
        size_t l = strlen(s);
        char * e = strstr(s, "-");
        char * o = s+l;

        char * n1 = calloc(sizeof(char), e - s + 1);
        char * n2 = calloc(sizeof(char), o - e + 1);

        strncpy(n1, s, e - s);
        strncpy(n2, e + 1, o - e - 1);

        LPoint * p = calloc(sizeof(LPoint), 1);

        p->x = strtol(n1, NULL, 10);
        p->y = strtol(n2, NULL, 10);

        free(n1);
        free(n2);

        return p;
}

char pointInRanges(LinkedList * ll, size_t x)
{
    LinkedList * c = ll;

    while (NULL != c && NULL !=c->data) {
        LPoint * p = (LPoint *)c->data;
        if (pointInRange(p, x)) {
            return 1;
        }
        c = c->next;
    }

    return 0;
}

char pointInRange(LPoint * p, size_t x)
{
    return (x >= p->x && x <= p->y);
}