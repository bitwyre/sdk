pub mod config;

use std::error::Error;
use std::io::Read;
use string_builder::Builder;

trait Formatter {
    fn format(&self, base: &str, endpoint: &str, param: &str) -> String;
}

trait Request {
    fn execute(&self, temp: &str) -> Result<(), Box<dyn Error>>;
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

struct PublicAPI;

impl Request for PublicAPI {
    fn execute(&self, temp: &str) -> Result<(), Box<dyn Error>> {
        let mut res = reqwest::blocking::get(temp)?;
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

pub fn get_server_time() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"SERVERTIME"),
        ""
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_asset_pairs(market: &str, product: &str, country: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?market=", &market, "&product=", &product, "&country=", &country].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"INSTRUMENT"),
        &param
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_ticker(instrument: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?instrument=", &instrument].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"TICKER"),
        &param
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_trades(trade_num: &str, instrument: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?trade_num=", &trade_num, "&instrument=", &instrument].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"TRADES"),
        &param
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_depth(instrument: &str, depth_num: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?instrument=", &instrument, "&depth_num=", &depth_num].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"DEPTH"),
        &param
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_assets() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ASSETS"),
        ""
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_markets() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"MARKETS"),
        ""
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_products() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"PRODUCTS"),
        ""
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub fn get_announcements() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ANNOUNCEMENTS"),
        ""
    );
    match PublicAPI.execute(&temp) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

use async_trait::async_trait;

#[async_trait]
trait RequestAsync {
    async fn execute_async(&self, temp: &str) -> Result<(), Box<dyn Error>>;
}

#[async_trait]
impl RequestAsync for PublicAPI {
    async fn execute_async(&self, temp: &str) -> Result<(), Box<dyn Error>> {
        let res = reqwest::get(temp).await?;
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

pub async fn get_server_time_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"SERVERTIME"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_markets_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"MARKETS"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_products_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"PRODUCTS"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_assets_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ASSETS"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_crypto_assets_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ASSETS_CRYPTO"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_fiat_assets_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ASSETS_FIAT"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_asset_pairs_async(market: &str, product: &str, country: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?market=", &market, "&product=", &product, "&country=", &country].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"INSTRUMENT"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_trades_async(trade_num: &str, instrument: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?trade_num=", &trade_num, "&instrument=", &instrument].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"TRADES"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_depth_async(instrument: &str, depth_num: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?instrument=", &instrument, "&depth_num=", &depth_num].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"DEPTH"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_ticker_async(instrument: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?instrument=", &instrument].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"TICKER"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_contract_async(instrument: &str) -> Result<(), Box<dyn Error>> {
    let param = ["?instrument=", &instrument].concat();
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"CONTRACT"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_insider_profiles_async(username: Option<&str>) -> Result<(), Box<dyn Error>> {
    let param = match username {
        None => "".to_string(),
        Some(_username) => ["?username=", &_username].concat()
    };
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"INSIDER_PROFILES"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_insider_trades_async(username: Option<&str>) -> Result<(), Box<dyn Error>> {
    let param = match username {
        None => "".to_string(),
        Some(_username) => ["?username=", &_username].concat()
    };
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"INSIDER_TRADES"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_announcements_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ANNOUNCEMENTS"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_order_types_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ORDER_TYPES"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

