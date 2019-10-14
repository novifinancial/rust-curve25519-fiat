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
pub const FIAT_FILE_HASH: [u8; 32] = [
    0xde, 0x8f, 0x2c, 0x6a, 0x1d, 0x20, 0xc2, 0x53, 0x81, 0x85, 0x82, 0xfc, 0x6c, 0x78, 0x91, 0x96,
    0x27, 0xd3, 0xf, 0xc7, 0x5a, 0x27, 0x7b, 0x57, 0x5c, 0xb1, 0x58, 0x5d, 0x6b, 0xd9, 0xa2, 0x2d,
];

use sha2::{Digest, Sha256};
use std::{fs, io};

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
    println!("Dir is: {:?}", basedir);
    // the fiat-crypto submodule
    let fiat_crypto = basedir.join("external").join("fiat-crypto");

    // this ised to do a submodule update, see
    // https://github.com/google/shaderc-rs/issues/15 for why it does not any
    // more
    let src_path = fiat_crypto
        .join("fiat-rust")
        .join("src")
        .join("curve25519_64.rs");
    let cond = if let Ok(mut file) = fs::File::open(src_path) {
        let mut sha256 = Sha256::new();
        io::copy(&mut file, &mut sha256).expect("failed to copy file");
        let hash = sha256.result();
        hash[..] == FIAT_FILE_HASH
    } else {
        false
    };
    // Go to the fiat directory
    if !cond && !fiat_crypto.join(".git").exists() {
        std::fs::remove_dir_all(&fiat_crypto).expect("could not remove fiat-crypto");
        std::fs::create_dir_all(&basedir.join("external"))
            .expect("could not create external subdirectory");
        assert!(env::set_current_dir(&basedir.join("external")).is_ok());

        run("git", |command| {
            command
                .arg("clone")
                .arg("--recurse-submodules")
                .arg("https://github.com/mit-plv/fiat-crypto.git")
                .arg("fiat-crypto")
        })
    }
    assert!(env::set_current_dir(&fiat_crypto).is_ok());
    if !cond {
        // Checkout a particular dalek commit
        run("git", |command| command.arg("checkout").arg(FIAT_HASH));
    }
    let long_file = fiat_crypto.join("coqprime").join("src").join("Coqprime").join("examples").join("prime216656403549020227250327256032933021325435259861468456540459488823774358486649614451547405419273433458932168893949521787.v");
    let diag = format!("could not remove unarchivable file at {:?}", &long_file);
    if long_file.exists() {
        std::fs::remove_file(long_file).expect(&diag[..]);
    };

    // Go to the base directory
    assert!(env::set_current_dir(&basedir).is_ok());

    // copy the curve25519_64 file from fiat to src/
    let origin_file = fiat_crypto
        .join("fiat-rust")
        .join("src")
        .join("curve25519_64.rs");
    let diag = format!(
        "could not copy source file from {:?} to {:?}",
        &origin_file, &src_dir,
    );
    std::fs::copy(origin_file, &src_dir.join("curve25519_64.rs")).expect(&diag[..]);
}
