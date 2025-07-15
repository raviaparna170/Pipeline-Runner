#include "gtest/gtest.h"
#include "../modules/FFT.h"
#include <optional>

TEST(FFTTest, HandlesConstantSignal) {
    FFT fft;

    std::optional<double> result;
    for (int i = 0; i < 16; ++i) {
        result = fft.process(1.0); 
    }

    ASSERT_TRUE(result.has_value()) << "FFT did not return a value after 16 samples";
    EXPECT_GT(result.value(), 0.0) << "FFT magnitude should be greater than 0 for constant signal";
}
