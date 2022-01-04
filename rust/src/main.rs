mod public;

use std::error::Error;
//use public::config;

fn main() -> Result<(), Box<dyn Error>> {
    /*
    println!("{:?}", config::get_public_api_endpoint(&"SERVERTIME"));
    println!("{:?}", config::get_public_api_endpoint(&"TRADES"));
    println!("{:?}", config::get_private_api_endpoint(&"ACCOUNT_BALANCE"));
    println!("{:?}", config::get_private_api_endpoint(&"ORDER"));
    println!("{:?}", config::url_api_bitwyre());
    println!("{:?}", config::timeout());
    */
    //public::get_server_time().map_err(|err| println!("{:?}", err)).ok();
    match public::get_server_time() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_asset_pairs("crypto","spot","ID") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_ticker("btc_usdt_spot") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_trades("2", "btc_usdt_spot") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_depth("btc_usdt_spot", "5") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_assets() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_markets() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_products() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_announcements() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
