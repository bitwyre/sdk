mod public;
mod private;

use std::error::Error;
use crate::public::config;

fn main() -> Result<(), Box<dyn Error>> {
    match public::get_server_time() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_asset_pairs("crypto","spot","ID") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_ticker(config::bitwyre_instrument("btc_usdt_spot")) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_trades("2", config::bitwyre_instrument("btc_usdt_spot")) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_depth(config::bitwyre_instrument("btc_usdt_spot"), "5") {
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
    match private::get_account_balance() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_account_statement() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_transaction_histories() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
