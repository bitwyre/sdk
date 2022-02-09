#[cfg(test)]
use crate::{
    public,
    public::config
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