enable_testing()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include")

ADD_EXECUTABLE(runBloomFilterUnitTests Test_BloomFilter.cpp main.cpp)

TARGET_LINK_LIBRARIES(runBloomFilterUnitTests
    bloom_filter
    libgtest
    libgmock
)

add_test(BloomFilterUnitTests runBloomFilterUnitTests)
