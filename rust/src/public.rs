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

pub async fn get_languages_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"LANGUAGES"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_search_results_async() -> Result<(), Box<dyn Error>> {
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"SEARCH"),
        ""
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_price_index_async(instrument: &str, amount: Option<&i8>, to_time: Option<&i8>, from_time: Option<&i8>, ascending: Option<&bool>) -> Result<(), Box<dyn Error>> {
    let mut param = ["?instrument=", &instrument].concat();
    param = match amount {
        None => param,
        Some(_amount) => [param, "?amount=".to_string(), _amount.to_string()].concat()
    };
    param = match to_time {
        None => param,
        Some(_to_time) => [param, "?to_time=".to_string(), _to_time.to_string()].concat()
    };
    param = match from_time {
        None => param,
        Some(_from_time) => [param, "?from_time=".to_string(), _from_time.to_string()].concat()
    };
    param = match ascending {
        None => param,
        Some(_ascending) => [param, "?ascending=".to_string(), _ascending.to_string()].concat()
    };
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"PRICE_INDEX"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_search_async(country: &str, instrument: Option<&str>) -> Result<(), Box<dyn Error>> {
    let mut param = ["?country=", &country].concat();
    param = match instrument {
        None => param,
        Some(_instrument) => [param, "?instrument=".to_string(), _instrument.to_string()].concat()
    };
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"SEARCH"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}

pub async fn get_matching_engine_order_lag(instrument: Option<&str>) -> Result<(), Box<dyn Error>> {
    let param = match instrument {
        None => "".to_string(),
        Some(_instrument) => ["?instrument=", _instrument].concat()
    };
    let temp = URLBuilder.format (
        config::url_api_bitwyre(),
        config::get_public_api_endpoint(&"ORDER_LAG"),
        &param
    );
    match PublicAPI.execute_async(&temp).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
