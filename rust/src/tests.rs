#[cfg(test)]
use crate::{
    public,
    public::config,
    private,
    private::{credential, sign}
};

#[cfg(test)]
use mockito::mock;
  
#[tokio::test]
async fn get_server_time_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"SERVERTIME"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_server_time_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_server_time_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"SERVERTIME"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_server_time_async().await;
}
  
#[tokio::test]
async fn get_markets_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"MARKETS"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_markets_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_markets_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"MARKETS"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_markets_async().await;
}
  
#[tokio::test]
async fn get_products_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"PRODUCTS"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_products_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_products_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"PRODUCTS"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_products_async().await;
}
  
#[tokio::test]
async fn get_assets_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_assets_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_assets_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_assets_async().await;
}
  
#[tokio::test]
async fn get_crypto_assets_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS_CRYPTO"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_crypto_assets_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_crypto_assets_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS_CRYPTO"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_crypto_assets_async().await;
}
  
#[tokio::test]
async fn get_fiat_assets_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS_FIAT"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_fiat_assets_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_fiat_assets_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ASSETS_FIAT"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_fiat_assets_async().await;
}
  
#[tokio::test]
async fn get_asset_pairs_async_should_work() {
    let market = "market";
    let product = "product";
    let country = "country";

    let url_string = [
        config::get_public_api_endpoint(&"INSTRUMENT"),
        "?market=", &market, "&product=", &product, "&country=", &country
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_asset_pairs_async(
        market,
        product,
        country
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_asset_pairs_async_should_panic() {
    let market = "market";
    let product = "product";
    let country = "country";

    let url_string = [
        config::get_public_api_endpoint(&"INSTRUMENT"),
        "?market=", &market, "&product=", &product, "&country=", &country
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_asset_pairs_async(
        market,
        product,
        country
    ).await;
}
  
#[tokio::test]
async fn get_trades_async_should_work() {
    let trade_num = "trade_num";
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"TRADES"),
        "?trade_num=", &trade_num, "&instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_trades_async(
        trade_num,
        instrument
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_trades_async_should_panic() {
    let trade_num = "trade_num";
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"TRADES"),
        "?trade_num=", &trade_num, "&instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_trades_async(
        trade_num,
        instrument
    ).await;
}
  
#[tokio::test]
async fn get_depth_async_should_work() {
    let instrument = "instrument";
    let depth_num = "depth_num";

    let url_string = [
        config::get_public_api_endpoint(&"DEPTH"),
        "?instrument=", &instrument, "&depth_num=", &depth_num
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_depth_async(
        instrument,
        depth_num
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_depth_async_should_panic() {
    let instrument = "instrument";
    let depth_num = "depth_num";

    let url_string = [
        config::get_public_api_endpoint(&"DEPTH"),
        "?instrument=", &instrument, "&depth_num=", &depth_num
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_depth_async(
        instrument,
        depth_num
    ).await;
}
  
#[tokio::test]
async fn get_ticker_async_should_work() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"TICKER"),
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_ticker_async(
        instrument
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_ticker_async_should_panic() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"TICKER"),
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_ticker_async(
        instrument
    ).await;
}
  
#[tokio::test]
async fn get_contract_async_should_work() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"CONTRACT"),
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_contract_async(
        instrument
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_contract_async_should_panic() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"CONTRACT"),
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_contract_async(
        instrument
    ).await;
}
  
#[tokio::test]
async fn get_insider_profiles_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_PROFILES")
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_insider_profiles_async(None).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_insider_profiles_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_PROFILES")
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_insider_profiles_async(None).await;
}
  
#[tokio::test]
async fn get_insider_profiles_async_with_optional_parameters_should_work() {
    let username = "username";

    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_PROFILES"),
        "?username=", &username
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_insider_profiles_async(
        Some(username)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_insider_profiles_async_with_optional_parameters_should_panic() {
    let username = "username";

    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_PROFILES"),
        "?username=", &username
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_insider_profiles_async(
        Some(username)
    ).await;
}
  
#[tokio::test]
async fn get_insider_trades_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_TRADES")
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_insider_trades_async(None).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_insider_trades_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_TRADES")
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_insider_trades_async(None).await;
}
  
#[tokio::test]
async fn get_insider_trades_async_with_optional_parameters_should_work() {
    let username = "username";

    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_TRADES"),
        "?username=", &username
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_insider_trades_async(
        Some(username)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_insider_trades_async_with_optional_parameters_should_panic() {
    let username = "username";

    let url_string = [
        config::get_public_api_endpoint(&"INSIDER_TRADES"),
        "?username=", &username
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_insider_trades_async(
        Some(username)
    ).await;
}
  
#[tokio::test]
async fn get_announcements_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ANNOUNCEMENTS"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_announcements_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_announcements_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ANNOUNCEMENTS"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_announcements_async().await;
}
  
#[tokio::test]
async fn get_order_types_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ORDER_TYPES"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_order_types_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_order_types_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ORDER_TYPES"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_order_types_async().await;
}
  
#[tokio::test]
async fn get_languages_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"LANGUAGES"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_languages_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_languages_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"LANGUAGES"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_languages_async().await;
}
  
#[tokio::test]
async fn get_search_results_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_search_results_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_search_results_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_search_results_async().await;
}
  
#[tokio::test]
async fn get_price_index_async_should_work() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"PRICE_INDEX"),
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_price_index_async(
        instrument,
        None,
        None,
        None,
        None
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_price_index_async_should_panic() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"PRICE_INDEX"),
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_price_index_async(
        instrument,
        None,
        None,
        None,
        None
    ).await;
}
  
