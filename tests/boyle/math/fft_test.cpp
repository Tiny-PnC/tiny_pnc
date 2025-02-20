/**
 * @file fft_test.cpp
 * @author Houchen Li (houchen_li@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024 Boyle Development Team
 *            All rights reserved.
 *
 */

#include "boyle/math/fft.hpp"

#include <complex>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

namespace boyle::math {

using namespace std::literals::complex_literals;

TEST_CASE_TEMPLATE("FftTest", T, float, double, long double) {
    constexpr std::array<std::complex<T>, 4> data{1.0, 2.0, 3.0, 4.0};
    constexpr std::array<std::complex<T>, 4> expected_fft_result{
        std::complex<T>(10.0), std::complex<T>(-2.0, 2.0), std::complex<T>(-2.0),
        std::complex<T>(-2.0, -2.0)
    };
    const std::vector<std::complex<T>> result = fft(std::span{data.cbegin(), data.cend()});

    CHECK_EQ(result.size(), expected_fft_result.size());

    for (size_t i = 0; i < result.size(); ++i) {
        CHECK_EQ(result[i].real(), doctest::Approx(expected_fft_result[i].real()).epsilon(1E-8));
        CHECK_EQ(result[i].imag(), doctest::Approx(expected_fft_result[i].imag()).epsilon(1E-8));
    }
}

TEST_CASE_TEMPLATE("RfftTest", T, float, double, long double) {
    constexpr std::array<T, 4> data{1.0, 2.0, 3.0, 4.0};
    constexpr std::array<std::complex<T>, 3> expected_fft_result{
        std::complex<T>(10.0), std::complex<T>(-2.0, 2.0), std::complex<T>(-2.0)
    };
    const std::vector<std::complex<T>> result = rfft(std::span{data.cbegin(), data.cend()});

    CHECK_EQ(result.size(), expected_fft_result.size());

    for (size_t i = 0; i < result.size(); ++i) {
        CHECK_EQ(result[i].real(), doctest::Approx(expected_fft_result[i].real()).epsilon(1E-8));
        CHECK_EQ(result[i].imag(), doctest::Approx(expected_fft_result[i].imag()).epsilon(1E-8));
    }
}

TEST_CASE_TEMPLATE("IfftTest", T, float, double, long double) {
    constexpr std::array<std::complex<T>, 4> fft_data{
        std::complex<T>(10.0), std::complex<T>(-2.0, 2.0), std::complex<T>(-2.0),
        std::complex<T>(-2.0, -2.0)
    };
    constexpr std::array<std::complex<T>, 4> expected_ifft_result{1.0, 2.0, 3.0, 4.0};
    const std::vector<std::complex<T>> result = ifft(std::span{fft_data.cbegin(), fft_data.cend()});

    CHECK_EQ(result.size(), expected_ifft_result.size());

    for (size_t i = 0; i < result.size(); ++i) {
        CHECK_EQ(result[i].real(), doctest::Approx(expected_ifft_result[i].real()).epsilon(1E-8));
        CHECK_EQ(result[i].imag(), doctest::Approx(expected_ifft_result[i].imag()).epsilon(1E-8));
    }
}

TEST_CASE_TEMPLATE("IrfftTest", T, float, double, long double) {
    constexpr std::array<std::complex<T>, 3> rfft_data{
        std::complex<T>(10.0), std::complex<T>(-2.0, 2.0), std::complex<T>(-2.0)
    };
    constexpr std::array<T, 4> expected_ifft_result{1.0, 2.0, 3.0, 4.0};
    const std::vector<T> result = irfft(std::span{rfft_data.cbegin(), rfft_data.cend()});

    CHECK_EQ(result.size(), expected_ifft_result.size());

    for (size_t i = 0; i < result.size(); ++i) {
        CHECK_EQ(result[i], doctest::Approx(expected_ifft_result[i]).epsilon(1E-8));
    }
}

TEST_CASE_TEMPLATE("FftfreqTest", T, float, double, long double) {
    constexpr std::array<T, 8> expected_freq{0.0, 1.25, 2.5, 3.75, -5.0, -3.75, -2.5, -1.25};
    const std::vector<T> freq = fftfreq<T>(8, 0.1);

    CHECK_EQ(freq.size(), expected_freq.size());

    for (size_t i = 0; i < freq.size(); ++i) {
        CHECK_EQ(freq[i], doctest::Approx(expected_freq[i]).epsilon(1E-8));
    }
}

TEST_CASE_TEMPLATE("RfftfreqTest", T, float, double, long double) {
    constexpr std::array<T, 5> expected_freq{0.0, 1.25, 2.5, 3.75, 5.0};
    const std::vector<T> freq = rfftfreq<T>(8, 0.1);

    CHECK_EQ(freq.size(), expected_freq.size());

    for (size_t i = 0; i < freq.size(); ++i) {
        CHECK_EQ(freq[i], doctest::Approx(expected_freq[i]).epsilon(1E-8));
    }
}

} // namespace boyle::math
