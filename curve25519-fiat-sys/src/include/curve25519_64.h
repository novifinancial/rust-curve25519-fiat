// Copyright (c) Facebook, Inc. and its affiliates.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef _CURVE25519_64_H_
#define _CURVE25519_64_H_

        /* curve description: 25519 */
        /* requested operations: carry_mul, carry_square, carry_scmul121666, carry, add, sub, opp, selectznz, to_bytes, from_bytes */
        /* n = 5 (from "5"); */
        /* s = 0x8000000000000000000000000000000000000000000000000000000000000000 (from "2^255"); */
        /* c = [(1, 19);] (from "1,19"); */
        /* machine_wordsize = 64 (from "64"); */

        /* Computed values: */
        /* carry_chain = [0, 1, 2, 3, 4, 0, 1] */

#include <stdint.h>
        typedef unsigned char fiat_25519_uint1;
        typedef signed char fiat_25519_int1;
        typedef signed __int128 fiat_25519_int128;
        typedef unsigned __int128 fiat_25519_uint128;


        /*
         * The function fiat_25519_addcarryx_u51 is an addition with carry.
         * Postconditions:
         *   out1 = (arg1 + arg2 + arg3); mod 2^51
         *   out2 = ⌊(arg1 + arg2 + arg3); / 2^51⌋
         *
         * Input Bounds:
         *   arg1: [0x0 ~> 0x1]
         *   arg2: [0x0 ~> 0x7ffffffffffff]
         *   arg3: [0x0 ~> 0x7ffffffffffff]
         * Output Bounds:
         *   out1: [0x0 ~> 0x7ffffffffffff]
         *   out2: [0x0 ~> 0x1]
         */
        extern void fiat_25519_addcarryx_u51(uint64_t* out1, fiat_25519_uint1* out2, fiat_25519_uint1 arg1, uint64_t arg2, uint64_t arg3);

        /*
         * The function fiat_25519_subborrowx_u51 is a subtraction with borrow.
         * Postconditions:
         *   out1 = (-arg1 + arg2 + -arg3); mod 2^51
         *   out2 = -⌊(-arg1 + arg2 + -arg3); / 2^51⌋
         *
         * Input Bounds:
         *   arg1: [0x0 ~> 0x1]
         *   arg2: [0x0 ~> 0x7ffffffffffff]
         *   arg3: [0x0 ~> 0x7ffffffffffff]
         * Output Bounds:
         *   out1: [0x0 ~> 0x7ffffffffffff]
         *   out2: [0x0 ~> 0x1]
         */
        extern void fiat_25519_subborrowx_u51(uint64_t* out1, fiat_25519_uint1* out2, fiat_25519_uint1 arg1, uint64_t arg2, uint64_t arg3);

        /*
         * The function fiat_25519_cmovznz_u64 is a single-word conditional move.
         * Postconditions:
         *   out1 = (if arg1 = 0 then arg2 else arg3);
         *
         * Input Bounds:
         *   arg1: [0x0 ~> 0x1]
         *   arg2: [0x0 ~> 0xffffffffffffffff]
         *   arg3: [0x0 ~> 0xffffffffffffffff]
         * Output Bounds:
         *   out1: [0x0 ~> 0xffffffffffffffff]
         */
        extern void fiat_25519_cmovznz_u64(uint64_t* out1, fiat_25519_uint1 arg1, uint64_t arg2, uint64_t arg3);

        /*
         * The function fiat_25519_carry_mul multiplies two field elements and reduces the result.
         * Postconditions:
         *   eval out1 mod m = (eval arg1 * eval arg2); mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         *   arg2: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         */
        extern void fiat_25519_carry_mul(uint64_t out1[5], const uint64_t arg1[5], const uint64_t arg2[5]);

        /*
         * The function fiat_25519_carry_square squares a field element and reduces the result.
         * Postconditions:
         *   eval out1 mod m = (eval arg1 * eval arg1); mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         */
        extern void fiat_25519_carry_square(uint64_t out1[5], const uint64_t arg1[5]);

        /*
         * The function fiat_25519_carry_scmul_121666 multiplies a field element by 121666 and reduces the result.
         * Postconditions:
         *   eval out1 mod m = (121666 * eval arg1); mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         */
        extern void fiat_25519_carry_scmul_121666(uint64_t out1[5], const uint64_t arg1[5]);

        /*
         * The function fiat_25519_carry reduces a field element.
         * Postconditions:
         *   eval out1 mod m = eval arg1 mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         */
        extern void fiat_25519_carry(uint64_t out1[5], const uint64_t arg1[5]);

        /*
         * The function fiat_25519_add adds two field elements.
         * Postconditions:
         *   eval out1 mod m = (eval arg1 + eval arg2); mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         *   arg2: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         */
        extern void fiat_25519_add(uint64_t out1[5], const uint64_t arg1[5], const uint64_t arg2[5]);

        /*
         * The function fiat_25519_sub subtracts two field elements.
         * Postconditions:
         *   eval out1 mod m = (eval arg1 - eval arg2); mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         *   arg2: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         */
        extern void fiat_25519_sub(uint64_t out1[5], const uint64_t arg1[5], const uint64_t arg2[5]);

        /*
         * The function fiat_25519_opp negates a field element.
         * Postconditions:
         *   eval out1 mod m = -eval arg1 mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664], [0x0 ~> 0x1a666666666664]]
         */
        extern void fiat_25519_opp(uint64_t out1[5], const uint64_t arg1[5]);

        /*
         * The function fiat_25519_selectznz is a multi-limb conditional select.
         * Postconditions:
         *   eval out1 = (if arg1 = 0 then eval arg2 else eval arg3);
         *
         * Input Bounds:
         *   arg1: [0x0 ~> 0x1]
         *   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
         *   arg3: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
         */
        extern void fiat_25519_selectznz(uint64_t out1[5], fiat_25519_uint1 arg1, const uint64_t arg2[5], const uint64_t arg3[5]);

        /*
         * The function fiat_25519_to_bytes serializes a field element to bytes in little-endian order.
         * Postconditions:
         *   out1 = map (λ x, ⌊((eval arg1 mod m); mod 2^(8 * (x + 1););); / 2^(8 * x);⌋); [0..31]
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x7f]]
         */
        extern void fiat_25519_to_bytes(uint8_t out1[32], const uint64_t arg1[5]);

        /*
         * The function fiat_25519_from_bytes deserializes a field element from bytes in little-endian order.
         * Postconditions:
         *   eval out1 mod m = bytes_eval arg1 mod m
         *
         * Input Bounds:
         *   arg1: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x7f]]
         * Output Bounds:
         *   out1: [[0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc], [0x0 ~> 0x8cccccccccccc]]
         */
        extern void fiat_25519_from_bytes(uint64_t out1[5], const uint8_t arg1[32]);

#endif
