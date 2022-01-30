extern crate crypto;
extern crate ring;
extern crate hex;

use std::error::Error;
use std::io::Read;
use std::time::{SystemTime, UNIX_EPOCH, Duration};
use std::env;
use reqwest::{header, blocking};
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

trait Request {
    fn execute(&self, temp: &str, api_key: &str, signature: &str) -> Result<(), Box<dyn Error>>;
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

struct PrivateAPI;

impl Request for PrivateAPI {
    fn execute(&self, temp: &str, api_key: &str, signature: &str) -> Result<(), Box<dyn Error>> {
        let mut headers = header::HeaderMap::new();
        headers.insert("API-Key", header::HeaderValue::from_str(&api_key).unwrap());
        headers.insert("API-Sign", header::HeaderValue::from_str(&signature).unwrap());
        let client = blocking::Client::builder()
            .default_headers(headers)
            .timeout(Duration::from_secs(config::timeout()))
            .build()?;
        let mut res = client.get(temp).send()?;
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

pub fn sign(secret_key: &str, uri_path: &str, payload: &str) -> (u128, String, String) {
    let nonce = get_nonce();
    let temp = format!("{:?}", payload);
    let temp2 = format!("{:?}",temp);
    let checksum = get_checksum(&temp2);
    let nonce_checksum = get_nonce_checksum(&nonce.to_string(), &checksum);
    let data = [uri_path, &nonce_checksum].concat();
    let hex_string = encode(secret_key.as_bytes());
    let key_value = decode(&hex_string);
    let s_key = hmac::Key::new(hmac::HMAC_SHA512, &key_value.unwrap());
    let signature = hmac::sign(&s_key, data.as_bytes());
    (nonce, checksum, signature.as_ref().to_hex())
}

pub fn get_account_balance() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_BALANCE");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ACCOUNT_BALANCE"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_account_statement() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_STATEMENT");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ACCOUNT_STATEMENT"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_transaction_histories() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"TRANSACTION_HISTORIES");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"TRANSACTION_HISTORIES"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