#[tokio::test]
async fn get_price_index_async_with_optional_parameters_should_work() {
    let instrument = "instrument";
    let amount = 0;
    let to_time = 0;
    let from_time = 0;
    let ascending = true;

    let url_string = [
        config::get_public_api_endpoint(&"PRICE_INDEX"),
        "?instrument=", &instrument,
        "?amount=", amount.to_string().as_str(),
        "?to_time=", to_time.to_string().as_str(),
        "?from_time=", from_time.to_string().as_str(),
        "?ascending=", ascending.to_string().as_str(),
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_price_index_async(
        instrument,
        Some(&amount),
        Some(&to_time),
        Some(&from_time),
        Some(&ascending)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_price_index_async_with_optional_parameters_should_panic() {
    let instrument = "instrument";
    let amount = 0;
    let to_time = 0;
    let from_time = 0;
    let ascending = true;

    let url_string = [
        config::get_public_api_endpoint(&"PRICE_INDEX"),
        "?instrument=", &instrument,
        "?amount=", amount.to_string().as_str(),
        "?to_time=", to_time.to_string().as_str(),
        "?from_time=", from_time.to_string().as_str(),
        "?ascending=", ascending.to_string().as_str(),
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_price_index_async(
        instrument,
        Some(&amount),
        Some(&to_time),
        Some(&from_time),
        Some(&ascending)
    ).await;
}
  
#[tokio::test]
async fn get_search_async_should_work() {
    let country = "country";

    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
        "?country=", &country
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_search_async(
        country,
        None
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_search_async_should_panic() {
    let country = "country";

    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
        "?country=", &country
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_search_async(
        country,
        None
    ).await;
}
  
#[tokio::test]
async fn get_search_async_with_optional_parameters_should_work() {
    let country = "country";
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
        "?country=", &country,
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_search_async(
        country,
        Some(instrument)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_search_async_with_optional_parameters_should_panic() {
    let country = "country";
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"SEARCH"),
        "?country=", &country,
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_search_async(
        country,
        Some(instrument)
    ).await;
}
  
#[tokio::test]
async fn get_matching_engine_order_lag_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"ORDER_LAG")
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_matching_engine_order_lag_async(None).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_matching_engine_order_lag_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"ORDER_LAG")
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_matching_engine_order_lag_async(None).await;
}
  
#[tokio::test]
async fn get_matching_engine_order_lag_async_with_optional_parameters_should_work() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"ORDER_LAG"),
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_matching_engine_order_lag_async(
        Some(instrument)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_matching_engine_order_lag_async_with_optional_parameters_should_panic() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"ORDER_LAG"),
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_matching_engine_order_lag_async(
        Some(instrument)
    ).await;
}
  
#[tokio::test]
async fn get_matching_engine_throughput_async_should_work() {
    let url_string = [
        config::get_public_api_endpoint(&"THROUGHPUT")
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_matching_engine_throughput_async(None).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_matching_engine_throughput_async_should_panic() {
    let url_string = [
        config::get_public_api_endpoint(&"THROUGHPUT")
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_matching_engine_throughput_async(None).await;
}
  
#[tokio::test]
async fn get_matching_engine_throughput_async_with_optional_parameters_should_work() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"THROUGHPUT"),
        "?instrument=", &instrument
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = public::get_matching_engine_throughput_async(
        Some(instrument)
    ).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_matching_engine_throughput_async_with_optional_parameters_should_panic() {
    let instrument = "instrument";

    let url_string = [
        config::get_public_api_endpoint(&"THROUGHPUT"),
        "?instrument=", &instrument
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = public::get_matching_engine_throughput_async(
        Some(instrument)
    ).await;
}

#[cfg(test)]
use std::env;

#[test]
fn is_env_set() {
    let secret_env = match env::var("SECRET_KEY") {
        Ok(_) => true,
        _ => false
    };
    let api_env = match env::var("API_KEY") {
        Ok(_) => true,
        _ => false
    };
    assert!(secret_env);
    assert!(api_env);
}

#[cfg(test)]
fn build_nonce_checksum_payload(uri_path: &str, payload: &str) -> (String, String, String) {
    let (secret_key, api_key) = credential(&option_env!("SECRET_KEY").unwrap(), &option_env!("API_KEY").unwrap());
    let (nonce, checksum, signature) = sign(&secret_key, uri_path, payload);
    (
        ["?nonce=", &nonce.to_string(), "&checksum=", &checksum, "&payload=", &payload].concat(),
        api_key,
        signature
    )
}

#[tokio::test]
async fn get_account_balance_async_should_work() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_BALANCE");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    println!("{}", url_string);
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = private::get_account_balance_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_account_balance_async_should_panic() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_BALANCE");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = private::get_account_balance_async().await;
}

#[tokio::test]
async fn get_account_statement_async_should_work() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_STATEMENT");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = private::get_account_statement_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_account_statement_async_should_panic() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ACCOUNT_STATEMENT");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = private::get_account_statement_async().await;
}

#[tokio::test]
async fn get_transaction_histories_async_should_work() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"TRANSACTION_HISTORIES");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = private::get_transaction_histories_async().await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_transaction_histories_async_should_panic() {
    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"TRANSACTION_HISTORIES");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        param.as_str()
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = private::get_transaction_histories_async().await;
}

