mod config;

fn main() {
    println!("{}", config::get_public_api_endpoint(&"SERVERTIME"));
    println!("{:?}", config::get_public_api_endpoint(&"TRADES"));
    println!("{:?}", config::get_private_api_endpoint(&"ACCOUNT_BALANCE"));
    println!("{:?}", config::get_private_api_endpoint(&"ORDER"));
    println!("{:?}", config::url_api_bitwyre());
    println!("{:?}", config::timeout());
}
