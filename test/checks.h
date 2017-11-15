#define AMATRIX_CHECK_EQUAL(a, b)                                \
    if (a != b) {                                                \
        std::cout << a << " is not equal to " << b << std::endl; \
        return 1;                                                \
    }

#define AMATRIX_CHECK_ALMOST_EQUAL(a, b)                         \
    if (std::abs(a - b) > std::numeric_limit<double>::epsilon) { \
        std::cout << a << " is not equal to " << b << std::endl; \
        return 1;                                                \
    }
