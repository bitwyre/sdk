import com.bitwyre.kotlin_sdk.PublicAPI

fun main() {
    val app = PublicAPI()
    app.getServerTime()
    app.getAssetPairs("crypto","spot", "ID")
    app.getTicker("btc_idr_spot")
    app.getTrades(2, "btc_usdt_spot")
    app.getDepth("btc_usdt_spot", 2)
    app.getAssets()
    app.getMarkets()
    app.getProducts()
    app.getAnnouncements()
}
