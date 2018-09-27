#define AMATRIX_CHECK(a)                               \
    if (!(a)) {                                          \
        std::cout << "in line " << __LINE__ << " : " << #a << " is not true" << std::endl; \
        return 1;                                      \
    }

#define AMATRIX_CHECK_EQUAL(a, b)                                \
    if (a != b) {                                                \
        std::cout << "in line " << __LINE__ << " : " << a   \
                  << " is not equal to " << b << std::endl; \
        return 1;                                                \
    }

#define AMATRIX_CHECK_ALMOST_EQUAL(a, b)                         \
    if (std::abs(a - b) > std::numeric_limits<double>::epsilon()) { \
        std::cout << "in line " << __LINE__ << " : " << a           \
                  << " is not equal to " << b << std::endl; \
        return 1;                                                \
    }
