extern crate crypto;
extern crate ring;
extern crate hex;

use std::error::Error;
use std::io::Read;
use std::time::{SystemTime, UNIX_EPOCH, Duration};
use std::env;
use reqwest;
use crypto::digest::Digest;
use crypto::sha2::Sha256;
use ring::hmac;
use hex::{encode, decode};
use rustc_serialize::hex::ToHex;
use string_builder::Builder;
use crate::public::config;

trait Formatter {
    fn format(&self, base: &str, endpoint: &str, param: &str) -> String;
}

struct URLBuilder;

impl Formatter for URLBuilder {
    fn format(&self, base: &str, endpoint: &str, param: &str) -> String {
        let mut path = Builder::default();
        path.append(base);
        path.append(endpoint);
        path.append(param);
        path.string().unwrap()
    }
}

pub fn credential(secret_key: &str, api_key: &str) -> (String, String) {
    (secret_key.to_string(), api_key.to_string())
}

pub fn get_nonce() -> u128 {
    let start = SystemTime::now();
    let since_the_epoch = start
        .duration_since(UNIX_EPOCH)
        .expect("Time went backwards");
    let in_nanos = since_the_epoch.as_nanos();
    in_nanos
}

pub fn get_checksum(payload: &str) -> String {
    let mut sha256 = Sha256::new();
    sha256.input_str(payload);
    sha256.result_str()
}

pub fn get_nonce_checksum(nonce: &str, checksum: &str) -> String {
    let temp = [nonce, checksum].concat();
    let mut sha256 = Sha256::new();
    sha256.input_str(&temp);
    sha256.result_str()
}

pub fn get_signature(uri_path: &str, nonce_checksum: &str) -> String {
    let data = [uri_path, nonce_checksum].concat();
    let hex_string = encode(env!("SECRET_KEY"));
    let key_value = decode(&hex_string);
    let s_key = hmac::Key::new(hmac::HMAC_SHA512, &key_value.unwrap());
    let signature = hmac::sign(&s_key, data.as_bytes());
    signature.as_ref().to_hex()
}

pub fn get_account_balance() -> Result<(), Box<dyn Error>> {
    let payload = "\"\\\"\\\"\"";
    let nonce = get_nonce();
    let checksum = get_checksum(&payload);
    let nonce_checksum = get_nonce_checksum(&nonce.to_string(), &checksum);
    let signature = get_signature(config::get_private_api_endpoint(&"ACCOUNT_BALANCE"), &nonce_checksum);
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", ""].concat();
    let client = reqwest::blocking::Client::builder()
        .timeout(Duration::from_secs(config::timeout()))
        .build()?;
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ACCOUNT_BALANCE"),
        &param
    );
    let mut res = client.get(&temp)
        .header("API_Key", api_key)
        .header("API_Sign", signature)
        .send()?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Success");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };
    Ok(())
}