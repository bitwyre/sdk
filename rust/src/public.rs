pub mod config;

use std::error::Error;
use std::io::Read;
use string_builder::Builder;

pub fn get_server_time() -> Result<(), Box<dyn Error>> {
    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"SERVERTIME"));

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved server time");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_asset_pairs(market: &str, product: &str, country: &str) -> Result<(), Box<dyn Error>> {
    let params = ["?market=", &market, "&product=", &product, "&country=", &country].concat();

    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"INSTRUMENT"));
    url_builder.append(params);

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved instruments");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_ticker(instrument: &str) -> Result<(), Box<dyn Error>> {
    let params = ["?instrument=", &instrument].concat();

    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"TICKER"));
    url_builder.append(params);

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved tickers");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_trades(trade_num: &str, instrument: &str) -> Result<(), Box<dyn Error>> {
    let params = ["?trade_num=", &trade_num, "&instrument=", &instrument].concat();

    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"TRADES"));
    url_builder.append(params);

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved trades");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_depth(instrument: &str, depth_num: &str) -> Result<(), Box<dyn Error>> {
    let params = ["?instrument=", &instrument, "&depth_num=", &depth_num].concat();

    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"DEPTH"));
    url_builder.append(params);

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved depth");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_assets() -> Result<(), Box<dyn Error>> {
    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"ASSETS"));

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved assets");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_markets() -> Result<(), Box<dyn Error>> {
    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"MARKETS"));

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved markets");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_products() -> Result<(), Box<dyn Error>> {
    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"PRODUCTS"));

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved products");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
pub fn get_announcements() -> Result<(), Box<dyn Error>> {
    let mut url_builder = Builder::default();
    url_builder.append(config::url_api_bitwyre());
    url_builder.append(config::get_public_api_endpoint(&"ANNOUNCEMENTS"));

    let mut res = reqwest::blocking::get(url_builder.string().unwrap())?;
    let mut body = String::new();
    res.read_to_string(&mut body)?;
    match res.status() {
        reqwest::StatusCode::OK => {
            println!("Status: {} -> {}", res.status(), "Successfully retrieved announcements");
            println!("{}", body);
        },
        _ => {
            panic!("{} -> {}", res.status(), "Error, please check again your request");
        },
    };

    Ok(())
}
