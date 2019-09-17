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

macro_rules! get(($name:expr) => (ok!(env::var($name))));
macro_rules! ok(($expression:expr) => ($expression.unwrap()));

pub const FIAT_REPO: &str = "https://github.com/mit-plv/fiat-crypto.git";
pub const FIAT_HASH: &str = "c96f983228d08c74254004b0bc101d3f6ff8b051";

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
    let src_dir = basedir.join("src");
    // println!("Dir is: {:?}", basedir);
    // the fiat-crypto submodule
    let fiat_crypto = basedir.join("src").join("external").join("fiat-crypto");

    // get some data
    run("git", |command| {
        command.arg("submodule").arg("update").arg("--init")
    });
    // Go to the fiat directory
    assert!(env::set_current_dir(&fiat_crypto).is_ok());
    // Checkout a particular dalek commit
    run("git", |command| command.arg("checkout").arg(FIAT_HASH));
    // Go to the base directory
    assert!(env::set_current_dir(&basedir).is_ok());

    // move the curve25519_64 file from fiat to src/
    run("cp", |command| {
        command
            .arg(fiat_crypto.join("fiat-rust").join("src").join("curve25519_64.rs"))
            .arg(&src_dir)
    });
}
