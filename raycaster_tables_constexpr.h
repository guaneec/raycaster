#pragma once

#include <math.h>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include "defs.h"

static constexpr const std::array<uint16_t, 256> g_tan_stda = ([]() constexpr {
    std::array<uint16_t, 256> out{};
    for (int i = 0; i < 256; ++i) {
        out[i] = static_cast<uint16_t>((256.0f * tan(i * M_PI_2 / 256.0f)));
    }
    return out;
})();

constexpr const uint16_t *g_tan = g_tan_stda.data();

static constexpr const std::array<uint16_t, 256> g_cotan_stda =
    ([]() constexpr {
        std::array<uint16_t, 256> out{};
        for (int i = 0; i < 256; ++i) {
            i == 0 ? std::numeric_limits<uint16_t>().max()
                   : out[i] = static_cast<uint16_t>(
                         (256.0f / tan(i * M_PI_2 / 256.0f)));
        }
        return out;
    })();

constexpr const uint16_t *g_cotan = g_cotan_stda.data();

static constexpr const std::array<uint8_t, 256> g_sin_stda = ([]() constexpr {
    std::array<uint8_t, 256> out{};
    for (int i = 0; i < 256; ++i) {
        out[i] = static_cast<uint8_t>(256.0f * sin(i / 1024.0f * 2 * M_PI));
    }
    return out;
})();

constexpr const uint8_t *g_sin = g_sin_stda.data();

static constexpr const std::array<uint8_t, 256> g_cos_stda = ([]() constexpr {
    std::array<uint8_t, 256> out{};
    for (int i = 0; i < 256; ++i) {
        out[i] = static_cast<uint8_t>(
            std::min(255.0, 256.0f * cos((i) / 1024.0f * 2 * M_PI)));
    }
    return out;
})();

constexpr const uint8_t *g_cos = g_cos_stda.data();


static constexpr const std::array<uint8_t, 256> g_nearHeight_stda =
    ([]() constexpr {
        std::array<uint8_t, 256> out{};
        for (int i = 0; i < 256; ++i) {
            out[i] = static_cast<uint8_t>(
                (INV_FACTOR_INT / (((i << 2) + MIN_DIST) >> 2)) >> 2);
        }
        return out;
    })();

constexpr const uint8_t *g_nearHeight = g_nearHeight_stda.data();

static constexpr const std::array<uint8_t, 256> g_farHeight_stda =
    ([]() constexpr {
        std::array<uint8_t, 256> out{};
        for (int i = 0; i < 256; ++i) {
            out[i] = static_cast<uint8_t>(
                (INV_FACTOR_INT / (((i << 5) + MIN_DIST) >> 5)) >> 5);
        }
        return out;
    })();

constexpr const uint8_t *g_farHeight = g_farHeight_stda.data();

static constexpr const std::array<uint16_t, 256> g_nearStep_stda =
    ([]() constexpr {
        std::array<uint16_t, 256> out{};
        for (int i = 0; i < 256; i++) {
            auto txn =
                ((INV_FACTOR_INT / (((i * 4.0f) + MIN_DIST) / 4.0f)) / 4.0f) *
                2.0f;
            if (txn != 0) {
                out[i] = (256 / txn) * 256;
            }
        }
        return out;
    })();

constexpr const uint16_t *g_nearStep = g_nearStep_stda.data();

static constexpr const std::array<uint16_t, 256> g_farStep_stda =
    ([]() constexpr {
        std::array<uint16_t, 256> out{};
        for (int i = 0; i < 256; i++) {
            auto txf = ((INV_FACTOR_INT / (((i * 32.0f) + MIN_DIST) / 32.0f)) /
                        32.0f) *
                       2.0f;
            if (txf != 0) {
                out[i] = (256 / txf) * 256;
            }
        }
        return out;
    })();

constexpr const uint16_t *g_farStep = g_farStep_stda.data();


static constexpr const std::array<uint16_t, 256> g_overflowOffset_stda =
    ([]() constexpr {
        std::array<uint16_t, 256> out{};
        for (int i = 1; i < 256; i++) {
            auto txs = ((INV_FACTOR_INT / (float) (i / 2.0f)));
            auto ino = (txs - SCREEN_HEIGHT) / 2;
            out[i] = int16_t(ino * (256 / txs) * 256);  // ???
        }
        return out;
    })();

constexpr const uint16_t *g_overflowOffset = g_overflowOffset_stda.data();

static constexpr const std::array<uint16_t, 256> g_overflowStep_stda =
    ([]() constexpr {
        std::array<uint16_t, 256> out{};
        for (int i = 1; i < 256; i++) {
            auto txs = ((INV_FACTOR_INT / (float) (i / 2.0f)));
            out[i] = (256 / txs) * 256;
        }
        return out;
    })();

constexpr const uint16_t *g_overflowStep = g_overflowStep_stda.data();

static constexpr const std::array<uint16_t, SCREEN_WIDTH> g_deltaAngle_stda =
    ([]() constexpr {
        std::array<uint16_t, SCREEN_WIDTH> out{};
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            float deltaAngle = atanf(((int16_t) i - SCREEN_WIDTH / 2.0f) /
                                     (SCREEN_WIDTH / 2.0f) * M_PI / 4);
            int16_t da = static_cast<int16_t>(deltaAngle / M_PI_2 * 256.0f);
            if (da < 0) {
                da += 1024;
            }
            out[i] = static_cast<uint16_t>(da);
        }
        return out;
    })();

constexpr const uint16_t *g_deltaAngle = g_deltaAngle_stda.data();
