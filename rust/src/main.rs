mod public;
mod private;

use std::error::Error;

fn main() -> Result<(), Box<dyn Error>> {
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
    match private::get_account_balance() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