#[tokio::test]
async fn get_order_info_async_should_work() {
    let order_id = "order_id";
    let order_id_path = ["/", &order_id].concat();

    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ORDER_INFO");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        order_id_path.as_str(),
        param.as_str()
    ].concat();
    
    let mock = mock("GET", url_string.as_str())
        .create();
    let _ = private::get_order_info_async(order_id).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn get_order_info_async_should_panic() {
    let order_id = "order_id";
    let order_id_path = ["/", &order_id].concat();

    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"ORDER_INFO");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        order_id_path.as_str(),
        param.as_str()
    ].concat();
    
    let _ = mock("GET", url_string.as_str())
        .with_status(500)
        .create();
    let _ = private::get_order_info_async(order_id).await;
}

#[tokio::test]
async fn cancelling_open_order_per_instrument_async_should_work() {
    let instrument = "instrument";
    let instrument_path = ["/instrument/", &instrument].concat();

    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"CANCEL_ORDER");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        instrument_path.as_str(),
        param.as_str()
    ].concat();
    
    let mock = mock("DELETE", url_string.as_str())
        .create();
    let _ = private::cancelling_open_order_per_instrument_async(instrument).await;
    assert!(mock.matched());
}
  
#[tokio::test]
#[should_panic]
async fn cancelling_open_order_per_instrument_async_should_panic() {
    let instrument = "instrument";
    let instrument_path = ["/instrument/", &instrument].concat();

    let payload = "";
    let uri_path = config::get_private_api_endpoint(&"CANCEL_ORDER");
    let (param, _, _) = build_nonce_checksum_payload(&uri_path, &payload);

    let url_string = [
        &uri_path,
        instrument_path.as_str(),
        param.as_str()
    ].concat();
    
    let _ = mock("DELETE", url_string.as_str())
        .with_status(500)
        .create();
    let _ = private::cancelling_open_order_per_instrument_async(instrument).await;
}
