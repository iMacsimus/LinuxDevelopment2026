#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

void print_help(void) {
    printf("Usage: ./range arg1 (arg2) (arg3)\n");
    printf("(1) ./range N: prints sequence 0, ..., N-1. One element per line.\n");
    printf("(2) ./range M N: prints sequence M, M+1, … N-1. One element per line.\n");
    printf("(3) ./range M N S: prints sequence of numbers M+i*S between M, N not including N. One element per line.\n");
}

int parse_int(const char *src, int64_t *dst) {
    while(*src == ' ') ++src;
    char *end = NULL;
    int64_t res = strtoll(src, &end, 10);
    if (errno != 0) {
        return -1;
    }

    while(*end == ' ') ++end;
    if (*end != '\0') {
        return -1;
    }

    *dst = res;
    return 0;
}

int64_t try_parse_int(const char *src) {
    int64_t dst = 0;
    int err = parse_int(src, &dst);
    if (err) {
        fprintf(stderr, "error: couldn't parse integer from \"%s\".\n", src);
        exit(-1);
    }
    return dst;
}

int64_t try_parse_uint(const char *src) {
    int64_t res = try_parse_int(src);
    if (res < 0) {
        fprintf(stderr, "error: got %ld, but expected non-negative value.\n", res);
        exit(-1);
    }
}

void check_order(int64_t start, int64_t stop) {
    if (stop < start) {
        fprintf(stderr, "error: got %ld > %ld, but the 1-st argument expected to be less or equal the 2-nd argument\n", start, stop);
        exit(-1);
    }
}

void check_step(int64_t start, int64_t stop, int64_t step) {
    if (step == 0 && start != stop) {
        fprintf(stderr, "error: invalid step\n");
        exit(-1);
    }
    if (step > 0 && start > stop) {
        fprintf(stderr, "error: invalid step\n");
        exit(-1);
    }
    if (step < 0 && start < stop) {
        fprintf(stderr, "error: invalid step\n");
        exit(-1);
    }
}

int sgn(int64_t x) { return ((x) > 0) - ((x) < 0); }

int main(int argc, const char **argv) {
    if (argc == 1) {
        print_help();
        return 0;
    } 

    int64_t start = 0, stop = 0, step = 1;
    
    if (argc == 2) {
        stop = try_parse_uint(argv[1]);
    } else if (argc == 3) {
        start = try_parse_int(argv[1]);
        stop = try_parse_int(argv[2]);
        check_order(start, stop);
    } else if (argc == 4) {
        start = try_parse_int(argv[1]);
        stop = try_parse_int(argv[2]);
        step = try_parse_int(argv[3]);
        check_step(start, stop, step);
    }

    for (int64_t n = start; n * sgn(step) < stop * sgn(step); n += step) {
        printf("%ld\n", n);
    }

    return 0;
}