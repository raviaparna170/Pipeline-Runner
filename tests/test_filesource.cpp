#include <gtest/gtest.h>
#include "../modules/FileSource.h"

TEST(FileSourceTest, ReadsSamples) {
    std::ofstream testFile("../tests/test_input.txt");
    testFile << "1.23\n4.56\n7.89\n";
    testFile.close();

    FileSource fs("../tests/test_input.txt", 10);
    EXPECT_NEAR(fs.getNextSample(), 1.23, 0.01);
    EXPECT_NEAR(fs.getNextSample(), 4.56, 0.01);
    EXPECT_NEAR(fs.getNextSample(), 7.89, 0.01);
}
