#define AMATRIX_CHECK_EQUAL(a, b)                                \
    if (a != b) {                                                \
        std::cout << a << " is not equal to " << b << std::endl; \
        return 1;                                                \
    \
}