#[cfg(test)]
use mockito;

pub fn url_api_bitwyre() -> String {
    #[cfg(test)]
    let url = mockito::server_url();

    #[cfg(not(test))]
    let url = "https://api.bitwyre.com".to_string();

    return url;
}

pub fn timeout() -> u64 {
    return 5;
}
pub fn get_public_api_endpoint(key: &str) -> &str {
    match key {
        "SERVERTIME" => "/public/time",
        "TRADES" => "/public/trades",
        "TICKER" => "/public/ticker",
        "INSTRUMENT" => "/public/pairs",
        "DEPTH" => "/public/depth",
        "ANNOUNCEMENTS" => "/public/announcements",
        "PRODUCTS" => "/public/products",
        "MARKETS" => "/public/markets",
        "ASSETS" => "/public/assets",
        "ASSETS_CRYPTO" => "/public/assets/crypto",
        "ASSETS_FIAT" => "/public/assets/fiat",
        "CONTRACT" => "/public/contract",
        "INSIDER_PROFILES" => "/public/insider",
        "INSIDER_TRADES" => "/public/insider/trades",
        "ORDER_TYPES" => "/public/ordertypes",
        "LANGUAGES" => "/public/languages",
        "SEARCH" => "/public/search",
        "PRICE_INDEX" => "/public/index",
        "ORDER_LAG" => "/public/orderlag",
        "THROUGHPUT" => "/public/throughput",
        _ => ""
    }
}
pub fn get_private_api_endpoint(key: &str) -> &str {
    match key {
        "ACCOUNT_BALANCE" => "/private/account/spotbalance",
        "ACCOUNT_STATEMENT" => "/private/account/statement",
        "TRANSACTION_HISTORIES" => "/private/account/transactions",
        "ORDER" => "/private/orders",
        "CANCEL_ORDER" => "/private/orders/cancel",
        "OPEN_ORDERS" => "/private/orders/open",
        "CLOSED_ORDERS" => "/private/orders/closed",
        "ORDER_INFO" => "/private/orders/info",
        "TRADE_HISTORY" => "/private/trades",
        _ => ""
    }
}
pub fn bitwyre_instrument(key: &str) -> &str {
    match key {
        "1" => "btc_usdt_spot",
        "2" => "eth_usdt_spot",
        "3" => "usdt_idr_spot",
        "4" => "usdc_idr_spot",
        "5" => "usdc_usd_spot",
        "6" => "usdt_usd_spot",
        "7" => "btcusdtx_usdt_200607F1000000",
        _ => ""
    }
}