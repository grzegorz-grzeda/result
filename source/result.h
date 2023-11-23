/*
 * MIT License
 *
 * Copyright (c) 2023 Grzegorz Grzęda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef RESULT_H
#define RESULT_H

/**
 * @defgroup result Result
 * @brief Generic result type definition and basic macros to handle checking of that result
 * @{
 */

#ifdef RESULT_ASSERT
#include <assert.h>
#define RESULT_ASSERT_FAIL_FUNCTION() assert(0) /**< Standard assert fail function implementation */
#else
#define RESULT_ASSERT_FAIL_FUNCTION() /**< Empty assert fail function if @ref RESULT_ASSERT is undefined */
#endif

/**
 * @brief Result type
 *
 * A generic result type covering most cases
 */
typedef enum result {
    RESULT_OK,                       /**< OK - The operation was successfull */
    RESULT_ERROR_ARGUMENT_INVALID,   /**< The provided function argument was invalid */
    RESULT_ERROR_MEMORY_NOT_ENOUGH,  /**< Not enough memory to perform the operation */
    RESULT_ERROR_HARDWARE_NO_DEVICE, /**< The hardware failed to appear */
    RESULT_ERROR_HARDWARE_BUSY,      /**< The hardware was busy */
    RESULT_ERROR_HARDWARE_IO,        /**< An transmission hardware error */
    RESULT_ERROR_OTHER,              /**< An undefined error */
    _RESULT_COUNT,                   /**< Result options count */
} result_t;

/**
 * @brief Check for invalid condition and goto the provided label
 * This macro checks the provided condition. If it is not valid
 * it asserts and jumps to the provided goto label.
 * @param[in] condition the condition to check
 * @param[in] goto_label the label to jump to in case of the condition failing
 */
#define ERR_GOTO(condition, goto_label)            \
    do {                                           \
        int _ERR_RET_CONDITION = (int)(condition); \
        if (_ERR_RET_CONDITION == 0) {             \
            RESULT_ASSERT_FAIL_FUNCTION();         \
            goto goto_label;                       \
        }                                          \
    } while (0)

/**
 * @brief Check for invalid condition and return some value
 * This macro checks the provided condition. If it is not valid
 * it asserts and returns the provided value.
 * @note use in functions returning a non-void type
 * @param[in] condition the condition to check
 * @param[in] return_value the value to return in case of the condition failing
 * @return the provided return_value
 */
#define ERR_RET(condition, return_value)           \
    do {                                           \
        int _ERR_RET_CONDITION = (int)(condition); \
        if (_ERR_RET_CONDITION == 0) {             \
            RESULT_ASSERT_FAIL_FUNCTION();         \
            return (return_value);                 \
        }                                          \
    } while (0)

/**
 * @brief Check for invalid condition and return
 * This macro checks the provided condition. If it is not valid
 * it asserts and returns.
 * @note use in functions returning void
 * @param[in] condition the condition to check
 */
#define ERR_RET_VOID(condition)                    \
    do {                                           \
        int _ERR_RET_CONDITION = (int)(condition); \
        if (_ERR_RET_CONDITION == 0) {             \
            RESULT_ASSERT_FAIL_FUNCTION();         \
            return;                                \
        }                                          \
    } while (0)

/**
 * @brief Check for errorous result and return it
 * This macro checks the provided result. If it is not @ref RESULT_OK
 * it asserts and returns it.
 * @note use in functions returning @ref result_t type
 * @param[in] result the result to check
 * @return the result (@ref result_t) if was not @ref RESULT_OK
 */
#define ERR_RET_RESULT(result)                     \
    do {                                           \
        result_t _ERR_RESULT = (result_t)(result); \
        if (_ERRRESULT != RESULT_OK) {             \
            RESULT_ASSERT_FAIL_FUNCTION();         \
            return _ERRRESULT;                     \
        }                                          \
    } while (0)

/**
 * @brief Get C-String description of given result
 * @param[in] result the result to get description of
 * @return NULL if invalid result was provided
 * @return pointer to the C-String with result description
 */
const char* result_get_string(result_t result);

/**
 * @}
 */

#endif  // RESULT_H