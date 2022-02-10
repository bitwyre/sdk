#[cfg(test)]
mod test {
    use rust_sdk::{
        public,
        public::config
    };
    
    #[tokio::test]
    async fn get_server_time_async_should_work() {
        let data = public::get_server_time_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_markets_async_should_work() {
        let data = public::get_markets_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_products_async_should_work() {
        let data = public::get_products_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_assets_async_should_work() {
        let data = public::get_assets_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_crypto_assets_async_should_work() {
        let data = public::get_crypto_assets_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_fiat_assets_async_should_work() {
        let data = public::get_fiat_assets_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_asset_pairs_async_should_work() {
        let data = public::get_asset_pairs_async("crypto","spot","ID").await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_ticker_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = public::get_ticker_async(instrument).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_trades_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = public::get_trades_async("2", instrument).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_depth_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = public::get_depth_async(instrument, "5").await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_contract_async_should_work() {
        let instrument_contract = config::bitwyre_instrument("7");
        let data = public::get_contract_async(instrument_contract).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_insider_profiles_async_should_work() {
        let data = public::get_insider_profiles_async(None).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_insider_trades_async_should_work() {
        let data = public::get_insider_trades_async(None).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_announcements_async_should_work() {
        let data = public::get_announcements_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_order_types_async_should_work() {
        let data = public::get_order_types_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_languages_async_should_work() {
        let data = public::get_languages_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_search_results_async_should_work() {
        let data = public::get_search_results_async().await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_price_index_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = public::get_price_index_async(instrument, None, None, None, None).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_search_async_should_work() {
        let data = public::get_search_async("ID", None).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_matching_engine_order_lag_async_should_work() {
        let data = public::get_matching_engine_order_lag_async(None).await;
        assert!(data.is_ok());
    }
    
    #[tokio::test]
    async fn get_matching_engine_throughput_async_should_work() {
        let data = public::get_matching_engine_throughput_async(None).await;
        assert!(data.is_ok());
    }
}