import com.bitwyre.kotlin_sdk.PrivateAPI
import com.bitwyre.kotlin_sdk.PublicAPI

fun main() {
    val app = PublicAPI()
    //app.getServerTime()
    app.getAssetPairs("crypto","spot", "ID")
    //app.getTicker("btc_idr_spot")
    //app.getTrades(2, "btc_usdt_spot")
    //app.getDepth("btc_usdt_spot", 2)
    //app.getAssets()
    //app.getMarkets()
    //app.getProducts()
    //app.getAnnouncements()

    val secretkey = System.getenv("SECRET_KEY")
    val apikey = System.getenv("API_KEY")
    val p = PrivateAPI(secretkey, apikey)
    //p.get_account_balance()
    //p.get_account_statement()
    //p.get_transaction_histories()
    //p.get_open_orders("btc_usdt_spot", 0, 0)
    //p.get_closed_orders("btc_usdt_spot", 0, 0)
    //p.get_trade_history("btc_usdt_spot", 2, 0, 0)
    //p.opening_new_order("btc_usdt_spot", 1, "30000", 2, "0.0125")
    //p.opening_new_order("btc_usdt_spot", 1, "35000", 2, "0.001")
    p.get_order_info("bd9edbda-69eb-4874-8f3f-d004e4fac9bd")
    //p.get_order_info("0d4b33e9-6b41-49eb-b8c0-21d0112f9724")
    //p.cancelling_open_order_per_instrument("btc_usdt_spot")
    //p.cancelling_open_order(arrayOf("e7ee03fe-f5bc-47dc-a1a1-5736e5147ca7","c98090d5-3ec0-4e9a-a2e0-2fb904d7580a"), arrayOf(1,1))
}
