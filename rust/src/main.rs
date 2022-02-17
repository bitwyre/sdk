mod public;
mod private;
mod tests;

use std::error::Error;
use crate::public::config;

async fn async_main(
    product: &str, 
    market: &str, 
    country: &str, 
    order_id: &str, 
    order_ids: Vec<&str>, 
    qtys: Vec<i32>, 
    price: i32, 
    orderqty: &str
) {
    let instrument = config::bitwyre_instrument("1");
    let instrument_contract = config::bitwyre_instrument("7");

    println!("{:?}", public::get_server_time_async().await);
    println!("{:?}", public::get_markets_async().await);
    println!("{:?}", public::get_products_async().await);
    println!("{:?}", public::get_assets_async().await);
    println!("{:?}", public::get_crypto_assets_async().await);
    println!("{:?}", public::get_fiat_assets_async().await);
    println!("{:?}", public::get_asset_pairs_async(product, market, country).await);
    println!("{:?}", public::get_ticker_async(instrument).await);
    println!("{:?}", public::get_trades_async("2", instrument).await);
    println!("{:?}", public::get_depth_async(instrument, "5").await);
    println!("{:?}", public::get_contract_async(instrument_contract).await);
    println!("{:?}", public::get_insider_profiles_async(None).await);
    println!("{:?}", public::get_insider_trades_async(None).await);
    println!("{:?}", public::get_announcements_async().await);
    println!("{:?}", public::get_order_types_async().await);
    println!("{:?}", public::get_languages_async().await);
    println!("{:?}", public::get_search_results_async().await);
    println!("{:?}", public::get_price_index_async(instrument, None, None, None, None).await);
    println!("{:?}", public::get_search_async(country, None).await);
    println!("{:?}", public::get_matching_engine_order_lag_async(None).await);
    println!("{:?}", public::get_matching_engine_throughput_async(None).await);
    println!("{:?}", private::get_account_balance_async().await);
    println!("{:?}", private::get_account_statement_async().await);
    println!("{:?}", private::get_transaction_histories_async().await);
    println!("{:?}", private::get_open_orders_async(instrument, 0, 0).await);
    println!("{:?}", private::get_closed_orders_async(instrument, 0, 0).await);
    println!("{:?}", private::get_order_info_async(order_id).await);
    println!("{:?}", private::get_trade_history_async(instrument, 2, 0, 0).await);
    println!("{:?}", private::cancelling_open_order_per_instrument_async(instrument).await);
    println!("{:?}", private::cancelling_open_order_per_orderids_async(order_ids, qtys).await);
    println!("{:?}", private::opening_new_order_async(instrument, 1, Some(price.to_string()), 2, orderqty).await);
    println!("{:?}", private::opening_new_order_async(instrument, 1, Some(price.to_string()), 1, orderqty).await);
}

fn main() -> Result<(), Box<dyn Error>> {
    let instrument = config::bitwyre_instrument("1");
    tokio::runtime::Runtime::new()
        .unwrap()
        .block_on(async_main(
            "crypto",
            "spot",
            "ID",
            "3f128876-a082-4b18-8fd4-abbcc4aa7915",
            vec!["5033216a-dad5-4cb6-87d6-0084603be699", "3d19d8d1-c576-4109-8671-5e4115cf6e5e"], 
            vec![-1, -1],
            35000,
            "0.0001"
        ));

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
    match private::cancelling_open_order_per_instrument(instrument) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::cancelling_open_order_per_orderids(vec!["5033216a-dad5-4cb6-87d6-0084603be699", "3d19d8d1-c576-4109-8671-5e4115cf6e5e"], vec![-1, -1]) {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::opening_new_order(instrument, 1, Some(35000.to_string()), 2, "0.0001") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::opening_new_order(instrument, 1, Some("".to_string()), 1, "0.0001") {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    Ok(())
}
