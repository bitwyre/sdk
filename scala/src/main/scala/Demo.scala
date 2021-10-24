import com.bitwyre.scala_sdk.PublicAPI

object Demo extends App {
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
}
