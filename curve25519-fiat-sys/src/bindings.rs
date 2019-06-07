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

#[allow(non_camel_case_types)]
pub type fiat_25519_uint1 = ::std::os::raw::c_uchar;

#[allow(non_camel_case_types)]
pub type fiat_25519_int1 = ::std::os::raw::c_schar;

#[allow(non_camel_case_types)]
pub type fiat_25519_int128 = [u64; 2];

#[allow(non_camel_case_types)]
pub type fiat_25519_uint128 = [u64; 2];

extern "C" {
    pub fn fiat_25519_addcarryx_u51(
        out1: *mut u64,
        out2: *mut fiat_25519_uint1,
        arg1: fiat_25519_uint1,
        arg2: u64,
        arg3: u64,
    );
}

extern "C" {
    pub fn fiat_25519_subborrowx_u51(
        out1: *mut u64,
        out2: *mut fiat_25519_uint1,
        arg1: fiat_25519_uint1,
        arg2: u64,
        arg3: u64,
    );
}

extern "C" {
    pub fn fiat_25519_cmovznz_u64(out1: *mut u64, arg1: fiat_25519_uint1, arg2: u64, arg3: u64);
}

extern "C" {
    pub fn fiat_25519_carry_mul(out1: *mut u64, arg1: *const u64, arg2: *const u64);
}

extern "C" {
    pub fn fiat_25519_carry_square(out1: *mut u64, arg1: *const u64);
}

extern "C" {
    pub fn fiat_25519_carry_scmul_121666(out1: *mut u64, arg1: *const u64);
}

extern "C" {
    pub fn fiat_25519_carry(out1: *mut u64, arg1: *const u64);
}

extern "C" {
    pub fn fiat_25519_add(out1: *mut u64, arg1: *const u64, arg2: *const u64);
}

extern "C" {
    pub fn fiat_25519_sub(out1: *mut u64, arg1: *const u64, arg2: *const u64);
}

extern "C" {
    pub fn fiat_25519_opp(out1: *mut u64, arg1: *const u64);
}

extern "C" {
    pub fn fiat_25519_selectznz(
        out1: *mut u64,
        arg1: fiat_25519_uint1,
        arg2: *const u64,
        arg3: *const u64,
    );
}

extern "C" {
    pub fn fiat_25519_to_bytes(out1: *mut u8, arg1: *const u64);
}

extern "C" {
    pub fn fiat_25519_from_bytes(out1: *mut u64, arg1: *const u8);
}
