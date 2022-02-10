#[cfg(test)]
use rust_sdk::public;
  
#[tokio::test]
async fn get_server_time_async_should_work() {
    let _ = public::get_server_time_async().await;
}