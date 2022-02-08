extern crate crypto;
extern crate ring;
extern crate hex;

use std::error::Error;
use std::io::Read;
use std::time::{SystemTime, UNIX_EPOCH, Duration};
use std::env;
use reqwest::{header, blocking, Client};
use crypto::digest::Digest;
use crypto::sha2::Sha256;
use ring::hmac;
use hex::{encode, decode};
use rustc_serialize::hex::ToHex;
use string_builder::Builder;
use crate::public::config;

trait Formatter {
    fn format(&self, base: &str, endpoint: &str, param: &str) -> String;
    fn build_nonce_checksum_payload(&self, uri_path: &str, payload: &str) -> (String, String, String);
}

trait Request {
    fn execute(&self, temp: &str, api_key: &str, signature: &str, flag: &str) -> Result<(), Box<dyn Error>>;
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
    fn build_nonce_checksum_payload(&self, uri_path: &str, payload: &str) -> (String, String, String) {
        let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
        let (nonce, checksum, signature) = sign(&secret_key, uri_path, payload);
        (
            ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat(),
            api_key,
            signature
        )
    }
}

struct PrivateAPI;

impl Request for PrivateAPI {
    fn execute(&self, temp: &str, api_key: &str, signature: &str, flag: &str) -> Result<(), Box<dyn Error>> {
        let mut headers = header::HeaderMap::new();
        headers.insert("API-Key", header::HeaderValue::from_str(&api_key).unwrap());
        headers.insert("API-Sign", header::HeaderValue::from_str(&signature).unwrap());
        let client = blocking::Client::builder()
            .default_headers(headers)
            .timeout(Duration::from_secs(config::timeout()))
            .build()?;
        let mut res;
        if flag == "NewOrder" {
            res = client.post(temp).send()?;
        } else if flag == "CancelOrder" {
            res = client.delete(temp).send()?;
        } else {
            res = client.get(temp).send()?;
        }
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
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
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
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
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
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_open_orders(instrument: &str, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"OPEN_ORDERS");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, &payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"OPEN_ORDERS"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_closed_orders(instrument: &str, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"CLOSED_ORDERS");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, &payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"CLOSED_ORDERS"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_order_info(order_id: &str) -> Result<(), Box<dyn Error>> {
    let payload = "";
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = [config::get_private_api_endpoint(&"ORDER_INFO"), "/", order_id].concat();
    let (nonce, checksum, signature) = sign(&secret_key, &uri_path, payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        &uri_path,
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_trade_history(instrument: &str, count: u8, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"count\":", &count.to_string(), ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"TRADE_HISTORY");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, &payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"TRADE_HISTORY"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn cancelling_open_order_per_instrument(instrument: &str) -> Result<(), Box<dyn Error>> {
    let payload = "";
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = [config::get_private_api_endpoint(&"CANCEL_ORDER"), "/instrument/", instrument].concat();
    let (nonce, checksum, signature) = sign(&secret_key, &uri_path, payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        &uri_path,
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "CancelOrder") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn cancelling_open_order_per_orderids(order_ids: Vec<&str>, qtys: Vec<i32>) -> Result<(), Box<dyn Error>> {
    let temp = format!("{:?}", order_ids);
    let temp2 = format!("{:?}", qtys);
    if order_ids.len() != qtys.len() {
        println!("Specify the same number of orders with quantities to ammend/cancel");
    }
    let payload = ["{\"order_ids\":", &temp, ",\"qtys\":", &temp2, "}"].concat();
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"CANCEL_ORDER");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, &payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"CANCEL_ORDER"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "CancelOrder") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn opening_new_order(
    instrument: &str,
    side: u8,
    mut price: Option<String>,
    ordtype: u8,
    orderqty: &str) -> Result<(), Box<dyn Error>> {
    if ordtype == 1 {
        price = Some("0".to_string());
    }
    if ordtype == 2 && price.is_none() {
        println!("Limit order price cannot be null");
    }
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"side\":", &side.to_string(),
        ",\"price\":", "\"", &price.unwrap(), "\"", ",\"ordtype\":", &ordtype.to_string(), ",\"orderqty\":", "\"", &orderqty, "\"", "}"].concat();
    let (secret_key, api_key) = credential(&env!("SECRET_KEY"), &env!("API_KEY"));
    let uri_path = config::get_private_api_endpoint(&"ORDER");
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, &payload);
    let param = ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ORDER"),
        &param
    );
    match PrivateAPI.execute(&temp, &api_key, &signature, "NewOrder") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

use async_trait::async_trait;

#[async_trait]
trait RequestAsync {
    async fn execute_async(&self, temp: &str, api_key: &str, signature: &str, flag: &str) -> Result<(), Box<dyn Error>>;
}

#[async_trait]
impl RequestAsync for PrivateAPI {
    async fn execute_async(&self, temp: &str, api_key: &str, signature: &str, flag: &str) -> Result<(), Box<dyn Error>> {
        let mut headers = header::HeaderMap::new();
        headers.insert("API-Key", header::HeaderValue::from_str(&api_key).unwrap());
        headers.insert("API-Sign", header::HeaderValue::from_str(&signature).unwrap());
        
        let client = Client::builder()
            .default_headers(headers)
            .timeout(Duration::from_secs(config::timeout()))
            .build()?;

        let res;
        if flag == "NewOrder" {
            res = client.post(temp).send().await?;
        } else if flag == "CancelOrder" {
            res = client.delete(temp).send().await?;
        } else {
            res = client.get(temp).send().await?;
        }

        match res.status() {
            reqwest::StatusCode::OK => {
                println!("Status: {} -> {}", res.status(), "Success");
                println!("{}", res.text().await?);
            },
            _ => {
                panic!("{} -> {}", res.status(), "Error, please check again your request");
            },
        };
        Ok(())
    }
}

pub async fn get_account_balance_async() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_BALANCE");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ACCOUNT_BALANCE"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_account_statement_async() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_STATEMENT");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ACCOUNT_STATEMENT"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_transaction_histories_async() -> Result<(), Box<dyn Error>> {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"TRANSACTION_HISTORIES");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"TRANSACTION_HISTORIES"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_open_orders_async(instrument: &str, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let uri_path = config::get_private_api_endpoint(&"OPEN_ORDERS");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"OPEN_ORDERS"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_closed_orders_async(instrument: &str, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let uri_path = config::get_private_api_endpoint(&"CLOSED_ORDERS");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"CLOSED_ORDERS"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_order_info_async(order_id: &str) -> Result<(), Box<dyn Error>> {
    let payload = "";
    let uri_path = [config::get_private_api_endpoint(&"ORDER_INFO"), "/", order_id].concat();
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        &uri_path,
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_trade_history_async(instrument: &str, count: u8, from_time: u128, to_time: u128) -> Result<(), Box<dyn Error>> {
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"count\":", &count.to_string(), ",\"from_time\":", &from_time.to_string(), ",\"to_time\":", &to_time.to_string(), "}"].concat();
    let uri_path = config::get_private_api_endpoint(&"TRADE_HISTORY");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"TRADE_HISTORY"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn cancelling_open_order_per_instrument_async(instrument: &str) -> Result<(), Box<dyn Error>> {
    let payload = "";
    let uri_path = [config::get_private_api_endpoint(&"CANCEL_ORDER"), "/instrument/", instrument].concat();
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        &uri_path,
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "CancelOrder").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn cancelling_open_order_per_orderids_async(order_ids: Vec<&str>, qtys: Vec<i32>) -> Result<(), Box<dyn Error>> {
    let temp = format!("{:?}", order_ids);
    let temp2 = format!("{:?}", qtys);
    if order_ids.len() != qtys.len() {
        println!("Specify the same number of orders with quantities to ammend/cancel");
    }
    let payload = ["{\"order_ids\":", &temp, ",\"qtys\":", &temp2, "}"].concat();
    let uri_path = config::get_private_api_endpoint(&"CANCEL_ORDER");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"CANCEL_ORDER"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "CancelOrder").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn opening_new_order_async(
    instrument: &str,
    side: u8,
    mut price: Option<String>,
    ordtype: u8,
    orderqty: &str
) -> Result<(), Box<dyn Error>> {
    if ordtype == 1 {
        price = Some("0".to_string());
    }
    if ordtype == 2 && price.is_none() {
        println!("Limit order price cannot be null");
    }
    let payload = ["{\"instrument\":", "\"", &instrument, "\"", ",\"side\":", &side.to_string(),
        ",\"price\":", "\"", &price.unwrap(), "\"", ",\"ordtype\":", &ordtype.to_string(), ",\"orderqty\":", "\"", &orderqty, "\"", "}"].concat();
    let uri_path = config::get_private_api_endpoint(&"ORDER");
    let (param, api_key, signature) = URLBuilder.build_nonce_checksum_payload(&uri_path, &payload);
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_private_api_endpoint(&"ORDER"),
        &param
    );
    match PrivateAPI.execute_async(&temp, &api_key, &signature, "NewOrder").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
