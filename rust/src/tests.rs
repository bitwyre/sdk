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