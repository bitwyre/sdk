import com.bitwyre.scala_sdk.{PrivateAPI, PublicAPI}

object Demo extends App {
    /*
    val public = new PublicAPI()
    public.get_server_time()
    public.get_asset_pairs("crypto","spot","US")
    public.get_ticker("btc_idr_spot")
    public.get_trades(2, "btc_usd_spot")
    public.get_depth("btc_usd_spot", 20)
    public.get_assets()
    public.get_markets()
    public.get_products()
    public.get_announcements()
    */
    val p = new PrivateAPI(System.getenv("SECRET_KEY"), System.getenv("API_KEY"))
    //p.get_account_balance()
    //p.get_account_statement()
    //p.get_transaction_histories()
    //p.get_open_orders("btc_usdt_spot", 0, 0);
    //p.get_closed_orders("btc_usdt_spot", 0, 0);
    //p.get_trade_history("btc_usdt_spot", 2, 0, 0);
    //p.get_order_info("d16489da-6899-4200-8ed1-4ff8cfb423e0");
    //p.opening_new_order("btc_usdt_spot", 2, "69000", 2, "0.00001");
    //p.cancelling_open_order_per_instrument("btc_usdt_spot");
    p.cancelling_open_order(Array("3eb90ccd-ce4c-4174-ab40-f54956d164a7"),Array(1));
}
