// Null check elimination benchmark (C version with runtime checks)
// In C, null checks must be done at runtime

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int has_value;
    int64_t value;
} Option;

Option none() {
    return (Option){0, 0};
}

Option some(int64_t value) {
    return (Option){1, value};
}

int is_some(Option opt) {
    return opt.has_value;
}

int64_t unwrap(Option opt) {
    if (!opt.has_value) {
        fprintf(stderr, "Unwrap on None\n");
        exit(1);
    }
    return opt.value;
}

int64_t unwrap_or(Option opt, int64_t default_val) {
    return opt.has_value ? opt.value : default_val;
}

Option map_double(Option opt) {
    if (is_some(opt)) {
        return some(unwrap(opt) * 2);  // Runtime null check
    }
    return none();
}

int64_t process_chain(int64_t value) {
    Option step1 = some(value);
    Option step2 = map_double(step1);  // Runtime check
    Option step3 = map_double(step2);  // Runtime check
    Option step4 = map_double(step3);  // Runtime check
    return unwrap_or(step4, 0);        // Runtime check
}

int main() {
    int64_t acc = 0;
    for (int n = 10000; n > 0; n--) {
        acc += process_chain(n);
    }
    printf("%lld\n", (long long)acc);
    return 0;
}
