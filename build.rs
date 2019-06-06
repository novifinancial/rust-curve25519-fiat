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

use std::path::PathBuf;
use std::{env, process::Command};

pub const FIAT_HASH: &str = "2fdaa1024f39c1df1a6956e37970374b8bb5a9ba"; // latest commit in fiat-crypto master as of 05/28/2019

macro_rules! get(($name:expr) => (ok!(env::var($name))));
macro_rules! ok(($expression:expr) => ($expression.unwrap()));

fn run<F>(name: &str, mut configure: F)
where
    F: FnMut(&mut Command) -> &mut Command,
{
    let mut command = Command::new(name);
    let configured = configure(&mut command);
    if !ok!(configured.status()).success() {
        panic!("failed to execute {:?}", configured);
    }
}

fn main() {
    // this folder
    let basedir = PathBuf::from(&get!("CARGO_MANIFEST_DIR"));

    // the fiat-crypto submodule
    let fiat_crypto = basedir.join("src").join("external").join("fiat-crypto");

    // path to our patches
    let patches = basedir.join("patches");

    // cd to the fiat-crypto submodule and reset to the correct version
    assert!(env::set_current_dir(&fiat_crypto).is_ok());
    // Reset
    run("git", |command| command.arg("reset").arg("--hard"));
    // Checkout a particular fiat commit
    run("git", |command| command.arg("checkout").arg(FIAT_HASH));
    // Go to the base directory
    assert!(env::set_current_dir(&basedir).is_ok());

    // patch that fiat file
    run("patch", |command| {
        command
            .arg("-t")
            .arg("-p3")
            .arg("-d")
            .arg(fiat_crypto.to_str().unwrap())
            .arg("-i")
            .arg(patches.join("fiat_library.patch").to_str().unwrap())
    });

    assert!(env::set_current_dir(&basedir).is_ok());

    cc::Build::new()
        .file("src/external/fiat-crypto/curve25519_64.c")
        .include("src/include/")
        .shared_flag(true)
        .static_flag(true)
        .compile("curve25519_64");
}
