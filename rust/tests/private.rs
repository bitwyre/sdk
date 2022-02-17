#[cfg(test)]
mod test {
    use rust_sdk::{
        private,
        public::config
    };
    use serde::{Deserialize, Serialize};
    
    #[derive(Serialize, Deserialize)]
    struct ResultString {
        error: Vec<String>,
    }
    
    #[tokio::test]
    async fn get_account_balance_async_should_work() {
        let data = private::get_account_balance_async().await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_account_statement_async_should_work() {
        let data = private::get_account_statement_async().await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_transaction_histories_async_should_work() {
        let data = private::get_transaction_histories_async().await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_open_orders_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = private::get_open_orders_async(instrument, 0, 0).await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_closed_orders_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = private::get_closed_orders_async(instrument, 0, 0).await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_order_info_async_should_work() {
        let data = private::get_order_info_async("3f128876-a082-4b18-8fd4-abbcc4aa7915").await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn get_trade_history_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = private::get_trade_history_async(instrument, 2, 0, 0).await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn cancelling_open_order_per_instrument_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = private::cancelling_open_order_per_instrument_async(instrument).await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn cancelling_open_order_per_orderids_async_should_work() {
        let data = private::cancelling_open_order_per_orderids_async(
            vec!["5033216a-dad5-4cb6-87d6-0084603be699", "3d19d8d1-c576-4109-8671-5e4115cf6e5e"], vec![-1, -1]
        ).await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
    
    #[tokio::test]
    async fn opening_new_order_async_should_work() {
        let instrument = config::bitwyre_instrument("1");
        let data = private::opening_new_order_async(instrument, 1, Some(35000.to_string()), 2, "0.0001").await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
        
        let data = private::opening_new_order_async(instrument, 1, Some("".to_string()), 1, "0.0001").await;
        assert!(data.is_ok());

        let r: ResultString = serde_json::from_str(
            &data.unwrap()
        ).unwrap();
        assert!(r.error.is_empty());
    }
}