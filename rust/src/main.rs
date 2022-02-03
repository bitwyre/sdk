mod public;
mod private;

use std::error::Error;
use crate::public::config;

fn main() -> Result<(), Box<dyn Error>> {
    let instrument = config::bitwyre_instrument("1");
    match public::get_server_time() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_asset_pairs("crypto","spot","ID") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_ticker(instrument) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_trades("2", instrument) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_depth(instrument, "5") {
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
    match private::get_open_orders(instrument, 0, 0) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_closed_orders(instrument, 0, 0) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_order_info("3f128876-a082-4b18-8fd4-abbcc4aa7915") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_trade_history(instrument, 2, 0, 0) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
