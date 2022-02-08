mod public;
mod private;

use std::error::Error;
use crate::public::config;

async fn async_main() {
    let instrument = config::bitwyre_instrument("1");
    let instrument_contract = config::bitwyre_instrument("7");

    match public::get_server_time_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_markets_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_products_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_assets_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_crypto_assets_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_fiat_assets_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_asset_pairs_async("crypto","spot","ID").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_ticker_async(instrument).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_trades_async("2", instrument).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_depth_async(instrument, "5").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_contract_async(instrument_contract).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_insider_profiles_async(None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_insider_trades_async(None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_announcements_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_order_types_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_languages_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_search_results_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_price_index_async(instrument, None, None, None, None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_search_async("ID", None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_matching_engine_order_lag(None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match public::get_matching_engine_throughput(None).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_account_balance_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_account_statement_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_transaction_histories_async().await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_open_orders_async(instrument, 0, 0).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_closed_orders_async(instrument, 0, 0).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_order_info_async("3f128876-a082-4b18-8fd4-abbcc4aa7915").await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::get_trade_history_async(instrument, 2, 0, 0).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::cancelling_open_order_per_instrument_async(instrument).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
    match private::cancelling_open_order_per_orderids_async(vec!["5033216a-dad5-4cb6-87d6-0084603be699", "3d19d8d1-c576-4109-8671-5e4115cf6e5e"], vec![-1, -1]).await {
        Err(e) => println!("{:?}", e),
        _ => ()
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let instrument = config::bitwyre_instrument("1");
    tokio::runtime::Runtime::new()
        .unwrap()
        .block_on(async_main());

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
